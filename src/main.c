#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "io.h"

#define MAX_MOVES 256
// 1MB
#define OUTPUT_BUFFER_SIZE 1048576

#ifndef TEST

int main(void)
{
    char *out = malloc(OUTPUT_BUFFER_SIZE * sizeof(*out));
    if (out == NULL)
    {
        printf("Unable to allocate memory.");
        exit(EXIT_FAILURE);
    }

    struct Move *moves = malloc(MAX_MOVES * sizeof(*moves));
    if (moves == NULL)
    {
        printf("Unable to allocate memory.");
        exit(EXIT_FAILURE);
    }

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
    // clang-format on

    int numMoves = loadMoves(moves, "io/input.txt");

    pOut = writeBoard(pOut, &board);

    for (int i = 0; i < numMoves; ++i)
    {
        enum Player player = i % 2 == 0 ? BLACK : WHITE;
        enum MoveError error = makeMove(&board, player, moves[i]);
        if (error)
        {
            pOut = writeError(pOut, error);
            break;
        }

        int cost = getBoardCost(&board, BLACK);
        pOut = writeMoveSummary(pOut, player, moves[i], i, cost);
        pOut = writeBoard(pOut, &board);
    }

    printf("%s", out);
    return 0;
}

#endif