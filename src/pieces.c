/* src/pieces.c
 * created sun may 26 2024
 * by catroidvania
 */

#include "pieces.h"


const Piece I_PIECE = (Piece){
                .type = I, .rotation = UP,
                .x = 3, .y = 21,
                .offsets        = {0, -2, 1, -2, 2, -2, 3, -2},
                .up_offsets     = {0, -2, 1, -2, 2, -2, 3, -2},
                .right_offsets  = {2,  0, 2, -1, 2, -2, 2, -3},
                .down_offsets   = {0, -2, 1, -2, 2, -2, 3, -2},
                .left_offsets   = {2,  0, 2, -1, 2, -2, 2, -3}
            },
            O_PIECE = (Piece){
                .type = O, .rotation = UP,
                .x = 3, .y = 20,
                .offsets        = {1, -1, 1, -2, 2, -1, 2, -2},
                .up_offsets     = {1, -1, 1, -2, 2, -1, 2, -2},
                .right_offsets  = {1, -1, 1, -2, 2, -1, 2, -2},
                .down_offsets   = {1, -1, 1, -2, 2, -1, 2, -2},
                .left_offsets   = {1, -1, 1, -2, 2, -1, 2, -2}
            },
            L_PIECE = (Piece){
                .type = L, .rotation = UP,
                .x = 4, .y = 20,
                .offsets        = {0, -1, 1, -1, 2, -1, 2, -2},
                .up_offsets     = {0, -1, 1, -1, 2, -1, 2, -2},
                .right_offsets  = {0, -2, 1,  0, 1, -1, 1, -2},
                .down_offsets   = {0,  0, 0, -1, 1, -1, 2, -1},
                .left_offsets   = {1,  0, 1, -1, 1, -2, 2,  0}
            },
            J_PIECE = (Piece){
                .type = J, .rotation = UP,
                .x = 4, .y = 20,
                .offsets        = {0, -1, 0, -2, 1, -1, 2, -1},
                .up_offsets     = {0, -1, 0, -2, 1, -1, 2, -1},
                .right_offsets  = {0,  0, 1,  0, 1, -1, 1, -2},
                .down_offsets   = {0, -1, 1, -1, 2, -1, 2,  0},
                .left_offsets   = {1,  0, 1, -1, 1, -2, 2, -2}
            },
            S_PIECE = (Piece){
                .type = S, .rotation = UP,
                .x = 4, .y = 20, 
                .offsets        = {0, -2, 1, -1, 1, -2, 2, -1},
                .up_offsets     = {0, -2, 1, -1, 1, -2, 2, -1},
                .right_offsets  = {1,  0, 1, -1, 2, -1, 2, -2},
                .down_offsets   = {0, -2, 1, -1, 1, -2, 2, -1},
                .left_offsets   = {1,  0, 1, -1, 2, -1, 2, -2},
            },
            T_PIECE = (Piece){
                .type = T, .rotation = UP,
                .x = 4, .y = 20, 
                .offsets        = {0, -1, 1, -1, 1, -2, 2, -1},
                .up_offsets     = {0, -1, 1, -1, 1, -2, 2, -1},
                .right_offsets  = {0, -1, 1,  0, 1, -1, 1, -2},
                .down_offsets   = {0, -1, 1,  0, 1, -1, 2, -1},
                .left_offsets   = {1, -0, 1, -1, 1, -2, 2, -1}
            },
            Z_PIECE = (Piece){
                .type = Z, .rotation = UP,
                .x = 4, .y = 20, 
                .offsets        = {0, -1, 1, -1, 1, -2, 2, -2},
                .up_offsets     = {0, -1, 1, -1, 1, -2, 2, -2},
                .right_offsets  = {1, -1, 1, -2, 2, -0, 2, -1},
                .down_offsets   = {0, -1, 1, -1, 1, -2, 2, -2},
                .left_offsets   = {1, -1, 1, -2, 2, -0, 2, -1}
            };



// checks if a piece intersects any non BLANK blocks
// does not use SDL style return codes, instead returns 1 if there is a collision and 0 if not
int piece_collision(Piece* piece, Board* board) {
    
    if (piece == NULL) { return 0; }
    if (board == NULL) { return 0; }

    for (int i = 0; i < 4; i++) {
        if (piece->x + piece->offsets[i*2] > 9 || piece->x + piece->offsets[i*2] < 0 ||
            piece->y + piece->offsets[i*2+1] > 23 || // you can rotate pieces into the top of the board
            piece->y + piece->offsets[i*2+1] < 0 ||
            board->blocks[POINT(piece->x + piece->offsets[i*2], piece->y + piece->offsets[i*2+1], 10)] != BLANK) {

            return 1;
        }
    }
    
    return 0;
}


// copy an offsets array into another array
// both MUST be length 8
void copy_offsets(int* dest, int* source) {
    // this is so stupid!
    for (int i = 0; i < 8; i++) {
        dest[i] = source[i];
    }
}


// rotates a piece clockwise if possible, no kicks or anything fancy
void rotate_piece_right(Piece* piece, Board* board) {
    
    if (piece == NULL) { return; }
    if (board == NULL) { return; }

    Piece test_piece = *piece;

    switch (piece->rotation) {
        case UP:
            copy_offsets(test_piece.offsets, piece->right_offsets);
            test_piece.rotation = RIGHT;
            break;
        case RIGHT:
            copy_offsets(test_piece.offsets, piece->down_offsets);
            test_piece.rotation = DOWN;
            break;
        case DOWN:
            copy_offsets(test_piece.offsets, piece->left_offsets);
            test_piece.rotation = LEFT;
            break;
        case LEFT:
            copy_offsets(test_piece.offsets, piece->up_offsets);
            test_piece.rotation = UP;
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

    switch (piece->rotation) {
        case UP:
            copy_offsets(test_piece.offsets, piece->left_offsets);
            test_piece.rotation = LEFT;
            break;
        case RIGHT:
            copy_offsets(test_piece.offsets, piece->up_offsets);
            test_piece.rotation = UP;
            break;
        case DOWN:
            copy_offsets(test_piece.offsets, piece->right_offsets);
            test_piece.rotation = RIGHT;
            break;
        case LEFT:
            copy_offsets(test_piece.offsets, piece->down_offsets);
            test_piece.rotation = DOWN;
            break;
    }

    if (!piece_collision(&test_piece, board)) {
        *piece = test_piece;
    }
}


// places a pieces minos on the board
// it will replace any non blank peices it intersects
void solidify_piece(Piece* piece, Board* board) {

    if (piece == NULL) { return; }
    if (board == NULL) { return; }

    for (int i = 0; i < 4; i++) {
        board->blocks[POINT(piece->x + piece->offsets[i*2], piece->y + piece->offsets[i*2+1], 10)] = piece->type;
    }
}
