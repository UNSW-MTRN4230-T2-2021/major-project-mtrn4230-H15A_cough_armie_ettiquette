#ifndef IMPROC_H
#define IMPROC_H

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <math.h>

#include "project/Point.h"
#include "project/PointArray.h"
#include "project/ImageService.h"

#include "BoardState.hpp"

class ImageProcessor {
private:
    ros::ServiceServer mService;
    // Camera c;
    bool serviceHandler(project::ImageService::Request &req,
                        project::ImageService::Response &res);

public:
    ImageProcessor(ros::NodeHandle &n);
};

#endif