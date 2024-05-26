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
            *BLANK_TEXTURE = NULL;


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
}
