/* src/assets.c 
 * created sat may 25 2024
 * by catroidvania
 */

#include "assets.h"


// this is pretty goofy but you have no idea how bad it was before
// each texture used to be individually defined allocated and free
// you can probably see it in old commits lmao
SDL_Surface* TEXTURES[TEXTURE_COUNT];
const char* texture_filepaths[TEXTURE_COUNT] = {
        "assets/t.png",
        "assets/i.png",
        "assets/o.png",
        "assets/l.png",
        "assets/j.png",
        "assets/s.png",
        "assets/z.png",
        "assets/blank.png",
        "assets/ghost.png",
        "assets/bg.png",
        "assets/board_bg.png",
        "assets/preview.png",
        "assets/score.png",
        "assets/level.png",
        "assets/lines.png",
        "assets/game_over.png",
        "assets/splash.png",
        "assets/0.png",
        "assets/1.png",
        "assets/2.png",
        "assets/3.png",
        "assets/4.png",
        "assets/5.png",
        "assets/6.png",
        "assets/7.png",
        "assets/8.png",
        "assets/9.png",
        "assets/big_1.png",
        "assets/big_2.png",
        "assets/big_3.png",
        "assets/solo_off.png",
        "assets/solo_on.png",
        "assets/vs_cpu_off.png",
        "assets/vs_cpu_on.png",
        "assets/quit_off.png",
        "assets/quit_on.png",
        "assets/garbage.png",
        "assets/incoming.png",
        "assets/game_win.png"
    };


Mix_Chunk* SOUNDS[SOUND_COUNT];
const char* sound_filepaths[SOUND_COUNT] = {
        "assets/menu_blip.wav",
        "assets/1.wav",
        "assets/3_2.wav",
        "assets/game_over.wav",
        "assets/garbage.wav",
        "assets/hard_drop.wav",
        "assets/line_clear.wav",
        "assets/select.wav",
        "assets/solidify.wav",
        "assets/level_up.wav"
    };


// load png function with error checking
//int load_png(SDL_Surface** surface, char* filepath) {
int load_png(Texture index, const char* filepath) {

    SDL_RWops* file = NULL;

    file = SDL_RWFromFile(filepath, "r");

    if (file == NULL) {
        printf("could not load %s!\n%s\n", filepath, SDL_GetError());
        return -1;
    }
    
    //*surface = IMG_LoadPNG_RW(file);
    TEXTURES[index] = IMG_LoadPNG_RW(file);

    return 0;
}


// loads a .wav audio file into the sfx array
int load_wav(Sound index, const char* filepath) {
    
    SOUNDS[index] = NULL;
    SOUNDS[index] = Mix_LoadWAV(filepath);

    if (SOUNDS[index] == NULL) {
        printf("counld not load %s!\n%s\n", filepath, Mix_GetError());
        return -1;
    }

    return 0;
}


// init function for loading all textures
int load_assets() {

    //SDL_RWops* file = NULL;
    int all_success = 0;

    for (int i = 0; i < TEXTURE_COUNT; i++) {
        if (load_png(i, texture_filepaths[i]) < 0) { all_success = -1; }
    }

    for (int i = 0; i < SOUND_COUNT; i++) {
        if (load_wav(i, sound_filepaths[i]) < 0) { all_success = -1; }
    }

    return all_success;
}


// function to unload all assets
void unload_assets() {
    
    for (int i = 0; i < TEXTURE_COUNT; i++) {
        SDL_FreeSurface(TEXTURES[i]);
    }

    for (int i = 0; i < SOUND_COUNT; i++) {
        Mix_FreeChunk(SOUNDS[i]);
    }
}
