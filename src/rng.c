/* src/rng.c
 * created fri may 31 2024
 * by catroidvania
 */

#include "rng.h"


// rotate the bits of x k places to the left
inline uint32_t bit_rotate_left(uint32_t x, int k) {
	return (x << k) | (x >> (32 - k));
}


// get the next number in the prng sequence
uint32_t rng_next(RNGState* state) {

	uint32_t state1 = state->states[0];
	uint32_t state2 = state->states[1];

	uint32_t result = bit_rotate_left(state1 * 0x9E3779BB, 5) * 5;

    // lots of xor screwery
	state2 ^= state1;

	state->states[0] = bit_rotate_left(state1, 26) ^ state2 ^ (state2 << 9);
	state->states[1] = bit_rotate_left(state2, 13);

	return state->value;
}
