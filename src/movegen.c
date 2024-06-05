/* src/movegen.c
 * Logan Gallagher
 * 2024/05/01
 */

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include "bitboard.h"


static const char O_info[37] = {1,2,0,0,0,/*standard pos*/ 1,2,1,2,0,0,0,0, /*rotate 1*/ 0,0,0,0,0,0,0,0,/**/0,0,0,0,0,0,0,0,/**/0,0,0,0,0,0,0,0};
static const char S_info[37] = {2,3,2,0,0,/*standard pos*/ 1,1,1,2,2,2,0,0, /*rotate 1*/ 2,3,1,2,0,0,0,0,/**/0,0,0,0,0,0,0,0,/**/0,0,0,0,0,0,0,0};
static const char Z_info[37] = {2,3,2,0,0,/*standard pos*/ 2,2,1,2,1,1,0,0, /*rotate 1*/ 1,2,2,3,0,0,0,0,/**/0,0,0,0,0,0,0,0,/**/0,0,0,0,0,0,0,0};
static const char I_info[37] = {2,4,1,0,0,/*standard pos*/ 1,4,0,0,0,0,0,0, /*rotate 1*/ 1,1,1,1,1,1,1,1,/**/0,0,0,0,0,0,0,0,/**/0,0,0,0,0,0,0,0};
static const char L_info[37] = {4,3,2,3,2,/*standard pos*/ 1,1,1,1,1,2,0,0, /*rotate 1*/ 1,3,1,1,0,0,0,0,/**/1,2,2,2,2,2,0,0,/**/3,3,1,3,0,0,0,0};
static const char J_info[37] = {4,3,2,3,2,/*standard pos*/ 1,2,1,1,1,1,0,0, /*rotate 1*/ 1,3,3,3,0,0,0,0,/**/2,2,2,2,1,2,0,0,/**/1,1,1,3,0,0,0,0};
static const char T_info[37] = {4,3,2,3,2,/*standard pos*/ 1,1,1,2,1,1,0,0, /*rotate 1*/ 1,3,2,2,0,0,0,0,/**/2,2,1,2,2,2,0,0,/**/2,2,1,3,0,0,0,0};



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
    }
    
    for (int i = 0; i < 20; i++) {
        info[i] = temp[i];
    }
}

char* getHeight(unsigned char *board) {
   	char* height = (char*)malloc(10 * sizeof(char));
	for (char i=0; i<10; i++) {
		for (char j=0; j<20; j++) {
			height[i] = 19-j;
			if (isTileSet(board,i,19-j)) {
				break;
			}
		}
	}
	return height;
}


int getLegalMoves(char piece, unsigned char *board, char **moves) {
    char *height = getHeight(board);
    int nummoves = 0;
    char info[37];
    getInfo(piece, info);
    // iterate through rotations
    for (char rot = 0; rot < info[0]; rot++) {
        // iterate through positions
        for (char pos = 0; pos < 10 - height[1 + rot]; pos++) {
            char elevation = 0;
            // iterate through rows
            for (char irow = 0; irow < info[1 + rot]; irow++) {
                if (height[pos + irow] - info[5 + 8 * rot + 2 * irow] + 1 > elevation) {
                    elevation = height[pos + irow] - info[5 + 8 * rot + 2 * irow] + 1;
                }
            }
            moves[nummoves][0] = piece;
            moves[nummoves][1] = rot;
            moves[nummoves][2] = pos;
            moves[nummoves][3] = elevation;
            nummoves = nummoves + 1;
        }
    }
    return nummoves;
}


int main() {
    struct Bitboard board;
	
    initBoard(&board, 'L', 'S');
	//setBit(board.board,2,3,1);

	char piece = 'I';

	char **moves = (char **)malloc(40 * sizeof(char *));
    for (int i = 0; i < 40; i++) {
        moves[i] = (char *)malloc(4 * sizeof(char));
    }

	int nummoves = getLegalMoves(piece, board.board,moves);

	for (char i = 0; i < nummoves; i++) {
		printf("%c %d %d %d",moves[i][0], moves[i][1], moves[i][2], moves[i][3]);
		printf("\n");
	}
	
	return 0;
}



