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
    int frame = 0, countdown_frame = 0, countdown_counter = 2;

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

        // handle keypresses
        update_gamepad(&event, &application.game.keystates);

    // update game stuff
    if (application.screen == GAMEPLAYING) {
        
        // gameover check
        if (piece_collision(&application.game.current_piece, &application.game.board)) {
            application.screen = GAMEOVER;
            // i should not that this does not set all elements to 0, it just does that 
            application.game.keystates = RESET_GAMEPAD;
        }

        move_current_piece(&application.game, frame);
        piece_gravity(&application.game, frame);
        update_score(&application.game, clear_lines(&application.game));
    }

    // draw game stuff
    if (application.screen == GAMEPLAYING || application.screen == GAMECOUNTDOWN || application.screen == GAMEOVER) {
        // clear for drawing
        clear_window(&application);
        
        // draw stuff
        draw_board(&application.game.board, application.window_surface, SPBOARDX, SPBOARDY);
        draw_stats(&application.game, application.window_surface, SPSTATSX, SPSTATSY);
        draw_preview(&application.game, application.window_surface, SPPREVIEWX, SPPREVIEWY);
        draw_ghost(&application.game, application.window_surface, SPBOARDX, SPBOARDY);
        draw_piece(&application.game.current_piece, application.window_surface, SPBOARDX, SPBOARDY);
    }


    // if doing the little countdown we need to draw these on top of everything else 
    if (application.screen == GAMECOUNTDOWN) {
        if (!countdown_frame) {
            countdown_frame = frame;
        } else if (frame >= countdown_frame + 60) {
            countdown_counter--;
            countdown_frame = frame;
        }

        if (countdown_counter < 0) {
            application.screen = GAMEPLAYING;
            countdown_frame = 0;
            countdown_counter = 2;
            application.game.keystates = RESET_GAMEPAD;
        } else {
            draw_image(BIG_1_TEXTURE +countdown_counter, application.window_surface, SPBOARDX, SPBOARDY);
        }
    // game over graphic
    } else if (application.screen == GAMEOVER) {
        draw_image(GAME_OVER_TEXTURE, application.window_surface, SPBOARDX, SPBOARDY);

        if (application.game.keystates.button_a || application.game.keystates.button_b) {
            reset_game(&application.game);
            application.screen = GAMECOUNTDOWN;
        }
    }

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
