#include "ros/ros.h"
#include "project/ImageRequest.h"


int main(int argc, char **argv) {

    ros::init(argc, argv, "image_process_test");
    ros::NodeHandle n;
    ros::ServiceClient client {n.serviceClient<project::ImageRequest>("imageRequest")};

    project::ImageRequest srv;
    // srv.req

    if (client.call(srv)) {
        std::cout << "DONE" << std::endl;
    }

    // ros::spinOnce();

    return 0;
}