/* src/main.c 
 * created thu may 23 2024
 * by catroidvania
 */

#include "main.h"


// TODO move this stuff somewhere else for like  organisation lol
int main() {

    // declarations
    Game game;
    SDL_Event event;

    // init sdl check
    if (init_sdl() < 0) { return -1; }

    // create window
    if (init_game(&game) < 0) { return -1; }

    // primitive draw loop
    while (1) {
        // exit on close window button
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            break;
        }
        // refresh window
        SDL_UpdateWindowSurface(game.window);
    }

    // uninit sdl stuff
    free_game(&game);
    quit_sdl();

    return 0;
}
