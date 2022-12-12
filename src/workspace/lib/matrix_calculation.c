#include "matrix_calculation.h"

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

double pivotSearch(int k, dynamicMemory *data) {
  double max = 0;
  int max_row = 0;

  /*最大絶対値を探索*/
  for (int i = k; i < data[0].col; i++) {
    if (data[0].matrix[i][k] > max) {
      max = data[0].matrix[i][k];
      max_row = i;
    }
  }
  if (max == 0) {
    exit(0);
  }
  return max_row;
}

int swapRows(int k, int p, dynamicMemory *data) {
  double tmp;
  tmp = data[1].matrix[k][0];
  data[1].matrix[k][0] = data[1].matrix[p][0];
  data[1].matrix[p][0] = tmp;
  for (int i = 0; i < data[0].col; i++) {
    tmp = data[0].matrix[k][i];
    data[0].matrix[k][i] = data[0].matrix[p][i];
    data[0].matrix[p][i] = tmp;
  }
  return EXIT_SUCCESS;
}

int dashRows(int selected, int target, dynamicMemory *data) {
  double tmp;
  double r =
      data[0].matrix[target][selected] / data[0].matrix[selected][selected];
  for (int i = 0; i < data[0].col; i++) {
    tmp = data[0].matrix[target][i];
    data[0].matrix[target][i] =
        data[0].matrix[target][i] - r * data[0].matrix[selected][i];
  }
  data[1].matrix[target][0] =
      data[1].matrix[target][0] - r * data[1].matrix[selected][0];
  return EXIT_SUCCESS;
}

int triangulation(dynamicMemory *data) {
  double pivot = 0;
  for (int i = 0; i < data[0].col; i++) {
    pivot = pivotSearch(i, data);
    swapRows(i, pivot, data);
    for (int j = i + 1; j < data[0].col; j++) {
      dashRows(i, j, data);
    }
  }
  return EXIT_SUCCESS;
}

int backSubstitution(dynamicMemory *data, double *x) {
  double tmp = 0;
  /*行*/
  for (int i = data[0].col - 1; i >= 0; i--) {
    tmp = 0;
    /*列*/
    for (int j = i + 1; j < data[0].col; j++) {
      tmp += data[0].matrix[i][j] * x[j];
    }
    x[i] = (data[1].matrix[i][0] - tmp) / data[0].matrix[i][i];
  }
  return EXIT_SUCCESS;
}