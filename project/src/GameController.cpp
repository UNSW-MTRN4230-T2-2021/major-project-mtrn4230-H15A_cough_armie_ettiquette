#include "GameController.hpp"

GameController::GameController():
    SetCount{0},
    CurrentPlayer{NA},
    SelectedDifficulty{Null},
    TimeLimit{120},
    GameActive{false},
    SetStarted{false}
{
    controllerPublisher = n.advertise<project::ControllerMessage>("controller_message", 100);
    mImageSub = n.subscribe("processed_image", 100, &GameController::imageCallBack, this);
}

void GameController::imageCallBack(const project::BoardInfo::ConstPtr &msg) {

    BoardState newBoard(msg->board);
    newBoard.showBoardState();
}

void GameController::saveBoardState(BoardState &state) {

    mState.setBoardState(state);
}

void GameController::determineCurrentPlayer() {
    if (SetStarted) {
        if (controllerStatus.playerId == AI) {
            controllerStatus.playerId = OP;
        } 
        else if (controllerStatus.playerId == OP) {
            controllerStatus.playerId = AI;
        }
        else {
            if (SelectedDifficulty == GameController::Hard) {
                controllerStatus.playerId = AI;;
            }
            else if (SelectedDifficulty == GameController::Easy) {
                controllerStatus.playerId = OP;
            }
            else {
                // TODO: Throw Exception --> Request for a difficulty level input
            }
        }
    }
    
    GameController::controllerPublisher.publish(GameController::controllerStatus);
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
    
    std::cout << "Controller Initiating...." << std::endl;
    ros::init(argc, argv, "game_controller");
    
    std::cout << "GameController Readying...." << std::endl;
    GameController firstGame;
    
    std::cout << "Game Begin!" << std::endl;
    
    while(ros::ok()) {
        firstGame.determineCurrentPlayer();
        ros::Duration(3).sleep();
    }
    
    std::cout << "Game Finished!" << std::endl;
    std::cout << "Thanks for playing!" << std::endl;
    ros::spin();
}
