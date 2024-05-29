/* src/gamepad.h
 * created wed may 29 2024
 * by catroidvania
 */

#pragma once

#include <SDL.h>


typedef struct Gamepad {
    int button_up, button_down, button_left, button_right,
        button_a, button_b,
        das_left_counter, das_right_counter, soft_drop_counter;
} Gamepad;


void update_gamepad(SDL_Event* event, Gamepad* gp);
