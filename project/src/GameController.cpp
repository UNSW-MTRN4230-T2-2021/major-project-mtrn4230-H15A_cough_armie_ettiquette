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
    
    for (int i = 0; i < TOTAL_STAT; i++) {
        controllerStatus.setWinners.push_back(NA);
    }
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

void GameController::indicateSetWinner() {
    /* TRIADS: ROWs, COLs, when row == col */
    // TODO: double check the letters used and who the players are, then update controllerStatus.setWinners[SetCount] = OP or AI
    
    BoardState::Board board = mState.getBoard();
    
    // Check for all rows
    for (int row = 0; row < BoardState::BOARD_SIZE; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2] && board[row][0] != ' ') {
            controllerStatus.winStatus = true;
            controllerStatus.setWinners[SetCount] = board[row][0];
        }
    }
    
    // Check for all columns
    for (int col = 0; col < BoardState::BOARD_SIZE; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col] && board[0][col] != ' ') {
            controllerStatus.winStatus = true;
            controllerStatus.setWinners[SetCount] = board[0][col];
        }
    }
    
    // Check for diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        controllerStatus.winStatus = true;
        controllerStatus.setWinners[SetCount] = board[0][0];
    }
    
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ') {
        controllerStatus.winStatus = true;
        controllerStatus.setWinners[SetCount] = board[1][1];
    }
    
    GameController::controllerPublisher.publish(GameController::controllerStatus);
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
        firstGame.indicateSetWinner();
        ros::Duration(3).sleep();
    }
    
    std::cout << "Game Finished!" << std::endl;
    std::cout << "Thanks for playing!" << std::endl;
    ros::spin();
}
