/* src/main.c 
 * created thu may 23 2024
 * by catroidvania
 */

#include "main.h"


int main() {

    // declarations
    Game game;
    SDL_Event event;

    // init sdl check
    if (init_sdl() < 0) { return -1; }

    // load textures
    if (load_assets() < 0) { return -1; }

    // create window
    if (init_game(&game) < 0) { return -1; }

    // TODO test stuff
    game.board.blocks[0] = L;
    game.board.blocks[4] = J;
    game.board.blocks[8] = S;
    game.board.blocks[12] = Z;
    game.board.blocks[16] = T;
    game.board.blocks[20] = I;
    game.board.blocks[24] = O;

    // TODO move this into its own thing in app.c
    // primitive draw loop
    while (1) {
        // exit on close window button
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            break;
        }
        // refresh window
        draw_board(&game.board, game.window_surface, 0, 0);
        SDL_UpdateWindowSurface(game.window);
    }

    // uninit sdl stuff
    free_game(&game);
    unload_assets();
    quit_sdl();

    return 0;
}
