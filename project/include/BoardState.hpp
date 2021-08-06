#ifndef BSTATE_H
#define BSTATE_H

#include <ros/ros.h>

#include <string>
#include <array>
#include <sstream>

class BoardState {
public:
    enum {
        BOARD_SIZE = 3
    };

    typedef std::array<std::array<char, BOARD_SIZE>, BOARD_SIZE> Board;

private:
    Board mBoard;

public:
    BoardState(Board board = {{{' ', ' ', ' '},
                               {' ', ' ', ' '},
                               {' ', ' ', ' '}}}): mBoard{board} {}

    BoardState(const std::string &boardString);

    void showBoardState() {
        for (auto &row : mBoard) {
            for (auto &v : row) {
                std::cout << '[' << v << ']';
            }
            std::cout << std::endl;
        }
    }

    bool addPiece(const int &x, const int &y, const char &letter);
    std::string boardToString();

    void setBoardState(BoardState &state);
};
#endif