/* ライブラリのインクルード */
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"
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
    fprintf(stderr, "ERR: 引数の数が違います．%s\n", argv[0]);
    return 0;
  }

  printf("-- Info -- \n");
  printf("係数行列Aファイル名: %s\n", argv[1]);
  printf("ベクトルYファイル名: %s\n", argv[2]);

  /* CSVを読み込み動的配列に格納 */
  fileReader(memory);

  /* 終了処理 */
  allAllocatedMemoryFree(memory);
  return EXIT_SUCCESS;
}