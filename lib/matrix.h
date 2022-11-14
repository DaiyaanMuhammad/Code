#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include "array.h"

typedef struct Matrix{
	int row;
	int col;
	int **mat;
}matrix;

/*function to initialize the matrix through malloc*/
matrix createMatrix(int r, int c){
	matrix M;
	int failure=0;
	M.row = r;
	M.col = c;
	M.mat = (int **)malloc(sizeof(int*)*M.row);
	/*make sure the compiler did not fail to allocate memory */
	if(M.mat == NULL){
		failure=1;
		printf("\033[31mFailed to allocate memory for matrix\033[0m\n");
		exit(failure);
	}
	for(int i=0; i<M.row; i++){
		M.mat[i] = (int*)malloc(sizeof(int)*M.col);
		/*make sure the compiler did not fail to allocate memory */
		if(M.mat[i] == NULL){
			failure=1;
			printf("\033[31mFailed to allocate memory for matrix\033[0m\n");
			exit(failure);
		}
	}
	return M;
}
/* function to free the matrix from memory */
void destroyMatrix(matrix M){
	for(int i=0; i<M.row; i++){
		free(M.mat[i]);
	}
	free(M.mat);
}

/* use freeMatrix() in your main function to free the matrix from memory. */
void freeMatrix(int num, ...){
	va_list argArr;
	va_start(argArr, num);
	for(int i=0; i<num; i++){
		destroyMatrix(va_arg(argArr, matrix));
	}
}

/* function to get the matrix from the user */
void inputMatrix(matrix M){
	for(int r=0; r<M.row; r++){
		for(int c=0; c<M.col; c++){
			scanf("%d", &M.mat[r][c]);
		}
	}
}

/*function to get the matrix from random values*/

void randEntries(matrix M, int min, int max){
	/* use srand(time(NULL)); in your main function to initialize the random number generator */
	for(int r=0; r<M.row; r++){
		for(int c=0; c<M.col; c++){
			M.mat[r][c] = randomNum(min, max);
		}
	}
}

/* function to print the matrix on the console */
void printMatrixWithColor(matrix M){
	for(int r=0; r<M.row; r++){
		for(int c=0; c<M.col; c++){
			unsigned char elmnt = M.mat[r][c];
			printf("\033[48;2;%d;%d;%dm", elmnt, elmnt, elmnt);
			printf("\033[38;5;%dm %3d \033[0m", (elmnt>128)?0:255, elmnt);
		}
		printf("\n");
	}
}

void printAsPixels(matrix M){ //only for 0 to 9 values
	for(int r=0; r<M.row; r++){
		for(int c=0; c<M.col; c++){
			unsigned char elmnt = M.mat[r][c];
			printf("\033[48;2;%d;%d;%dm  \033[0m", elmnt, elmnt, elmnt);
		}
		printf("\n");
	}
}

void printMatrix(matrix M){
	for(int r=0; r<M.row; r++){
		for(int c=0; c<M.col; c++){
			int elmnt = M.mat[r][c];
			printf("%5d",elmnt);
		}
		printf("\n");
	}
}

matrix sumMatrix(matrix A, matrix B){
	matrix result = createMatrix(A.row, B.col);
	if((A.row == B.row) && (A.col == B.col)){
		for(int r=0; r<A.row; r++){
			for(int c=0; c<A.col; c++){
				result.mat[r][c] = A.mat[r][c] + B.mat[r][c];
			}
		}
	}
else{
		printf("The matricies can't be added\n");
		exit(1);
	}
	return result;
}

matrix prodMatrix(matrix A, matrix B){
	matrix result = createMatrix(A.row, B.col);
	if(A.col == B.row){
		for(int r=0; r<A.row; r++){
			for(int c=0; c<A.col; c++){
				result.mat[r][c] = 0;
				for(int i=0; i<B.row; i++){
					result.mat[r][c] += A.mat[r][i] * B.mat[i][c];
				}
			}
		}
	}
else{
		printf("The matricies can't be multiplied\n");
	exit(1);
	}
	return result;
}
