#include "ros/ros.h"

#include "std_srvs/Empty.h"

#include "project/ImageRequest.h"
#include "project/BoardInfo.h"
#include "project/UserMoveService.h"
#include "project/RobotMoveService.h"
#include "project/TestViolation.h"
#include "project/Point.h"

#include "BoardState.hpp"
#include "ImageProcessor.hpp"
#include "GazeboController.hpp"

void powerOn(ros::NodeHandle &n) {
    ros::ServiceClient client {n.serviceClient<project::UserMoveService>("userMoveService")};

    project::UserMoveService srv;
    srv.request.service = GazeboController::Service::POWER_ON;
    srv.request.player = GazeboController::Player::O;

    assert(client.call(srv));
}

void testSpawnOnLine(ros::NodeHandle &n) {
    ros::ServiceClient client {n.serviceClient<project::UserMoveService>("userMoveService")};
    ros::ServiceClient iclient {n.serviceClient<project::ImageRequest>("imageRequest")};
    project::ImageRequest isrv;
    isrv.request.service = ImageProcessor::Request::SETUP;
    assert(iclient.call(isrv));

    std::array<std::pair<float, float>, 8> invalid {
        std::pair<float, float>{130.0, 200.0}, std::pair<float, float>{215.0, 360.0},
        std::pair<float, float>{375.0, 150.0}, std::pair<float, float>{500.0, 250.0},
        std::pair<float, float>{180.0, 110.0}, std::pair<float, float>{420.0, 235.0},
        std::pair<float, float>{300.0, 372.0}, std::pair<float, float>{175.0, 470.0}
    };

    project::UserMoveService srv;
    srv.request.service = GazeboController::Service::CLEAR_BOARD;
    assert(client.call(srv));

    srv.request.service = GazeboController::Service::SPAWN_TEST;
    srv.request.player = GazeboController::Player::O;
    project::Point p;

    isrv.request.service = ImageProcessor::Request::PROCESS;

    for (auto &pair : invalid) {
        srv.request.service = GazeboController::Service::SPAWN_TEST;
        p.x = pair.first;
        p.y = pair.second;
        srv.request.goal = p;
        assert(client.call(srv));
        assert(!iclient.call(isrv));
        srv.request.service = GazeboController::Service::CLEAR_BOARD;
        assert(client.call(srv));
    }
}

void testSpawnTwoPiecesSameSquare(ros::NodeHandle &n) {
    ros::ServiceClient client {n.serviceClient<project::UserMoveService>("userMoveService")};
    ros::ServiceClient iclient {n.serviceClient<project::ImageRequest>("imageRequest")};
    project::ImageRequest isrv;

    std::array<std::pair<float, float>, 2> invalid {
        std::pair<float, float>{155.0, 275.0}, std::pair<float, float>{205.0, 325.0}
    };

    project::UserMoveService srv;
    srv.request.service = GazeboController::Service::CLEAR_BOARD;
    assert(client.call(srv));

    srv.request.service = GazeboController::Service::SPAWN_TEST;
    srv.request.player = GazeboController::Player::O;
    project::Point p;

    isrv.request.service = ImageProcessor::Request::PROCESS;

    for (auto &pair : invalid) {
        p.x = pair.first;
        p.y = pair.second;
        srv.request.goal = p;
        assert(client.call(srv));
    }

    assert(!iclient.call(isrv));
    srv.request.service = GazeboController::Service::CLEAR_BOARD;
    assert(client.call(srv));
}

void testIncorrectNewPiece(ros::NodeHandle &n) {
    ros::ServiceClient client {n.serviceClient<project::TestViolation>("testViolation")};
    project::TestViolation srv;
    srv.request.curr = "xo  xx o ";
    srv.request.next = "xo  xxxo ";
    assert(!client.call(srv));

    // BoardState currBoard {{{{'x', 'o', ' '},
    //                       {' ', 'x', 'x'},
    //                       {' ', 'o', ' '}}}};

    // BoardState nextBoard {{{{'x', 'o', ' '},
    //                     {' ', 'x', 'x'},
    //                     {'x', 'o', ' '}}}};
}

void testMultiplePiecesPlaced(ros::NodeHandle &n) {
    ros::ServiceClient client {n.serviceClient<project::TestViolation>("testViolation")};
    project::TestViolation srv;
    srv.request.curr = "xo  xx o ";
    srv.request.next = "xo  xxooo";
    assert(!client.call(srv));
    // BoardState currBoard {{{{'x', 'o', ' '},
    //                       {' ', 'x', 'x'},
    //                       {' ', 'o', ' '}}}};

    // BoardState nextBoard {{{{'x', 'o', ' '},
    //                     {' ', 'x', 'x'},
    //                     {'o', 'o', 'o'}}}};
}

void testPlaceNoPiece(ros::NodeHandle &n) {
    ros::ServiceClient client {n.serviceClient<project::TestViolation>("testViolation")};
    project::TestViolation srv;
    srv.request.curr = "xo  xx o ";
    srv.request.next = "xo  xx o ";
    assert(!client.call(srv));
    // BoardState currBoard {{{{'x', 'o', ' '},
    //                       {' ', 'x', 'x'},
    //                       {' ', 'o', ' '}}}};

    // BoardState nextBoard {{{{'x', 'o', ' '},
    //                     {' ', 'x', 'x'},
    //                     {' ', 'o', ' '}}}};
}

void testRemovePiece(ros::NodeHandle &n) {
    ros::ServiceClient client {n.serviceClient<project::TestViolation>("testViolation")};
    project::TestViolation srv;
    srv.request.curr = "xo  xx o ";
    srv.request.next = "xo  x  o ";
    assert(!client.call(srv));

    srv.request.curr = "xo  xx o ";
    srv.request.next = "xo  xx   ";
    assert(!client.call(srv));
    // BoardState currBoard {{{{'x', 'o', ' '},
    //                       {' ', 'x', 'x'},
    //                       {' ', 'o', ' '}}}};

    // BoardState nextBoard {{{{'x', 'o', ' '},
    //                     {' ', 'x', 'x'},
    //                     {' ', 'o', ' '}}}};
}

void testMovePiece(ros::NodeHandle &n) {
    ros::ServiceClient client {n.serviceClient<project::TestViolation>("testViolation")};
    project::TestViolation srv;
    srv.request.curr = "xo  xx o ";
    srv.request.next = "xo  xx  o";
    assert(!client.call(srv));

    // BoardState currBoard {{{{'x', 'o', ' '},
    //                       {' ', 'x', 'x'},
    //                       {' ', 'o', ' '}}}};

    // BoardState nextBoard {{{{'x', 'o', ' '},
    //                     {' ', 'x', 'x'},
    //                     {' ', ' ', 'o'}}}};
}

void testReplacePiece(ros::NodeHandle &n) {
    ros::ServiceClient client {n.serviceClient<project::TestViolation>("testViolation")};
    project::TestViolation srv;
    srv.request.curr = "xo  xx o ";
    srv.request.next = "xo  xx x ";
    assert(!client.call(srv));

    srv.request.curr = "xo  xx o ";
    srv.request.next = "xo  xo o ";
    assert(!client.call(srv));

    // BoardState currBoard {{{{'x', 'o', ' '},
    //                       {' ', 'x', 'x'},
    //                       {' ', 'o', ' '}}}};

    // BoardState nextBoard {{{{'x', 'o', ' '},
    //                     {' ', 'x', 'x'},
    //                     {' ', 'x', ' '}}}};
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "violation_test");
    ros::NodeHandle n;
    // powerOn(n); 
    // testSpawnOnLine(n);
    // testSpawnTwoPiecesSameSquare(n); 
    
    testIncorrectNewPiece(n);
    testMultiplePiecesPlaced(n);
    testPlaceNoPiece(n);
    testRemovePiece(n);
    testMovePiece(n);
    testReplacePiece(n);

    return 0;
}