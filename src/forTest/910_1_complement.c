/* Hisho SEKI
・生成された実行ファイルを以下の形式で実行してください。
> (実行ファイル) （点データファイル）（xの値）*/

#include "lib/NAbasic.h"       /* 数値解析用基本関数群 */
#include "lib/NAplus.h"        /* 数値解析用追加関数群 */
#include "lib/interpolation.h" /* 補間用関数群 */

#define ARGC_NUM 3 /* コマンドライン引数の数 */

int main(int argc, char **argv) {
  int row, col, i;
  double **matrix, x, *y;
  FILE *fp;
  vector2 *init;

  /* コマンドライン引数チェック */
  if (argCheck(argc, ARGC_NUM)) return 0;

  /* ファイルを開く */
  if (fileOpen(&fp, argv[1], "r")) return 0;

  /* ファイルのデータを取得 */
  matrix = csvRead(&row, &col, fp);
  if (matrix == NULL) return 0;

  /* データの確認 */
  if (col != 2) {
    fprintf(stderr, "Input data must be in two columns.\n");
    freeMatrix(matrix);
    return 0;
  }

  /* 最初の点の準備 */
  init = (vector2 *)malloc(sizeof(vector2) * row);
  for (i = 0; i < row; i++) {
    init[i].x = matrix[i][0];
    init[i].y = matrix[i][1];
  }

  /* xの値 */
  x = atof(argv[2]);
  printf("x = %f\n", x);

  /* 補間の計算 */
  y = NewtonianInterpolation(init, row, x);

  /* 結果の表示 */
  printf("                    | yの値\n");
  for (i = 1; i <= row; i++) {
    printf("%3d行目までのデータ | %f\n", i, y[i - 1]);
  }

  /* メモリの開放 */
  freeMatrix(matrix);
  free(init);
  free(y);
  fclose(fp);
}