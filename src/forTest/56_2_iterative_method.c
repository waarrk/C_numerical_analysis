/* ? Yusaku WASHIO 2023 All rights reserved.*/

/* ライブラリのインクルード */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"
#include "lib/matrix_calculation.h"
#include "lib/memory_controller.h"

/* 各種マクロ定義 */
#define ARGC_QUANTITY 3

#define SEARCH_ATTEMPTS 100

int main(int argc, char **argv) {
  /* 構造体の初期化 */
  dynamicMemory memory[3] = {
      {"係数行列A", argv[1], NULL, NULL},
      {"ベクトルb", argv[2], NULL, NULL},
      {NULL, NULL, NULL, NULL},
  };

  /* 引数のチェック */
  if (argc != ARGC_QUANTITY) {
    fprintf(stderr, "ERR!: 引数の数が違います　%s\n", argv[0]);
    return 0;
  }

  /* CSVを読み込み動的配列に格納 */
  fileReader(memory);

  printf("-- Info -- \n");
  printf("係数行列Aファイル名: %s\n", argv[1]);
  showMatrix((const double **)memory[0].matrix, memory[0].row, memory[0].col);
  printf("ベクトルbファイル名: %s\n", argv[2]);
  showMatrix((const double **)memory[1].matrix, memory[1].row, memory[1].col);

  printf("-- OutPut -- \n");
  /* 行列のLU分解 */
  printf("ヤコビ法\n");
  jacobiMethod(memory, SEARCH_ATTEMPTS);
  printf("ガウスザイデル法\n");
  gaussSeidelMethod(memory, SEARCH_ATTEMPTS);

  /* 終了処理 */
  allAllocatedMemoryFree(memory);
  return EXIT_SUCCESS;
}