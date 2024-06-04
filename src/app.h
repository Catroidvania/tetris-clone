/* src/app.h 
 * created thu may 23 2024
 * by catroidvania
 */

#pragma once

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"


#define WINDOWWIDTH 960
#define WINDOWHEIGHT 720


// what screen were on
typedef enum MenuState {
    MAINMENU,
    GAMESETTINGS,
    GAMECOUNTDOWN,
    GAMEPLAYING,
    GAMEOVER
} Screen;


// contains app stuff
typedef struct Application {
    
    // sdl stuff
    SDL_Window* window;
    SDL_Surface* window_surface;

    Screen screen;

    Game game, cpu_game;
    int rng_seed, vs_cpu, player_win;

} App;


int init_sdl();
void quit_sdl();
int init_app(App* app, int rng_seed);
void end_app(App* app);

