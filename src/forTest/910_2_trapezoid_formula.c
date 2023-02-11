/* ? Yusaku WASHIO 2023 All rights reserved.*/

/* ライブラリのインクルード */
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"
#include "lib/memory_controller.h"

/* 各種マクロ定義 */
#define DEBUG 1
#define ARGC_QUANTITY 2

#define SEARCH_ATTEMPTS 10

/* 関数プロトタイプ */
float f(float x);
float trapezoid_integral(int division, float a, float b);

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
      &memory[0].matrix[0][2] != NULL) {
    printf("分割数入力: [%g]\n", memory[0].matrix[0][0]);
    printf("積分範囲入力: [%g, %g]\n", memory[0].matrix[0][1],
           memory[0].matrix[0][2]);

  } else {
    printf("ERR: CSVデータ が 異常 です．\n");
    /* 異常で終了 */
    allAllocatedMemoryFree(memory);
    return EXIT_FAILURE;
  }

  printf("-- OUTPUT -- \n");
  answer = trapezoid_integral(memory[0].matrix[0][0], memory[0].matrix[0][1],
                              memory[0].matrix[0][2]);

  printf("積分結果 [%g]\n", answer);

  printf("-- EXIT -- \n");

  /* 終了処理 */
  allAllocatedMemoryFree(memory);
  return EXIT_SUCCESS;
}

/* 関数 */
float f(float x) { return x * x; }

/*  division 分割数（近似漸近和の詳細度）
    a b 積分範囲*/

float trapezoid_integral(int division, float a, float b) {
  float delta = (b - a) / division;
  float s = 0;
  s = f(a) + f(b);

  int i;
  for (i = 1; i <= division - 1; i++) {
    s = s + 2 * f(a + i * delta);
  }

  s = delta / 2 * s;
  return s;
}