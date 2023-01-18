#include "matrix_calculation.h"

int matrixProduct(int left, int right, dynamicMemory *data, double **matrixOut,
                  int *rowOut, int *colOut) {
  /* 行列の要素計算用変数 */
  int element;
  int i;

  /* matrixAとmatrixBから積matrixOutを計算*/
  for (*rowOut = 0; *rowOut < data[0].row; (*rowOut)++) {
    for (*colOut = 0; *colOut < data[1].col; (*colOut)++) {
      /* 行列要素の計算 */
      /* A1*b1 + A2*B2 ....*/
      element = 0;
      for (i = 0; i < data[1].row; i++) {
        element += data[0].matrix[*rowOut][i] * data[1].matrix[i][*colOut];
      }
      matrixOut[*rowOut][*colOut] = element;
    }
  }
  return EXIT_SUCCESS;
}

int innerProduct(int left, int right, dynamicMemory *data, double **matrixOut,
                 int *rowOut, int *colOut) {
  /* 行列の要素計算用変数 */
  int element;
  int i, j;

  double **trans = allocMatrix(data[0].col, data[0].row);

  for (i = 0; i < data[0].row; i++) {
    for (j = 0; j < data[0].col; j++) {
      trans[j][i] = data[0].matrix[i][j];
    }
  }

  /* matrixAとmatrixBから積matrixOutを計算*/
  for (*rowOut = 0; *rowOut < data[0].col; (*rowOut)++) {
    for (*colOut = 0; *colOut < data[1].col; (*colOut)++) {
      /* 行列要素の計算 */
      /* A1*b1 + A2*B2 ....*/
      element = 0;
      for (i = 0; i < data[1].row; i++) {
        element += trans[*rowOut][i] * data[1].matrix[i][*colOut];
      }
      matrixOut[*rowOut][*colOut] = element;
    }
  }
  return EXIT_SUCCESS;
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