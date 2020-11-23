#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#define DIM 1000

/* 
 * The program creates 3 square matrices(arr1, arr2, sum) of size DIM (customizable).
 * The first two matrices are filled with random values ranging from 0 - 100
 * The third one(sum) is created with the sums of the other two.
 * sum is finally printed out.
 *
*/


int main(int argc, char *argv)	{

	srand(time(NULL));
	uint16_t* arr1 = (uint16_t*)malloc(DIM*sizeof(uint16_t));
	uint16_t* arr2 = (uint16_t*)malloc(DIM*sizeof(uint16_t));
	uint16_t* sum = (uint16_t*)malloc(DIM*sizeof(uint16_t));

	for (uint16_t i = 0; i < DIM; i++) {
		arr1[i] = rand() % 100;
		arr2[i] = rand() % 100;
		sum[i] = arr1[i] + arr2[i];
	
	}

	for (uint16_t i = 0; i < DIM; i++) {
		printf("index %d: value: %d\n", i, sum[i]);
	}

	return 0;
}
