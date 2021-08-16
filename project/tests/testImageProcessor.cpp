#include "ros/ros.h"
#include "project/ImageRequest.h"
#include "project/BoardInfo.h"
#include "project/UserMoveService.h"
#include "project/RobotMoveService.h"
#include "project/Point.h"

#include "ImageProcessor.hpp"
#include "GazeboController.hpp"
#include "BoardState.hpp"

void testNoBoard(ros::NodeHandle &n) {
    ros::ServiceClient client {n.serviceClient<project::ImageRequest>("imageRequest")};

    project::ImageRequest srv;
    srv.request.service = ImageProcessor::Request::SETUP;

    assert(!client.call(srv));
}

void testOXVision(ros::NodeHandle &n, project::UserMoveService &srv) {
    ros::ServiceClient client {n.serviceClient<project::UserMoveService>("userMoveService")};

    srv.request.service = GazeboController::Service::POWER_ON;

    assert(client.call(srv));

    ros::ServiceClient iclient {n.serviceClient<project::ImageRequest>("imageRequest")};
    project::ImageRequest isrv;
    isrv.request.service = ImageProcessor::Request::SETUP;

    assert(iclient.call(isrv));

    project::Point p;
    srv.request.service = GazeboController::Service::SPAWN_MOVE; 
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            p.x = x;
            p.y = y;
            srv.request.goal=p;
            assert(client.call(srv));
        }
    }

    ros::Duration(0.5).sleep();

    isrv.request.service = ImageProcessor::Request::PROCESS;
    assert(iclient.call(isrv));
    project::BoardInfo info = isrv.response.info;
    BoardState board{info.board};
    board.showBoardState();
    std::cout << "Available pieces:" << std::endl;
    for (auto &point : info.pieces) {
        std::cout << "(" << point.x << ", " << point.y << ", " << point.letter << ")" << std::endl;
    }

    srv.request.service = GazeboController::Service::CLEAR_BOARD;
    assert(client.call(srv));
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "image_process_test");
    ros::NodeHandle n;

    testNoBoard(n);

    project::UserMoveService srv;
    srv.request.player = GazeboController::Player::O;
    testOXVision(n, srv);

    srv.request.player = GazeboController::Player::X;
    testOXVision(n, srv);

    return 0;
}