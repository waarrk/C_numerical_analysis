/* ライブラリのインクルード */
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"
#include "lib/matrix_calculation.h"
#include "lib/memory_controller.h"

/* 各種マクロ定義 */
#define ARGC_QUANTITY 3

int main(int argc, char **argv) {
  /* ファイルデータの読み込み後保存領域 */
  double **matrixOut;
  /* 行列積計算に使用する変数 */
  int rowOut, colOut;

  /* 構造体の初期化 */
  dynamicMemory memory[3] = {
      {"行列1", argv[1], NULL, NULL},
      {"行列2", argv[2], NULL, NULL},
      {NULL, NULL, NULL, NULL},
  };

  /* 引数のチェック */
  if (argc != ARGC_QUANTITY) {
    fprintf(stderr, "ERR!: 引数の数が違います　%s\n", argv[0]);
    return 0;
  }

  printf("-- Info -- \n");
  printf("係数行列Aファイル名: %s\n", argv[1]);
  printf("ベクトルYファイル名: %s\n", argv[2]);

  /* CSVを読み込み動的配列に格納 */
  fileReader(memory);

  printf("matrixA: \n");
  showMatrix((const double **)memory[0].matrix, memory[0].row, memory[0].col);
  printf("matrixB: \n");
  showMatrix((const double **)memory[1].matrix, memory[0].row, memory[0].col);

  /* 内積の計算が可能か確認 */
  if (memory[0].row != memory[1].row) {
    printf("この行列の組み合わせで積は計算できません．\n");
    return EXIT_FAILURE;
  }

  printf("--OutPut--\n");
  printf("matrixOut: \n");

  /* 行列の積を計算 */
  matrixOut = allocMatrix(memory[0].col, memory[1].row);
  innerProduct(0, 1, memory, matrixOut, &rowOut, &colOut);

  /* 計算結果の表示 */
  showMatrix((const double **)matrixOut, rowOut, colOut);

  /* 終了処理 */
  allAllocatedMemoryFree(memory);
  freeMatrix(matrixOut);
  return EXIT_SUCCESS;
}