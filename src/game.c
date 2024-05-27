/* src/game.c 
 * created mon may 27 2024
 * by catroidvania
 */

#include "game.h"


// initialises a game of tetris
int init_game(Game* game) {
    
    if (game == NULL) { return -1; }

    clear_board(&game->board);

    // seed initial pieces
    game->current_piece = randomize_piece(NULL);
    game->next_piece = randomize_piece(&game->current_piece);

    game->score = 0;
    game->level = 1;
    game->lines_cleared = 0;

    return 0;
}


// changes the current to the next piece and generates a new next piece
void swap_pieces(Game* game) {
    
    if (game == NULL) { return; }

    game->current_piece = game->next_piece;
    game->next_piece = randomize_piece(&game->current_piece);
}


// moves the current piece around based on keypresses
// TODO add DAS and stuff
void move_current_piece(Game* game, SDL_Event* event) {

    if (game == NULL) { return; }
    if (event == NULL) { return; }

    Piece test_piece;

    // make sure a key is actually pressed
    if (event->type == SDL_KEYDOWN) {

        test_piece = game->current_piece; // for checking things

        switch (event->key.keysym.sym) {
        case SDLK_LEFT:
            test_piece.x -= 1;
            if (!piece_collision(&test_piece, &game->board)) { game->current_piece = test_piece; }
            break;
        case SDLK_RIGHT:
            test_piece.x += 1;
            if (!piece_collision(&test_piece, &game->board)) { game->current_piece = test_piece; }
            break;

        // TODO for testing, change later
        case SDLK_UP:
            test_piece.y += 1;
            if (!piece_collision(&test_piece, &game->board)) { game->current_piece = test_piece; }
            break;
        case SDLK_DOWN:
            test_piece.y -= 1;
            if (!piece_collision(&test_piece, &game->board)) { game->current_piece = test_piece; }
            break;

        case SDLK_x:
            rotate_piece_right(&game->current_piece, &game->board);
            break;
        case SDLK_z:
            rotate_piece_left(&game->current_piece, &game->board);
            break;
        }
    }
}


// locks the current piece if it cannot go any lower
void lock_current_piece(Game* game) {

    if (game == NULL) { return; }

    Piece test_piece = game->current_piece;
    test_piece.y -= 1;

    // check if the piece can move down
    if (piece_collision(&test_piece, &game->board)) {
        // lock the piece to the board if not and move onto the next piece
        solidify_piece(&game->current_piece, &game->board);
        swap_pieces(game);
    }
}


// shifts all rows above the given row down 1 position
void shift_rows_down(Game* game, int row) {
    
    if (game == NULL) { return; }

    for (int i = row * BOARDWIDTH; i < 200; i++) {
        if (i+10 > 199) {
            game->board.blocks[i] = BLANK;
        } else {
            game->board.blocks[i] = game->board.blocks[i+10];
        }
    }
}


// clears and full rows and returns 1 if any lines were cleared, 0 otherwise
int clear_lines(Game* game) {

    if (game == NULL) { return 0; }

    int is_full,  cleared_any = 0;

    // row, column
    for (int r = 19; r > -1; r--) {

        is_full = 1;

        for (int c = 0; c < 10; c++) {
            if (game->board.blocks[POINT(c, r, BOARDWIDTH)] == BLANK) {
                is_full = 0;
            }
        }

        if (is_full) {
            cleared_any = 1;

            for (int c = 0; c < 10; c++) {
                game->board.blocks[POINT(c, r, BOARDWIDTH)] = BLANK;
            }

            shift_rows_down(game, r);
        }
    }

    return cleared_any;
}
