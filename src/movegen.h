#ifndef MOVEGEN_H
#define MOVEGEN_H

# include <stdbool.h>

// Function prototypes
void getInfo(char piece, char *info);
/*
 *gets information about a piece 
 * 
 * char piece;
 * the piece to get info on
 *
 * char *info;
 * the pointer to be filled with info about the piece
 */

char* getHeight(unsigned char *board);
/*
 * gets the height of all columns relitive to the bottom
 *
 * unsigned char *board;
 * the board to get hieght of 
 *
 * return char*;
 * length 10 array containing the height
 */



int getLegalMoves(char piece, unsigned char *board, char **moves);
/*
 * gets a list of the legal moves in a position
 *
 * char piece;
 * piece to drop
 *
 * unsigned char *board;
 * the board to get moves from
 *
 * char **moves;
 * pointer where moves will be stored
 *
 * return int;
 * the nimber of legal moves
 */



void playMove(unsigned char *board, short int *score, char *move);
/*
 * Plays a given move on the board
 *
 * unsigned char *board;
 * the board to play a move on
 *
 * short int *score;
 * pointer to the board's score value
 *
 * char *move;
 * the move to be made
 */



#endif // MOVEGEN_H
