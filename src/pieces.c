/* src/pieces.c
 * created sun may 26 2024
 * by catroidvania
 */

#include "pieces.h"

    // O piece
int O_PIECE[8] = {1, -1, 1, -2, 2, -1, 2, -2},
    // I piece
    I_PIECE_HORIZONTAL[8],
    I_PIECE_VERTICAL[8],
    // L piece
    L_PIECE_UP[8],
    L_PIECE_RIGHT[8],
    L_PIECE_DOWN[8],
    L_PIECE_LEFT[8],
    // J piece
    J_PIECE_UP[8],
    J_PIECE_RIGHT[8],
    J_PIECE_DOWN[8],
    J_PIECE_LEFT[8],
    // S piece
    S_PIECE_UP[8],
    S_PIECE_RIGHT[8],
    S_PIECE_DOWN[8],
    S_PIECE_LEFT[8],
    // T piece
    T_PIECE_UP[8]       = {0, -1, 1, -1, 1, -2, 2, -1},
    T_PIECE_RIGHT[8]    = {0, -1, 1,  0, 1, -1, 1, -2},
    T_PIECE_DOWN[8]     = {0, -1, 1,  0, 1, -1, 2, -1},
    T_PIECE_LEFT[8]     = {1, -0, 1, -1, 1, -2, 2, -1},
    // Z piece
    Z_PIECE_UP[8],
    Z_PIECE_RIGHT[8],
    Z_PIECE_DOWN[8],
    Z_PIECE_LEFT[8];


/*
// get the x offset from mino 0 - 3
inline int x_offset(int* offsets, int mino) {
    return offsets[mino*2];
}


// get the y offset from mino 0 - 3
inline int y_offset(int* offsets, int mino) {
    return offsets[mino*2+1];
}
*/


// initialises a piece of the given type
int init_piece(Piece* piece, Block type) {

    if (piece == NULL) { return -1; }

    // same for every piece
    piece->type     = type;
    piece->rotation = UP;

    switch (type) {
    case T:
        // pieces spawned highest piece at row 19, centered to the right
        piece->x = 4;
        piece->y = 20;
        piece->offsets = T_PIECE_UP;
        break;
    }

    return 0;
}


// checks if a piece intersects any non BLANK blocks
// does not use SDL style return codes, instead returns 1 if there is a collision and 0 if not
int piece_collision(Piece* piece, Board* board) {
    
    if (piece == NULL) { return 0; }
    if (board == NULL) { return 0; }

    for (int i = 0; i < 4; i++) {
        if (piece->x + piece->offsets[i*2] > 9 || piece->x + piece->offsets[i*2] < 0 ||
            piece->y + piece->offsets[i*2+1] > 19 || piece->y + piece->offsets[i*2+1] < 0 ||
            board->blocks[POINT(piece->x + piece->offsets[i*2], piece->y + piece->offsets[i*2+1], 10)] != BLANK) {

            return 1;
        }
    }
    
    return 0;
}


// rotates a piece clockwise if possible, no kicks or anything fancy
void rotate_piece_right(Piece* piece, Board* board) {
    
    if (piece == NULL) { return; }
    if (board == NULL) { return; }

    Piece test_piece = *piece;

    // if i had any more forethought some kind of map wouldve been useful here
    switch (piece->type) {
    case T:
        switch (piece->rotation) {
            case UP:
                test_piece.offsets = T_PIECE_RIGHT;
                test_piece.rotation = RIGHT;
                break;
            case RIGHT:
                test_piece.offsets = T_PIECE_DOWN;
                test_piece.rotation = DOWN;
                break;
            case DOWN:
                test_piece.offsets = T_PIECE_LEFT;
                test_piece.rotation = LEFT;
                break;
            case LEFT:
                test_piece.offsets = T_PIECE_UP;
                test_piece.rotation = UP;
                break;
        }

        break;
    }

    if (!piece_collision(&test_piece, board)) {
        *piece = test_piece;
    }
}


// counterclockwise version of rotate_piece_right()
// TODO theres a lot of duplicate code so i might merge the two functions into one
void rotate_piece_left(Piece* piece, Board* board) {
    
    if (piece == NULL) { return; }
    if (board == NULL) { return; }

    Piece test_piece = *piece;

    switch (piece->type) {
    case T:
        switch (piece->rotation) {
            case UP:
                test_piece.offsets = T_PIECE_LEFT;
                test_piece.rotation = LEFT;
                break;
            case RIGHT:
                test_piece.offsets = T_PIECE_UP;
                test_piece.rotation = UP;
                break;
            case DOWN:
                test_piece.offsets = T_PIECE_RIGHT;
                test_piece.rotation = RIGHT;
                break;
            case LEFT:
                test_piece.offsets = T_PIECE_DOWN;
                test_piece.rotation = DOWN;
                break;
        }

        break;
    }

    if (!piece_collision(&test_piece, board)) {
        *piece = test_piece;
    }
}
