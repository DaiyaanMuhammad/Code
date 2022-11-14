#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include "matrix.h"
matrix blur(matrix input){ //must use with printAsPixels() to display
	matrix blurred = createMatrix(input.row, input.col);
	for(int r=0; r<input.row; r++){
		for(int c=0; c<input.col; c++){
			int left, right, up, down, cornerUR, cornerUL, cornerDR, cornerDL, entryOUT;

			left = (c == 0)? 0: input.mat[r][c-1];
			right = (c == input.col-1)? 0: input.mat[r][c+1];
			up = (r == 0)? 0: input.mat[r-1][c];
			down = (r == input.row-1)? 0: input.mat[r+1][c];
			cornerUL = (r == 0 || c == 0)? input.mat[r][c]: input.mat[r-1][c-1];
			cornerUR = (r == 0 || c == input.col-1)? input.mat[r][c]: input.mat[r-1][c+1];
			cornerDL = (r == input.row-1 || c == 0)? input.mat[r][c]: input.mat[r+1][c-1];
			cornerDR = (r == input.row-1 || c == input.col-1)? input.mat[r][c]: input.mat[r+1][c+1];

			entryOUT = (left + right + up + down + cornerUL + cornerUR + cornerDL + cornerDR + input.mat[r][c]) / 9;

			blurred.mat[r][c] = entryOUT;
		}
	}
	return blurred;
}
matrix perlinNoise(matrix input){ 	//must use with printAsPixels() to display
	matrix output = createMatrix(input.row, input.col);
	for(int r=0; r<input.row; r++){
		for(int c=0; c<input.col; c++){
			int left, right, up, down, cornerUR, cornerUL, cornerDR, cornerDL, entryOUT;

			left = (c == 0)? 0: input.mat[r][c-1];
			right = (c == input.col-1)? 0: input.mat[r][c+1];
			up = (r == 0)? 0: input.mat[r-1][c];
			down = (r == input.row-1)? 0: input.mat[r+1][c];
			cornerUL = (r == 0 || c == 0)? 0: input.mat[r-1][c-1];
			cornerUR = (r == 0 || c == input.col-1)? 0: input.mat[r-1][c+1];
			cornerDL = (r == input.row-1 || c == 0)? 0: input.mat[r+1][c-1];
			cornerDR = (r == input.row-1 || c == input.col-1)? 0: input.mat[r+1][c+1];

			entryOUT = left + right + up + down + cornerUL + cornerUR + cornerDL + cornerDR;

			output.mat[r][c] = entryOUT;
		}
	}
	return output;
}
int main(){
	srand(time(NULL)); //for random generated entry values
	int row, col, blr;
	scanf("%d %d %d", &row, &col, &blr);
	/* row = 105;		//zoomed out resolution of the kitty terminal */
	/* col = 192; 		//zoomed out resolution of the kitty terminal */
	matrix input = createMatrix(row, col);	//allocating memory for input matrix
	matrix perlin = createMatrix(row, col);	//allocating memory for output matrix
	randEntries(input, 0, 30);				//randomly generating matrix entries
	for(int r=0; r<input.row; r++){
		for(int c=0; c<input.col; c++){
			unsigned char elmnt = input.mat[r][c];
			printf("\033[48;2;%d;%d;%dm  \033[0m", elmnt*8, elmnt*8, elmnt*8);
		}
		printf("\n");
	}

	perlin = perlinNoise(input);
	printf("\n");
	printAsPixels(perlin);
	for(int i=0; i< blr; i++){ //number of blur passes
		perlin = blur(perlin);
		printf("\n");
		printAsPixels(perlin);
	}
	freeMatrix(2, input, perlin);

	return 0;
}
