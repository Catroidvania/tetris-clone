/* src/board.h 
 * created thu may 23 2024
 * by catroidvania
 */

#pragma once

#include <SDL.h>
#include <stddef.h> // WHY is null undeclared in THIS FILE ONLY???
#include "assets.h"
#include "block.h"


#define BOARDSIZE 220 // somwe extra room to allow piece rotation on the top ro
#define BOARDWIDTH 10
#define BOARDHEIGHT 20
#define POINT(x, y, w) ((y) * (w) + (x)) // 2d coordinates to 1d array index


typedef struct Board {

    // nes tetris board, 10x20
    // blocks spawn highest mino on row 19
    // board coordinates start at 0 not 1
    Block blocks[BOARDSIZE];

} Board;


int clear_board(Board* board);
