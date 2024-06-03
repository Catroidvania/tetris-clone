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

// singleplayer rendering coordinates
#define SPBOARDX 300
#define SPBOARDY 20

#define SPPREVIEWX 676
#define SPPREVIEWY 20

#define SPSTATSX 676
#define SPSTATSY 220

// rendering functions go here to avoid any circular dependancies
void clear_window(App* app);
void draw_board(Board* board, SDL_Surface* dest, int x, int y);
int draw_block(Block type, SDL_Surface* dest, int x, int y);
void draw_piece(Piece* piece, SDL_Surface* dest, int x, int y);
void draw_ghost(Game* game, SDL_Surface* dest, int x, int y);
void draw_preview(Game* game, SDL_Surface* dest, int x, int y);
void draw_stats(Game* game, SDL_Surface* dest, int x, int y);
void draw_number(int number, int places, SDL_Surface* dest, int x, int y);
int draw_image(Texture index, SDL_Surface* dest, int x, int y);
