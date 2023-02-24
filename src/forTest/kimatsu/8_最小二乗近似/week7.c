/*
最小二乗近似
*/

#include "NAbasic.h"
#define DIMENSION 3 /* n次多項式 */

/*
  abs_d(double x)
    実数の絶対値を求める．
      戻り値: 実数の絶対値

    パラメータ
    　入力
        x: 実数
*/
double abs_d(double x)
{
  double a;
  a = x;

  if (a < 0.0)
    a *= -1;

  return a;
}

/*
 changeRow(double **matrix, int row1, int row2)
  行列データ（実数行列）の2つ行を入れ替える．
    戻り値: 入れ替え後の行列

    パラメータ
      出力
        matrix: 操作対象の行列

    　入力
        row: 操作対象の行列の行
        col: 操作対象の行列の列
        row1: 入れ替える行（1つ目）
        row2: 入れ替える行（2つ目）
*/
int changeRow(double **matrix, int row, int col, int row1, int row2)
{
  /* 入力値のチェック */
  if ((row < row1) || (row < row2))
  {
    fprintf(stderr, "入れ替える行に範囲外の行を指定しています．\n");
    return 1;
  }

  double *buf;
  buf = allocVector(col);

  /* 行の入れ替え */
  int i;
  for (i = 0; i < col; i++)
  {
    buf[i] = matrix[row1][i];
    matrix[row1][i] = matrix[row2][i];
    matrix[row2][i] = buf[i];
  }

  freeVector(buf);

  return 0;
}

/*
 pvEli(double **matrix1, int row, int col, double **matrix2, int k)
  ピボット選択付き前進消去
    戻り値: 終了ステータス

    パラメータ
      出力
        matrix1: 操作対象の行列（1つ目）
        matrix2: 操作対象の行列（2つ目）

      入力
        row: matrix1の行数（matrix2の行数）
        col: matrix1の列数
        k: 対象の左上（k行k列）
*/
int pvEli(double **matrix, int row, int col, double *vector, int k)
{
  double x;

  int i, j;
  for (i = k + 1; i < row; i++)
  {
    x = matrix[i][k] / matrix[k][k];
    for (j = k; j < col; j++)
      matrix[i][j] = matrix[i][j] - matrix[k][j] * x;
    vector[i] = vector[i] - vector[k] * x;
  }

  return EXIT_SUCCESS;
}

/*
 answer(double **matrix1, int row, int col, double **matrix2, double *vector)
  ピボット選択付き前進消去
    戻り値: 終了ステータス

    パラメータ
    　出力
        vector : 解

      入力
        matrix1: 左辺の行列（解の行列がかけられている方）
        matrix2: 右辺の行列
        row: matrix1の行数（matrix2の行数）
        col: matrix1の列数
*/
int answer(double **matrix, int row, int col, double *vector, double *ans)
{
  int i, j;
  for (i = row - 1; i >= 0; i--)
  {
    ans[i] = vector[i];
    for (j = row - 1; j > i; j--)
    {
      ans[i] -= matrix[i][j] * ans[j];
    }
    ans[i] /= matrix[i][i];
  }

  return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
  int i, j, k, l, row, col, row_max;
  double **matrix, x, *left, **right, *a;
  FILE *fin;

  /* csvファイルから行列の読み込み */
  fin = fopen(argv[1], "r");
  if (fin == NULL)
  {
    return EXIT_FAILURE;
  }
  matrix = csvRead(&row, &col, fin);
  if (matrix == NULL)
  {
    free(fin);
    return EXIT_FAILURE;
  }

  /* 左 */
  left = (double *)malloc(sizeof(double) * DIMENSION);
  for (i = 0; i < row; i++)
  {
    left[i] = 0.0;
    for (k = 0; k < row; k++)
    {
      x = 1.0;
      for (l = 0; l < i; l++)
      {
        x *= matrix[k][0];
      }
      left[i] += matrix[k][1] * x;
    }
  }
  /* 右 */
  right = allocMatrix(DIMENSION, DIMENSION);
  for (i = 0; i < DIMENSION; i++)
  {
    for (j = 0; j < DIMENSION; j++)
    {
      right[i][j] = 0.0;
      for (k = 0; k < row; k++)
      {
        x = 1.0;
        for (l = 0; l < j; l++)
        {
          x *= matrix[k][0];
        }
        for (l = 0; l < i; l++)
        {
          x *= matrix[k][0];
        }
        right[i][j] += x;
      }
    }
  }
  /* 部分ピボット */
  for (i = 0; i < DIMENSION - 1; i++)
  {
    /* 最大絶対値を含む行の探索． */
    for (j = row_max = i; j < DIMENSION; j++)
    {
      if (j == i)
        continue;
      if (abs_d(right[row_max][i]) < abs_d(right[j][i]))
        row_max = j;
    }

    /* i行i列が絶対最大値ではなかった場合 */
    if (row_max != i)
    {
      /* 行の入れ替え */
      changeRow(right, DIMENSION, DIMENSION, i, row_max);
      changeRow(right, DIMENSION, DIMENSION, i, row_max);
    }

    /* ピボット選択付き前進消去 */
    pvEli(right, DIMENSION, DIMENSION, left, i);
  }
  a = (double *)malloc(sizeof(double) * DIMENSION);
  answer(right, DIMENSION, DIMENSION, left, a);

  printf("近似曲線\ny = ");
  for (i = DIMENSION - 1; i >= 0; i--)
  {
    printf("a[%d] ", i);
    if (i != 0)
    {
      printf("* x");
      if (i != 1)
        printf("^%d ", i);
      printf(" + ");
    }
  }
  printf("\n");

  for (i = 0; i < DIMENSION; i++)
    printf("a[%d] : %f\n", i, a[i]);

  /* メモリの開放 */
  freeMatrix(matrix);
  freeMatrix(right);
  free(left);
  free(a);

  return EXIT_SUCCESS;
}