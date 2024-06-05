/* src/selector.c
 * created mon jun 3 2024
 * by catroidvania
 */

#include "selector.h"


// struct initialisers
// i wonder if this is bad practice?
Button DEFAULT_BUTTON = (Button){
        .x = 0, .y = 0,
        .texture = BLANK_TEXTURE,
        .up = NULL, .down = NULL, .left = NULL, .right = NULL
    };

Selector DEFAULT_SELECTOR = (Selector){
        .current = NULL,
        .button_count = 0,
        .buttons = NULL
    };


// main menu buttons
Button  SOLO_BUTTON = (Button){
        .x = 0, .y = 0,
        .texture = SOLO_BTN_OFF_TEXTURE,
        .up = NULL, .down = &VS_CPU_BUTTON, .left = NULL, .right = NULL
    },
        VS_CPU_BUTTON = (Button){
        .x = 0, .y = 150,
        .texture = VS_CPU_BTN_OFF_TEXTURE,
        .up = &SOLO_BUTTON, .down = &QUIT_BUTTON, .left = NULL, .right = NULL
    },
        QUIT_BUTTON = (Button){
        .x = 0, .y = 300,
        .texture = QUIT_BTN_OFF_TEXTURE,
        .up = &VS_CPU_BUTTON, .down = NULL, .left = NULL, .right = NULL
    };

Button* main_menu_buttons[3] = {&SOLO_BUTTON, &VS_CPU_BUTTON, &QUIT_BUTTON};
Selector MAIN_MENU_SELECTOR = (Selector){
        .current = &SOLO_BUTTON,
        .button_count = 3,
        .buttons = main_menu_buttons
    };


// updates which button is selected
// returns 1 if a new button is selected, 0 if not
int update_selected(Selector* menu, Gamepad* inputs) {
    
    if (menu == NULL) { return 0; }
    if (inputs == NULL) { return 0; }

    if (inputs->button_up && menu->current->up != NULL) {
        menu->current = menu->current->up;
        Mix_PlayChannel(-1, SOUNDS[MENU_BLIP_SFX], 0);
        return 1;
    } else if (inputs->button_down && menu->current->down != NULL) {
        menu->current = menu->current->down;
        Mix_PlayChannel(-1, SOUNDS[MENU_BLIP_SFX], 0);
        return 1;
    } else if (inputs->button_left && menu->current->left != NULL) {
        menu->current = menu->current->left;
        Mix_PlayChannel(-1, SOUNDS[MENU_BLIP_SFX], 0);
        return 1;
    } else if (inputs->button_right && menu->current->right != NULL) {
        menu->current = menu->current->right;
        Mix_PlayChannel(-1, SOUNDS[MENU_BLIP_SFX], 0);
        return 1;
    } 

    return 0;
}
