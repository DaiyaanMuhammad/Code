#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include "matrix.h"

int main(){
	srand(time(NULL)); //for random generated entry values
	int row, col;
	printf("Enter row and colum: ");
	scanf("%dx%d", &row, &col);
	matrix input = createMatrix(row, col);	//allocating memory for input matrix
	matrix output = createMatrix(row, col);	//allocating memory for output matrix
	randEntries(input, 0, 1);				//randomly generating matrix entries

	for(int r=0; r<input.row; r++){
		for(int c=0; c<input.col; c++){
			int entryOUT = 9;				//if the number is anything other than 0, output entry is 9
			if(input.mat[r][c] == 0){
				int left, right, up, down;

				left = (c == 0)? 0: input.mat[r][c-1];
				right = (c == input.col-1)? 0: input.mat[r][c+1];
				up = (r == 0)? 0: input.mat[r-1][c];
				down = (r == input.row-1)? 0: input.mat[r+1][c];

				entryOUT = left+right+up+down;
			}
			output.mat[r][c] = entryOUT;
		}
	}
	printf("\nInput matrix\n");
	printMatrix(input);
	printf("\nOutput matrix\n");
	printMatrix(output);

	freeMatrix(2, input, output);

	return 0;
}
