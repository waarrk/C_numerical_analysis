/* ? Yusaku WASHIO 2023 All rights reserved.*/

/* ライブラリのインクルード */
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"

int main(int argc, char *argv[]) {
  /* CSVファイルのインスタンス */
  FILE *fin;
  /* ファイルデータの読み込み後保存領域 */
  double **matrix;
  int row, col;
  /* 2進数変換時に使用する変数 */
  char buf[sizeof(double)];
  int i, j, k;

  /* 引数のチェック */
  if (argc != 2) {
    fprintf(stderr, "ERR: 引数の数が違います．%s\n", argv[0]);
    return 0;
  }
  printf("-- Info -- \n");
  printf("ファイル名: %s\n", argv[1]);

  /* ファイルの読み込み */
  if ((fin = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "ERR: ファイルを正常に読み込ませんでした．%s\n", argv[1]);
    return EXIT_FAILURE;
  }

  /* CSVを二次元配列にコピー */;
  matrix = csvRead(&row, &col, fin);
  fclose(fin);

  /* 1行1列目のデータの存在確認 */
  if (&matrix[0][0] != NULL) {
    printf("元数値: %g\n", matrix[0][0]);
  } else {
    printf("ERR: matrix[0][0] が NULL です．\n");
    return EXIT_FAILURE;
  }

  /* メモリアドレスを処理用バッファにコピー */
  memcpy(buf, &matrix[0][0], sizeof(double));

  /* ファイルデータのメモリ領域開放 */
  freeMatrix(matrix);

  /* バッファの中身をIEEE754形式にダンプ */
  printf("-- OutPut -- \n");
  printf("sEEEEEEE EEEEdddd dddddddd... \n");
  for (i = sizeof(double) - 1; i >= 0; i--) {
    for (j = sizeof(buf[i]) * 8 - 1; j >= 0; j--) {
      k = buf[i] & (1 << j);
      printf("%d", k ? 1 : 0);
    }
    printf(" ");
  }
  printf("\n");
  return EXIT_SUCCESS;
}