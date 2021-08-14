#include "ros/ros.h"
#include "project/ImageRequest.h"
#include "project/BoardInfo.h"
#include "project/Point.h"

#include "ImageProcessor.hpp"
#include "BoardState.hpp"


int main(int argc, char **argv) {

    ros::init(argc, argv, "image_process_test");
    ros::NodeHandle n;
    ros::ServiceClient client {n.serviceClient<project::ImageRequest>("imageRequest")};

    project::ImageRequest srv;
    srv.request.service = ImageProcessor::Request::SETUP;

    if (client.call(srv)) {
        std::cout << "SETUP DONE" << std::endl;
    }

    srv.request.service = ImageProcessor::Request::PROCESS;

    if (client.call(srv)) {
        std::cout << "PROCESS DONE" << std::endl;
        project::BoardInfo info = srv.response.info;
        BoardState board{info.board};
        board.showBoardState();
        std::cout << "Available pieces:" << std::endl;
        for (auto &point : info.pieces) {
            std::cout << "(" << point.x << ", " << point.y << ", " << point.letter << ")" << std::endl;
        }
    }
    // ros::spinOnce();

    return 0;
}