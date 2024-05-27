/* src/app.h 
 * created thu may 23 2024
 * by catroidvania
 */

#pragma once

#include <SDL.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "board.h"
#include "pieces.h"


#define WINDOWWIDTH 320
#define WINDOWHEIGHT 640


// a game of tetris
// designed after NES tetris, not the modern guidelines
typedef struct Game {

    Board board;    // 10x20 tetris board
    Piece current_piece, next_piece;
    int score, level;

} Game;


// contains app stuff
typedef struct Application {
    
    // sdl stuff
    SDL_Window* window;
    SDL_Surface* window_surface;

    Game game;

} App;


int init_sdl();
void quit_sdl();
int init_app(App* app);
void end_app(App* app);
int init_game(Game* game);
void swap_pieces(Game* game);
