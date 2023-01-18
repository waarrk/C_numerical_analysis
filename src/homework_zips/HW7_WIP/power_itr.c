#include <math.h>
#include <stdio.h>

#include "NAbasic.h"

#define MAX_ITER 1000
#define TOL 1e-5

FILE *fin;
double **matrix;
double At[3][3];  // 転置行列At
int row, col;

int i, j, k;
double x[3] = {1, 0, 0};  // 初期値
double lambda = 0;        // 最大固有値
double lambda_prev = 0;   // 1つ前の最大固有値

void largest() {
  // Power Iteration
  for (k = 0; k < MAX_ITER; k++) {
    // 行列Aとベクトルxの積を計算
    double Ax[3] = {0, 0, 0};
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        Ax[i] += matrix[i][j] * x[j];
      }
    }

    // ベクトルxの更新
    double x_norm = 0;
    for (i = 0; i < 3; i++) {
      x_norm += x[i] * x[i];
    }
    x_norm = sqrt(x_norm);
    for (i = 0; i < 3; i++) {
      x[i] = Ax[i] / x_norm;
    }

    // 最大固有値の更新
    lambda_prev = lambda;
    lambda = 0;
    for (i = 0; i < 3; i++) {
      lambda += x[i] * Ax[i];
    }

    // 収束判定
    if (fabs(lambda - lambda_prev) < TOL) {
      break;
    }
  }

  printf("Largest eigenvalue: %f\n", lambda);
}

void smallest() {
  // Power Iteration
  for (k = 0; k < MAX_ITER; k++) {
    // 行列Atとベクトルxの積を計算
    double Atx[3] = {0, 0, 0};
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        Atx[i] += At[i][j] * x[j];
      }
    }

    // ベクトルxの更新
    double x_norm = 0;
    for (i = 0; i < 3; i++) {
      x_norm += x[i] * x[i];
    }
    x_norm = sqrt(x_norm);
    for (i = 0; i < 3; i++) {
      x[i] = Atx[i] / x_norm;
    }

    // 最小固有値の更新
    lambda_prev = lambda;
    lambda = 0;
    for (i = 0; i < 3; i++) {
      lambda += x[i] * Atx[i];
    }

    // 収束判定
    if (fabs(lambda - lambda_prev) < TOL) {
      break;
    }
  }

  printf("Smallest eigenvalue: %f\n", lambda);
}

int main(int argc, char *argv[]) {
  /* 引数のチェック */
  if (argc != 2) {
    fprintf(stderr, "ERR: 引数の数が違います．%s\n", argv[0]);
    return 0;
  }

  /* CSVから行列を読み込む */
  if ((fin = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "ERR: ファイルを正常に読み込ませんでした．%s\n", argv[1]);
    return EXIT_FAILURE;
  }

  matrix = csvRead(&row, &col, fin);
  showMatrix((const double **)matrix, row, col);

  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      At[i][j] = matrix[j][i];
    }
  }

  largest();
  smallest();

  freeMatrix(matrix);
  return 0;
}
