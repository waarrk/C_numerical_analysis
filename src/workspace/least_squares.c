#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4  // データ数

int main(void) {
  double x[N] = {-3.00, 1.00, 1.50, 4.70};   // x座標
  double y[N] = {-26.3, 2.05, 0.99, -29.0};  // y座標
  double a, b, c;                            // 係数

  // 係数を求めるための方程式を構築
  double S1 = 0, S2 = 0, S3 = 0, S4 = 0, S5 = 0;
  for (int i = 0; i < N; i++) {
    S1 += x[i] * x[i];
    S2 += x[i];
    S3 += x[i] * y[i];
    S4 += y[i];
  }
  a = (N * S3 - S2 * S4) / (N * S1 - S2 * S2);
  b = (S1 * S4 - S2 * S3) / (N * S1 - S2 * S2);
  c = (S4 - b * S2) / N;

  // 二次多項式を表す式を出力
  printf("y = %fx^2 + %fx + %f\n", a, b, c);

  return 0;
}