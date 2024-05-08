/* src/main.cpp
 * created apr 30 2024
 * by catroidvania
 */

#include "main.hpp"


int main() {

    SDL_Window* window = nullptr;
    SDL_Surface* windowSurface = nullptr;
    SDL_Event event;

    // make sure sdl is initialsed properly
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Could not initialise SDL!" << NL;
        std::cerr << SDL_GetError() << NL;
        return -1;
    }
    
    // create the window
    window = SDL_CreateWindow(
                "sirtet", 
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                SCR_WIDTH, SCR_HEIGHT,
                SDL_WINDOW_SHOWN);

    // make sure we have a window before we continue
    if (window == nullptr) {
        std::cout << "Could not create SDL window!" << NL;
        std::cerr << SDL_GetError() << NL;
        return -1;
    }

    // get the window surface so we can draw on it
    windowSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(windowSurface, nullptr, SDL_MapRGB(windowSurface->format, 0, 0, 0));
    SDL_UpdateWindowSurface(window);

    while (true) {
        SDL_PollEvent(&event);
        
        if (event.type == SDL_QUIT) {
            break;
        }
    }

    return 0;
}