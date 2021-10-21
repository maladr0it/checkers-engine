#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "main.h"

#define MOVE_LINE_LEN 8

char *copyString(char *dest, char *source)
{
    char *pSource = source;
    char *pDest = dest;
    do
    {
        *pDest++ = *pSource++;
    } while (*pSource != '\0');

    return pDest;
}

char *copyChar(char *dest, char c)
{
    char *pDest = dest;
    *pDest++ = c;
    *pDest = '\0';
    return pDest;
}

char *writeInt(char *dest, int num)
{
    int n = num;
    int len = 0;
    bool isNegative = false;

    if (num < 0)
    {
        isNegative = true;
        n *= -1;
    }

    do
    {
        dest[len++] = '0' + (n % 10);
        n /= 10;
    } while (n != 0);

    if (isNegative)
    {
        dest[len++] = '-';
    }

    // Reverse digits
    for (int i = 0; i < len / 2; ++i)
    {
        char temp = dest[i];
        dest[i] = dest[len - 1 - i];
        dest[len - 1 - i] = temp;
    }

    return dest + len;
}

int loadMoves(struct Move *moves, char *filePath)
{
    int numMoves = 0;
    char line[MOVE_LINE_LEN];

    FILE *file = fopen(filePath, "r");
    if (file == NULL)
    {
        printf("Unable to open file.\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, MOVE_LINE_LEN, file) != NULL)
    {
        moves[numMoves].fromX = line[0] - 'A';
        moves[numMoves].fromY = line[1] - '1';
        moves[numMoves].toX = line[3] - 'A';
        moves[numMoves].toY = line[4] - '1';
        ++numMoves;
    }

    fclose(file);
    return numMoves;
}

char *writeError(char *dest, enum MoveError error)
{
    char *p = dest;
    switch (error)
    {
    case ERR_NONE:
        break;
    case ERR_SOURCE_CELL_OUTSIDE_BOARD:
        p = copyString(p, "ERROR: Source cell is outside of the board.\n");
        break;
    case ERR_TARGET_CELL_OUTSIDE_BOARD:
        p = copyString(p, "ERROR: Target cell is outside of the board.\n");
        break;
    case ERR_SOURCE_CELL_EMPTY:
        p = copyString(p, "ERROR: Source cell is empty.\n");
        break;
    case ERR_TARGET_CELL_NOT_EMPTY:
        p = copyString(p, "ERROR: Target cell is not empty.\n");
        break;
    case ERR_SOURCE_CELL_HOLDS_OPPONENTS_PIECE:
        p = copyString(p, "ERROR: Source cell holds opponent's piece/tower.\n");
        break;
    case ERR_ILLEGAL_ACTION:
        p = copyString(p, "ERROR: Illegal action.\n");
        break;
    }

    return p;
}

char *writeMove(char *dest, struct Move move)
{
    char *p = dest;
    p = copyChar(p, move.fromX + 'A');
    p = copyChar(p, move.fromY + '1');
    p = copyChar(p, '-');
    p = copyChar(p, move.toX + 'A');
    p = copyChar(p, move.toY + '1');
    return p;
}

char *writeMoveSummary(char *dest, enum Player player, struct Move move, int moveNum, int boardCost)
{
    char *p = dest;

    p = copyString(p, "=====================================\n");
    p = copyString(p, player == BLACK ? "BLACK" : "WHITE");
    p = copyString(p, " ACTION #");
    p = writeInt(p, moveNum + 1);
    p = copyString(p, ": ");
    p = writeMove(p, move);
    p = copyChar(p, '\n');
    p = copyString(p, "BOARD COST: ");
    p = writeInt(p, boardCost);
    p = copyChar(p, '\n');

    return p;
}

char *writeBoard(char *dest, struct Board *board)
{
    char *p = dest;
    p = copyString(p, "    A   B   C   D   E   F   G   H\n");
    p = copyString(p, "  +---+---+---+---+---+---+---+---+\n");

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        p = copyChar(p, '1' + i);
        p = copyChar(p, ' ');
        p = copyChar(p, '|');
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            p = copyChar(p, ' ');
            char space;
            switch (board->spaces[i][j])
            {
            case BLACK_PIECE:
                space = 'b';
                break;
            case BLACK_TOWER:
                space = 'B';
                break;
            case WHITE_PIECE:
                space = 'w';
                break;
            case WHITE_TOWER:
                space = 'W';
                break;
            case BLANK:
                space = '.';
                break;
            }
            p = copyChar(p, space);
            p = copyChar(p, ' ');
            p = copyChar(p, '|');
        }
        p = copyChar(p, '\n');
        p = copyString(p, "  +---+---+---+---+---+---+---+---+\n");
    }
    return p;
}
