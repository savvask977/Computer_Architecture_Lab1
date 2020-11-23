#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#define DIM 1000

/*
 * The program creates a random array of dimension DIM (specified by the user). 
 * Then it prints the elements of the array
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
