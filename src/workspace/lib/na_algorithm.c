#include "na_algorithm.h"

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
    printf("att: %d, left: %lf, right: %lf, result: %lf\n", attempts, left,
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
  printf("att: %d, result: %f\n", attempts, solution);
#endif

  /* 解の精度が十分に高くなるまで再帰 */
  if (attempts > 1) {
    return newton(solution, data, attempts - 1);
  } else {
    return solution;
  }
}