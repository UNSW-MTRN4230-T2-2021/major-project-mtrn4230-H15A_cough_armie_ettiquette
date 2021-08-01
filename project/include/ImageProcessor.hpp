#ifndef IMPROC_H
#define IMPROC_H

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <math.h>

#include "project/Point.h"
#include "project/PointArray.h"
#include "project/BoardInfo.h"

#include "BoardState.hpp"


class Piece {
private:
    float mX;
    float mY;
    char mLetter;

public:
    Piece(const float &x, const float &y, const char &letter): 
        mX{x}, mY{y}, mLetter{letter} {}

    bool inGrid(const float &xMin, const float &xMax,
                const float &yMin, const float &yMax) { return (mX < xMax && mX > xMin && 
                                                                mY < yMax && mY > yMin); }

    float getX() { return mX; }
    float getY() { return mY; }
    char getLetter() { return mLetter; }
};

class ImageProcessor {
private:
    ros::Publisher mPub;
    // Camera c;
    // bool serviceHandler(project::ImageService::Request &req,
    //                     project::ImageService::Response &res);

public:
    ImageProcessor(ros::NodeHandle &n);

    // TODO: Make this private
    void imageRequestCallBack(/* TODO: Implement subscriber callbback here */ );
};

#endif