#ifndef BSTATE_H
#define BSTATE_H

#include <ros/ros.h>

#include <string>
#include <array>
#include <sstream>

class Piece {
private:
    float mX;
    float mY;
    char mLetter;

public:
    Piece(const float &x, const float &y, const char &letter): 
        mX{x}, mY{y}, mLetter{letter} {}

    bool inGrid() { return (mX < 100 && mX > 10 && 
                            mY < 100 && mY > 10); }

    float getX() { return mX; }
    float getY() { return mY; }
    char getLetter() { return mLetter; }
};

class BoardState {
public:
    enum {
        BOARD_SIZE = 3
    };

    typedef std::array<std::array<char, BOARD_SIZE>, BOARD_SIZE> Board;

private:
    // std::unique_ptr<Board> mBoard;
    Board mBoard;

public:
    BoardState(Board board = {{{' ', ' ', ' '},
                               {' ', ' ', ' '},
                               {' ', ' ', ' '}}}): //mBoard{std::make_unique<Board>(board)} {}
                                                    mBoard{board} {}
    BoardState(const std::string &boardString);
    // Temporary function
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