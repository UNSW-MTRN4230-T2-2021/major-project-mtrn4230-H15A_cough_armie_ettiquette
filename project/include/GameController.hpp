#ifndef CONTROL_H
#define CONTROL_H

#include <ros/ros.h>
#include <cmath>

#include "project/BoardInfo.h"
#include "project/ControllerMessage.h"
#include "project/PiecePosition.h"
#include "BoardState.hpp"

class GameController {
public: 
    enum Player {
            OP = 1, // indicates the opponent
            AI = -1,// indicates the computer
            NA = 0, // indicates an undefined
            DR = 2  // indicates one set draw
        };

    enum DifficultyLevel {
            Easy = -1,
            Hard = 1,
            Null = 0,
    };

    static const int TOTAL_STAT = 3;
    ros::NodeHandle n; /* This has to be public for each class */

private:
    BoardState mState;
    ros::Subscriber mImageSub;
    std::array<GameController::Player, TOTAL_STAT> WinnerArray;
    project::ControllerMessage controllerStatus;
    ros::Publisher controllerPublisher;

    int SetCount;
    Player CurrentPlayer;
    DifficultyLevel SelectedDifficulty;
    int TimeLimit;
    bool GameActive;
    bool SetStarted;
    
public:
    void showBoardState() { mState.showBoardState(); }

    GameController();

    void imageCallBack(const project::BoardInfo::ConstPtr &msg);

    void saveBoardState(BoardState &state);

    void determineCurrentPlayer();

    void indicateSetWinner();

    void determineGameWinner();

    void decideMove(); // RETURN TYPE DEPENDS ON GAZEBO CONTROLLER

    bool validateMove(const BoardState currentInput); // INCLUDES CHECKING FOR TIME AND 

    void throwViolation(); // RETURN TYPE DEPENDS ON USER INTERFACE

    void endGame(); // announce winner and clear board and ask if user wants to play again
};

#endif
