/* ? Yusaku WASHIO 2023 All rights reserved.*/

/* ライブラリのインクルード */
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"

/* 行列積計算関数 */
int matrixProduct(const double **matrixA, const double **matrixB,
                  double **matrixOut, int *rowA, int *colA, int *rowB,
                  int *colB, int *rowOut, int *colOut) {
  /* 行列の要素計算用変数 */
  int element;
  int i;

  /* matrixAとmatrixBから積matrixOutを計算*/
  for (*rowOut = 0; *rowOut < *rowA; (*rowOut)++) {
    for (*colOut = 0; *colOut < *colB; (*colOut)++) {
      /* 行列要素の計算 */
      /* A1*b1 + A2*B2 ....*/
      element = 0;
      for (i = 0; i < *rowB; i++) {
        element += matrixA[*rowOut][i] * matrixB[i][*colOut];
      }
      matrixOut[*rowOut][*colOut] = element;
    }
  }
  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  /* CSVファイルのインスタンス */
  FILE *finA, *finB;
  /* ファイルデータの読み込み後保存領域 */
  double **matrixA, **matrixB, **matrixOut;
  /* 行列積計算に使用する変数 */
  int rowA, colA, rowB, colB, rowOut, colOut;

  /* 引数のチェック */
  if (argc != 3) {
    fprintf(stderr, "ERR: 引数の数が違います．%s\n", argv[0]);
    return 0;
  }
  printf("-- Info -- \n");
  printf("A行列ファイル名: %s\n", argv[1]);
  printf("B行列ファイル名: %s\n", argv[2]);

  /* CSVから行列を読み込む */
  if ((finA = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "ERR: ファイルを正常に読み込ませんでした．%s\n", argv[1]);
    return EXIT_FAILURE;
  }
  if ((finB = fopen(argv[2], "r")) == NULL) {
    fprintf(stderr, "ERR: ファイルを正常に読み込ませんでした．%s\n", argv[2]);
    return EXIT_FAILURE;
  }

  matrixA = csvRead(&rowA, &colA, finA);
  matrixB = csvRead(&rowB, &colB, finB);
  fclose(finA);
  fclose(finB);

  printf("matrixA: \n");
  showMatrix((const double **)matrixA, rowA, colA);
  printf("matrixB: \n");
  showMatrix((const double **)matrixB, rowB, colB);

  /* 行列積の計算が可能か確認 */
  if (colA != rowB) {
    printf("この行列の組み合わせで積は計算できません．\n");
    return EXIT_FAILURE;
  }

  printf("--OutPut--\n");
  printf("matrixOut: \n");

  /* 行列の積を計算 */
  matrixOut = allocMatrix(rowA, colB);
  matrixProduct((const double **)matrixA, (const double **)matrixB, matrixOut,
                &rowA, &colA, &rowB, &colB, &rowOut, &colOut);

  /* ファイルデータのメモリ領域開放 */
  freeMatrix(matrixA);
  freeMatrix(matrixB);

  /* 計算結果の表示 */
  showMatrix((const double **)matrixOut, rowOut, colOut);
  return EXIT_SUCCESS;
}