/* src/app.c 
 * created thu may 23 2024
 * by catroidvania
 */


#include "app.h"


int init_sdl() {
    // init sdl check
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("no sdl?? more likely than youd think!\n%s\n", SDL_GetError());
        return -1;
    }
    return 0;
}


void quit_sdl() {
    SDL_Quit();
}


// init game stuff
int init_game(Game* game) {

    // null pointer check
    if (game == NULL) { return -1; }

    game->window = NULL;
    game->window_surface = NULL;

    // create window
    game->window = SDL_CreateWindow(
                    "cetris (CursEd skull TetRomIno Stacking game)",
                    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                    WINDOWWIDTH, WINDOWHEIGHT,
                    SDL_WINDOW_SHOWN);

    // window init check
    if (game->window == NULL) {
        printf("alas no window...\n%s\n", SDL_GetError());
        return -1;
    }

    // decorate window
    game->window_surface = SDL_GetWindowSurface(game->window);
    SDL_FillRect(game->window_surface, NULL, SDL_MapRGB(game->window_surface->format, 255, 255, 255));

    clear_board(&game->board);
    
    return 0;
}


// frees allocated memory in game
void free_game(Game* game) {
    
    // null pointer check
    if (game == NULL) { return; }

    // this takes care of window_surface
    if (game->window != NULL) { SDL_DestroyWindow(game->window); }

    game->window = NULL;
    game->window_surface = NULL;
}
