/* src/rendering.h
 * created sun may 26 2024
 * by catroidvania
 */

#pragma once

#include "app.h"
#include "assets.h"
#include "block.h"
#include "board.h"
#include "pieces.h"


// rendering functions go here to avoid any circular dependancies
void clear_window(App* app);
void draw_board(Board* board, SDL_Surface* dest, int x, int y);
int draw_block(Block type, SDL_Surface* dest, int x, int y);
void draw_piece(Piece* piece, SDL_Surface* dest, int x, int y);
