#ifndef CONTROL_H
#define CONTROL_H

#include <ros/ros.h>
#include <stdio.h>
#include <cmath>

#include "project/BoardInfo.h"
#include "project/ControllerMessage.h"
#include "project/PiecePosition.h"
#include "project/ImageRequest.h"
#include "ImageProcessor.hpp"
#include "project/RobotMoveService.h"
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

    /* This has to be public for each class */
    ros::NodeHandle n; 

private:
    project::ControllerMessage controllerStatus;

    BoardState mState;
    std::array<GameController::Player, TOTAL_STAT> WinnerArray;

    ros::ServiceClient mImageSub;
    ros::ServiceClient robotClient;
    ros::Publisher controllerPublisher;

    int SetCount;
    int TimeLimit;
    bool GameActive;
    bool SetStarted;
    Player CurrentPlayer;
    DifficultyLevel SelectedDifficulty;
    
public:
    void showBoardState() { mState.showBoardState(); }
    void setDifficultyLevel(DifficultyLevel d) { SelectedDifficulty = d; }
    void setCurrentPlayer(Player p) { CurrentPlayer = p; }
    void activateGame() { GameActive = true; }
    void deactiveGame() { GameActive = false; }
    Player getCurrentPlayer() { return CurrentPlayer; }
    void addPieceTest(int row, int col) { mState.addPiece(col, row, 'o'); }

    GameController();

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
