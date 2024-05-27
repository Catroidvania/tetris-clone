/* src/main.c 
 * created thu may 23 2024
 * by catroidvania
 */

#include "main.h"


int main() {

    // declarations
    App application;
    SDL_Event event;
    Piece test_piece;

    // init sdl check
    if (init_sdl() < 0) { return -1; }

    // load textures
    if (load_assets() < 0) { return -1; }

    // create window
    if (init_app(&application) < 0) { return -1; }

    // TODO move this into its own thing in app.c or something
    // primitive draw loop
    while (1) {
        // exit on close window button
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            break;
        }

        if (event.type == SDL_KEYDOWN) {
            test_piece = application.game.current_piece; // for checking things
            switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                test_piece.x -= 1;
                if (!piece_collision(&test_piece, &application.game.board)) { application.game.current_piece = test_piece; }
                break;
            case SDLK_RIGHT:
                test_piece.x += 1;
                if (!piece_collision(&test_piece, &application.game.board)) { application.game.current_piece = test_piece; }
                break;

            // TODO for testing, remove later
            case SDLK_UP:
                test_piece.y += 1;
                if (!piece_collision(&test_piece, &application.game.board)) { application.game.current_piece = test_piece; }
                break;
            case SDLK_DOWN:
                test_piece.y -= 1;
                if (!piece_collision(&test_piece, &application.game.board)) { application.game.current_piece = test_piece; }
                break;
            /*
            case SDLK_1:
                piece = I_PIECE;
                break;
            case SDLK_2:
                piece = O_PIECE;
                break;
            case SDLK_3:
                piece = J_PIECE;
                break;
            case SDLK_4:
                piece = L_PIECE;
                break;
            case SDLK_5:
                piece = S_PIECE;
                break;
            case SDLK_6:
                piece = T_PIECE;
                break;
            case SDLK_7:
                piece = Z_PIECE;
                break;
            */

            case SDLK_x:
                rotate_piece_right(&application.game.current_piece, &application.game.board);
                break;
            case SDLK_z:
                rotate_piece_left(&application.game.current_piece, &application.game.board);
                break;
            }
        }


        // piece clearing test
        test_piece = application.game.current_piece;
        test_piece.y -= 1;
        if (piece_collision(&test_piece, &application.game.board)) {
            solidify_piece(&application.game.current_piece, &application.game.board);

            if (piece_collision(&application.game.next_piece, &application.game.board)) {
                clear_board(&application.game.board);
            }

            swap_pieces(&application.game);
        }

        // refresh window
        clear_window(&application);
        draw_board(&application.game.board, application.window_surface, 0, 0);
        draw_piece(&application.game.current_piece, application.window_surface, 0, 0);
        SDL_UpdateWindowSurface(application.window);
    }

    // uninit sdl stuff
    end_app(&application);
    unload_assets();
    quit_sdl();

    return 0;
}
