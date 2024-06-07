/* src/movegen.h
 * Logan Gallagher
 * 2024/05/07
 */

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include "bitboard.h"
# include "movegen.h"


void splitBoard(struct Bitboard *boards, char piece, int *end, int *start, int *index, int depth);
/*
 * splits a list of boards into its component 
 *
 * struct Board *boards;
 * the list of boards
 *
 * char piece;
 * the current piece to edit
 * 
 * int *end;
 * the end of boards to read
 *
 * int *start;
 * the start of boards to write
 *
 * ind *index;
 * the index to write to
 *
 * ind depth;
 * the current level of generation
 */



int scoreBoard(struct Bitboard board);
/*
 * gives a numeric score to a board
 * 
 * struct Bitboard board;
 * the board to score
 *
 * return int;
 * the move to score
 */


bool arraysAreEqual(char arr1[3][4], char arr2[2][4]);
/*
 * Checks if two arrays are equal
 * arr1;
 * arr2;
 * the two arrays to checl
 *
 * return book;
 * are they equal
 */


char (*getBest(struct Bitboard *boards, int *indices))[4];
/*
 * struct Bitboard *boards;
 * list of generated boards
 *
 * int *indices
 * the position of each predicted piece
 *
 * return (*char)[4];
 * the best move
 *
 */


char (*getBot(struct Bitboard board,char pieces[2]))[4];
/*
 * do all bot funcs in order
 *
 * struct Bitboard board;
 * the initial baord
 *
 * char pieces[2];
 * the two next pieces
 *
 * return (*char)[4];
 * the best move
 *
 */
