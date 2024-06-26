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

    SDL_BlitSurface(TEXTURES[WINDOW_BG_TEXTURE], NULL, app->window_surface, &coords);
}


// draw the board at a specific x y position
void draw_board(Board* board, SDL_Surface* dest, int x, int y) {
    
    if (board == NULL) { return; }
    if (dest == NULL)  { return; }

    //SDL_Rect coords = (SDL_Rect){x, y, 0, 0};

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

    Texture texture = BLANK_TEXTURE;
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
    case GARBAGE:
        texture = GARBAGE_TEXTURE;
        break;
    }
    
    return SDL_BlitSurface(TEXTURES[texture], NULL, dest, &coords);
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
        test_piece.y--;
    }
    test_piece.y++;

    if (test_piece.y < game->current_piece.y) { draw_piece(&test_piece, dest, x, y); }
}


// draws a preview of the next piece
void draw_preview(Game* game, SDL_Surface* dest, int x, int y) {

    if (game == NULL) { return; }
    if (dest == NULL)  { return; }

    SDL_Rect coords = (SDL_Rect){x, y, 0, 0};
    SDL_BlitSurface(TEXTURES[PREVIEW_FRAME_TEXTURE], NULL, dest, &coords);

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
    SDL_BlitSurface(TEXTURES[SCORE_TEXTURE], NULL, dest, &coords);
    draw_number(game->score, 6, dest, x, y + 64);
    
    coords = (SDL_Rect){x, y + 128, 0, 0};
    SDL_BlitSurface(TEXTURES[LINES_TEXTURE], NULL, dest, &coords);
    draw_number(game->lines_cleared, 6, dest, x, y + 192);

    coords = (SDL_Rect){x, y + 256, 0, 0};
    SDL_BlitSurface(TEXTURES[LEVEL_TEXTURE], NULL, dest, &coords);
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
        SDL_BlitSurface(TEXTURES[N0_TEXTURE+digit], NULL, dest, &coords);
    }
}


// wrapper over SDL_BlitSurface so i dont need to screw with rects
int draw_image(Texture index, SDL_Surface* dest, int x, int y) {

    //if (src == NULL) { return -1; }
    if (dest == NULL)  { return -1; }

    SDL_Rect coords = (SDL_Rect){x, y, 0, 0};
    return SDL_BlitSurface(TEXTURES[index], NULL, dest, &coords);
}


// draws a selector menu
void draw_selector(Selector* menu, SDL_Surface* dest, int x, int y) {
    
    if (menu == NULL) { return; }
    if (dest == NULL) { return; }

    for (int b = 0; b < menu->button_count; b++) {
        if (menu->buttons[b] == menu->current) {
            draw_image(menu->buttons[b]->texture + 1, dest, x + menu->buttons[b]->x, y + menu->buttons[b]->y);
        } else {
            draw_image(menu->buttons[b]->texture , dest, x + menu->buttons[b]->x, y + menu->buttons[b]->y);
        }
    }
}


// draws red tinted blocks from the top of the board downwarsd based on how much garbage is incoming
void draw_incoming(Game* game, SDL_Surface* dest, int x, int y) {
    
    if (game == NULL) { return; }
    if (dest == NULL)  { return; }

    SDL_Rect coords = (SDL_Rect){x, y, 0, 0};
    SDL_BlitSurface(TEXTURES[BOARD_BG_TEXTURE], NULL, dest, &coords);

    for (int r = BOARDHEIGHT-1; r > BOARDHEIGHT - game->garbage - 1; r--) {
        draw_image( INCOMING_TEXTURE, dest, BOARDBORDERSIZE + x,
                    (BOARDHEIGHT-1 - r) * BLOCKSIZE + BOARDBORDERSIZE + y);
    }
}
