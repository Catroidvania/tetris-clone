/* src/board.c
 * created thu may 23 2024
 * by catroidvania
 */

#include "board.h"


// fill a board with empty blocks
int clear_board(Board* board) {

    if (board == NULL) { return -1; }

    for (int i = 0; i < BOARDSIZE; i++) {
        board->blocks[i] = BLANK;
    }

    return 0;
}
