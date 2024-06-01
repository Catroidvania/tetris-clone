/* src/rng.c
 * created fri may 31 2024
 * by catroidvania
 */

#include "rng.h"


// 16bit fibonacci lfsr randomiser
// taps are 16 14 13 11, taken from wikipedia
// its distribution isnt perfect but its good enough, as well as being in the NES tetris spirit
static inline uint16_t flfsr_next(RNGState* rng) {

    // xor all our tap bits
    //uint32_t next_bit = ((rng->state >> 0) ^ (rng->state >> 26) ^ (rng->state >> 27) ^ (rng->state >> 31)) & 1u;
    uint16_t next_bit = ((rng->state >> 0) ^ (rng->state >> 2) ^ (rng->state >> 3) ^ (rng->state >> 5)) & 1u;

    // stick our output bit at the end
    rng->state = (rng->state >> 1) | (next_bit << 15);

    return next_bit;
}


// gets 16 bits of randomness
uint16_t rng_next(RNGState* state) {

    uint16_t number = 0;

    for (int k = 0; k < 16; k++) {
        number <<= 1;
        number |= flfsr_next(state);
    }
    
    return number;
}


    /* THIS CODE IS MEANT OT BE IN main.c! DONT RUN IT HERE!
    int ts = 0, is = 0, os = 0, js = 0, ls = 0, ss = 0, zs = 0;
    Piece testy = application.game.current_piece;

    int TESTS = 1000000;
    for (int k=0; k < TESTS; k++) {
        testy = randomize_piece(&application.game, &testy);

        switch (testy.type) {
        case T:
            ts++;
            break;
        case I:
            is++;
            break;
        case O:
            os++;
            break;
        case J:
            js++;
            break;
        case L:
            ls++;
            break;
        case S:
            ss++;
            break;
        case Z:
            zs++;
            break;
        }
    }

    printf("\nT: %d\nI: %d\nO: %d\nJ: %d\nL: %d\nZ: %d\nS: %d\n", ts, is, os, js, ls, zs, ss);


    */

