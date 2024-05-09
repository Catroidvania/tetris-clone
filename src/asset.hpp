/* src/asset.hpp
 * created wed may 8 2024
 * by catroidvania
 */


#ifndef ASSET_HPP
#define ASSET_HPP

#include <SDL_image.h>

extern const* SDL_Surface   TPIECETEXTURE, 
                            LPIECETEXTURE, 
                            JPIECETEXTURE, 
                            IPIECETEXTURE, 
                            OPIECETEXTURE, 
                            SPIECETEXTURE, 
                            ZPIECETEXTURE,
                            EMPTYBOARDTEXTURE;

void loadPNG(SDL_Surface* &target, char* filePath);
bool loadAssets();
void unloadAssets();

#endif
