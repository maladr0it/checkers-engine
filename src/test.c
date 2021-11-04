#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "game.h"
#include "io.h"

// 1MB
#define OUTPUT_BUFFER_SIZE 1048576

#ifdef TEST

int main(void)
{
    char *out = malloc(OUTPUT_BUFFER_SIZE * sizeof(*out));
    char *pOut = out;

    // clang-format off
    struct Board board = {
        .spaces = {
        //   0            1            2            3            4            5            6            7
            {BLANK,       WHITE_PIECE, BLANK,       WHITE_PIECE, BLANK,       WHITE_PIECE, BLANK,       WHITE_PIECE}, // 0
            {WHITE_PIECE, BLANK,       WHITE_PIECE, BLANK,       WHITE_PIECE, BLANK,       WHITE_PIECE, BLANK      }, // 1
            {BLANK,       WHITE_PIECE, BLANK,       WHITE_PIECE, BLANK,       WHITE_PIECE, BLANK,       WHITE_PIECE}, // 2
            {BLANK,       BLANK,       BLANK,       BLANK,       BLANK,       BLANK,       BLANK,       BLANK      }, // 3
            {BLANK,       BLANK,       BLANK,       BLANK,       BLANK,       BLANK,       BLANK,       BLANK      }, // 4
            {BLACK_PIECE, BLANK,       BLACK_PIECE, BLANK,       BLACK_PIECE, BLANK,       BLACK_PIECE, BLANK      }, // 5
            {BLANK,       BLACK_PIECE, BLANK,       BLACK_PIECE, BLANK,       BLACK_PIECE, BLANK,       BLACK_PIECE}, // 6
            {BLACK_PIECE, BLANK,       BLACK_PIECE, BLANK,       BLACK_PIECE, BLANK,       BLACK_PIECE, BLANK      }, // 7
        },
    };

    struct Board desiredBoard = {
        .spaces = {
        //   0            1            2            3            4            5            6            7
            {BLANK,       WHITE_PIECE, BLANK,       WHITE_PIECE, BLANK,       WHITE_PIECE, BLANK,       WHITE_PIECE}, // 0
            {WHITE_PIECE, BLANK,       WHITE_PIECE, BLANK,       WHITE_PIECE, BLANK,       WHITE_PIECE, BLANK      }, // 1
            {BLANK,       WHITE_PIECE, BLANK,       BLACK_PIECE, BLANK,       WHITE_PIECE, BLANK,       WHITE_PIECE}, // 2
            {BLANK,       BLANK,       BLANK,       BLANK,       BLANK,       BLANK,       BLANK,       BLANK      }, // 3
            {BLANK,       BLANK,       BLANK,       BLANK,       BLANK,       BLANK,       BLANK,       BLANK      }, // 4
            {BLACK_PIECE, BLANK,       BLANK,       BLANK,       BLACK_PIECE, BLANK,       BLACK_PIECE, BLANK      }, // 5
            {BLANK,       BLACK_PIECE, BLANK,       BLACK_PIECE, BLANK,       BLACK_PIECE, BLANK,       BLACK_PIECE}, // 6
            {BLACK_PIECE, BLANK,       BLACK_PIECE, BLANK,       BLACK_PIECE, BLANK,       BLACK_PIECE, BLANK      }, // 7
        },
    };
    // clang-format on
    enum Player player;
    struct Move move;

    player = BLACK;
    move.fromX = 2;
    move.fromY = 5;
    move.toX = 1;
    move.toY = 4;
    assert(makeMove(&board, player, move) == ERR_NONE);

    player = WHITE;
    move.fromX = 3;
    move.fromY = 2;
    move.toX = 2;
    move.toY = 3;
    assert(makeMove(&board, player, move) == ERR_NONE);

    player = BLACK;
    move.fromX = 1;
    move.fromY = 4;
    move.toX = 3;
    move.toY = 2;
    assert(makeMove(&board, player, move) == ERR_NONE);

    printf("Pieces can be taken");
    assert(compareBoards(&board, &desiredBoard));

    pOut = writeBoard(pOut, &board);
    printf("%s", out);

    player = WHITE;

    return 0;
}

#endif