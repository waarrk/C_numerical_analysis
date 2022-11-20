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
double equationSolver(double x, dynamicMemory *data);
double dichotomy(double left, double right, dynamicMemory *data, int attempts);
double differential(double x, dynamicMemory *data);

double newton(double newton_default, dynamicMemory *data, int attempts) {
  double solution = 0;

  /* 漸化式を用いて近似値を計算 */
  solution = newton_default - (equationSolver(newton_default, data) /
                               differential(newton_default, data));

#if DEBUG
  printf("att: %d, solution: %f\n", attempts, solution);
#endif

  /* 解の精度が十分に高くなるまで再帰 */
  if (attempts > 1) {
    return newton(solution, data, attempts - 1);
  } else {
    return solution;
  }
}

int main(int argc, char **argv) {
  /* 構造体の初期化 */
  dynamicMemory memory[3] = {
      {"関数", argv[1], NULL, NULL},
      {"区間", argv[2], NULL, NULL},
      {NULL, NULL, NULL, NULL},
  };

  double newton_default;

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

  /* 二分探索 */
  dichotomy(memory[1].matrix[0][0], memory[1].matrix[0][1], memory,
            SEARCH_ATTEMPTS);

  /* ニュートン法 */
  newton_default = (memory[1].matrix[0][0] + memory[1].matrix[0][1]) / 2;
  newton(newton_default, memory, SEARCH_ATTEMPTS);

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
#if DEBUG
  printf("att: %d, left: %g, right: %g, mid: %g\n", attempts, left, right, mid);
#endif
  /* 符号反転条件に従い解の区間を再指定 */
  if ((equationSolver(mid, data) * equationSolver(left, data)) < 0) {
    right = mid;
  } else if ((equationSolver(mid, data) * equationSolver(right, data)) < 0) {
    left = mid;
  }

  /* 解の精度が十分に高くなるまで再帰 */
  if (attempts > 1) {
    return dichotomy(left, right, data, attempts - 1);
  } else {
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