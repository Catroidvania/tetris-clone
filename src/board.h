/* src/board.h 
 * created thu may 23 2024
 * by catroidvania
 */

#pragma once

#include <SDL.h>
#include <stddef.h> // WHY is null undeclared in THIS FILE ONLY???
#include "assets.h"


#define BOARDSIZE 200
#define BOARDWIDTH 10
#define BOARDHEIGHT 20
#define POINT(x, y, w) (y * w + x) // 2d coordinates to 1d array index


typedef enum BlockType {
    T = 'T',
    I = 'I',
    O = 'O',
    L = 'L',
    J = 'J',
    S = 'S',
    Z = 'Z',
    BLANK = ' '
} Block;


typedef struct Board {

    // nes tetris board, 10x20
    // blocks spawn highest mino on row 20
    Block blocks[BOARDSIZE];

} Board;


int clear_board(Board* board);
int draw_board(Board* board, SDL_Surface* dest, int x, int y);
