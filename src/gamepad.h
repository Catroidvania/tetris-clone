/* src/gamepad.h
 * created wed may 29 2024
 * by catroidvania
 */

#pragma once

#include <SDL.h>


// with the benefit of hindsight i wouldve stored the relevant keybinds in the struct
// TODO maybe do this later
typedef struct Gamepad {
    SDL_Keycode up, down, left, right, a, b;
    int button_up, button_down, button_left, button_right,
        button_a, button_b,
        das_left_counter, das_right_counter;
} Gamepad;

extern Gamepad RESET_GAMEPAD, LOCAL1_GAMEPAD, LOCAL2_GAMEPAD;

void update_gamepad(SDL_Event* event, Gamepad* gp);
