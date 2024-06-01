/* src/assets.c 
 * created sat may 25 2024
 * by catroidvania
 */

#include "assets.h"


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
            *LINES_TEXTURE = NULL;

SDL_Surface* NUMBER_TEXTURE[10] = {NULL};



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

    for (int i = 0; i < 10; i++) {
        SDL_FreeSurface(NUMBER_TEXTURE[i]);
    }
}
