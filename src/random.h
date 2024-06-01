/* src/random.h
 * created fri may 31 2024
 * by catroidvania
 */

#pragma once

#include <stdint.h>


/* xoroshiro64 randomiser
 * see https://prng.di.unimi.it/ for details
 */


// remember to seed the state otherwise it will generate only 0s!
typedef struct RandomNumber {
    uint32_t states[2];
} RNGState;


inline uint32_t bit_rotate_left(uint32_t x, int k);
uint32_t rng_next(RNGState* state);
