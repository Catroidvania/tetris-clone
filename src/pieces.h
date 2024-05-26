/* src/pieces.h
 * created sun may 26 2024
 * by catroidvania
 */

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "assets.h"
#include "block.h"
#include "board.h"


// tracks piece rotations
typedef enum PieceRotation {
    UP = 0, // default rotation
    RIGHT,
    DOWN,
    LEFT
} Rotation;


// tetrominos
typedef struct Piece {
    
    Block type;         // block used for rendering
    Rotation rotation;  // piece orientation
    int x, y;           // piece position origin on the board
    int* offsets;       // mino offset data relative relative to the origin in the top left corner, see https://tetris.wiki/Nintendo_Rotation_System
                        // it is hard coded as a tetromino, should only ever use the predefined offsets
                        // array is meant to be x1 y1 x2 y2 x3 y3 x4 y4, TODO maybe i should invest in a coordinate struct...
} Piece;


// said predefined offsets, all should be pointers to these
// based on the right handed nintendo rotation system
extern int  O_PIECE[8],
            I_PIECE_HORIZONTAL[8], I_PIECE_VERTICAL[8],
            L_PIECE_UP[8], L_PIECE_RIGHT[8], L_PIECE_DOWN[8], L_PIECE_LEFT[8],
            J_PIECE_UP[8], J_PIECE_RIGHT[8], J_PIECE_DOWN[8], J_PIECE_LEFT[8],
            S_PIECE_UP[8], S_PIECE_RIGHT[8], S_PIECE_DOWN[8], S_PIECE_LEFT[8],
            T_PIECE_UP[8], T_PIECE_RIGHT[8], T_PIECE_DOWN[8], T_PIECE_LEFT[8],
            Z_PIECE_UP[8], Z_PIECE_RIGHT[8], Z_PIECE_DOWN[8], Z_PIECE_LEFT[8];


//inline int x_offset(int* offsets, int mino);
//inline int y_offset(int* offsets, int mino);
int init_piece(Piece* piece, Block type);
int piece_collision(Piece* piece, Board* board);
void rotate_piece_right(Piece* piece, Board* board);
void rotate_piece_left(Piece* piece, Board* board);
