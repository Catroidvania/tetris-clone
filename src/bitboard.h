/* src/bitboard.h
 * Logan Gallagher
 * 2024/05/31
 */

#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdio.h>
#include <stdint.h>

struct Bitboard {
    unsigned char board[25];
    short int score;
	char moves[3][4];
};

void initBoard(struct Bitboard *board);
int isTileSet(unsigned char *board, int col, int row);
void setBit(unsigned char board[], int col, int row, int value);
void dispBoard(unsigned char board[]);

#endif /* BITBOARD_H */
