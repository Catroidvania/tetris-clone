/* src/board.h 
 * created thu may 23 2024
 * by catroidvania
 */

#pragma once

#include <stddef.h> // WHY is null undeclared in THIS FILE ONLY???

typedef enum BlockType {
    T = 'T',
    I = 'I',
    O = 'O',
    L = 'L',
    J = 'J',
    S = 'S',
    Z = 'Z',
    NONE = ' '
} Block;


typedef struct Board {

    // nes tetris board, 10x20
    // blocks spawn highest mino on row 20
    Block blocks[200];

} Board;


int clear_board(Board* board);
