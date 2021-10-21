#ifndef IO_H
#define IO_H

char *copyString(char *dest, char *source);

char *copyChar(char *dest, char c);

int loadMoves(struct Move *moves, char *filePath);

char *writeError(char *dest, enum MoveError error);

char *writeMoveSummary(char *dest, enum Player player, struct Move move, int moveNum, int boardCost);

char *writeBoard(char *out, struct Board *board);

#endif