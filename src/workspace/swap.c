/* ライブラリのインクルード */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"
#include "lib/matrix_calculation.h"
#include "lib/memory_controller.h"

/* 各種マクロ定義 */
#define ARGC_QUANTITY 3

int main(int argc, char **argv) {
  /* 構造体の初期化 */
  dynamicMemory memory[3] = {
      {"係数行列A", argv[1], NULL, NULL},
      {"ベクトルY", argv[2], NULL, NULL},
      {NULL, NULL, NULL, NULL},
  };

  /* 引数のチェック */
  if (argc != ARGC_QUANTITY) {
    fprintf(stderr, "ERR!: 引数の数が違います　%s\n", argv[0]);
    return 0;
  }

  /* CSVを読み込み動的配列に格納 */
  fileReader(memory);

  printf("-- Original -- \n");
  printf("matrixA: \n");
  showMatrix((const double **)memory[0].matrix, memory[0].row, memory[0].col);

  swapRows(0, 2, memory);

  printf("-- Swap -- \n");
  showMatrix((const double **)memory[0].matrix, memory[0].row, memory[0].col);

  /* 終了処理 */
  allAllocatedMemoryFree(memory);

  return EXIT_SUCCESS;
}