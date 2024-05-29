/* src/gamepad.c 
 * created wed may 29 2024
 * by catroidvania
 */

#include "gamepad.h"


// keyboard states
int BUTTON_UP = 0,
    BUTTON_DOWN = 0,
    BUTTON_LEFT = 0,
    BUTTON_RIGHT = 0,
    BUTTON_A = 0,
    BUTTON_B = 0;


// update state of buttons so we can use our own key repeat delays
void update_gamepad(SDL_Event* event) {
    
    if (event == NULL) { return; }

    if (event->type == SDL_KEYDOWN && !event->key.repeat) {
        switch (event->key.keysym.sym) {
        case SDLK_LEFT:
            BUTTON_LEFT = 1;
            break;
        case SDLK_RIGHT:
            BUTTON_RIGHT = 1;
            break;
        case SDLK_x:
            BUTTON_B = 1;
            break;
        case SDLK_z:
            BUTTON_A = 1;
            break;
        case SDLK_UP:
            BUTTON_UP = 1;
            break;
        case SDLK_DOWN:
            BUTTON_DOWN = 1;
            break;
        }
    } else if (event->type == SDL_KEYUP && !event->key.repeat) {
        switch (event->key.keysym.sym) {
        case SDLK_LEFT:
            BUTTON_LEFT = 0;
            break;
        case SDLK_RIGHT:
            BUTTON_RIGHT = 0;
            break;
        case SDLK_x:
            BUTTON_B = 0;
            break;
        case SDLK_z:
            BUTTON_A = 0;
            break;
        case SDLK_UP:
            BUTTON_UP = 0;
            break;
        case SDLK_DOWN:
            BUTTON_DOWN = 0;
            break;
        }
    }
}
