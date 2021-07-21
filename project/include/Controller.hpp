#ifndef CONTROL_H
#define CONTROL_H

#include <ros/ros.h>

#include "project/ImageService.h"
#include "BoardState.hpp"

class Controller {
private:
    BoardState mState;
    ros::ServiceClient mImageClient;
    
public:
    Controller(ros::NodeHandle &n);

    void showBoardState() { mState.showBoardState(); }

    // TODO: Private this function
    BoardState getNewBoardState();

    void saveBoardState(BoardState &state);
};

#endif