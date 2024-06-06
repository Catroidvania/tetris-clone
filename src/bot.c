/* src/movegen.c
 * Logan Gallagher
 * 2024/05/01
 */

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include "bitboard.h"
# include "movegen.h"

/*void genBoard(struct Board *boards, int depth) {
	;

}*/


void splitBoard(struct Bitboard *boards, char piece, int *end, int *start, int *index, int depth) {
	for (int i = *start; i < *end; i++) {

		char **moves = (char **)malloc(40 * sizeof(char *));
		for (int j = 0; j < 40; j++) {
			moves[j] = (char *)malloc(4 * sizeof(char));
		}

		int nummoves = getLegalMoves(piece, boards[i].board , moves);

		for (char j = 0; j < nummoves; j++) {
			boards[*index] = boards[i];
			playMove(boards[*index].board, moves[j]);
			for (char k = 0; k < 4; k++) {
				boards[*index].moves[depth][k] = moves[j][k];
			}
			*index += 1;
		}
		
	}
	
}




int main() {
    struct Bitboard board;
	
    initBoard(&board);
	
	int start = 0;
	int end = 1;
	int index = 1;

	struct Bitboard *boards = (struct Bitboard *)malloc(449640 * sizeof(struct Bitboard));
    if (boards == NULL) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
	}
	boards[0] = board;
	char pieces[2] = {'L','J'};

	for (int i = 0; i < 2; i++) {
		splitBoard(boards,pieces[i],&end,&start,&index,i);
		start = end;
		end = index;
	}

	char allpieces[7] = {'O','S','Z','I','L','J','T'};

	for (int i = 0; i < 7; i++) {
		splitBoard(boards,allpieces[i],&end,&start,&index,2);
	}
	

	


	for (int i = index-5; i < index; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d: %c %d %d %d\n",j,boards[i].moves[j][0], boards[i].moves[j][1], boards[i].moves[j][2], boards[i].moves[j][3]);
		}
		dispBoard(boards[i].board);
	}
	
	
	return 0;
}
