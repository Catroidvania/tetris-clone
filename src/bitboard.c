/* src/bitboard.c
 * Logan Gallagher
 * 2024/05/31
 */

#include "bitboard.h" 


void initBoard(struct Bitboard *board) {
    // Set the board as a blank board
    for (int i = 0; i < 25; i++) {
		// setting the board as 0
        board->board[i] = 0;
    }
	// set the initial score of the board
    board->score = 0;
}

int isTileSet(unsigned char *board, int col, int row) {
	// get actual bit position from rows and columns
    int position = 10 * row + col;
    int index_out = position / 8;
    int index_in = position % 8;
	
	// use bitwise operations to determine state of bit at given pos
    unsigned char mask = 1 << index_in;

    return (board[index_out] & mask) != 0;
}

void setBit(unsigned char *board, int col, int row, int value) {
	// get actual bit pos from row & col
    int position = 10 * row + col;
    int index_out = position / 8;
    int index_in = position % 8;

	// set the bit with bitwise operations
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
	// get the bits in all positions and print them
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
