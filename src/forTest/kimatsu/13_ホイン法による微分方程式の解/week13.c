/*
ホイン法による微分方程式の解
dy/dx = -xy + x

xの初期値，ステップ幅，xの最終値，yの初期値

bcc32c ./week13.c ./NAbasic.c
./week13.exe ./k13-input.csv
*/

#include "NAbasic.h"
#include "math.h"

#define EQU(x, y) (-1 * x * y + x) /* 微分方程式の右辺 */

int main(int argc, char **argv) {
  int i, row, col;
  double **matrix, step, x, y, x_e;
  FILE *fin;

  /* csvファイルから行列の読み込み */
  fin = fopen(argv[1], "r");
  if (fin == NULL) {
    return EXIT_FAILURE;
  }
  matrix = csvRead(&row, &col, fin);
  if (matrix == NULL) {
    free(fin);
    return EXIT_FAILURE;
  }

  printf("解：\n");

  step = matrix[0][1];
  x = matrix[0][0];
  y = matrix[0][3];
  x_e = matrix[0][2];
  printf("x=%f, y=%f\n", x, y);
  for (i = 0;; i++) {
    x += step;
    if (x > x_e) break;
    y = y + step * 0.5 *
                ((EQU(step * i, y)) + (EQU(x, y + (EQU(step * i, y)) * step)));

    printf("x=%f, y=%f\n", x, y);
  }

  /* メモリの開放 */
  freeMatrix(matrix);

  return EXIT_SUCCESS;
}