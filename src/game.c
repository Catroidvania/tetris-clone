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

    // unseeded rng, call seed_rng later
    game->rng_state = (RNGState){0};

    // initialise starting pieces
    // moved piece generation into seed_rng() so the first 2 pieces can be randomised
    /*game->current_piece = randomize_piece(game, NULL); 
    game->next_piece = randomize_piece(game, &game->current_piece);*/

    game->level = 0;
    game->score = 0;
    game->lines_cleared = 0;
    game->soft_drop_bonus = 0;

    return 0;
}


// changes the current to the next piece and generates a new next piece
void swap_pieces(Game* game) {
    
    if (game == NULL) { return; }

    game->current_piece = game->next_piece;
    game->next_piece = randomize_piece(game, &game->current_piece);
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
    /*if (game->keystates.button_up) {
        test_piece.y += 1;
        if (!piece_collision(&test_piece, &game->board)) { game->current_piece = test_piece; }
    } else */
    if (game->keystates.button_down &&
                // only soft drop in between gravity ticks
                !(frame % 2) && (frame % gravity_delay(game->level))) {
        test_piece.y -= 1;
        if (!piece_collision(&test_piece, &game->board)) {
            game->current_piece = test_piece;
            game->soft_drop_bonus += 1;
        }
    } else if (!game->keystates.button_down && game->soft_drop_bonus) {
        game->score += game->soft_drop_bonus;
        game->soft_drop_bonus = 0;
        printf("level: %d | lines: %d | score: %d\n", game->level, game->lines_cleared, game->score);
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
    // and we are not soft droppping
    if (frame % gravity_delay(game->level)) { return; }

    Piece test_piece = game->current_piece;
    test_piece.y -= 1;

    if (piece_collision(&test_piece, &game->board)) {
        // duplicateish of lock_current_piece but ah well
        solidify_piece(&game->current_piece, &game->board);
        swap_pieces(game);
        // stop soft dropping when next piece spawns
        game->keystates.button_down = 0;
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


// randomises the provided piece
// if piece is not NULL, will try and avoid generating the same piece as the current one
Piece randomize_piece(Game* game, Piece* piece) {

    Piece new_piece;
    
    if (piece == NULL) {
        switch (rng_next(&game->rng_state) % 7) {
        case 0:
            new_piece = I_PIECE;
            break;
        case 1:
            new_piece = O_PIECE;
            break;
        case 2:
            new_piece = L_PIECE;
            break;
        case 3:
            new_piece = J_PIECE;
            break;
        case 4:
            new_piece = S_PIECE;
            break;
        case 5:
            new_piece = T_PIECE;
            break;
        case 6:
            new_piece = Z_PIECE;
            break;
        }
    } else {
 
        // one higher to emulate the NES tetris randomiser
        switch (rng_next(&game->rng_state) % 8) {
        case 0:
            new_piece = I_PIECE;
            break;
        case 1:
            new_piece = O_PIECE;
            break;
        case 2:
            new_piece = L_PIECE;
            break;
        case 3:
            new_piece = J_PIECE;
            break;
        case 4:
            new_piece = S_PIECE;
            break;
        case 5:
            new_piece = T_PIECE;
            break;
        case 6:
            new_piece = Z_PIECE;
            break;
        case 7:
            new_piece = *piece;
            break;
        }

        if (new_piece.type == piece->type) {
            // the compiler can figure this crap out lmao
            switch (rng_next(&game->rng_state) % 7) {
            case 0:
                new_piece = I_PIECE;
                break;
            case 1:
                new_piece = O_PIECE;
                break;
            case 2:
                new_piece = L_PIECE;
                break;
            case 3:
                new_piece = J_PIECE;
                break;
            case 4:
                new_piece = S_PIECE;
                break;
            case 5:
                new_piece = T_PIECE;
                break;
            case 6:
                new_piece = Z_PIECE;
                break;
            }
        }
    }

    return new_piece;
}


// seeds the game rng
// called seperately since init_app calls init_game atm lmao
void seed_rng(Game* game, int seed) {
    
    if (game == NULL) { return; };
    game->rng_state = (RNGState){seed};
    rng_next(&game->rng_state);

    // this is really terrible organisation!
    game->current_piece = randomize_piece(game, NULL); 
    game->next_piece = randomize_piece(game, &game->current_piece);
}
