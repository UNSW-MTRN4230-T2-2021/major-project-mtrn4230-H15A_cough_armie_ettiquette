#include "GameController.hpp"
#include "project/PiecePosition.h"
#include "project/ControllerMessage.h"

GameController::GameController(ros::NodeHandle &n):
    mImageSub{n.subscribe("processed_image", 100, &GameController::imageCallBack, this)},
    controllerPublisher{n.advertise<project::ControllerMessage>("controller_message", 100)},
    SetCount{0},
    CurrentPlayer{0},
    DifficultyLevel{-1},
    TimeLimit{120}
{
}

void GameController::imageCallBack(const project::BoardInfo::ConstPtr &msg) {

    BoardState newBoard(msg->board);
    newBoard.showBoardState();
}

void GameController::saveBoardState(BoardState &state) {

    mState.setBoardState(state);
}

void determineCurrentPlayer(GameController::Player PreviousPlayer) {
    // TODO: Implement Me!
}

void indicateSetWinner() {
    // TODO: Implement Me!
}

void determineGameWinner() {
    // TODO: Implement Me!
}

void decideMove() { // RETURN TYPE DEPENDS ON GAZEBO CONTROLLER

}

bool validateMove(const BoardState currentInput); // INCLUDES CHECKING FOR TIME AND 

void throwViolation(); // RETURN TYPE DEPENDS ON USER INTERFACE

void endGame(); // announce winner and clear board and ask if user wants to play again


int main(int argc, char **argv) {

    ros::init(argc, argv, "game_controller");
    ros::NodeHandle n;

    // Random code for testing
    GameController c(n);

    ros::spin();
}
