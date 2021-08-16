#include "GameController.hpp"

GameController::GameController():
    SetCount{0},
    CurrentPlayer{NA},
    SelectedDifficulty{Null},
    GameActive{false},
    SetStarted{false}
{
    controllerPublisher = n.advertise<std_msgs::Int32>("controller_message", 100);
    CameraClient = n.serviceClient<project::ImageRequest>("imageRequest");
    robotClient = n.serviceClient<project::RobotMoveService>("robotMoveService");
    userClient = n.serviceClient<project::UserMoveService>("userMoveService");
    uiSubscriber = n.subscribe("msgsToController", 1000, &GameController::uiCallback, this);
    
    for (int i = 0; i < TOTAL_STAT; i++) {
        controllerStatus.setWinners.push_back(NA);
    }
}

void GameController::uiCallback(const std_msgs::Int32::ConstPtr& status) {
    CurrentStatusUI = status->data;
    std::cout << CurrentStatusUI << std::endl;
    
    if (CurrentStatusUI == NO_UI_INFO) {
        // DO NOTHING!
        
    } else if (CurrentStatusUI >= POS_1 && CurrentStatusUI <= POS_9 && GameActive) {
        // RECORD OPPONENT MOVE
        CurrentMove = CurrentStatusUI - 1; // change input to 0 - 8
        int row = CurrentMove / BoardState::BOARD_SIZE;
        int col = CurrentMove % BoardState::BOARD_SIZE;
        addPieceTest(row, col);
        showBoardState();
        userPlacePiece(row, col);
        
        getBoardStateFromCamera();
        
        // CHECK FOR WINS
        bool setWon = indicateSetWinner();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        // CHECK IF ANYONE HAS WON THE ENTIRE GAME
        if (setWon) {
            SetCount++;
            clearBoard();
            if (determineGameWinner()) {
                endGame();
            };
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        
        // MAKE A MOVE
        determineCurrentPlayer();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (CurrentPlayer == AI) {
            decideMove();
        }
        
        // CHECK IF ROBOT HAS WON THEN END THE SET AND SEND STATUS TO UI
        setWon = indicateSetWinner();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        // CHECK IF ANYONE HAS WON THE ENTIRE GAME
        if (setWon) {
            SetCount++;
            clearBoard();
            if (determineGameWinner()) {
                endGame();
            };
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        
        // SET CURRENTPLAYER
        determineCurrentPlayer();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        CurrentMove = 0;
        
    } else if (CurrentStatusUI >= START_EASY && CurrentStatusUI <= START_HARD && GameActive) {
        startGame();
        CurrentStatusUI = 0;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        determineCurrentPlayer();
        if (CurrentPlayer == AI) {
            decideMove();
            determineCurrentPlayer();
        }
        
    } else if (CurrentStatusUI == PAUSE_GAME) {
        GameActive = false;
    } else if (CurrentStatusUI == UNPAUSE_GAME) {
        GameActive = true;
    } else if (CurrentStatusUI == POWER_OFF) { 
        
    } else if (CurrentStatusUI == VIOLATION_RESOLVED) {
        
    } else {
        // DO NOTHING!
    }
}

void GameController::publishToUI(StatusController status) {
    std_msgs::Int32 msg;
    msg.data = status;
    GameController::controllerPublisher.publish(msg);
}

void GameController::startGame() {
    if (CurrentStatusUI == GameController::START_EASY) {
        SelectedDifficulty = GameController::Easy;
        std::cout << "Setting up an easy game...." << std::endl;
    }
    else if (CurrentStatusUI == GameController::START_HARD) {
        SelectedDifficulty = GameController::Hard;
        std::cout << "Setting up an hard game...." << std::endl;
    }
    else {
        // OBSOLETE: UI ENSURES DIFFICULTY IS ALWAYS SELECTED
        SelectedDifficulty = GameController::Null;
    }

    GameActive = true;
    publishToUI(GAME_STARTED);
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
                // OBSOLETE: UI ENSURES DIFFICULTY IS ALWAYS SELECTED
            }
        }
    }
    
    if (CurrentPlayer == OP) {
        publishToUI(PLAYER_TURN);
    }
    else if (CurrentPlayer == AI) {
        publishToUI(ROBOT_TURN);
    }
}

void GameController::getBoardStateFromCamera() {
    BoardState::Board b = mState.getBoard();
    
    project::ImageRequest srv;
    srv.request.service = ImageProcessor::Request::SETUP;
    CameraClient.call(srv);
    
    srv.request.service = ImageProcessor::Request::PROCESS;
    CameraClient.call(srv);
    
    project::BoardInfo info = srv.response.info;
    
    auto newBoard = BoardState(info.board);
    b = newBoard.getBoard();
    
    mState.setBoardState(newBoard);
}

bool GameController::indicateSetWinner() {
    /* TRIADS: ROWs, COLs, when row == col */
    BoardState::Board board = mState.getBoard();

    bool winnerFound = false;
    char winner = ' ';
    
    // Check for all rows
    for (int row = 0; row < BoardState::BOARD_SIZE; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2] && board[row][0] != ' ') {
            controllerStatus.setWinners[SetCount] = board[row][0];
            winnerFound = true;
            winner = board[row][0];
        }
    }
    
    // Check for all columns
    for (int col = 0; col < BoardState::BOARD_SIZE; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col] && board[0][col] != ' ') {
            controllerStatus.setWinners[SetCount] = board[0][col];
            winnerFound = true;
            winner = board[0][col];
        }
    }
    
    // Check for diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        controllerStatus.setWinners[SetCount] = board[0][0];
        winnerFound = true;
        winner = board[1][1];
    }
    
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ') {
        controllerStatus.setWinners[SetCount] = board[1][1];
        winnerFound = true;
        winner = board[1][1];
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
            publishToUI(DRAW_SET);
        }
    }
    else 
    {
        if (winner == 'x') {
            publishToUI(ROBOT_WIN_SET);
        }
        else if (winner == 'o') {
            publishToUI(PLAYER_WIN_SET);
        }
    }
    
    return winnerFound;
}

bool isOP(int p) { return (p == GameController::OP); }
bool isAI(int p) { return (p == GameController::AI); }

bool GameController::determineGameWinner() {
    if (SetCount < 2) {
        controllerStatus.gameWinner = NA;
        return false;
    }
    
    int OPwincount = count_if(controllerStatus.setWinners.begin(), controllerStatus.setWinners.end(), isOP);
    int AIwincount = count_if(controllerStatus.setWinners.begin(), controllerStatus.setWinners.end(), isAI);
    
    if (std::abs(OPwincount - AIwincount) > 1) {
        if (OPwincount < AIwincount) {
            controllerStatus.gameWinner = AI;
            publishToUI(ROBOT_WIN_GAME);
            return true;
        }
        else if (AIwincount < OPwincount) {
            controllerStatus.gameWinner = OP;
            publishToUI(PLAYER_WIN_GAME);
            return true;
        }
    }
    
    if (SetCount == 2 && controllerStatus.gameWinner == NA) {
        controllerStatus.gameWinner = DR;
        publishToUI(DRAW_GAME);
        return true;
    }
    
    return false;
}

void GameController::decideMove() {
    BoardState::Board b = mState.getBoard();
    project::ImageRequest srv;
    srv.request.service = ImageProcessor::Request::SETUP;
    
    CameraClient.call(srv);
    srv.request.service = ImageProcessor::Request::PROCESS;
    CameraClient.call(srv);
    
    project::BoardInfo info = srv.response.info;
    auto point = info.pieces[0];
    auto newBoard = BoardState(info.board);
    b = newBoard.getBoard();
    mState.setBoardState(newBoard);

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
            makeMove(avRows.at(randomIndex), avCols.at(randomIndex), point);
        }
    }
    
    else if (SelectedDifficulty == GameController::Hard) {
        if (mState.BoardEmpty()) {
            makeMove(1, 1, point);
            return;
        }   
        
        // Can you win now?
        struct BoardState::point p = mState.formTriad('x');
        if (p.row != -1 && p.col != -1) {
            makeMove(p.row, p.col, point);
            return;
        }
        
        // Can the opponent win next?
        p = mState.formTriad('o');
        if (p.row != -1 && p.col != -1) {
            makeMove(p.row, p.col, point);
            return;
        }
        
        // Prioritise centre first, then corners, then 
        if (b[1][1] == ' ') {
            makeMove(1, 1, point);
            return;
        } else if (b[0][0] == ' ') {
            makeMove(0, 0, point);
            return;
        } else if (b[2][2] == ' ') {
            makeMove(2, 2, point);
            return;
        } else if (b[2][0] == ' ') {
            makeMove(2, 0, point);
            return;
        } else if (b[0][2] == ' ') {
            makeMove(0, 2, point);
            return;
        }
        
        // otherwise pick a random one
        for (int row = 0; row < BoardState::BOARD_SIZE; row++) {
            for (int col = 0; col < BoardState::BOARD_SIZE; col++) {
                if (b[row][col] == ' ') {
                    makeMove(row, col, point);
                }
            }
        }
    }
}

void GameController::makeMove(const int &row, const int &col, project::Point obj) {
    mState.addPiece(col, row, 'x');
    robotPlacePiece(row, col, obj);
    mState.showBoardState();
    StatusController position = static_cast<StatusController>(row*col+1);
    
    publishToUI(position);
}

void GameController::robotPlacePiece(const int &row, const int &col, project::Point obj) {
    project::Point start = obj;
    project::Point end;
    end.x = col; end.y = row;
    
    project::RobotMoveService robotSrv;
    robotSrv.request.start = start;
    robotSrv.request.goal = end;

    robotClient.call(robotSrv);
}

void GameController::userPlacePiece(int row, int col) {
    project::Point p; p.x = col; p.y = row;
    
    project::UserMoveService userSrv;
    userSrv.request.service = GazeboController::Service::SPAWN_MOVE; 
    userSrv.request.goal = p;
    
    userClient.call(userSrv);
}

void GameController::startRobot() {
    project::UserMoveService userSrv;
    userSrv.request.service = GazeboController::Service::POWER_ON;
    userSrv.request.player = GazeboController::Player::O;
    
    userClient.call(userSrv);
}

void GameController::clearBoard() {
    project::UserMoveService userSrv;
    userSrv.request.service = GazeboController::Service::CLEAR_BOARD;
    
    userClient.call(userSrv);
}

bool validateMove(const BoardState currentInput); // INCLUDES CHECKING FOR TIME AND 

void GameController::endGame() {
    GameActive = false;
    SetCount = 0;
    mState.emptyBoard();
    SelectedDifficulty = Null;
    CurrentPlayer = NA;
    CurrentMove = 0;
}


int main(int argc, char **argv) {
    std::cout << "Controller Initiating...." << std::endl;
    ros::init(argc, argv, "game_controller");
    ros::AsyncSpinner spinner(2);
    spinner.start();
    
    std::cout << "GameController Readying...." << std::endl;
    GameController firstGame;
    
    std::cout << "Game Begin!" << std::endl;

    while(ros::ok()) {
        // Determine whose turn
        /*firstGame.determineCurrentPlayer();
        
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
            
            firstGame.userPlacePiece(row, col);
        }
        else if (firstGame.getCurrentPlayer() == GameController::AI) {
            firstGame.decideMove();
        }
        
        // Check for set winner after every move
	

        // TODO: THIS IS TESTING SECTION, DELETE LATER
        firstGame.indicateSetWinner();
        firstGame.determineGameWinner();
        ros::Duration(3).sleep();*/
    }
    
    std::cout << "Game Finished!" << std::endl;

    std::cout << "Thanks for playing!" << std::endl;

    ros::waitForShutdown();
}
