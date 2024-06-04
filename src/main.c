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

        // might as well keep randomising this thing lmao
        application.rng_seed = rand();

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
            application.game.keystates = RESET_GAMEPAD;
            application.player_win = 0;
        }

        if (application.vs_cpu && piece_collision(&application.cpu_game.current_piece, &application.cpu_game.board)) {
            application.screen = GAMEOVER;
            application.game.keystates = RESET_GAMEPAD;
            application.player_win = 1;
        }

        move_current_piece(&application.game, frame);
        piece_gravity(&application.game, frame);
        update_score(&application.game, clear_lines(&application.game));

        /*if (application.vs_cpu) {
            move_current_piece(&application.cpu_game, frame);
            piece_gravity(&application.cpu_game, frame);
            update_score(&application.cpu_game, clear_lines(&application.game));
        }*/

    } else if (application.screen == MAINMENU) {

        // main menu
        if (application.game.keystates.button_a) {
            if (MAIN_MENU_SELECTOR.current == &SOLO_BUTTON) {
                reset_game(&application.game, application.rng_seed);
                application.vs_cpu = 0;
                application.player_win = 0;
                application.screen = GAMECOUNTDOWN;
            } else if (MAIN_MENU_SELECTOR.current == &VS_CPU_BUTTON) {
                reset_game(&application.game, application.rng_seed);
                reset_game(&application.cpu_game, application.rng_seed);
                application.vs_cpu = 1;
                application.player_win = 0;
                application.screen = GAMECOUNTDOWN;
            } else if (MAIN_MENU_SELECTOR.current == &QUIT_BUTTON) {
                run = 0;
            }
        }
        update_selected(&MAIN_MENU_SELECTOR, &application.game.keystates);
        application.game.keystates = RESET_GAMEPAD;
    }

    // clear for drawing
    clear_window(&application);

    // draw game stuff
    if (application.screen == GAMEPLAYING || application.screen == GAMECOUNTDOWN || application.screen == GAMEOVER) {

        // draw stuff
        if (!application.vs_cpu) {
            draw_board(&application.game.board, application.window_surface, SPBOARDX, SPBOARDY);
            draw_stats(&application.game, application.window_surface, SPSTATSX, SPSTATSY);
            draw_preview(&application.game, application.window_surface, SPPREVIEWX, SPPREVIEWY);
            draw_ghost(&application.game, application.window_surface, SPBOARDX, SPBOARDY);
            draw_piece(&application.game.current_piece, application.window_surface, SPBOARDX, SPBOARDY);
        } else {
            // player
            draw_board(&application.game.board, application.window_surface, VSBOARDX, VSBOARDY);
            draw_stats(&application.game, application.window_surface, VSSTATSX, VSSTATSY);
            draw_preview(&application.game, application.window_surface, VSPREVIEWX, VSPREVIEWY);
            draw_ghost(&application.game, application.window_surface, VSBOARDX, VSBOARDY);
            draw_piece(&application.game.current_piece, application.window_surface, VSBOARDX, VSBOARDY);

            // cpu
            draw_board(&application.cpu_game.board, application.window_surface, CPUBOARDX, CPUBOARDY);
            draw_piece(&application.cpu_game.current_piece, application.window_surface, CPUBOARDX, CPUBOARDY);
        }
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
            application.game.keystates.das_left_counter = 0;
            application.game.keystates.das_right_counter = 0;
            application.player_win = 0;
        } else {
            if (!application.vs_cpu) {
                draw_image(BIG_1_TEXTURE + countdown_counter, application.window_surface, SPBOARDX, SPBOARDY);
            } else {
                draw_image(BIG_1_TEXTURE + countdown_counter, application.window_surface, VSBOARDX, VSBOARDY);
                draw_image(BIG_1_TEXTURE + countdown_counter, application.window_surface, CPUBOARDX, CPUBOARDY);
            }
        }
    // game over graphic
    } else if (application.screen == GAMEOVER) {
        if (!application.vs_cpu) {
            draw_image(GAME_OVER_TEXTURE, application.window_surface, SPBOARDX, SPBOARDY);
        } else {
            if (!application.player_win) {
                draw_image(GAME_OVER_TEXTURE, application.window_surface, VSBOARDX, VSBOARDY);
            } else { 
                draw_image(GAME_OVER_TEXTURE, application.window_surface, CPUBOARDX, CPUBOARDY);
            }
        }

        if (application.game.keystates.button_a || application.game.keystates.button_b) {
            application.screen = MAINMENU;
            application.game.keystates = RESET_GAMEPAD;
        }
    } else if (application.screen == MAINMENU) {
        draw_image(SPLASH_TEXTURE, application.window_surface, 0, 0);
        draw_selector(&MAIN_MENU_SELECTOR, application.window_surface, 170, 170);
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
