/* src/rng.h
 * created fri may 31 2024
 * by catroidvania
 */

#pragma once

#include <stdint.h>
#include <stdio.h>


/* xoroshiro64 randomiser
 * see https://prng.di.unimi.it/ for details
 */


// remember to seed the state otherwise it will generate only 0s!
typedef struct RandomState {
    uint16_t state;
} RNGState;


/*
// for some reason making this inline makes it fail to link
//uint32_t bit_rotate_left(uint32_t x, int k);
*/
uint16_t rng_next(RNGState* state);

