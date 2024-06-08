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

    // init image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("no sdl image??? its not looking good...\n%s\n", IMG_GetError());
        return -1;
    }

    // default audio settings
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("no sdl mixer! aw this sounds baddd\n%s\n", Mix_GetError());
        return -1;
    }

    return 0;
}


void quit_sdl() {
    IMG_Quit();
    Mix_Quit();
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
    init_game(&app->cpu_game, rng_seed);
    
    initBoard(&app->bitboard);

    app->screen = MAINMENU;
    app->vs_cpu = 0;
    app->player_win = 0;
    app->local_2p = 0;
    app->bot_sp = 0;

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


// updates the bitboard and next pieces
void update_bot(App* app) {
    
    if (app == NULL) { return; }

    for (int r = 0; r < BOARDHEIGHT; r++) {
        for (int c = 0; c < BOARDWIDTH; c++) {
            setBit(app->bitboard.board, c, r, app->cpu_game.board.blocks[POINT(c, r, BOARDWIDTH)] != BLANK);
        }
    }

    app->bot_next[0] = app->cpu_game.current_piece.type;
    app->bot_next[1] = app->cpu_game.next_piece.type;
}
