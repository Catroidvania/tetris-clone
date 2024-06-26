/* src/assets.h
 * created sat may 25 2024
 * by catroidvania
 */

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>


#define BLOCKSIZE 32
#define BOARDBORDERSIZE 20
#define PREVIEWBORDERSIZE 20

#define TEXTURE_COUNT 39
#define SOUND_COUNT 10

// TODO
// when adding a new texture:
// 1. increase texture count
// 2. add a new thing to the enum
// 3. then add the file path to assets.c


// enum representing indexes into TEXTURES
typedef enum TextureIndex {
    T_TEXTURE = 0,
    I_TEXTURE,
    O_TEXTURE,
    L_TEXTURE,
    J_TEXTURE,
    S_TEXTURE,
    Z_TEXTURE,
    BLANK_TEXTURE,
    GHOST_TEXTURE,
    WINDOW_BG_TEXTURE,
    BOARD_BG_TEXTURE,
    PREVIEW_FRAME_TEXTURE,
    SCORE_TEXTURE,
    LEVEL_TEXTURE,
    LINES_TEXTURE,
    GAME_OVER_TEXTURE,
    SPLASH_TEXTURE,
    N0_TEXTURE,
    N1_TEXTURE,
    N2_TEXTURE,
    N3_TEXTURE,
    N4_TEXTURE,
    N5_TEXTURE,
    N6_TEXTURE,
    N7_TEXTURE,
    N8_TEXTURE,
    N9_TEXTURE,
    BIG_1_TEXTURE,
    BIG_2_TEXTURE,
    BIG_3_TEXTURE,
    SOLO_BTN_OFF_TEXTURE,
    SOLO_BTN_ON_TEXTURE,
    VS_CPU_BTN_OFF_TEXTURE,
    VS_CPU_BTN_ON_TEXTURE,
    QUIT_BTN_OFF_TEXTURE,
    QUIT_BTN_ON_TEXTURE,
    GARBAGE_TEXTURE,
    INCOMING_TEXTURE,
    GAME_WIN_TEXTURE
} Texture;


// same idea for audio
typedef enum SoundEffect {
    MENU_BLIP_SFX,
    COUNTDOWN1_SFX,
    COUNTDOWN23_SFX,
    GAME_OVER_SFX,
    GARBAGE_SFX,
    HARD_DROP_SFX,
    LINE_CLEAR_SFX,
    SELECT_SFX,
    SOLIDIFY_SFX,
    LEVEL_UP_SFX
} Sound;


extern SDL_Surface* TEXTURES[TEXTURE_COUNT];
extern const char* texture_filepaths[TEXTURE_COUNT];

extern Mix_Chunk* SOUNDS[SOUND_COUNT];
extern const char* sound_filepaths[SOUND_COUNT];


//int load_png(SDL_Surface** surface, char* filepath);
int load_png(Texture index, const char* filepath);
int load_wav(Sound index, const char* filepath);
int load_assets();
void unload_assets();
