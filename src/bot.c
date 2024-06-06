/* src/movegen.c
 * Logan Gallagher
 * 2024/05/01
 */

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include "bitboard.h"
# include "movegen.h"


void splitBoard(struct Bitboard *boards, char piece, int *end, int *start, int *index, int depth) {
	for (int i = *start; i < *end; i++) {

		char **moves = (char **)malloc(40 * sizeof(char *));
		for (int j = 0; j < 40; j++) {
			moves[j] = (char *)malloc(4 * sizeof(char));
		}

		int nummoves = getLegalMoves(piece, boards[i].board , moves);

		for (char j = 0; j < nummoves; j++) {
			boards[*index] = boards[i];
			playMove(boards[*index].board,&boards[*index].score, moves[j]);
			for (char k = 0; k < 4; k++) {
				boards[*index].moves[depth][k] = moves[j][k];
			}
			*index += 1;
		}
		
	}
	
}



int scoreBoard(struct Bitboard board) {
	int score = board.score;
	char *height = getHeight(board.board);

	// get holes
	//int holes = 0;
	for (char i = 0; i < 10; i++) {
		for (char j = 0; j < height[i]; j++) {
			if (isTileSet(board.board,i,height[i]-j-1)==0) {
				//holes += 1;
				//printf("i: %d j: %d over: %d under: %d\n",i,height[i]-j,height[i]-j-1,j);
				score -= (height[i]-j-1)*(height[i]-j-1) + (j*j)/2 + 10;
			}
		}
	}

	// get relief 
	char gradient = 0;
	char currentGradient = 0;
	char maxGradient = 0;
	for (char i = 0; i < 10; i++) {
		if (i != 0) {
			gradient = abs(height[i-1] - height[i]);
			if (gradient > 1) {
				score -= gradient;
			}
		} else {
			gradient = 4;
		}
		currentGradient += gradient;
		if (i != 9) {
			gradient = abs(height[i+1] - height[i]);
			if (gradient > 1) {
				score -= gradient;
			}
		} else {
			gradient = 4;
		}

		currentGradient *= gradient;
		if (currentGradient > maxGradient) {
			maxGradient = currentGradient;
		}
		currentGradient = 0;
	}
	// reward best well
	score += maxGradient;
	return score;
}






int main() {
    struct Bitboard board;
	
    initBoard(&board);
	
	int start = 0;
	int end = 1;
	int index = 1;
	int indices[10];
	indices[0] = 1;

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
		indices[i+1] = index;
	}

	char allpieces[7] = {'O','S','Z','I','L','J','T'};

	for (int i = 0; i < 7; i++) {
		splitBoard(boards,allpieces[i],&end,&start,&index,2);

	}
	

	

	/*
	for (int i = index-5; i < index; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d: %c %d %d %d\n",j,boards[i].moves[j][0], boards[i].moves[j][1], boards[i].moves[j][2], boards[i].moves[j][3]);
		}

		printf("score: %d\n",scoreBoard(boards[i]));
		dispBoard(boards[i].board);
	}8?
	
	*/
	return 0;
}
