/* src/asset.hpp
 * created wed may 8 2024
 * by catroidvania
 */


#ifndef ASSET_HPP
#define ASSET_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>


extern SDL_Surface  *TPIECETEXTURE, 
                    *LPIECETEXTURE, 
                    *JPIECETEXTURE, 
                    *IPIECETEXTURE, 
                    *OPIECETEXTURE, 
                    *SPIECETEXTURE, 
                    *ZPIECETEXTURE,
                    *EMPTYBOARDTEXTURE;

void loadPNG(SDL_Surface* const &target, std::string filePath);
bool loadAssets();
void unloadAssets();

#endif
