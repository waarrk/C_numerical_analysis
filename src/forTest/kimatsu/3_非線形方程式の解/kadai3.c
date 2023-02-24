/*
    非線形方程式の解の計算（２分法＆ニュートン法）
*/

/*
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
*/
#include <math.h>

#include "NAbasic.h"

#define MAX_STR_LENGTH 200 /* 1行の文字数の最大値 */
#define EQUATION(x) \
  (x * x * x * x - 3 * x * x + 5 * x - 9) /* 非線型方程式の左辺 */
#define DEQUATION(x)                                                  \
  (4 * x * x * x - 6 * x + 5) /* 非線型方程式の左辺の微分 \
                               */
#define REPEAT_TIME 10        /* 繰り返す回数 */

/* 入力ファイルの読み込み */
/* 戻り値（0：成功，-1：ファイル読み込み失敗, -2：入力ファイル記載ミス） */
int inputRange(double *a, double *b, char *fname) {
  FILE *file;
  file = fopen(fname, "r");
  if (file == NULL) {
    fprintf(stderr, "ファイルの読み込みに失敗しました。\n");
    fprintf(stderr,
            "ファイル名が間違っているか，ファイルが破損している可能性があります"
            "。\n");
    return -1;
  }

  double **matrix;

  int row, col;
  matrix = csvRead(&row, &col, file);
  fclose(file);

  if ((row != 1) || (col != 2)) {
    fprintf(stderr, "入力ファイル内の記載方法が異なります。\n");
    freeMatrix(matrix);
    return -2;
  }

  *a = matrix[0][0];
  *b = matrix[0][1];

  freeMatrix(matrix);
  return 0;
}

/* 二分法 */
/* 戻り値（0：成功，-1：区間の下限と上限が同符号） */
int bisection(double a, double b) {
  /* 区間の上限と下限での符号チェック */
  if (EQUATION(a) * EQUATION(b) > 0.0) {
    fprintf(stderr, "区間の下限と上限の方程式の解が同符号です。\n");
    return -1;
  }

  /* 区間の上限と下限の設定 */
  double left, right, middle;
  left = fmin(a, b);
  right = fmax(a, b);

  /* 二分法の主要部 */
  int i;
  printf("回数    解\n");
  for (i = 0; i < REPEAT_TIME; i++) {
    middle = (left + right) / 2.0;
    printf("%d  %f\n", i, middle);

    if (EQUATION(left) * EQUATION(middle) > 0.0)
      left = middle;
    else if (EQUATION(right) * EQUATION(middle) > 0.0)
      right = middle;
  }
  middle = (left + right) / 2.0;
  printf("二分法 %d 回で求めた解は %f です。\n", REPEAT_TIME, middle);

  return 0;
}

/* ニュートン法 */
void newton(double a, double b) {
  int i;
  double x;
  x = (a + b) / 2.0; /* 初期値の設定 */

  printf("回数    解\n");
  for (i = 0; i < REPEAT_TIME; i++) {
    x = x - (EQUATION(x) / DEQUATION(x));
    printf("%d  %f\n", i + 1, x);
  }
  printf("ニュートン法 %d 回で求めた解は %f です。\n", REPEAT_TIME, x);
}

int main(int argc, char *argv[]) {
  /* コマンドライン引数のチェック */
  if (argc != 2) {
    fprintf(stderr, "コマンドライン引数の数が違います。\n");
    return EXIT_FAILURE;
  }

  /* 区間の上限と下限の読み込み */
  double a, b;
  if (inputRange(&a, &b, argv[1]) != 0) return EXIT_FAILURE;

  bisection(a, b);
  printf("\n");
  newton(a, b);

  return EXIT_SUCCESS;
}