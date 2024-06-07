/* src/bitboard.c
 * Logan Gallagher
 * 2024/05/31
 */

#include "bitboard.h" 


void initBoard(struct Bitboard *board) {
    // Set the board as a blank board (temporary)
    for (int i = 0; i < 25; i++) {
        board->board[i] = 0;
    }
    board->score = 0;
}

int isTileSet(unsigned char *board, int col, int row) {
    int position = 10 * row + col;
    int index_out = position / 8;
    int index_in = position % 8;

    unsigned char mask = 1 << index_in;

    return (board[index_out] & mask) != 0;
}

void setBit(unsigned char *board, int col, int row, int value) {
    int position = 10 * row + col;
    int index_out = position / 8;
    int index_in = position % 8;

    unsigned char mask = 1 << index_in;
    if (value) {
        // Set to 1
        board[index_out] |= mask;
    } else {
        // Set to 0
        board[index_out] &= ~mask;
    }
}

void dispBoard(unsigned char board[]) {
    for (int i = 19; i >= 0; i--) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", isTileSet(board, j, i));
        }
        printf("\n");
    }
	printf("\n\n\n");
}

/*int main() {
    struct Bitboard board;
    initBoard(&board, 'L', 'S');

    setBit(board.board, 1, 2, 1); // Set a bit at position (1, 1) to 1

    dispBoard(board.board); // Display the board with set bit

    return 0;
}*/
