/* src/main.c 
 * created thu may 23 2024
 * by catroidvania
 */

#include "main.h"


int main() {

    // declarations
    App application;
    SDL_Event event;

    int run = 1;
    int start_ms, end_ms, dt;
    int frame = 0;

    srand(time(NULL));

    // init sdl check
    if (init_sdl() < 0) { return -1; }

    // load textures
    if (load_assets() < 0) { return -1; }

    // create window
    if (init_app(&application, rand()) < 0) { return -1; }

    // game loop
    while (run) {
        
        // get time at start of frame
        start_ms = SDL_GetTicks64();

        // get window events
        SDL_PollEvent(&event);

        // exit on close window button
        if (event.type == SDL_QUIT) {
            run = 0;
        }

        update_gamepad(&event, &application.game.keystates);
        move_current_piece(&application.game, frame);
        piece_gravity(&application.game, frame);
        update_score(&application.game, clear_lines(&application.game));
        
        // TODO wipes the board if we cannot spawn a new piece
        if (piece_collision(&application.game.next_piece, &application.game.board)) {
            clear_board(&application.game.board);
            application.game.level = 0;
            application.game.lines_cleared = 0;
            application.game.score = 0;
        }

        // clear for drawing
        clear_window(&application);
        
        // draw stuff
        draw_board(&application.game.board, application.window_surface, 0, 0);
        draw_piece(&application.game.current_piece, application.window_surface, 0, 0);

        // refresh window
        SDL_UpdateWindowSurface(application.window);

        // get time at end of frame
        end_ms = SDL_GetTicks64();
        dt = end_ms - start_ms;
        
        // wait for next frame so we run at around 60 fps
        // in reality precision is bad so it alternates between 58.8 and 62.5 fps
        if (dt <= FRAMEDELAY) {
            SDL_Delay(FRAMEDELAY - dt);
        }

        frame += 1;
    }

    // uninit sdl stuff
    end_app(&application);
    unload_assets();
    quit_sdl();

    return 0;
}
