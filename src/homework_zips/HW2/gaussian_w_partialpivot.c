/* ライブラリのインクルード */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"
#include "lib/memory_controller.h"

/* 各種マクロ定義 */
#define ARGC_QUANTITY 3

/*行列のk列目の絶対最大値を返す*/
double pivotSearch(int k, dynamicMemory *data);
/*行列のk行目とp行目を入れ替える*/
int swapRows(int k, int p, dynamicMemory *data);
/*行列のピボットされている行(selected)使ってある行(target)を割る*/
int dashRows(int selected, int target, dynamicMemory *data);
/*上三角行列の生成*/
int triangulation(dynamicMemory *data);
/*上三角行列を解く*/
int backSubstitution(dynamicMemory *data, double *x);

int main(int argc, char **argv) {
  /* 構造体の初期化 */
  dynamicMemory memory[3] = {
      {"係数行列A", argv[1], NULL, NULL},
      {"ベクトルY", argv[2], NULL, NULL},
      {NULL, NULL, NULL, NULL},
  };

  /* 引数のチェック */
  if (argc != ARGC_QUANTITY) {
    fprintf(stderr, "ERR!: 引数の数が違います　%s\n", argv[0]);
    return 0;
  }

  printf("-- Info -- \n");
  printf("係数行列Aファイル名: %s\n", argv[1]);
  printf("ベクトルYファイル名: %s\n", argv[2]);

  /* CSVを読み込み動的配列に格納 */
  fileReader(memory);
  double *answer = (double *)malloc(sizeof(double) * 3);

  /* 行列の三角化 */
  triangulation(memory);
  /* 上三角行列を解く*/
  backSubstitution(memory, answer);

  /*解の表示*/
  for (int i = 0; i < memory[0].col; i++) {
    printf("x%d = %g\n", i, answer[i]);
  }

  /* 終了処理 */
  free(answer);
  allAllocatedMemoryFree(memory);
  return EXIT_SUCCESS;
}

/*ユーザー定義関数群*/

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