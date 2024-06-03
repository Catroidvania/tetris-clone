/* src/app.c 
 * created thu may 23 2024
 * by catroidvania
 */


#include "app.h"


int init_sdl() {
    // init sdl check
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("no sdl?? more likely than youed think!\n%s\n", SDL_GetError());
        return -1;
    }

    return 0;
}


void quit_sdl() {
    SDL_Quit();
}


// create a window and inits a game
int init_app(App* app, int rng_seed) {

    // null pointer check
    if (app == NULL) { return -1; }

    // sdl window stuff
    app->window = NULL;
    app->window_surface = NULL;

    // create window
    app->window = SDL_CreateWindow(
                    "cetris (CursEd skull TetRomIno Stacking game)",
                    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                    WINDOWWIDTH, WINDOWHEIGHT,
                    SDL_WINDOW_SHOWN);

    // window init check
    if (app->window == NULL) {
        printf("alas no window...\n%s\n", SDL_GetError());
        return -1;
    }

    // decorate window
    app->window_surface = SDL_GetWindowSurface(app->window);

    // for starting future games that need the same rng
    app->rng_seed = rng_seed;
    init_game(&app->game, rng_seed);

    app->screen = MAINMENU;

    return 0;
}


// frees memory related to the window
void end_app(App* app) {
    
    // null pointer check
    if (app == NULL) { return; }

    // this takes care of window_surface
    if (app->window != NULL) { SDL_DestroyWindow(app->window); }

    app->window = NULL;
    app->window_surface = NULL;
}
