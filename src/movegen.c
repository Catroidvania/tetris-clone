/* src/movegen.c
 * Logan Gallagher
 * 2024/05/01
 */

# include <stdio.h>
# include <stdbool.h>
# include "bitboard.h"


static const char O_info[20] = {2,2,1,1,/*standard pos*/ 1,2,1,2,0,0,0,0, /*rotate 1*/ 1,2,1,2,0,0,0,0};
static const char S_info[20] = {3,2,0,0,/*standard pos*/ 1,1,1,2,2,2,0,0, /*rotate 1*/ 2,3,1,2,0,0,0,0};
static const char Z_info[20] = {3,2,0,0,/*standard pos*/ 2,2,1,2,1,1,0,0, /*rotate 1*/ 1,2,2,3,0,0,0,0};
static const char I_info[20] = {3,2,1,0,/*standard pos*/ 1,4,0,0,0,0,0,0, /*rotate 1*/ 1,1,1,1,1,1,1,1};
static const char L_info[20] = {3,2,0,0,/*standard pos*/ 1,1,1,1,1,2,0,0, /*rotate 1*/ 1,3,1,1,0,0,0,0};
static const char J_info[20] = {3,2,0,0,/*standard pos*/ 1,2,1,1,1,1,0,0, /*rotate 1*/ 1,3,3,3,0,0,0,0};
static const char T_info[20] = {3,2,0,0,/*standard pos*/ 1,1,1,2,1,1,0,0, /*rotate 1*/ 1,3,2,2,0,0,0,0};



void getInfo(char piece, char *info) {
    const char *temp = NULL;
    
    switch(piece) {
        case 'O':
            temp = O_info;
            break;
        case 'S':
            temp = S_info;
            break;
        case 'Z':
            temp = Z_info;
            break;
        case 'I':
            temp = I_info;
            break;
        case 'L':
            temp = L_info;
            break;
        case 'J':
            temp = J_info;
            break;
        case 'T':
            temp = T_info;
            break;
        default:
            // Handle invalid piece
            return;
    }
    
    for (int i = 0; i < 20; ++i) {
        info[i] = temp[i];
    }
}


char** getLegalMoves(char piece, unsigned char board[]) {
	char moves[40][4];
	char info[20];
	getInfo(piece,info);
	for (int i = 0; i <
	return NULL;


}




int main() {
    struct Bitboard board;
	
    initBoard(&board, 'L', 'S');
	
	char piece = 'L';

	getLegalMoves(piece, board.board);

    return 0;
}



