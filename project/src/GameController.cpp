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
    mImageSub = n.serviceClient<project::ImageRequest>("imageRequest");
    robotClient = n.serviceClient<project::RobotMoveService>("robotMoveService");
    
    for (int i = 0; i < TOTAL_STAT; i++) {
        controllerStatus.setWinners.push_back(NA);
    }
}

void GameController::saveBoardState(BoardState &state) {
    mState.setBoardState(state);
}

void GameController::determineCurrentPlayer() {
    if (GameActive) {
        if (controllerStatus.playerId == AI) {
            controllerStatus.playerId = OP;
            CurrentPlayer = OP;
        } 
        else if (controllerStatus.playerId == OP) {
            controllerStatus.playerId = AI;
            CurrentPlayer = AI;
        }
        else {
            if (SelectedDifficulty == GameController::Hard) {
                controllerStatus.playerId = AI;
                CurrentPlayer = AI;
            }
            else if (SelectedDifficulty == GameController::Easy) {
                controllerStatus.playerId = OP;
                CurrentPlayer = OP;
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
    BoardState::Board board = mState.getBoard();
    
    project::ImageRequest srv;
    srv.request.service = ImageProcessor::Request::SETUP;
    if (GameController::mImageSub.call(srv)) {
        std::cout << "SETUP DONE" << std::endl;
    }

    srv.request.service = ImageProcessor::Request::PROCESS;
    if (GameController::mImageSub.call(srv)) {
        std::cout << "PROCESS DONE" << std::endl;
        project::BoardInfo info = srv.response.info;
        auto newBoard = BoardState(info.board);
        newBoard.showBoardState();
    }


    bool winnerFound = false;
    
    // Check for all rows
    for (int row = 0; row < BoardState::BOARD_SIZE; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2] && board[row][0] != ' ') {
            controllerStatus.setWinners[SetCount] = board[row][0];
            winnerFound = true;
        }
    }
    
    // Check for all columns
    for (int col = 0; col < BoardState::BOARD_SIZE; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col] && board[0][col] != ' ') {
            controllerStatus.setWinners[SetCount] = board[0][col];
            winnerFound = true;
        }
    }
    
    // Check for diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        controllerStatus.setWinners[SetCount] = board[0][0];
        winnerFound = true;
    }
    
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ') {
        controllerStatus.setWinners[SetCount] = board[1][1];
        winnerFound = true;
    }
    
    // Check for draw
    if (!winnerFound) {
        bool isFull = true;
        for (int row = 0; row < BoardState::BOARD_SIZE; row++) {
            for (int col = 0; col < BoardState::BOARD_SIZE; col++) { 
                if (board[row][col] == ' ') {
                    isFull = false;
                }
            }
        }
        
        if (isFull) {
            controllerStatus.setWinners[SetCount] = DR;
        }
    }
    
    GameController::controllerPublisher.publish(GameController::controllerStatus);
}

bool isOP(int p) { return (p == GameController::OP); }

bool isAI(int p) { return (p == GameController::AI); }

void GameController::determineGameWinner() {
    // TODO: Update so that it works as such: this only gets called when a winner of a set is found this increment setcount after
    if (SetCount < 2) {
        controllerStatus.gameWinner = NA;
    }
    
    int OPwincount = count_if(controllerStatus.setWinners.begin(), controllerStatus.setWinners.end(), isOP);
    int AIwincount = count_if(controllerStatus.setWinners.begin(), controllerStatus.setWinners.end(), isAI);
    
    if (std::abs(OPwincount - AIwincount) > 1) {
        if (OPwincount < AIwincount) {
            controllerStatus.gameWinner = AI;
        }
        else if (AIwincount < OPwincount) {
            controllerStatus.gameWinner = OP;
        }
    }
    
    if (SetCount == 2 && controllerStatus.gameWinner == NA) {
        controllerStatus.gameWinner = DR;
    }
}

void GameController::decideMove() { // TODO: SEND RESULT TO robotClient
    BoardState::Board b = mState.getBoard();
    if (SelectedDifficulty == GameController::Null) {
        // TODO: Throw violation --> difficulty was somehow unset or unselected
    }
    
    else if (SelectedDifficulty == GameController::Easy) {
        std::vector<int> avRows; std::vector <int> avCols; int nSpaces = 0;
        
        for(int row = 0; row < BoardState::BOARD_SIZE; row++) {
            for (int col = 0; col < BoardState::BOARD_SIZE; col++) {
                if (b[row][col] == ' ') {
                    avRows.push_back(row); 
                    avCols.push_back(col);
                    nSpaces++;
                }
            }
        }
        
        if (nSpaces == 0) {
            // TODO: Deal with a full board
            std::cout << "FULL BOARD" << std::endl;
        }
        else {
            int randomIndex = rand() % nSpaces;
            mState.addPiece(avCols.at(randomIndex), avRows.at(randomIndex), 'x');
            mState.showBoardState();
        }
    }
    
    else if (SelectedDifficulty == GameController::Hard) {
        if (mState.BoardEmpty()) {
            mState.addPiece(1, 1, 'x');
            mState.showBoardState();
            return;
        }   
        
        // Can you win now?
        struct BoardState::point p = mState.formTriad('x');
        if (p.row != -1 && p.col != -1) {
            mState.addPiece(p.col, p.row, 'x');
            mState.showBoardState();
            return;
        }
        
        // Can the opponent win next?
        p = mState.formTriad('o');
        if (p.row != -1 && p.col != -1) {
            mState.addPiece(p.col, p.row, 'x');
            mState.showBoardState();
            return;
        }
        
        // Prioritise centre first, then corners, then 
        if (b[1][1] == ' ') {
            mState.addPiece(1, 1, 'x');
            mState.showBoardState();
            return;
        } else if (b[0][0] == ' ') {
            mState.addPiece(0, 0, 'x');
            mState.showBoardState();
            return;
        } else if (b[2][2] == ' ') {
            mState.addPiece(2, 2, 'x');
            mState.showBoardState();
            return;
        } else if (b[2][0] == ' ') {
            mState.addPiece(0, 2, 'x');
            mState.showBoardState();
            return;
        } else if (b[0][2] == ' ') {
            mState.addPiece(2, 0, 'x');
            mState.showBoardState();
            return;
        }
        
        // otherwise pick a random one
        for (int row = 0; row < BoardState::BOARD_SIZE; row++) {
            for (int col = 0; col < BoardState::BOARD_SIZE; col++) {
                if (b[row][col] == ' ') {
                    mState.addPiece(col, row, 'x');
                }
            }
        }
    }
}

bool validateMove(const BoardState currentInput); // INCLUDES CHECKING FOR TIME AND 

void throwViolation(); // RETURN TYPE DEPENDS ON USER INTERFACE

void endGame(); // announce winner and clear board and ask if user wants to play again


int main(int argc, char **argv) {
    std::cout << "Controller Initiating...." << std::endl;
    ros::init(argc, argv, "game_controller");
    ros::AsyncSpinner spinner(2);
    spinner.start();
    
    std::cout << "GameController Readying...." << std::endl;
    GameController firstGame;
    
    std::cout << "Game Begin!" << std::endl;
    
    // Wait for user to select difficulty level
    char level = ' ';
    std::cout << "choose 'e' for easy, 'h' for hard, or 'r' to randomise: ";
    std::cin.get(level);
    std::cout << "LEVEL: " << level << std::endl;
    if (level == 'r') {
        if (std::rand() % 2 == 0) {
            firstGame.setDifficultyLevel(GameController::Easy);
            std::cout << "Playing an easy game...." << std::endl;
        }
        else {
            firstGame.setDifficultyLevel(GameController::Hard);
            std::cout << "Playing a hard game...." << std::endl;
        }
    }
    else if (level == 'h') {
        firstGame.setDifficultyLevel(GameController::Hard);
        std::cout << "Playing a hard game...." << std::endl;
    }
    else if (level == 'e') {
        firstGame.setDifficultyLevel(GameController::Easy);
        std::cout << "Playing an easy game...." << std::endl;
    }
    else {
        firstGame.setDifficultyLevel(GameController::Null);
        
        // TODO: Message To User --> Get Input Again --> Placeholder, this would not be a console request
    }
    
    firstGame.activateGame();

    while(ros::ok()) {
        // Determine whose turn
        firstGame.determineCurrentPlayer();
        
        // Get current players move
        if (firstGame.getCurrentPlayer() == GameController::NA) {
            // TODO: ERROR! --> Message to User / maybe just let user start(?)
        }
        else if (firstGame.getCurrentPlayer() == GameController::OP) {
            // TODO: Request User to make a move
            int row = 0; int col = 0;
            std::cout << "Enter row: ";
            std::cin >> row;
            
            std::cout << "Enter col: ";
            std::cin >> col;
            
            firstGame.addPieceTest(row, col);
            firstGame.showBoardState();
        }
        else if (firstGame.getCurrentPlayer() == GameController::AI) {
            firstGame.decideMove();
        }
        
        
        // Check for violations after every move
        
        
        
        // Check for set winner after every move


        // TODO: THIS IS TESTING SECTION, DELETE LATER
        firstGame.indicateSetWinner();
        firstGame.determineGameWinner();
        ros::Duration(3).sleep();
    }
    
    std::cout << "Game Finished!" << std::endl;

    std::cout << "Thanks for playing!" << std::endl;

    ros::waitForShutdown();
}
