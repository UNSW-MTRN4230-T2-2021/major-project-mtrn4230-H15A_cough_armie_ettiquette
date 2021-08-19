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

    assert(client.call(srv));
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
    project::UserMoveService srv;
    srv.request.service = GazeboController::Service::POWER_ON;
    srv.request.player = GazeboController::Player::X;

    ros::ServiceClient gclient {n.serviceClient<project::UserMoveService>("userMoveService")};

    project::UserMoveService gsrv;
    gsrv.request.service = GazeboController::Service::CLEAR_BOARD;

    assert(gclient.call(gsrv));

    gsrv.request.service = GazeboController::Service::SPAWN_TEST;
    gsrv.request.player = GazeboController::Player::X;

    std::array<std::pair<float, float>, 5> extremes {
        std::pair<float, float>(30, 30), std::pair<float, float>(180, 30),
        std::pair<float, float>(570, 30), std::pair<float, float>(30, 570),
        std::pair<float, float>(570, 570)
    };

    std::array<std::pair<float, float>, 4> oPieces {
        std::pair<float, float>(300, 30), std::pair<float, float>(570, 300),
        std::pair<float, float>(300, 570), std::pair<float, float>(30, 300),
    };

    project::Point p;

    for (auto &point : extremes) {
        p.x = point.first;
        p.y = point.second;
        gsrv.request.goal = p;
        assert(gclient.call(gsrv));
    }

    gsrv.request.player = GazeboController::Player::O;

    for (auto &point : oPieces) {
        p.x = point.first;
        p.y = point.second;
        gsrv.request.goal = p;
        assert(gclient.call(gsrv));
    }

    std::array<std::pair<float, float>, 5> goals {
        std::pair<float, float>(0, 0), std::pair<float, float>(0, 1),
        std::pair<float, float>(0, 2), std::pair<float, float>(1, 0),
        std::pair<float, float>(1, 1)
    };

    std::array<std::pair<float, float>, 4> oGoals {
        std::pair<float, float>(1, 2), std::pair<float, float>(2, 0),
        std::pair<float, float>(2, 1), std::pair<float, float>(2, 2),
    };

    ros::ServiceClient rclient {n.serviceClient<project::RobotMoveService>("robotMoveService")};
    project::RobotMoveService rsrv;
    project::Point p1;

    for (int i = 0; i < extremes.size(); i++) {
        p.x = extremes[i].first;
        p.y = extremes[i].second;
        rsrv.request.start = p;
        p1.x = goals[i].first;
        p1.y = goals[i].second;
        rsrv.request.goal = p1;
        assert(rclient.call(rsrv));
    }

    for (int i = 0; i < oPieces.size(); i++) {
        p.x = oPieces[i].first;
        p.y = oPieces[i].second;
        rsrv.request.start = p;
        p1.x = oGoals[i].first;
        p1.y = oGoals[i].second;
        rsrv.request.goal = p1;
        assert(rclient.call(rsrv));
    }
   

    // // Call Image Processing Service
    // ros::ServiceClient client {n.serviceClient<project::ImageRequest>("imageRequest")};
    // project::ImageRequest srv;
    // srv.request.service = ImageProcessor::Request::SETUP;

    // assert(client.call(srv));

    // // Wait a bit to let the Image be properly stored (likely not needed in program)
    // ros::Duration(1.0).sleep();

    // // Call Image processor to get pieces
    // srv.request.service = ImageProcessor::Request::PROCESS;
    // assert(client.call(srv));
    // if (client.call(srv)) {
    //     std::cout << "PROCESS DONE" << std::endl;
    //     // Get Boardstate
    //     project::BoardInfo info = srv.response.info;
    //     BoardState board{info.board};
    //     board.showBoardState();
    //     // Print Available pieces
    //     std::cout << "Available pieces:" << std::endl;
    //     for (auto &point : info.pieces) {
    //         std::cout << "(" << point.x << ", " << point.y << ", " << point.letter << ")" << std::endl;
    //     }

    //     auto iter{info.pieces.begin()};

    //     for (int i = 0; (i < 3) && (iter != info.pieces.end()); i++) {
    //         for (int j = 0; (j < 3) && (iter != info.pieces.end()); j++, iter++) {
    //             project::Point start = *iter;
    //             project::Point end;
    //             end.x = i; end.y = j;
    //             project::RobotMoveService robotSrv;
    //             robotSrv.request.start = start;
    //             robotSrv.request.goal = end;

    //             ros::ServiceClient robClient{n.serviceClient<project::RobotMoveService>("robotMoveService")};
    //             robClient.call(robotSrv);
    //         }
    //     }
    //     // Call RobotMoveService, which picks up a piece and puts it in the top left square
    // }

}

int main(int argc, char **argv) {

    ros::init(argc, argv, "image_process_test");
    ros::NodeHandle n;
    // testPowerOn(n);
    // testUserMove(n);
    testRobotMove(n);

    return 0;
}