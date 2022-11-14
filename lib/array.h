#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct List_t{
	int len;
	int *arr;
}list;

int n;
int arr[10][5];

list createList(int len){
	list array;
	array.len = len;
	array.arr = (int *) malloc(sizeof(int)*array.len);
	return array;
}

void destroyList(list array){
	free(array.arr);
}

void freeList(int num, ...){
	va_list argList;
	va_start(argList, num);
	for(int i=0; i<num; i++){
		destroyList(va_arg(argList, list));
	}
}

int freq(list arr, int value){
	int freq=0;
	for (int i=0; i<arr.len; i++) if (value == arr.arr[i]) freq++;
	return freq;
}

int* inputArr(int size){
	int *out;
	int arr[size];
	printf("Input %d numbers: ", size);
	for (int i=0; i<size; i++){
		scanf("%d", &arr[i]);
	}
	out=arr;
	return out;
}

int randomNum(int min, int max){
	int n = (rand() % (max - min + 1)) + min;
	return n;
}

list randArr(int min, int max, int len){
	list arr = createList(len);
	for(int i = 0; i < arr.len; i++){
		arr.arr[i] = randomNum(min, max);
	}
	return arr;
	/* be sure to free the array after the output */
}

void printList(list arr){
	for (int i=0; i<arr.len; i++){
		printf("%d, ", arr.arr[i]);
	}
	printf("\n");
}

list uniqVals(list array){
	list uniqNums;
	uniqNums.arr = array.arr;
	uniqNums.len = 1;

	for (int i = 0; i < array.len; i++){
		if (freq(uniqNums, array.arr[i]) == 0){
			*(uniqNums.arr + uniqNums.len) = array.arr[i];
			uniqNums.len++;
		}
	}
	return uniqNums;
}

int max(int *arr, int size){
	int max=arr[0];
	for(int i=1; i<size; i++) max=(arr[i]>max)?arr[i]:max;
	return max;
}
