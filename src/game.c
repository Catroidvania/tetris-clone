/* src/game.c 
 * created mon may 27 2024
 * by catroidvania
 */

#include "game.h"


const int gravity_delay_values[10] = {48, 43, 38, 33, 28, 23, 18, 13, 8, 6};


// initialises a game of tetris
int init_game(Game* game) {
    
    if (game == NULL) { return -1; }

    clear_board(&game->board);
    game->keystates = (Gamepad){0};

    // seed initial pieces
    game->current_piece = randomize_piece(NULL);
    game->next_piece = randomize_piece(&game->current_piece);

    game->level = 0;
    game->score = 0;
    game->lines_cleared = 0;
    game->last_gravity_frame = 0;

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
void move_current_piece(Game* game, int frame) {

    if (game == NULL) { return; }

    Piece test_piece;
    test_piece = game->current_piece; // for checking things

    if (game->keystates.button_left) {
        if (!game->keystates.das_left_counter || game->keystates.das_left_counter > 15) {

            test_piece.x -= 1;

            if (!piece_collision(&test_piece, &game->board)) { game->current_piece = test_piece; }

            if (game->keystates.das_left_counter > 15) {
                game->keystates.das_left_counter -= 6;
            }
        }
    } else if (game->keystates.button_right) {
        if (!game->keystates.das_right_counter || game->keystates.das_right_counter > 15) {

            test_piece.x += 1;

            if (!piece_collision(&test_piece, &game->board)) { game->current_piece = test_piece; }

            if (game->keystates.das_right_counter > 15) {
                game->keystates.das_right_counter -= 6;
            }
        }
    }

    test_piece = game->current_piece;
    if (game->keystates.button_up) {
        test_piece.y += 1;
        if (!piece_collision(&test_piece, &game->board)) { game->current_piece = test_piece; }
    } else if (game->keystates.button_down) {
        test_piece.y -= 1;
        if (!piece_collision(&test_piece, &game->board)) { game->current_piece = test_piece; }
    }

    test_piece = game->current_piece;
    if (game->keystates.button_b) {
        game->keystates.button_b = 0;
        rotate_piece_right(&game->current_piece, &game->board);
    } else if (game->keystates.button_a) {
       game->keystates.button_a = 0;
        rotate_piece_left(&game->current_piece, &game->board);
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


// clears and full rows and returns the number of lines cleared
int clear_lines(Game* game) {

    if (game == NULL) { return 0; }

    int is_full,  cleared = 0;

    // row, column
    for (int r = 19; r > -1; r--) {

        is_full = 1;

        for (int c = 0; c < 10; c++) {
            if (game->board.blocks[POINT(c, r, BOARDWIDTH)] == BLANK) {
                is_full = 0;
            }
        }

        if (is_full) {
            cleared += 1;

            for (int c = 0; c < 10; c++) {
                game->board.blocks[POINT(c, r, BOARDWIDTH)] = BLANK;
            }

            shift_rows_down(game, r);
        }
    }

    return cleared ;
}


// returns the frames between each levels gravity
// dont index into gravity_delay_values since it only handles levels up to 9
int gravity_delay(int level) {
    if (level < 0) {
        return gravity_delay_values[0];
    } else if (level < 10) {
        return gravity_delay_values[level];
    } else if (level < 13) {
        return 5;
    } else if (level < 16) {
        return 4;
    } else if (level < 19) {
        return 3;
    } else if (level < 29) {
        return 2;
    } else {
        return 1;
    }
}


// moves the piece down at level specific frame intervals
// will lock the piece if it cannot go down any further
void piece_gravity(Game* game, int frame) {

    if (game == NULL) { return; }
    // make sure we should actually gravity
    if (frame - game->last_gravity_frame < gravity_delay(game->level)) { return; }

    // remember this frame
    game->last_gravity_frame = frame;

    Piece test_piece = game->current_piece;
    test_piece.y -= 1;

    if (piece_collision(&test_piece, &game->board)) {
        // duplicateish of lock_current_piece but ah well
        solidify_piece(&game->current_piece, &game->board);
        swap_pieces(game);
    } else {
        game->current_piece = test_piece;
    }
}


// updates score, lines cleared, and level based on lines cleared
void update_score(Game* game, int lines) {
    
    if (game == NULL) { return; }
    if (!lines) { return; }

    game->lines_cleared += lines;
    // scoring is done using the resulting level
    if (game->lines_cleared > game->level * 10 + 10) { game->level += 1; } // level is not capped atm

    switch (lines) {
    case 1:
        game->score += 40 * (game->level + 1);
        break;
    case 2:
        game->score += 100 * (game->level + 1);
        break;
    case 3:
        game->score += 300 * (game->level + 1);
        break;
    default:
        game->score += 1200 * (game->level + 1);
        break;
    }

    printf("level: %d | lines: %d | score: %d\n", game->level, game->lines_cleared, game->score);
}