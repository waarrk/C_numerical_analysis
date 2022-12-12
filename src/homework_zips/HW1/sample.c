#include "NAbasic.h"

int main(void) {
  FILE *fin;
  double **matrix, **matrix2, **matrix3;
  double *vector, *vector2;
  int row, col;
  int k;

  /* CSV����s��E�x�N�g����ǂݍ��� */
  if ((fin = fopen("inData.csv", "r")) == NULL) {
    fprintf(stderr, "�t�@�C�������݂��܂���.\n");
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

  vector2 = matrix2colVector((const double **)matrix, row, col);
  for (k = 0; k < row * col; k++) {
    printf("%f, ", vector2[k]);
  }

  // �㏈���i���I�m�ۂ����z��͍폜��Y��Ȃ��j
  freeMatrix(matrix2);
  freeMatrix(matrix);
  freeMatrix(matrix3);
  freeVector(vector);
  freeVector(vector2);
  return 0;
}