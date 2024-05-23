/* src/main.c 
 * created thu may 23 2024
 * by catroidvania
 */

#include "main.h"


// TODO move this stuff somewhere else for like  organisation lol
int main() {

    // declarations
    SDL_Window* window = NULL;
    SDL_Surface* window_surface = NULL;
    SDL_Event event;

    // init sdl check
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("no sdl?? more likely than youd think!\n%s\n", SDL_GetError());
        return -1;
    }

    // create window
    window = SDL_CreateWindow(  "cetris (CursEd skull TetRomIno Stacking game)",
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                WINWIDTH, WINHEIGHT,
                                SDL_WINDOW_SHOWN);

    // window init check
    if (window == NULL) {
        printf("alas no window...\n%s\n", SDL_GetError());
        return -1;
    }

    // decorate window
    window_surface = SDL_GetWindowSurface(window);
    SDL_FillRect( window_surface, NULL, SDL_MapRGB( window_surface->format, 0xFF, 0xFF, 0xFF ) );

    // primitive draw loop
    while (1) {
        // exit on close window button
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            break;
        }
        // refresh window
        SDL_UpdateWindowSurface(window);
    }

    // uninit sdl stuff
    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}
