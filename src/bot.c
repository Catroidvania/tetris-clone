/* src/movegen.c
 * Logan Gallagher
 * 2024/05/01
 */

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include "bitboard.h"
# include "movegen.h"
# include "bot.h"


void splitBoard(struct Bitboard *boards, char piece, int *end, int *start, int *index, int depth) {
	// iterates through boards needed to be duplicated
	for (int i = *start; i < *end; i++) {

		// allocates memory to store moves
		char **moves = (char **)malloc(40 * sizeof(char *));
		for (int j = 0; j < 40; j++) {
			moves[j] = (char *)malloc(4 * sizeof(char));
		}

		// generates legal moves for board
		int nummoves = getLegalMoves(piece, boards[i].board , moves);

		// plays moves on duplicate board
		for (char j = 0; j < nummoves; j++) {


			boards[*index] = boards[i];
			playMove(boards[*index].board,&boards[*index].score, moves[j]);

			// saves move
			for (char k = 0; k < 4; k++) {
				boards[*index].moves[depth][k] = moves[j][k];
			}
			*index += 1;
		}

		// frees moves memory
		for (int j = 0; j < 40; j++) {
			free(moves[j]);
		}
		free(moves);
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

	// punish height
	for (char i = 0; i < 10; i ++) {
		score -= height[i]*height[i];
	}

	free(height);

	return score;
}



bool arraysAreEqual(char arr1[3][4], char arr2[2][4]) {
	// checks if two moves arrays are equal
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			if (arr1[i][j] != arr2[i][j]) {
				return false; 
			}
		}
	}
	return true; 
}




char (*getBest(struct Bitboard *boards, int *indices))[4] {
	static char bestMove[4] = {0, 0, 0, 0};
	char currMove[2][4];
	int currBestScore[7];
	int currScore;
	int bestScore = -10000;
	int maxInt = indices[7];
	char cont = 1;

	// while continue condition remanins true
	while (cont) { 
		// get the current move
		for (char i = 0; i < 2; i++) {
			for (char j = 0; j < 4; j++) {
				currMove[i][j] = boards[indices[0]].moves[i][j];
			}
		}
		// rotates through potential pieces
		for (char i = 0; i < 7; i++) {
			currBestScore[i] = -10000;
			while (1) { // repeat until broken 
						// detect if all tiles have been queried
				if (indices[6] >= maxInt) {
					cont = 0;
					break;
				}
				// if tiles are equal continue checking
				if (arraysAreEqual(boards[indices[i]].moves, currMove)) {
					currScore = scoreBoard(boards[indices[i]]);
					if (currScore > currBestScore[i]) {
						currBestScore[i] = currScore;
					}
					indices[i]++;
				} else {
					break;
				}
			}
			if (cont == 0) {
				break;
			}
		}
		if (cont == 0) {
			break;
		}
		currScore = 0;
		for (char i = 0; i < 7; i++) {
			currScore += currBestScore[i];
		}
		if (currScore > bestScore) {
			bestScore = currScore;
			for (char i = 0; i < 4; i++) {
				bestMove[i] = currMove[0][i];
			}
		}
	}

	return &bestMove;
}


char (*getBot(struct Bitboard board,char pieces[2]))[4] {
	int start = 0;
	int end = 1;
	int index = 1;
	int indices[7];

	// allocate space for the boards
	struct Bitboard *boards = (struct Bitboard *)malloc(449640 * sizeof(struct Bitboard));
	if (boards == NULL) {
		perror("Failed to allocate memory");
	}
	boards[0] = board;

	// split w/ known pieces
	for (int i = 0; i < 2; i++) {
		splitBoard(boards,pieces[i],&end,&start,&index,i);
		start = end;
		end = index;
	}

	// split w/ unknown pieces
	char allpieces[7] = {'O','S','Z','I','L','J','T'};
	for (int i = 0; i < 7; i++) {
		indices[i] = index;
		splitBoard(boards,allpieces[i],&end,&start,&index,2);
	}
	indices[7] = index;

	// get the best move
	char (*bestMove)[4] = getBest(boards, indices);

	free(boards);

	// return best move
	return bestMove;
}


int main() {

	struct Bitboard board;

	initBoard(&board);
	char pieces[2] = {'I','L'};

	getBot(board,pieces);

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
