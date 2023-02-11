/* ? Yusaku WASHIO 2023 All rights reserved.*/

/* ライブラリのインクルード */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"
#include "lib/memory_controller.h"

/* 各種マクロ定義 */
#define ARGC_QUANTITY 2

/* 関数プロトタイプ */
float f(float x, float y);
float euler(float x_start, float h, float x_end, float y_start);

int main(int argc, char **argv) {
  /* 構造体の初期化 */
  dynamicMemory memory[2] = {
      {"範囲", argv[1], NULL, NULL},
      {NULL, NULL, NULL, NULL},
  };

  float answer;

  /* 引数のチェック */
  if (argc != ARGC_QUANTITY) {
    fprintf(stderr, "ERR: 引数の数が違います．%s\n", argv[0]);
    return 0;
  }

  printf("-- Info -- \n");
  printf("範囲ファイル名: %s\n", argv[1]);

  /* CSVを読み込み動的配列に格納 */
  fileReader(memory);

  /* 区間データの存在確認 */
  if (&memory[0].matrix[0][0] != NULL && &memory[0].matrix[0][1] != NULL &&
      &memory[0].matrix[0][2] != NULL && &memory[0].matrix[0][3] != NULL) {
    printf("xの初期値入力: [%g]\n", memory[0].matrix[0][0]);
    printf("ステップ幅入力: [%g]\n", memory[0].matrix[0][1]);
    printf("xの最終値入力: [%g]\n", memory[0].matrix[0][2]);
    printf("yの初期値入力: [%g]\n", memory[0].matrix[0][3]);

  } else {
    printf("ERR: CSVデータ が 異常 です．\n");
    /* 異常で終了 */
    allAllocatedMemoryFree(memory);
    return EXIT_FAILURE;
  }

  printf("-- OUTPUT -- \n");
  answer = euler(memory[0].matrix[0][0], memory[0].matrix[0][1],
                 memory[0].matrix[0][2], memory[0].matrix[0][3]);

  printf("-- EXIT -- \n");

  /* 終了処理 */
  allAllocatedMemoryFree(memory);
  return EXIT_SUCCESS;
}

/* 関数 */
float f(float x, float y) { return (x * (1 - y)); }

/*引数
  x_start : xの初期値
  h       : ステップ幅
  x_end   : xの最終値
  y_start : yの初期値
戻り値
  y_end   : xの最終値におけるyの値*/
float euler(float x_start, float h, float x_end, float y_start) {
  while (x_start < (x_end + h)) {
    printf("結果 [x, y]  =  [%.6f, %.6f]\n", x_start, y_start);
    y_start += h * f(x_start, y_start);
    x_start += h;
  }

  printf("xの最終値に達しました\n");
  return y_start;
}
