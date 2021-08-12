#include "ros/ros.h"
#include "project/UserMoveService.h"
#include "GazeboController.hpp"

#include "std_srvs/Empty.h"

#include "project/BoardInfo.h"
#include "BoardState.hpp"


int main(int argc, char **argv) {

    ros::init(argc, argv, "image_process_test");
    ros::NodeHandle n;
    ros::ServiceClient client {n.serviceClient<project::UserMoveService>("userMoveService")};

    project::UserMoveService srv;
    srv.request.service = GazeboController::Service::POWER_ON;
    srv.request.player = GazeboController::Player::O;

    if (client.call(srv)) {
        std::cout << "SETUP DONE" << std::endl;
    } else {
        ROS_ERROR("ERRORRR");
    }

    // ros::ServiceClient client{n.serviceClient<std_srvs::Empty>("hi")};
    // std_srvs::Empty srv;
    // client.call(srv);
    // ros::spin();

    return 0;
}