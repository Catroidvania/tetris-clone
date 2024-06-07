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
/*
 *initalises the board struct
 *
 * struct Bitboard *board; 
 * the bitboard to initalise 
 */

int isTileSet(unsigned char *board, int col, int row);
/*
 * checks a tile on the board using row and column position
 *
 * unsigned car *board;
 * the board to set the tile of
 *
 * int col;
 * the colum in the board
 * 
 * int row;
 * the row in the board
 *
 * return int;
 * int value of the tile
 */

void setBit(unsigned char board[], int col, int row, int value);
/*
 * sets a tile on the board using row and col pos
 *
 * unsigned char board[];
 * the board being edited
 *
 * int col;
 * the colum in the board
 * 
 * int row;
 * the row in the board
 *
 * int value;
 * the value of the bit
 */



void dispBoard(unsigned char board[]);
/*
 * prints the board to the command line in an efficient mannor
 *
 * unsigned char Board[];
 * the board to be printed
 */



#endif /* BITBOARD_H */
