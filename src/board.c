/* src/board.c
 * created thu may 23 2024
 * by catroidvania
 */

#include "board.h"


// fill a board with empty blocks
int clear_board(Board* board) {

    if (board == NULL) {
        return -1;
    }

    for (int i=0; i < 200; i++) {
        board->blocks[i] = BLANK;
    }

    return 0;
}


// draw the board at a specific x y position
int draw_board(Board* board, SDL_Surface* dest, int x, int y) {
    
    int success = 0;
    SDL_Surface* texture = NULL;
    SDL_Rect coords = {0};

    // r(ow), c(olumn)
    for (int r = BOARDHEIGHT-1; r > -1; r--) {
        for (int c = 0; c < BOARDWIDTH; c++) {
    //for (int i = BOARDSIZE-1; i > -1; i--) {
            coords = (SDL_Rect){c * BLOCKSIZE + x, (BOARDHEIGHT-1 - r) * BLOCKSIZE + y, 0, 0};
            //coords = (SDL_Rect){(i % BOARDWIDTH) * BLOCKSIZE + x, (i / BOARDHEIGHT) * BLOCKSIZE + y, 0, 0};

            switch (board->blocks[POINT(c, r, BOARDWIDTH)]) {
            //switch (board->blocks[i]) {
            case BLANK:
                texture = BLANK_TEXTURE;
                break;
            case Z:
                texture = Z_TEXTURE;
                break;
            case L:
                texture = L_TEXTURE;
                break;
            case O:
                texture = O_TEXTURE;
                break;
            case S:
                texture = S_TEXTURE;
                break;
            case J:
                texture = J_TEXTURE;
                break;
            case I:
                texture = I_TEXTURE;
                break;
            case T:
                texture = T_TEXTURE;
                break;
            }

            success = SDL_BlitSurface(texture, NULL, dest, &coords) > 0;
        }
    }

    return success;
}
