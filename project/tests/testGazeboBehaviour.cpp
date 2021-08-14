#include "ros/ros.h"

#include "std_srvs/Empty.h"

#include "project/ImageRequest.h"
#include "project/BoardInfo.h"
#include "project/UserMoveService.h"
#include "project/RobotMoveService.h"
#include "project/Point.h"

#include "BoardState.hpp"
#include "ImageProcessor.hpp"
#include "GazeboController.hpp"

void testPowerOn(ros::NodeHandle &n) {
    ros::ServiceClient client {n.serviceClient<project::UserMoveService>("userMoveService")};

    project::UserMoveService srv;
    srv.request.service = GazeboController::Service::POWER_ON;
    srv.request.player = GazeboController::Player::O;

    if (client.call(srv)) {
        std::cout << "SETUP DONE" << std::endl;
    } else {
        ROS_ERROR("GAZEBO ERROR: Couldn't power on");
    }
}

void testUserMove(ros::NodeHandle &n) {
    ros::ServiceClient client{n.serviceClient<project::UserMoveService>("userMoveService")};

    project::UserMoveService srv;
    project::Point p;
    srv.request.service = GazeboController::Service::SPAWN_MOVE; 
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            p.x = x;
            p.y = y;
            srv.request.goal=p;
            client.call(srv);
        }
    }

    srv.request.service = GazeboController::Service::CLEAR_BOARD;
    client.call(srv);
}

void testRobotMove(ros::NodeHandle &n) {
    // Power on Robot
    testPowerOn(n);

    // Call Image Processing Service
    ros::ServiceClient client {n.serviceClient<project::ImageRequest>("imageRequest")};
    project::ImageRequest srv;
    srv.request.service = ImageProcessor::Request::SETUP;

    if (client.call(srv)) {
        std::cout << "SETUP DONE" << std::endl;
    }

    // Wait a bit to let the Image be properly stored (likely not needed in program)
    ros::Duration(1.0).sleep();

    // Call Image processor to get pieces
    srv.request.service = ImageProcessor::Request::PROCESS;
    if (client.call(srv)) {
        std::cout << "PROCESS DONE" << std::endl;
        // Get Boardstate
        project::BoardInfo info = srv.response.info;
        BoardState board{info.board};
        board.showBoardState();
        // Print Available pieces
        std::cout << "Available pieces:" << std::endl;
        for (auto &point : info.pieces) {
            std::cout << "(" << point.x << ", " << point.y << ", " << point.letter << ")" << std::endl;
        }

        auto iter{info.pieces.begin()};

        for (int i = 0; (i < 3) && (iter != info.pieces.end()); i++) {
            for (int j = 0; (j < 3) && (iter != info.pieces.end()); j++, iter++) {
                project::Point start = *iter;
                project::Point end;
                end.x = i; end.y = j;
                project::RobotMoveService robotSrv;
                robotSrv.request.start = start;
                robotSrv.request.goal = end;

                ros::ServiceClient robClient{n.serviceClient<project::RobotMoveService>("robotMoveService")};
                robClient.call(robotSrv);
            }
        }
        // Call RobotMoveService, which picks up a piece and puts it in the top left square
    }

}

int main(int argc, char **argv) {

    ros::init(argc, argv, "image_process_test");
    ros::NodeHandle n;
    // testPowerOn(n);
    // testUserMove(n);
    testRobotMove(n);

    return 0;
}