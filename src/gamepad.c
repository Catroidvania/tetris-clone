/* src/gamepad.c 
 * created wed may 29 2024
 * by catroidvania
 */

#include "gamepad.h"


// update state of buttons so we can use our own key repeat delays
// should only be called once per frame
void update_gamepad(SDL_Event* event, Gamepad* gp) {
    
    if (event == NULL) { return; }
    if (gp == NULL) { return; }

    // DAS updates
    if (gp->button_left) {
        gp->das_left_counter += 1;
    }

    if (gp->button_right) {
        gp->das_right_counter += 1;
    }

    if (event->type == SDL_KEYDOWN && !event->key.repeat) {
        switch (event->key.keysym.sym) {
        case SDLK_LEFT:
            // DAS reset
            if (!gp->button_left) {
                gp->das_left_counter = 0;
                gp->das_right_counter = 0;
            }
            gp->button_left = 1;
            break;
        case SDLK_RIGHT:
            // DAS reset
            if (!gp->button_right) {
                gp->das_left_counter = 0;
                gp->das_right_counter = 0;
            }
            gp->button_right = 1;
            break;
        case SDLK_x:
            gp->button_b = 1;
            break;
        case SDLK_z:
            gp->button_a = 1;
            break;
        case SDLK_UP:
            gp->button_up = 1;
            break;
        case SDLK_DOWN:
            gp->button_down = 1;
            break;
        }
    } else if (event->type == SDL_KEYUP && !event->key.repeat) {
        switch (event->key.keysym.sym) {
        case SDLK_LEFT:
            gp->button_left = 0;
            break;
        case SDLK_RIGHT:
            gp->button_right = 0;
            break;
        case SDLK_x:
            gp->button_b = 0;
            break;
        case SDLK_z:
            gp->button_a = 0;
            break;
        case SDLK_UP:
            gp->button_up = 0;
            break;
        case SDLK_DOWN:
            gp->button_down = 0;
            break;
        }
    }
}
