/* src/assets.h
 * created sat may 25 2024
 * by catroidvania
 */

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>


#define BLOCKSIZE 32


extern SDL_Surface  *T_TEXTURE,
                    *I_TEXTURE,
                    *O_TEXTURE,
                    *L_TEXTURE,
                    *J_TEXTURE,
                    *S_TEXTURE,
                    *Z_TEXTURE,
                    *BLANK_TEXTURE;


int load_png(SDL_Surface** surface, char* filepath);
int load_assets();
void unload_assets();

