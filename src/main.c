/* src/main.c 
 * created thu may 23 2024
 * by catroidvania
 */

#include "main.h"


// declarations
App application;
SDL_Event event;

char *botmove;

SDL_Thread* bot_t;
int thread_open = 0, cpu_think_cooldown = 0, cpu_move_cooldown = 0;


int bot_thread(void* data) {
    update_bot(&application);
    botmove = getBot(application.bitboard, application.bot_next);
    thread_open = 0;
    SDL_LockMutex(can_move_m);
    application.cpu_game.cpu_should_move = 1;
    SDL_UnlockMutex(can_move_m);
    //printf("%c %d %d %d\n", botmove[0], botmove[1], botmove[2], botmove[3]);
    return 1;
}


int main() {

    // more declarations
    int run = 1;
    int start_ms, end_ms, dt;
    int frame = 0, countdown_frame = 0, countdown_counter = 2;
    int junk = 0, confirm = 0;

    srand(time(NULL));

    // init sdl check
    if (init_sdl() < 0) { return -1; }

    // load textures
    if (load_assets() < 0) { return -1; }

    // create window
    if (init_app(&application, rand()) < 0) { return -1; }

    can_move_m = SDL_CreateMutex();
    SDL_UnlockMutex(can_move_m);

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
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_SPACE && !event.key.repeat) {
                confirm = 1;
            } else {
                confirm = 0;
            }
        }

        // handle keypresses
        update_gamepad(&event, &application.game.keystates);

        if (application.local_2p) {
            update_gamepad(&event, &application.cpu_game.keystates);
        }

    // update game stuff
    if (application.screen == GAMEPLAYING) {

        if (((!application.local_2p && application.vs_cpu) || application.bot_sp) && application.cpu_game.cpu_should_think) {
            if (cpu_think_cooldown) {
                cpu_think_cooldown--;
            } else {
                application.cpu_game.cpu_should_think = 0;
                thread_open = 1;
                cpu_think_cooldown = CPUTHINKDELAY;
                bot_t = SDL_CreateThread(bot_thread, "bot_t", NULL);
            }
        }
        
        // gameover check
        if (piece_collision(&application.game.current_piece, &application.game.board) && !application.bot_sp) {
            application.screen = GAMEOVER;
            if (application.local_2p) {
                application.game.keystates = LOCAL1_GAMEPAD;
                application.cpu_game.keystates = LOCAL2_GAMEPAD;
            } else {
                application.game.keystates = RESET_GAMEPAD;
            }
            application.player_win = 0;
            Mix_PlayChannel(-1, SOUNDS[GAME_OVER_SFX], 0);
        }

        if ((application.vs_cpu || application.bot_sp) && piece_collision(&application.cpu_game.current_piece, &application.cpu_game.board)) {
            confirm = 0;
            application.screen = GAMEOVER;
            if (application.local_2p) {
                application.game.keystates = LOCAL1_GAMEPAD;
                application.cpu_game.keystates = LOCAL2_GAMEPAD;
            } else {
                application.game.keystates = RESET_GAMEPAD;
            }
            application.player_win = 1;
            Mix_PlayChannel(-1, SOUNDS[GAME_OVER_SFX], 0);
        }

        move_current_piece(&application.game, frame);
        if (piece_gravity(&application.game, frame)) {
            Mix_PlayChannel(-1, SOUNDS[SOLIDIFY_SFX], 0);
        }
        junk = clear_lines(&application.game);

        if (update_score(&application.game, junk) && !application.local_2p) {
            Mix_PlayChannel(-1, SOUNDS[LEVEL_UP_SFX], 0);
        } else if (junk) {
            Mix_PlayChannel(-1, SOUNDS[LINE_CLEAR_SFX], 0);
        }

        if (application.vs_cpu || application.bot_sp) {
            send_garbage(&application.game, &application.cpu_game, junk-1);
            
            if (!application.local_2p) {
                SDL_LockMutex(can_move_m);
                application.cpu_game.keystates = RESET_GAMEPAD;
                if (application.cpu_game.cpu_should_move) {
                    if (cpu_move_cooldown) {
                        cpu_move_cooldown--;
                    } else {
                        cpu_move_cooldown = CPUMOVEDELAY;
                        move_bot_piece(&application.cpu_game, botmove);
                    }
                }
                SDL_UnlockMutex(can_move_m);
            }

            move_current_piece(&application.cpu_game, frame);
            if (piece_gravity(&application.cpu_game, frame)) {
                Mix_PlayChannel(-1, SOUNDS[SOLIDIFY_SFX], 0);
            }

            junk = clear_lines(&application.cpu_game);
            update_score(&application.cpu_game, junk);

            send_garbage(&application.cpu_game, &application.game, junk-1);

             if (junk) {
                Mix_PlayChannel(-1, SOUNDS[LINE_CLEAR_SFX], 0);
            }
        }

    // you can really tell how poorly planned this whole was since main menu code is smack dab in the middle
    } else if (application.screen == MAINMENU) {
        // main menu
        if (confirm) {
            confirm = 0;
            if (MAIN_MENU_SELECTOR.current == &SOLO_BUTTON) {
                reset_game(&application.game, application.rng_seed);
                application.vs_cpu = 0;
                application.player_win = 0;
                application.screen = GAMECOUNTDOWN;
                cpu_think_cooldown = 0;
                cpu_move_cooldown = 0;
                if (SDL_GetModState()) {
                    application.bot_sp = 1;
                    reset_game(&application.cpu_game, application.rng_seed);
                } else {
                    application.bot_sp = 0;
                }

                Mix_PlayChannel(-1, SOUNDS[COUNTDOWN23_SFX], 0);
            } else if (MAIN_MENU_SELECTOR.current == &VS_CPU_BUTTON) {
                reset_game(&application.game, application.rng_seed);
                reset_game(&application.cpu_game, application.rng_seed);
                application.vs_cpu = 1;
                application.bot_sp = 0;
                application.player_win = 0;
                application.screen = GAMECOUNTDOWN;
                cpu_think_cooldown = 0;
                cpu_move_cooldown = 0;
                SDL_UnlockMutex(can_move_m);
                if (SDL_GetModState()) {
                    application.local_2p = 1;
                    application.game.keystates = LOCAL1_GAMEPAD;
                    application.cpu_game.keystates = LOCAL2_GAMEPAD;
                } else {
                    application.local_2p = 0;
                }
                Mix_PlayChannel(-1, SOUNDS[COUNTDOWN23_SFX], 0);
            } else if (MAIN_MENU_SELECTOR.current == &QUIT_BUTTON) {
                run = 0;
                Mix_PlayChannel(-1, SOUNDS[SELECT_SFX], 0);
            }
        }

        update_selected(&MAIN_MENU_SELECTOR, &application.game.keystates);

        if (application.local_2p) {
            application.game.keystates = LOCAL1_GAMEPAD;
            application.cpu_game.keystates = LOCAL2_GAMEPAD;
        } else {
            application.game.keystates = RESET_GAMEPAD;
        }
    } else if (application.screen == GAMEOVER) {
        if (confirm) {
            confirm = 0;
            application.screen = MAINMENU;
            application.game.keystates = RESET_GAMEPAD;
            application.local_2p = 0;
            Mix_PlayChannel(-1, SOUNDS[SELECT_SFX], 0);
        }
    }

    /*if (thread_open) {
        SDL_WaitThread(bot_t, NULL);
        thread_open = 0;
    }*/

    // clear for drawing
    clear_window(&application);

    // draw game stuff
    if (application.screen == GAMEPLAYING || application.screen == GAMECOUNTDOWN || application.screen == GAMEOVER) {

        // draw stuff
        if (!application.vs_cpu) {
            Game* current_game;
            if (!application.bot_sp) {
                current_game = &application.game;
            } else {
                current_game = &application.cpu_game;
            }

            draw_incoming(current_game, application.window_surface, SPBOARDX, SPBOARDY);
            draw_board(&current_game->board, application.window_surface, SPBOARDX, SPBOARDY);
            draw_stats(current_game, application.window_surface, SPSTATSX, SPSTATSY);
            draw_preview(current_game, application.window_surface, SPPREVIEWX, SPPREVIEWY);
            draw_ghost(current_game, application.window_surface, SPBOARDX, SPBOARDY);
            draw_piece(&current_game->current_piece, application.window_surface, SPBOARDX, SPBOARDY);

        } else {
            // player
            draw_incoming(&application.game, application.window_surface, VSBOARDX, VSBOARDY);
            draw_board(&application.game.board, application.window_surface, VSBOARDX, VSBOARDY);
            if (!application.local_2p) {
            draw_stats(&application.game, application.window_surface, VSSTATSX, VSSTATSY);
            }
            draw_preview(&application.game, application.window_surface, VSPREVIEWX, VSPREVIEWY);
            draw_ghost(&application.game, application.window_surface, VSBOARDX, VSBOARDY);
            draw_piece(&application.game.current_piece, application.window_surface, VSBOARDX, VSBOARDY);

            // cpu
            draw_incoming(&application.cpu_game, application.window_surface, CPUBOARDX, CPUBOARDY);
            draw_board(&application.cpu_game.board, application.window_surface, CPUBOARDX, CPUBOARDY);
            if (application.local_2p) {
                draw_preview(&application.cpu_game, application.window_surface, CPUPREVIEWX, CPUPREVIEWY);
                draw_ghost(&application.cpu_game, application.window_surface, CPUBOARDX, CPUBOARDY);
            }
            draw_piece(&application.cpu_game.current_piece, application.window_surface, CPUBOARDX, CPUBOARDY);
        }
    }


    // if doing the little countdown we need to draw these on top of everything else 
    if (application.screen == GAMECOUNTDOWN) {
        if (!countdown_frame) {
            countdown_frame = frame;
        } else if (frame >= countdown_frame + 60) {
            if (countdown_counter == 0) {
                Mix_PlayChannel(-1, SOUNDS[COUNTDOWN1_SFX], 0);
            } else {
                Mix_PlayChannel(-1, SOUNDS[COUNTDOWN23_SFX], 0);
            }
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
                draw_image(GAME_WIN_TEXTURE, application.window_surface, CPUBOARDX, CPUBOARDY);
            } else {
                draw_image(GAME_WIN_TEXTURE, application.window_surface, VSBOARDX, VSBOARDY);
                draw_image(GAME_OVER_TEXTURE, application.window_surface, CPUBOARDX, CPUBOARDY);
            }
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
    SDL_DestroyMutex(can_move_m);
    end_app(&application);
    unload_assets();
    quit_sdl();

    return 0;
}
