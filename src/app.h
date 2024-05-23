/* src/app.h 
 * created thu may 23 2024
 * by catroidvania
 */

#pragma once

#include <SDL.h>
#include <stdio.h>

#define WINWIDTH 800
#define WINHEIGHT 600


// contains app stuff
typedef struct Application {
    
    // sdl stuff
    SDL_Window* window;
    SDL_Surface* window_surface;

    // standard tetris board, 10x20 visible area with a 20 row buffer above it
    // blocks spawn on rows 21 and 22
    Block blocks[400];

} Game;


int init_sdl();
void quit_sdl();
int init_game(Game* game);
void free_game(Game* game);
