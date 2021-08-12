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