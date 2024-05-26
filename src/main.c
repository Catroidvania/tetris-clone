/* src/main.c 
 * created thu may 23 2024
 * by catroidvania
 */

#include "main.h"


int main() {

    // declarations
    Game game;
    SDL_Event event;
    Piece piece, test_piece;

    // init sdl check
    if (init_sdl() < 0) { return -1; }

    // load textures
    if (load_assets() < 0) { return -1; }

    // create window
    if (init_game(&game) < 0) { return -1; }

    // TODO test stuff
    init_piece(&piece, T);
    piece.y -= 1;

    game.board.blocks[0] = L;
    game.board.blocks[4] = J;
    game.board.blocks[8] = S;
    game.board.blocks[12] = Z;
    game.board.blocks[16] = T;
    game.board.blocks[20] = I;
    game.board.blocks[24] = O;

    // TODO move this into its own thing in app.c or something
    // primitive draw loop
    while (1) {
        // exit on close window button
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            break;
        }

        if (event.type == SDL_KEYDOWN) {
            test_piece = piece; // for checking things
            switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                test_piece.x -= 1;
                if (!piece_collision(&test_piece, &game.board)) { piece = test_piece; }
                break;
            case SDLK_RIGHT:
                test_piece.x += 1;
                if (!piece_collision(&test_piece, &game.board)) { piece = test_piece; }
                break;

            // TODO for testing, remove later
            case SDLK_UP:
                test_piece.y += 1;
                if (!piece_collision(&test_piece, &game.board)) { piece = test_piece; }
                break;
            case SDLK_DOWN:
                test_piece.y -= 1;
                if (!piece_collision(&test_piece, &game.board)) { piece = test_piece; }
                break;

            case SDLK_x:
                rotate_piece_right(&piece, &game.board);
                break;
            case SDLK_z:
                rotate_piece_left(&piece, &game.board);
                break;
            }
        }

        // refresh window
        clear_window(&game);
        draw_board(&game.board, game.window_surface, 0, 0);
        draw_piece(&piece, game.window_surface, 0, 0);
        SDL_UpdateWindowSurface(game.window);
    }

    // uninit sdl stuff
    free_game(&game);
    unload_assets();
    quit_sdl();

    return 0;
}
