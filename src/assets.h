/* src/assets.h
 * created sat may 25 2024
 * by catroidvania
 */

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>


#define BLOCKSIZE 32
#define BOARDBORDERSIZE 20
#define PREVIEWBORDERSIZE 20


extern SDL_Surface  *T_TEXTURE,
                    *I_TEXTURE,
                    *O_TEXTURE,
                    *L_TEXTURE,
                    *J_TEXTURE,
                    *S_TEXTURE,
                    *Z_TEXTURE,
                    *BLANK_TEXTURE,
                    *GHOST_TEXTURE,
                    *WINDOW_BG_TEXTURE,
                    *BOARD_BG_TEXTURE,
                    *PREVIEW_FRAME_TEXTURE,
                    *SCORE_TEXTURE,
                    *LEVEL_TEXTURE,
                    *LINES_TEXTURE,
                    *GAME_OVER_TEXTURE,
                    *SPLASH_TEXTURE;

extern SDL_Surface* NUMBER_TEXTURE[10];
extern SDL_Surface* BIG_NUMBER_TEXTURE[3];
extern SDL_Surface* SOLO_BTN_TEXTURE[2];
extern SDL_Surface* VS_CPU_BTN_TEXTURE[2];
extern SDL_Surface* QUIT_BTN_TEXTURE[2];


int load_png(SDL_Surface** surface, char* filepath);
int load_assets();
void unload_assets();

