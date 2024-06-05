/* src/gamepad.c 
 * created wed may 29 2024
 * by catroidvania
 */

#include "gamepad.h"


// default gamepads
Gamepad RESET_GAMEPAD = {
        .up = SDLK_UP,
        .down = SDLK_DOWN,
        .left = SDLK_LEFT,
        .right = SDLK_RIGHT,
        .a = SDLK_z,
        .b = SDLK_x,
        .button_up = 0,
        .button_down = 0,
        .button_left = 0,
        .button_right = 0,
        .button_a = 0,
        .button_b = 0,
        .das_left_counter = 0,
        .das_right_counter = 0
    },
    LOCAL2_GAMEPAD = {
        .up = SDLK_UP,
        .down = SDLK_DOWN,
        .left = SDLK_LEFT,
        .right = SDLK_RIGHT,
        .a = SDLK_COMMA,
        .b = SDLK_PERIOD,
        .button_up = 0,
        .button_down = 0,
        .button_left = 0,
        .button_right = 0,
        .button_a = 0,
        .button_b = 0,
        .das_left_counter = 0,
        .das_right_counter = 0
    },
    LOCAL1_GAMEPAD = {
        .up = SDLK_w,
        .down = SDLK_s,
        .left = SDLK_a,
        .right = SDLK_d,
        .a = SDLK_BACKQUOTE,
        .b = SDLK_1,
        .button_up = 0,
        .button_down = 0,
        .button_left = 0,
        .button_right = 0,
        .button_a = 0,
        .button_b = 0,
        .das_left_counter = 0,
        .das_right_counter = 0
    };


// update state of buttons so we can use our own key repeat delays
// should only be called once per frame
// player 0: singleplayer, player 1 or 2, for local multiplayer
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
        // this used to be a switch case
        // back when life was good...
        if (event->key.keysym.sym == gp->left) {
            // DAS reset
            if (!gp->button_left) {
                gp->das_left_counter = 0;
                gp->das_right_counter = 0;
            }
            gp->button_left = 1;
        } else if (event->key.keysym.sym == gp->right) {
            // DAS reset
            if (!gp->button_right) {
                gp->das_left_counter = 0;
                gp->das_right_counter = 0;
            }
            gp->button_right = 1;
        } else if (event->key.keysym.sym == gp->b) {
            gp->button_b = 1;
        } else if (event->key.keysym.sym == gp->a) {
            gp->button_a = 1;
        } else if (event->key.keysym.sym == gp->up) {
            gp->button_up = 1;
        } else if (event->key.keysym.sym == gp->down) {
            gp->button_down = 1;
        }
    } else if (event->type == SDL_KEYUP && !event->key.repeat) {
        if (event->key.keysym.sym == gp->left) {
            gp->button_left = 0;
        } else if (event->key.keysym.sym == gp->right) {
            gp->button_right = 0;
        } else if (event->key.keysym.sym == gp->b) {
            gp->button_b = 0;
        } else if (event->key.keysym.sym == gp->a) {
            gp->button_a = 0;
        } else if (event->key.keysym.sym == gp->up) {
            gp->button_up = 0;
        } else if (event->key.keysym.sym == gp->down) {
            gp->button_down = 0;
        }
    }
}
