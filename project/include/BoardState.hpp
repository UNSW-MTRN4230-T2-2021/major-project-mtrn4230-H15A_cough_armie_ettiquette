#ifndef BSTATE_H
#define BSTATE_H

#include <ros/ros.h>
#include <tuple>
#include <string>
#include <array>
#include <sstream>

class BoardState {
public:
    enum {
        BOARD_SIZE = 3
    };

    typedef std::array<std::array<char, BOARD_SIZE>, BOARD_SIZE> Board;

    struct point {
        int row;
        int col;
    };

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
    bool addPieceForce(const int &x, const int &y, const char &letter);
    std::string boardToString();

    struct point formTriad(const char &c);
    char triadFound();

    void setBoardState(BoardState &state);
    void emptyBoard();
    Board getBoard() { return mBoard; }
    bool BoardEmpty();
};
#endif
