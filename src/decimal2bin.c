#include <stdio.h>
#include <stdlib.h>
#include "NAbasic.h"

int main(){

	FILE *fin;
	double **matrix, **matrix2, **matrix3;
	double *vector, *vector2;
	int row, col;
	int k;

	if((fin = fopen("data/k1-input.csv", "r")) == NULL) {
		printf("File Open Error\n");
		return EXIT_FAILURE;
	}

	matrix = csvRead(&row, &col, fin);
	matrix2 = allocMatrix(row, col);
	vector = allocVector(row);

	printf("matrix: \n");
	showMatrix((const double **)matrix, row, col);
	matrix3 = tpMatrix((const double **)matrix, row, col);
	printf("matrix3: \n");
	showMatrix((const double **)matrix3, col, row);

	return EXIT_SUCCESS;
}