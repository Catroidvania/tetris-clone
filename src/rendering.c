/* src/rendering.c
 * created sun may 26 2024
 * by catroidvania
 */

#include "rendering.h"


// fills the window with white
void clear_window(App* app) {
    //SDL_FillRect(app->window_surface, NULL, SDL_MapRGB(app->window_surface->format, 255, 255, 255));

    if (app == NULL)  { return; }

    SDL_Rect coords = {0};

    SDL_BlitSurface(WINDOW_BG_TEXTURE, NULL, app->window_surface, &coords);
}


// draw the board at a specific x y position
void draw_board(Board* board, SDL_Surface* dest, int x, int y) {
    
    if (board == NULL) { return; }
    if (dest == NULL)  { return; }

    SDL_Rect coords = (SDL_Rect){x, y, 0, 0};
    SDL_BlitSurface(BOARD_BG_TEXTURE, NULL, dest, &coords);

    // r(ow), c(olumn)
    for (int r = BOARDHEIGHT-1; r > -1; r--) {
        for (int c = 0; c < BOARDWIDTH; c++) {
            draw_block( board->blocks[POINT(c, r, BOARDWIDTH)], dest, c * BLOCKSIZE + BOARDBORDERSIZE + x,
                        (BOARDHEIGHT-1 - r) * BLOCKSIZE + BOARDBORDERSIZE + y);
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
    case GHOST:
        texture = GHOST_TEXTURE;
        break;
    }
    
    return SDL_BlitSurface(texture, NULL, dest, &coords);
}


// draws a piece, x and y should be the same as where you drew the board
// remember to draw the board first so the piece shows up on top
void draw_piece(Piece* piece, SDL_Surface* dest, int x, int y) {
    
    if (piece == NULL) { return; }
    if (dest == NULL)  { return; }

    for (int i = 0; i < 4; i++) {
        if (piece->x + piece->offsets[i*2] > -1 && piece->x + piece->offsets[i*2] < BOARDWIDTH &&
            piece->y + piece->offsets[i*2+1] > -1 && piece->y + piece->offsets[i*2+1] < BOARDHEIGHT) {
            draw_block( piece->type, dest, 
                        (piece->x + piece->offsets[i*2]) * BLOCKSIZE + BOARDBORDERSIZE + x, 
                        (19 - (piece->y + piece->offsets[i*2+1])) * BLOCKSIZE + BOARDBORDERSIZE + y);
        }
    }
}


// draws a ghost of the current piece to preview help visualize where the piece will go
void draw_ghost(Game* game, SDL_Surface* dest, int x, int y) {

    if (game == NULL) { return; }
    if (dest == NULL)  { return; }

    Piece test_piece = game->current_piece;
    test_piece.type = GHOST;

    while (!piece_collision(&test_piece, &game->board)) {
        test_piece.y -= 1;
    }
    test_piece.y += 1;

    if (test_piece.y < game->current_piece.y) { draw_piece(&test_piece, dest, x, y); }
}


// draws a preview of the next piece
void draw_preview(Game* game, SDL_Surface* dest, int x, int y) {

    if (game == NULL) { return; }
    if (dest == NULL)  { return; }

    SDL_Rect coords = (SDL_Rect){x, y, 0, 0};
    SDL_BlitSurface(PREVIEW_FRAME_TEXTURE, NULL, dest, &coords);

    Piece dummy = game->next_piece;
    dummy.x = 0;
    dummy.y = 20;

    switch (game->next_piece.type) {
    case I:
        //draw_piece(&dummy, dest, x + PREVIEWBORDERSIZE, y + PREVIEWBORDERSIZE);
        draw_piece(&dummy, dest, x, y + (BLOCKSIZE / 2));
        break;
    case O:
        draw_piece(&dummy, dest, x, y + BLOCKSIZE);
        //draw_piece(&dummy, dest, x + PREVIEWBORDERSIZE + BLOCKSIZE, y + PREVIEWBORDERSIZE + BLOCKSIZE);
        break;
    default:
        draw_piece(&dummy, dest, x + (BLOCKSIZE / 2), y + BLOCKSIZE);
        //draw_piece(&dummy, dest, x + PREVIEWBORDERSIZE + (BLOCKSIZE / 2), y + PREVIEWBORDERSIZE + (BLOCKSIZE / 2));
        break;
    }
}


// draws the game information
void draw_stats(Game* game, SDL_Surface* dest, int x, int y) {

    if (game == NULL) { return; }
    if (dest == NULL)  { return; }

    SDL_Rect coords = (SDL_Rect){x, y, 0, 0};
    SDL_BlitSurface(SCORE_TEXTURE, NULL, dest, &coords);
    draw_number(game->score, 6, dest, x, y + 64);
    
    coords = (SDL_Rect){x, y + 128, 0, 0};
    SDL_BlitSurface(LINES_TEXTURE, NULL, dest, &coords);
    draw_number(game->lines_cleared, 6, dest, x, y + 192);

    coords = (SDL_Rect){x, y + 256, 0, 0};
    SDL_BlitSurface(LEVEL_TEXTURE, NULL, dest, &coords);
    draw_number(game->level, 2, dest, x, y + 320);
}


// draws a number with places amount of digits, padded by leading 0s
void draw_number(int number, int places, SDL_Surface* dest, int x, int y) {

    if (dest == NULL)  { return; }

    SDL_Rect coords = (SDL_Rect){x, y, 0, 0};
    int digit = 0;

    for (int i = places-1; i > -1; i--) {
        digit = number % 10;
        number /= 10;

        coords = (SDL_Rect){x + (BLOCKSIZE * i), y, 0, 0};
        SDL_BlitSurface(NUMBER_TEXTURE[digit], NULL, dest, &coords);
    }
}
