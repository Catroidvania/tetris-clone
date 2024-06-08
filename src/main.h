/* src/main.h 
 * created thu may 23 2024
 * by catroidvania
 */

#pragma once

#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_thread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "app.h"
#include "assets.h"
#include "board.h"
#include "bot.h"
#include "game.h"
#include "gamepad.h"
#include "pieces.h"
#include "rendering.h"
#include "selector.h"

#define CPUTHINKDELAY 60
#define CPUMOVEDELAY 2

int bot_thread(void* data);
