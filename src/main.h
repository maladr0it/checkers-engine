#ifndef MAIN_H
#define MAIN_H

#define BOARD_SIZE 8

enum Player
{
    BLACK,
    WHITE,
};

enum BoardSpace
{
    BLACK_PIECE,
    BLACK_TOWER,
    WHITE_PIECE,
    WHITE_TOWER,
    BLANK,
};

enum MoveError
{
    ERR_NONE,
    ERR_SOURCE_CELL_OUTSIDE_BOARD,
    ERR_TARGET_CELL_OUTSIDE_BOARD,
    ERR_SOURCE_CELL_EMPTY,
    ERR_TARGET_CELL_NOT_EMPTY,
    ERR_SOURCE_CELL_HOLDS_OPPONENTS_PIECE,
    ERR_ILLEGAL_ACTION,
};

struct Board
{
    enum BoardSpace spaces[BOARD_SIZE][BOARD_SIZE];
};

struct Move
{
    int fromX;
    int fromY;
    int toX;
    int toY;
};

#endif