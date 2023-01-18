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

  printf("-- Info -- \n");
  printf("係数行列Aファイル名: %s\n", argv[1]);
  printf("ベクトルYファイル名: %s\n", argv[2]);

  /* CSVを読み込み動的配列に格納 */
  fileReader(memory);
  double *answer = (double *)malloc(sizeof(double) * 3);

  /* 行列の三角化 */
  triangulation(memory);
  /* 上三角行列を解く*/
  backSubstitution(memory, answer);

  /*解の表示*/
  for (int i = 0; i < memory[0].col; i++) {
    printf("x%d = %g\n", i, answer[i]);
  }

  /* 終了処理 */
  free(answer);
  allAllocatedMemoryFree(memory);
  return EXIT_SUCCESS;
}