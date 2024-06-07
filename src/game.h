/* src/game.h
 * created mon may 27 2024
 * by catroidvania
 */

#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdlib.h>

#include "assets.h"
#include "board.h"
#include "gamepad.h"
#include "pieces.h"
#include "rng.h"

#define FRAMEDELAY 16 //16.6392673398 // supposed to be 60.0988 frames per second
                        // im not sure this is used anywhere


// a game of tetris
// designed after NES tetris, not the modern guidelines
typedef struct Game {

    Board board;    // 10x20 tetris board
    Gamepad keystates;
    Piece current_piece, next_piece;
    RNGState rng_state;
    int score, level, lines_cleared, soft_drop_bonus, garbage, cpu_should_think;

} Game;


// frame delays for levels 0 - 9, higher levels are handed by the function gravity_delay
extern const int gravity_delay_values[10];


int init_game(Game* game, int seed);
void swap_pieces(Game* game);
void move_current_piece(Game* game, int frame);
void shift_rows_down(Game* game, int row);
int clear_lines(Game* game);
int gravity_delay(int level);
int piece_gravity(Game* game, int frame);
int update_score(Game* game, int lines);
Piece randomize_piece(Game* game, Piece* piece);
void reset_game(Game* game, int new_seed);
void hard_drop(Game*);
int send_garbage(Game* from, Game* to, int lines);
void spawn_garbage(Game* game);
void move_bot_piece(Game* game, char* stupid_bozo_move_format);
