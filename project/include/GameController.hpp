#ifndef CONTROL_H
#define CONTROL_H

#include <ros/ros.h>

#include "project/BoardInfo.h"
#include "BoardState.hpp"

class GameController {
private:
    BoardState mState;
    ros::Subscriber mImageSub;
    
public:
    GameController(ros::NodeHandle &n);

    void showBoardState() { mState.showBoardState(); }

    void imageCallBack(const project::BoardInfo::ConstPtr &msg);
    // BoardState getNewBoardState();

    void saveBoardState(BoardState &state);
};

#endif