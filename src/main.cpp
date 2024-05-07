/* src/main.cpp
 * created apr 30 2024
 * by catroidvania
 */

#include "main.hpp"


int main() {

    SDL_Window* window = nullptr;
    SDL_Surface* windowSurface = nullptr;

    // make sure sdl is initialsed properly
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Could not initialise SDL!\n" << SDL_GetError() << NL;
        return -1;
    }

    

    return 0;
}
