/* ライブラリのインクルード */
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"
#include "lib/memory_controller.h"
#include "lib/na_algorithm.h"

#define ARGC_QUANTITY 3

int main(int argc, char **argv) {
  /* 構造体の初期化 */
  dynamicMemory memory[3] = {
      {"関数", argv[1], NULL, NULL},
      {"区間", argv[2], NULL, NULL},
      {NULL, NULL, NULL, NULL},
  };

  double newton_default;
  double dichotomy_result;
  double newton_result;

  /* 引数のチェック */
  if (argc != ARGC_QUANTITY) {
    fprintf(stderr, "ERR: 引数の数が違います．%s\n", argv[0]);
    return 0;
  }

#if DEBUG
  printf("-- Info -- \n");
  printf("関数ファイル名: %s\n", argv[1]);
  printf("区間ファイル名: %s\n", argv[2]);
#endif

  /* CSVを読み込み動的配列に格納 */
  fileReader(memory);

  /* 関数の表示 */
#if DEBUG
  printf("関数: y = ");
  for (int i = 0; i < memory[0].col; i++) {
    if (memory[0].matrix[0][i] > 0) {
      printf("+%g", memory[0].matrix[0][i]);
    } else {
      printf("%g", memory[0].matrix[0][i]);
    }
    printf("x^%g", memory[0].matrix[1][i]);
  }
  printf("\n");
#endif

  /* 区間データの存在確認 */
  if (&memory[1].matrix[0][0] != NULL && &memory[1].matrix[0][1] != NULL) {
    printf("区間入力: [%g, %g]\n", memory[1].matrix[0][0],
           memory[1].matrix[0][1]);
  } else {
    printf("ERR: 区間CSVデータ が 異常 です．\n");
    /* 異常で終了 */
    allAllocatedMemoryFree(memory);
    return EXIT_FAILURE;
  }

#if DEBUG
  printf("-- OutPut -- \n");
  printf("二分探索処理...\n");
#endif
  /* 二分探索 */
  dichotomy_result = dichotomy(memory[1].matrix[0][0], memory[1].matrix[0][1],
                               memory, SEARCH_ATTEMPTS);

#if DEBUG
  printf("ニュートン法探索処理...\n");
#endif
  /* ニュートン法 */
  newton_default = (memory[1].matrix[0][0] + memory[1].matrix[0][1]) / 2;
  newton_result = newton(newton_default, memory, SEARCH_ATTEMPTS);

#if DEBUG
  printf("-- EXIT -- \n");
#endif

  /* 終了処理 */
  allAllocatedMemoryFree(memory);
  return EXIT_SUCCESS;
}