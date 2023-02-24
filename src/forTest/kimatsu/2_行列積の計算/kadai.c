/* 
課題2.
  行列積を計算するプログラム
*/
#include <stdio.h>
#include <stdlib.h>
#include "NAbasic.h"

int main(int argc, char *argv[]) {
  FILE *fin1, *fin2;
  double **matrix_A, **matrix_x, **matrix_ans;
  int row1, col1, row2, col2;

  int i, j, k;

  /* コマンドライン引数の確認 */
  if (argc != 3) {
    fprintf(stderr, "コマンドライン引数が間違っています．<*.exe> <input_file1> <input_file2>\n");
		return EXIT_FAILURE;
  }

  /* CSVファイルの読み込み */
  if ((fin1 = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "\"%s\"を開けませんでした.\n", argv[1]);
		return EXIT_FAILURE;
  }
  if ((fin2 = fopen(argv[2], "r")) == NULL) {
    fprintf(stderr, "\"%s\"を開けませんでした.\n", argv[2]);
    return EXIT_FAILURE;
  }

  /* CSVファイルから行列データの読み込み */
  matrix_A = csvRead(&row1, &col1, fin1);
  matrix_x = csvRead(&row2, &col2, fin2);

  printf("A:\n");
  showMatrix((const double**)matrix_A, row1, col1);
  printf("x:\n");
  showMatrix((const double**)matrix_x, row2, col2);

  /* 行列積が可能かの確認 */
  if (col1 != row2) {
    fprintf(stderr, "行列積の計算が行えない行列の組み合わせです．\n");
    return EXIT_FAILURE;
  }

  /* 計算結果用行列の用意 */
  matrix_ans = allocMatrix(row1, col2);

  for (i = 0; i < row1; i++) {
    for (j = 0; j < col2; j++) {
      matrix_ans[i][j] = 0.0;
    }
  }

  /* 行列積の計算 */
  for (i = 0; i < row1; i++) {
    for (j = 0; j < col2; j++) {
      for (k = 0; k < row2; k++) {
        matrix_ans[i][j] += matrix_A[i][k] * matrix_x[k][j];
      }
    }
  }

  /* 計算結果の出力 */
  printf("ans:\n");
  showMatrix((const double**)matrix_ans, row1, col2);

  /* メモリの開放 */
  fclose(fin1);
  fclose(fin2);
  freeMatrix(matrix_A);
  freeMatrix(matrix_x);
  freeMatrix(matrix_ans);

  return 0;
}