#ifndef MOVEGEN_H
#define MOVEGEN_H

# include <stdbool.h>

// Function prototypes
void getInfo(char piece, char *info);
char* getHeight(unsigned char *board);
int getLegalMoves(char piece, unsigned char *board, char **moves);
void playMove(unsigned char *board, short int *score, char *move);

#endif // MOVEGEN_H
