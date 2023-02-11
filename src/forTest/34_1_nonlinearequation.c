/* ? Yusaku WASHIO 2023 All rights reserved.*/

/* ライブラリのインクルード */
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"
#include "lib/memory_controller.h"

/* 各種マクロ定義 */
#define DEBUG 1
#define ARGC_QUANTITY 3

#define SEARCH_ATTEMPTS 10

/* 関数プロトタイプ */
/**
 * @param x 関数のxがわかっている際入力
 * @param data 動的確保した構造体配列のポインタ
 * @param left 二分探索区間の左端
 * @param right 二分探索区間の右端
 * @param newton_default　ニュートン法の初期値
 * @param attempts 探索の試行回数
 */
double equationSolver(double x, dynamicMemory *data);
double dichotomy(double left, double right, dynamicMemory *data, int attempts);
double differential(double x, dynamicMemory *data);
double newton(double newton_default, dynamicMemory *data, int attempts);

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

/* xがわかっているときyを計算する関数 */
double equationSolver(double x, dynamicMemory *data) {
  double tmp = 1;
  double solution = 0;

  /* 解の計算 */
  for (int i = 0; i < data[0].col; i++) {
    for (int j = 0; j < (data[0].matrix[1][i]); j++) {
      tmp *= x;
    }
    tmp *= data[0].matrix[0][i];
    solution += tmp;
    tmp = 1;
  }
  return solution;
}

/* 二分探索で解を推定 */
double dichotomy(double left, double right, dynamicMemory *data, int attempts) {
  double mid;
  mid = (left + right) / 2;
  /* 符号反転条件に従い解の区間を再指定 */
  if ((equationSolver(mid, data) * equationSolver(left, data)) < 0) {
    right = mid;
  } else if ((equationSolver(mid, data) * equationSolver(right, data)) < 0) {
    left = mid;
  }

  /* 解の精度が十分に高くなるまで再帰 */
  if (attempts > 1) {
#if DEBUG
    printf("att: %d, left: %lf, right: %lf, mid: %lf\n", attempts, left, right,
           mid);
#endif
    return dichotomy(left, right, data, attempts - 1);
  } else {
    printf("att: %d, left: %lf, right: %lf, result: %.9lf\n", attempts, left,
           right, mid);
    return mid;
  }
}

/* 高次の微係数を導出 */
double differential(double x, dynamicMemory *data) {
  double tmp = 1;
  double solution = 0;

  /* 微係数の導出 */
  for (int i = 0; i < data[0].col; i++) {
    for (int j = 0; j < (data[0].matrix[1][i] - 1); j++) {
      /* 次数をひとつ下げてx^Nを計算*/
      tmp *= x;
    }
    /* 各項を求める */
    tmp *= data[0].matrix[0][i] * data[0].matrix[1][i];
    solution += tmp;
    tmp = 1;
  }
  return solution;
}

/* ニュートン法 */
double newton(double newton_default, dynamicMemory *data, int attempts) {
  double solution = 0;

  /* 漸化式を用いて近似値を計算 */
  solution = newton_default - (equationSolver(newton_default, data) /
                               differential(newton_default, data));

#if DEBUG
  printf("att: %d, result: %.9f\n", attempts, solution);
#endif

  /* 解の精度が十分に高くなるまで再帰 */
  if (attempts > 1) {
    return newton(solution, data, attempts - 1);
  } else {
    return solution;
  }
}