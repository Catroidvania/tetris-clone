/* src/asset.cpp
 * created wed may 8 2024
 * by catroidvania
 */

#include "asset.hpp"


// textures
const* SDL_Surface  TPIECETEXTURE = nullptr, 
                    LPIECETEXTURE = nullptr, 
                    JPIECETEXTURE = nullptr, 
                    IPIECETEXTURE = nullptr, 
                    OPIECETEXTURE = nullptr, 
                    SPIECETEXTURE = nullptr, 
                    ZPIECETEXTURE = nullptr,
                    EMPTYBOARDTEXTURE = nullptr;


// load png function with error checking
void loadPNG(SDL_Surface* &target, char* filePath) {

    SDL_RWops* file = nullptr;

    file = SDL_RWFromFile(filePath, "r");
    if (file == nullptr) {
        std::cout << "Could not load " << filePath << "!" << NL;
        std::cerr << SDL_GetError() << NL;
        target = nullptr;
    } else {
        target = SDL_LoadPNG_RW(file);
    }

}


// init function for loading all textures
// TODO remember to add the corrosponding free to unloadAssets() when u add a new texture
bool loadAssets() {

    SDL_RWops* file = nullptr;
    bool allSuccess = true;

    loadPNG(&LPIECETEXTURE, "assets/l.png");
    if (LPIECETEXTURE == nullptr) { allSuccess = false; }

    loadPNG(&JPIECETEXTURE, "assets/j.png");
    if (JPIECETEXTURE == nullptr) { allSuccess = false; }

    loadPNG(&ZPIECETEXTURE, "assets/z.png");
    if (ZPIECETEXTURE == nullptr) { allSuccess = false; }

    loadPNG(&SPIECETEXTURE, "assets/s.png");
    if (SPIECETEXTURE == nullptr) { allSuccess = false; }

    loadPNG(&OPIECETEXTURE, "assets/o.png");
    if (OPIECETEXTURE == nullptr) { allSuccess = false; }

    loadPNG(&TPIECETEXTURE, "assets/t.png");
    if (TPIECETEXTURE == nullptr) { allSuccess = false; }

    loadPNG(&IPIECETEXTURE, "assets/i.png");
    if (IPIECETEXTURE == nullptr) { allSuccess = false; }

    loadPNG(&EMPTYBOARDTEXTURE, "assets/empty.png");
    if (EMPTYBOARDTEXTURE == nullptr) { allSuccess = false; }

    return allSuccess;
}


// function to unload all assets
void unloadAssets() {
    SDL_FreeSurface(LPIECETEXTURE);
    SDL_FreeSurface(JPIECETEXTURE);
    SDL_FreeSurface(ZPIECETEXTURE);
    SDL_FreeSurface(SPIECETEXTURE);
    SDL_FreeSurface(OPIECETEXTURE);
    SDL_FreeSurface(TPIECETEXTURE);
    SDL_FreeSurface(IPIECETEXTURE);
    SDL_FreeSurface(EMPTYBOARDTEXTURE);
}
