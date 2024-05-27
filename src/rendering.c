/* src/rendering.c
 * created sun may 26 2024
 * by catroidvania
 */

#include "rendering.h"


// fills the window with white
void clear_window(App* app) {
    SDL_FillRect(app->window_surface, NULL, SDL_MapRGB(app->window_surface->format, 255, 255, 255));
}


// draw the board at a specific x y position
void draw_board(Board* board, SDL_Surface* dest, int x, int y) {
    
    if (board == NULL) { return; }
    if (dest == NULL)  { return; }

    SDL_Surface* texture = NULL;
    SDL_Rect coords = {0};

    // r(ow), c(olumn)
    for (int r = BOARDHEIGHT-1; r > -1; r--) {
        for (int c = 0; c < BOARDWIDTH; c++) {
            draw_block(board->blocks[POINT(c, r, BOARDWIDTH)], dest, c * BLOCKSIZE + x, (BOARDHEIGHT-1 - r) * BLOCKSIZE + y);
        }
    }
}


// draws a single mino on the screen
int draw_block(Block type, SDL_Surface* dest, int x, int y) {

    SDL_Surface* texture = NULL;
    SDL_Rect coords = (SDL_Rect){x, y, 0, 0};

    switch (type) {
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
    
    return SDL_BlitSurface(texture, NULL, dest, &coords);
}


// draws a piece, x and y should be the same as where you drew the board
// remember to draw the board first so the piece shows up on top
void draw_piece(Piece* piece, SDL_Surface* dest, int x, int y) {
    
    if (piece == NULL) { return; }
    if (dest == NULL)  { return; }

    draw_block(piece->type, dest, (piece->x + piece->offsets[0]) * BLOCKSIZE + x, (19 - (piece->y + piece->offsets[1])) * BLOCKSIZE + y);
    draw_block(piece->type, dest, (piece->x + piece->offsets[2]) * BLOCKSIZE + x, (19 - (piece->y + piece->offsets[3])) * BLOCKSIZE + y);
    draw_block(piece->type, dest, (piece->x + piece->offsets[4]) * BLOCKSIZE + x, (19 - (piece->y + piece->offsets[5])) * BLOCKSIZE + y);
    draw_block(piece->type, dest, (piece->x + piece->offsets[6]) * BLOCKSIZE + x, (19 - (piece->y + piece->offsets[7])) * BLOCKSIZE + y);
}

