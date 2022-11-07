#include "NAbasic.h"

int main(void) {
  FILE *fin;
  double **matrix, **matrix2, **matrix3;
  double *vector, *vector2;
  int row, col;
  int k;

  /* CSVから行列・ベクトルを読み込む */
  if ((fin = fopen("inData.csv", "r")) == NULL) {
    fprintf(stderr, "ファイルが存在しません.\n");
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

  // 後処理（動的確保した配列は削除を忘れない）
  freeMatrix(matrix2);
  freeMatrix(matrix);
  freeMatrix(matrix3);
  freeVector(vector);
  freeVector(vector2);
  return 0;
}