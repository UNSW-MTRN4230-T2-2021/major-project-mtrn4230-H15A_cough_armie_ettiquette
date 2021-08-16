#ifndef IMPROC_H
#define IMPROC_H

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <sensor_msgs/image_encodings.h>

#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <math.h>
#include <vector>

#include "project/Point.h"
#include "project/ImageRequest.h"
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
    Piece(const cv::Point2f &centre, const char &letter):
        Piece{centre.x, centre.y, letter} {}

    bool inGrid(const float &min, const float &max) { return (mX < max && mX > min && 
                                                                mY < max && mY > min); }
    bool onLine(std::array<float, 4> lines, const int &distance) {
        for (auto &line : lines) {
            if (((mX > line - distance) && (mX < line + distance) &&
                 (mY > lines[0] - distance) && (mY < lines[3] + distance)) ||
                ((mY > line - distance) && (mY < line + distance) &&
                 (mX > lines[0] - distance) && (mX < lines[3] + distance))) return true;
        }

        return false;
    }

    float getX() { return mX; }
    float getY() { return mY; }
    char getLetter() { return mLetter; }
};

class ImageProcessor {
public:
    enum Request {
        SETUP=0,
        PROCESS=1
    };

private:
    image_transport::ImageTransport mIt;
    image_transport::Subscriber mImageSub;
    ros::ServiceServer mGameRequest;
    sensor_msgs::ImageConstPtr mImage;
    cv::Mat mH;

    // Callback Functions
    bool imageRequestCallBack(project::ImageRequest::Request &req,
                              project::ImageRequest::Response &res);
    void processImageCallBack(const sensor_msgs::Image::ConstPtr &msg);

    cv::Point2f findContourCentre(const std::vector<cv::Point> &contour);
    void sortCorners(std::array<cv::Point2f, 4> &corners);

    bool handleSetUp(cv::Mat &image);
    void findBinaryPieces(std::vector<Piece> &points, cv::Mat &threshold, const char &letter);
    void findRedPieces(std::vector<Piece> &points, cv::Mat &image);
    void findBluePieces(std::vector<Piece> &points, cv::Mat &image);
    project::BoardInfo processImage(cv::Mat &image);
    project::BoardInfo processPieces(std::vector<Piece> &points);

public:
    ImageProcessor(ros::NodeHandle &n);
};

#endif