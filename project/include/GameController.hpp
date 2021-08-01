#ifndef CONTROL_H
#define CONTROL_H

#include <ros/ros.h>

#include "project/BoardInfo.h"
#include "BoardState.hpp"

class GameController {
public: 
    enum Player {
            OP = 1, // indicates the opponent
            AI = -1,// indicates the computer
            NA = 0  // indicates an undefined
        };

    enum DifficultyLevel {
            Easy = 0,
            Hard = 1,
            Null = -1,
    };

    static const int TOTAL_STAT = 3;

private:
    BoardState mState;
    ros::Subscriber mImageSub;
    std::array<int, TOTAL_STAT> WinnerArray;
    int SetCount;
    int CurrentPlayer;
    int DifficultyLevel;
    int TimeLimit;
    
public:
    GameController(ros::NodeHandle &n);

    void showBoardState() { mState.showBoardState(); }

    void imageCallBack(const project::BoardInfo::ConstPtr &msg);

    void saveBoardState(BoardState &state);

    void determineCurrentPlayer(Player PreviousPlayer);

    void indicateSetWinner();

    void determineGameWinner();

    void decideMove(); // RETURN TYPE DEPENDS ON GAZEBO CONTROLLER

    bool validateMove(const BoardState currentInput); // INCLUDES CHECKING FOR TIME AND 

    void throwViolation(); // RETURN TYPE DEPENDS ON USER INTERFACE

    void endGame(); // announce winner and clear board and ask if user wants to play again
};

#endif
