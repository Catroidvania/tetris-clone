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
    
    Block type;             // block used for rendering
    Rotation rotation;      // piece orientation
    int x, y;               // piece position origin on the board
    int offsets[8];         // mino offset data relative relative to the origin in the top left corner, see https://tetris.wiki/Nintendo_Rotation_System
    int up_offsets[8];      // it is hard coded as a tetromino, should only ever use the predefined offsets
    int right_offsets[8];   // array is meant to be x1 y1 x2 y2 x3 y3 x4 y4, TODO maybe i should invest in a coordinate struct...
    int down_offsets[8];
    int left_offsets[8];

} Piece;


// said predefined offsets, all should be pointers to these
// based on the right handed nintendo rotation system
extern const Piece I_PIECE, O_PIECE, L_PIECE, J_PIECE, S_PIECE, T_PIECE, Z_PIECE;

int piece_collision(Piece* piece, Board* board);
void copy_offsets(int* dest, int* source);
void rotate_piece_right(Piece* piece, Board* board);
void rotate_piece_left(Piece* piece, Board* board);
