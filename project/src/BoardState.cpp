#include "BoardState.hpp"

BoardState::BoardState(const std::string &boardString) {
    // TODO: Throw error if message invalid
    if (boardString.size() != BOARD_SIZE * BOARD_SIZE)
        ROS_ERROR("Invalid board msg");

    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            mBoard[i][j] = boardString[i * BOARD_SIZE + j];
}

bool BoardState::addPiece(const int &x, const int &y, const char &letter) {
    if (mBoard[y][x] != ' ')
        // TODO: Throw a violation
        return false;
    else {
        mBoard[y][x] = letter;
        return true;
    }
}

bool BoardState::addPieceForce(const int &x, const int &y, const char &letter) {
	mBoard[y][x] = letter;
}

std::string BoardState::boardToString() {
    std::stringstream ss;

    for (auto &row : mBoard) {
        for (auto &v : row) {
            ss << v;
        }
    }

    return ss.str();
}

void BoardState::setBoardState(BoardState &state) {
    mBoard = state.mBoard;
}

bool BoardState::BoardEmpty() {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (mBoard[row][col] != ' ') {
                return false;
            }
        }
    }
    
    return true;
}

void BoardState::emptyBoard() {
    Board board = {{{' ', ' ', ' '},
                   {' ', ' ', ' '},
                   {' ', ' ', ' '}}};
    mBoard = board;
}

struct BoardState::point BoardState::formTriad(const char &c) {
    struct point p;

    if (triadFound() != ' ') {
        // someone already wins
        // TODO: DEAL WITH THIS
    }
    
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (mBoard[row][col] == ' ') {
                // ITS EMPTY, CHECK IF A TRIAD CAN BE FORMED HERE
                addPiece(col, row, c);
                char isTriad = triadFound();
                addPieceForce(col, row, ' ');
                
                if (isTriad == c) {
                    p.row = row;
                    p.col = col;
                    return p;
                }
            }
        }
    }
    
    p.row = -1;
    p.col = -1;
    return p;
}

char BoardState::triadFound() {
    // Check for all rows
    for (int row = 0; row < BoardState::BOARD_SIZE; row++) {
        if (mBoard[row][0] == mBoard[row][1] && mBoard[row][1] == mBoard[row][2] && mBoard[row][0] != ' ') {
            return mBoard[row][0];
        }
    }
    
    // Check for all columns
    for (int col = 0; col < BoardState::BOARD_SIZE; col++) {
        if (mBoard[0][col] == mBoard[1][col] && mBoard[1][col] == mBoard[2][col] && mBoard[0][col] != ' ') {
            return mBoard[0][col];
        }
    }
    
    // Check for diagonals
    if (mBoard[0][0] == mBoard[1][1] && mBoard[1][1] == mBoard[2][2] && mBoard[0][0] != ' ') {
        return mBoard[1][1];
    }
    
    if (mBoard[0][2] == mBoard[1][1] && mBoard[1][1] == mBoard[2][0] && mBoard[1][1] != ' ') {
        return mBoard[1][1];
    }
    
    return ' ';
}
