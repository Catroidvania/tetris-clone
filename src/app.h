/* src/app.h 
 * created thu may 23 2024
 * by catroidvania
 */

#pragma once

#include <SDL.h>
#include <stdio.h>
#include "board.h"

#define WINDOWWIDTH 320
#define WINDOWHEIGHT 640


// contains app stuff
typedef struct Application {
    
    // sdl stuff
    SDL_Window* window;
    SDL_Surface* window_surface;

    // see board.h
    Board board;

} Game;


int init_sdl();
void quit_sdl();
int init_game(Game* game);
void free_game(Game* game);
