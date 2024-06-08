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
	for (int i = *start; i < *end; i++) {

		char **moves = (char **)malloc(40 * sizeof(char *));
		for (int j = 0; j < 40; j++) {
			moves[j] = (char *)malloc(4 * sizeof(char));
		}

		int nummoves = getLegalMoves(piece, boards[i].board , moves);

		for (int j = 0; j < nummoves; j++) {
			boards[*index] = boards[i];
			playMove(boards[*index].board,&boards[*index].score, moves[j]);
			for (int k = 0; k < 4; k++) {
				boards[*index].moves[depth][k] = moves[j][k];
			}
			*index += 1;
		}

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
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < height[i]; j++) {
			if (isTileSet(board.board,i,height[i]-j-1)==0) {
				//holes += 1;
				//printf("i: %d j: %d over: %d under: %d\n",i,height[i]-j,height[i]-j-1,j);
				score -= (height[i]-j-1)*(height[i]-j-1)*20 + (j*j)*10 + 15;
			}
		}
	}

	// get relief 
	char gradient = 0;
	char currentGradient = 0;
	char maxGradient = 0;
	for (int i = 0; i < 10; i++) {
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

		currentGradient += gradient;
		if (currentGradient > maxGradient) {
			maxGradient = currentGradient;
		}
		currentGradient = 0;
	}
    
	// reward best well
	score += maxGradient;

	// punish height
	for (int i = 0; i < 10; i ++) {
		score -= height[i]*height[i];
        if (height[i] > 10) {
            score -= 300;
        }
	}
	
    free(height);

	return score;
}



bool arraysAreEqual(char arr1[3][4], char arr2[2][4]) {
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

	while (cont) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				currMove[i][j] = boards[indices[0]].moves[i][j];
			}
		}
		for (int i = 0; i < 7; i++) {
			currBestScore[i] = -10000;
			while (1) {
				if (indices[6] >= maxInt) {
					cont = 0;
					break;
				}
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
		for (int i = 0; i < 7; i++) {
			currScore += currBestScore[i];
		}
		if (currScore > bestScore) {
			bestScore = currScore;
			for (int i = 0; i < 4; i++) {
				bestMove[i] = currMove[0][i];
			}
		}
	}

    return &bestMove;
}


char *getBot(struct Bitboard board,char pieces[2]) {
	int start = 0;
	int end = 1;
	int index = 1;
	int indices[8];

	struct Bitboard *boards = (struct Bitboard *)malloc(449640 * sizeof(struct Bitboard));
    if (boards == NULL) {
        perror("Failed to allocate memory");
	}
	boards[0] = board;

	for (int i = 0; i < 2; i++) {
		splitBoard(boards,pieces[i],&end,&start,&index,i);
		start = end;
		end = index;
	}

	char allpieces[7] = {'O','S','Z','I','L','J','T'};
	for (int i = 0; i < 7; i++) {
		indices[i] = index;
		splitBoard(boards,allpieces[i],&end,&start,&index,2);
	}
	indices[7] = index;
	
    char (*bestMove)[4] = getBest(boards, indices);

    free(boards);

    /*
	printf("Best Move: ");
	printf("%c %d %d %d", (*bestMove)[0],(*bestMove)[1],(*bestMove)[2], (*bestMove)[3]);
    printf("\n");
    
    playMove(board.board,&board.score,bestMove);
    dispBoard(board.board);*/

	return *bestMove;
}
/*
int main() {

    struct Bitboard board;
	
    initBoard(&board);
	char pieces[2] = {'I','L'};

	getBot(board,pieces);
	
	
	for (int i = index-5; i < index; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d: %c %d %d %d\n",j,boards[i].moves[j][0], boards[i].moves[j][1], boards[i].moves[j][2], boards[i].moves[j][3]);
		}

		printf("score: %d\n",scoreBoard(boards[i]));
		dispBoard(boards[i].board);
	}8?
	
	
	return 0;
}
*/

/*
char randomize_piece() {
    char new_piece;
    switch (rand() % 7) {
    case 0:
        new_piece = 'O';
        break;
    case 1:
        new_piece = 'L';
        break;
    case 2:
        new_piece = 'I';
        break;
    case 3:
        new_piece = 'T';
        break;
    case 4:
        new_piece = 'S';
        break;
    case 5:
        new_piece = 'J';
        break;
    case 6:
        new_piece = 'Z';
        break;
    }

    return new_piece;
}

int main() {

    struct Bitboard board;
	
    initBoard(&board);
	char pieces[2];
    char *move;

    pieces[0] = randomize_piece();
    pieces[1] = randomize_piece();

    for (int i = 0; i < 1000; i++) {
        move = getBot(board,pieces);
        playMove(&board.board, &board.score, move);
        dispBoard(board.board);

        pieces[0] = pieces[1];
        pieces[1] = randomize_piece();
    }

    return 0;
}*/
