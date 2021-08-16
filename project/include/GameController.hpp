#ifndef CONTROL_H
#define CONTROL_H

#include <ros/ros.h>
#include <stdio.h>
#include <cmath>

#include "std_msgs/Int32.h"
#include "project/BoardInfo.h"
#include "project/ControllerMessage.h"
#include "project/PiecePosition.h"
#include "project/ImageRequest.h"
#include "ImageProcessor.hpp"
#include "project/RobotMoveService.h"
#include "project/UserMoveService.h"
#include "project/Point.h"
#include "BoardState.hpp"
#include "GazeboController.hpp"

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
    
    enum StatusUI {
        NO_UI_INFO = 0,
        POS_1 = 1,
        POS_2 = 2,
        POS_3 = 3,
        POS_4 = 4,
        POS_5 = 5,
        POS_6 = 6,
        POS_7 = 7,
        POS_8 = 8,
        POS_9 = 9,
        START_EASY = 10,
        START_HARD = 11,
        TIMER_EXPIRED = 12,
        PAUSE_GAME = 13,
        UNPAUSE_GAME = 14,
        POWER_OFF = 15,
        VIOLATION_RESOLVED = 16
    };
    
    enum StatusController {
        NO_CONTROLLER_INFO = 0,
        P_1 = 1,
        P_2 = 2,
        P_3 = 3, 
        P_4 = 4, 
        P_5 = 5,
        P_6 = 6,
        P_7 = 7,
        P_8 = 8,
        P_9 = 9,
        ROBOT_READY = 10,
        GAME_STARTED = 11,
        PLAYER_TURN = 12,
        ROBOT_TURN = 13,
        ROBOT_WIN_SET = 14,
        PLAYER_WIN_SET = 15,
        DRAW_SET = 16,
        ROBOT_WIN_GAME = 17,
        PLAYER_WIN_GAME = 18,
        DRAW_GAME = 19
    };

    static const int TOTAL_STAT = 3;
    ros::NodeHandle n; 

private:
    project::ControllerMessage controllerStatus;

    BoardState mState;
    std::array<GameController::Player, TOTAL_STAT> WinnerArray;

    ros::ServiceClient CameraClient;
    ros::ServiceClient robotClient;
    ros::ServiceClient userClient;
    ros::Subscriber uiSubscriber;
    ros::Publisher controllerPublisher;

    int SetCount;
    bool GameActive;
    bool SetStarted;
    int CurrentStatusUI;
    int CurrentMove; // number from 1-9, if this is -1 then no move was found

    Player CurrentPlayer;
    DifficultyLevel SelectedDifficulty;
    
public:
    void startGame();
    void publishToUI(StatusController status);
    void clearBoard();

    void showBoardState() { mState.showBoardState(); }
    void setDifficultyLevel(DifficultyLevel d) { SelectedDifficulty = d; }
    void setCurrentPlayer(Player p) { CurrentPlayer = p; }
    void activateGame() { GameActive = true; }
    void deactiveGame() { GameActive = false; }
    Player getCurrentPlayer() { return CurrentPlayer; }
    void addPieceTest(int row, int col) { mState.addPiece(col, row, 'o'); }
    void setCurrentUI(int val) { CurrentStatusUI = val; }
    int getCurrentStatusUI() { return CurrentStatusUI; }
    void makeMove(const int &row, const int &col, project::Point obj);

    void uiCallback(const std_msgs::Int32::ConstPtr& status);
    GameController();
    void saveBoardState(BoardState &state) { mState.setBoardState(state); };
    void getBoardStateFromCamera();
    void determineCurrentPlayer();
    void robotPlacePiece(const int &row, const int &col, project::Point obj);
    void userPlacePiece(int row, int col);
    void startRobot();
    bool indicateSetWinner();
    bool determineGameWinner();
    void decideMove(); 
    bool validateMove(const BoardState &currentInput);  
    void throwViolation();
    void endGame(); // announce winner and clear board and ask if user wants to play again
};

#endif
