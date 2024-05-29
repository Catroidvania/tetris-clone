/* src/gamepad.h
 * created wed may 29 2024
 * by catroidvania
 */

#pragma once

#include <SDL.h>


extern int  BUTTON_UP, BUTTON_DOWN, BUTTON_LEFT, BUTTON_RIGHT,
            BUTTON_A, BUTTON_B;
            // add more if needed


void update_gamepad(SDL_Event* event);
