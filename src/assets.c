/* src/assets.c 
 * created sat may 25 2024
 * by catroidvania
 */

#include "assets.h"


// im starting to think i shouldve used some kind of map or texture atlas for this lmao
SDL_Surface *T_TEXTURE = NULL,
            *I_TEXTURE = NULL,
            *O_TEXTURE = NULL,
            *L_TEXTURE = NULL,
            *J_TEXTURE = NULL,
            *S_TEXTURE = NULL,
            *Z_TEXTURE = NULL,
            *BLANK_TEXTURE = NULL,
            *GHOST_TEXTURE = NULL,
            *WINDOW_BG_TEXTURE = NULL,
            *BOARD_BG_TEXTURE = NULL, 
            *PREVIEW_FRAME_TEXTURE = NULL,
            *SCORE_TEXTURE = NULL, 
            *LEVEL_TEXTURE = NULL,
            *LINES_TEXTURE = NULL,
            *GAME_OVER_TEXTURE = NULL,
            *SPLASH_TEXTURE = NULL;

SDL_Surface* NUMBER_TEXTURE[10] = {NULL};
SDL_Surface* BIG_NUMBER_TEXTURE[3] = {NULL};
SDL_Surface* SOLO_BTN_TEXTURE[2] = {NULL};
SDL_Surface* VS_CPU_BTN_TEXTURE[2] = {NULL};
SDL_Surface* QUIT_BTN_TEXTURE[2] = {NULL};



// load png function with error checking
int load_png(SDL_Surface** surface, char* filepath) {

    SDL_RWops* file = NULL;

    file = SDL_RWFromFile(filepath, "r");

    if (file == NULL) {
        printf("could not load %s!\n%s\n", filepath, SDL_GetError());
        return -1;
    }
    
    *surface = IMG_LoadPNG_RW(file);

    return 0;
}


// init function for loading all textures
// TODO remember to add the corrosponding free to unload_assets() when u add a new texture
// there is mort certainly a better way to do this lmao
// in hindsight i shouldve just compared the output pf load_png but i did not think i was gonna be loading so many textures
int load_assets() {

    //SDL_RWops* file = NULL;
    int all_success = 0;

    load_png(&L_TEXTURE, "assets/l.png");
    if (L_TEXTURE == NULL) { all_success = -1; }

    load_png(&J_TEXTURE, "assets/j.png");
    if (J_TEXTURE == NULL) { all_success = -1; }

    load_png(&Z_TEXTURE, "assets/z.png");
    if (Z_TEXTURE == NULL) { all_success = -1; }

    load_png(&S_TEXTURE, "assets/s.png");
    if (S_TEXTURE == NULL) { all_success = -1; }

    load_png(&O_TEXTURE, "assets/o.png");
    if (O_TEXTURE == NULL) { all_success = -1; }

    load_png(&T_TEXTURE, "assets/t.png");
    if (T_TEXTURE == NULL) { all_success = -1; }

    load_png(&I_TEXTURE, "assets/i.png");
    if (I_TEXTURE == NULL) { all_success = -1; }

    load_png(&BLANK_TEXTURE, "assets/empty.png");
    if (BLANK_TEXTURE == NULL) { all_success = -1; }

    load_png(&GHOST_TEXTURE, "assets/ghost.png");
    if (GHOST_TEXTURE == NULL) { all_success = -1; }

    load_png(&WINDOW_BG_TEXTURE, "assets/bg.png");
    if (WINDOW_BG_TEXTURE == NULL) { all_success = -1; }

    load_png(&BOARD_BG_TEXTURE, "assets/board_bg.png");
    if (BOARD_BG_TEXTURE == NULL) { all_success = -1; }

    load_png(&PREVIEW_FRAME_TEXTURE, "assets/preview.png");
    if (PREVIEW_FRAME_TEXTURE == NULL) { all_success = -1; }

    load_png(&SCORE_TEXTURE, "assets/score.png");
    if (SCORE_TEXTURE == NULL) { all_success = -1; }

    load_png(&LEVEL_TEXTURE, "assets/level.png");
    if (LEVEL_TEXTURE == NULL) { all_success = -1; }

    load_png(&LINES_TEXTURE, "assets/lines.png");
    if (LINES_TEXTURE == NULL) { all_success = -1; }

    load_png(&GAME_OVER_TEXTURE, "assets/game_over.png");
    if (GAME_OVER_TEXTURE == NULL) { all_success = -1; }

    load_png(&BIG_NUMBER_TEXTURE[0], "assets/big_1.png");
    if (BIG_NUMBER_TEXTURE[0] == NULL) { all_success = -1; }

    load_png(&BIG_NUMBER_TEXTURE[1], "assets/big_2.png");
    if (BIG_NUMBER_TEXTURE[1] == NULL) { all_success = -1; }

    load_png(&BIG_NUMBER_TEXTURE[2], "assets/big_3.png");
    if (BIG_NUMBER_TEXTURE[2] == NULL) { all_success = -1; }

    load_png(&SPLASH_TEXTURE, "assets/splash.png");
    if (SPLASH_TEXTURE == NULL) { all_success = -1; }

    load_png(&SOLO_BTN_TEXTURE[0], "assets/solo_off.png");
    if (SOLO_BTN_TEXTURE[0] == NULL) { all_success = -1; }

    load_png(&SOLO_BTN_TEXTURE[1], "assets/solo_on.png");
    if (SOLO_BTN_TEXTURE[1] == NULL) { all_success = -1; }

    load_png(&VS_CPU_BTN_TEXTURE[0], "assets/vs_cpu_off.png");
    if (VS_CPU_BTN_TEXTURE[0] == NULL) { all_success = -1; }

    load_png(&VS_CPU_BTN_TEXTURE[1], "assets/vs_cpu_on.png");
    if (VS_CPU_BTN_TEXTURE[1] == NULL) { all_success = -1; }

    load_png(&QUIT_BTN_TEXTURE[0], "assets/quit_off.png");
    if (QUIT_BTN_TEXTURE[0] == NULL) { all_success = -1; }

    load_png(&QUIT_BTN_TEXTURE[1], "assets/quit_on.png");
    if (QUIT_BTN_TEXTURE[1] == NULL) { all_success = -1; }

    // load number textures
    char fp[13] = {'a', 's', 's', 'e', 't', 's', '/', '0', '.', 'p', 'n', 'g', '\0'}; // 7, 48
    for (int i = 0; i < 10; i++) {
        fp[7] = i+48;
        load_png(&NUMBER_TEXTURE[i], fp);
        if (NUMBER_TEXTURE[i] == NULL) { all_success = -1; }
    }

    return all_success;
}


// function to unload all assets
void unload_assets() {
    SDL_FreeSurface(L_TEXTURE);
    SDL_FreeSurface(J_TEXTURE);
    SDL_FreeSurface(Z_TEXTURE);
    SDL_FreeSurface(S_TEXTURE);
    SDL_FreeSurface(O_TEXTURE);
    SDL_FreeSurface(T_TEXTURE);
    SDL_FreeSurface(I_TEXTURE);
    SDL_FreeSurface(BLANK_TEXTURE);
    SDL_FreeSurface(GHOST_TEXTURE);
    SDL_FreeSurface(WINDOW_BG_TEXTURE);
    SDL_FreeSurface(BOARD_BG_TEXTURE);
    SDL_FreeSurface(PREVIEW_FRAME_TEXTURE);
    SDL_FreeSurface(SCORE_TEXTURE);
    SDL_FreeSurface(LEVEL_TEXTURE);
    SDL_FreeSurface(LINES_TEXTURE);
    SDL_FreeSurface(GAME_OVER_TEXTURE);
    SDL_FreeSurface(SPLASH_TEXTURE);

    for (int i = 0; i < 10; i++) {
        SDL_FreeSurface(NUMBER_TEXTURE[i]);
    }

    for (int i = 0; i < 3; i++) {
        SDL_FreeSurface(BIG_NUMBER_TEXTURE[i]);
    }

    for (int i = 0; i < 2; i++) {
        SDL_FreeSurface(SOLO_BTN_TEXTURE[i]);
        SDL_FreeSurface(VS_CPU_BTN_TEXTURE[i]);
        SDL_FreeSurface(QUIT_BTN_TEXTURE[i]);
    }

}
