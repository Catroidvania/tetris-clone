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
int scoreBoard(struct Bitboard board);
bool arraysAreEqual(char arr1[3][4], char arr2[2][4]);
char (*getBest(struct Bitboard *boards, int *indices))[4];
char *getBot(struct Bitboard board,char pieces[2]);
