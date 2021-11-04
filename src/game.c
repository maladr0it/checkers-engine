#include <stdlib.h>
#include "game.h"

static bool isPlayersPiece(enum BoardSpace space, enum Player player)
{
    if (player == BLACK)
    {
        return space == BLACK_PIECE || space == BLACK_TOWER;
    }
    else
    {
        return space == WHITE_PIECE || space == WHITE_TOWER;
    }
}

static bool isOpponentsPiece(enum BoardSpace space, enum Player player)
{
    if (player == BLACK)
    {
        return space == WHITE_PIECE || space == WHITE_TOWER;
    }
    else
    {
        return space == BLACK_PIECE || space == BLACK_TOWER;
    }
}

static bool isForwards(struct Move move, enum Player player)
{
    if (player == BLACK)
    {
        return move.toY - move.fromY < 0;
    }
    else
    {
        return move.toY - move.fromY > 0;
    }
}

static bool isDiagonal(struct Move move, int length)
{
    return abs(move.toX - move.fromX) == length && abs(move.toY - move.fromY) == length;
}

static bool isTower(enum BoardSpace space)
{
    return space == BLACK_TOWER || space == WHITE_TOWER;
}

bool compareBoards(struct Board *a, struct Board *b)
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (a->spaces[i][j] != b->spaces[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

int getBoardCost(struct Board *board, enum Player player)
{
    int numBlackPieces = 0;
    int numBlackTowers = 0;
    int numWhitePieces = 0;
    int numWhiteTowers = 0;

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            switch (board->spaces[i][j])
            {
            case BLACK_PIECE:
                ++numBlackPieces;
                break;
            case BLACK_TOWER:
                ++numBlackTowers;
                break;
            case WHITE_PIECE:
                ++numWhitePieces;
                break;
            case WHITE_TOWER:
                ++numWhiteTowers;
                break;
            default:
                break;
            }
        }
    }
    int cost = numBlackPieces + 3 * numBlackTowers - numWhitePieces - 3 * numWhiteTowers;
    return (player == BLACK ? 1 : -1) * cost;
}

enum MoveError makeMove(struct Board *board, enum Player player, struct Move move)
{
    enum BoardSpace fromSpace = board->spaces[move.fromY][move.fromX];
    enum BoardSpace toSpace = board->spaces[move.toY][move.toX];

    if (move.fromX < 0 || move.fromX >= BOARD_SIZE || move.fromY < 0 || move.fromY >= BOARD_SIZE)
    {
        return ERR_SOURCE_CELL_OUTSIDE_BOARD;
    }
    else if (move.toX < 0 || move.toX >= BOARD_SIZE || move.toY < 0 || move.toY >= BOARD_SIZE)
    {
        return ERR_TARGET_CELL_OUTSIDE_BOARD;
    }
    else if (fromSpace == BLANK)
    {
        return ERR_SOURCE_CELL_EMPTY;
    }
    else if (toSpace != BLANK)
    {
        return ERR_TARGET_CELL_NOT_EMPTY;
    }
    else if (isOpponentsPiece(fromSpace, player))
    {
        return ERR_SOURCE_CELL_HOLDS_OPPONENTS_PIECE;
    }
    else if (!isTower(fromSpace) && !isForwards(move, player))
    {
        return ERR_ILLEGAL_ACTION;
    }
    else if (isDiagonal(move, 1))
    {
        board->spaces[move.toY][move.toX] = fromSpace;
        board->spaces[move.fromY][move.fromX] = BLANK;

        // promote piece to tower
        if ((move.toY == 0 || move.toY == BOARD_SIZE - 1) && !isTower(fromSpace))
        {
            board->spaces[move.toY][move.toX] = player == BLACK ? BLACK_TOWER : WHITE_TOWER;
        }
        return ERR_NONE;
    }
    else if (isDiagonal(move, 2))
    {
        // capture a piece
        int capturedX = move.fromX + (move.toX - move.fromX) / 2;
        int capturedY = move.fromY + (move.toY - move.fromY) / 2;
        if (!isOpponentsPiece(board->spaces[capturedY][capturedX], player))
        {
            return ERR_ILLEGAL_ACTION;
        }

        board->spaces[capturedY][capturedX] = BLANK;
        board->spaces[move.toY][move.toX] = fromSpace;
        board->spaces[move.fromY][move.fromX] = BLANK;

        // promote piece to tower
        if ((move.toY == 0 || move.toY == BOARD_SIZE - 1) && !isTower(fromSpace))
        {
            board->spaces[move.toY][move.toX] = player == BLACK ? BLACK_TOWER : WHITE_TOWER;
        }
        return ERR_NONE;
    }
    else
    {
        return ERR_ILLEGAL_ACTION;
    }
}