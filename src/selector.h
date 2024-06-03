/* src/selector.h 
 * created mon jun 3 2024
 * by catroidvania
 */

#pragma once

#include "assets.h"
#include "gamepad.h"


// a seletable menu element
typedef struct Button {
    int x, y;
    Texture texture;
    struct Button *up, *down, *left, *right; // used for changing the selection
} Button;


// a collection of Buttons
typedef struct Selector {
    Button* current;    // pointer to the current button
    int button_count;   // number of buttons in the selector, used for bounds checking
    Button** buttons;    // an array of buttons
} Selector;


extern Button DEFAULT_BUTTON;
extern Selector DEFAULT_SELECTOR;

extern Button* main_menu_buttons[3];
extern Button SOLO_BUTTON, VS_CPU_BUTTON, QUIT_BUTTON;
extern Selector MAIN_MENU_SELECTOR;

int update_selected(Selector* menu, Gamepad* inputs);
