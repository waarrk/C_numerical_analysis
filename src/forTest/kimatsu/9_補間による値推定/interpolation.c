/*
補間用関数群
*/

#include "interpolation.h"

/*
double LagrangeInterpolation(vector2 *init, int n, double x, int last)
  ラグランジュ補間
    戻り値
      yの計算結果（配列）

    パラメータ
      入力
        init: 最初の点（配列）
        n: 最初の点の数
        x: xの値
*/
double LagrangeInterpolation(vector2 *init, int n, double x)
{
  int i, k;
  double y;

  /* SUM */
  for (i = 0; i < n; i++)
  {
    y = init[i].y;
    /* PI */
    for (k = 0; k < n; k++)
    {
      if (k == i)
      {
        continue;
      }
      y *= (x - init[k].x) / (init[i].x - init[k].x);
    }
  }

  return y;
}

/*
double NewtonianInterpolation(vector2 *init, int n, double x, int a)
  ニュートン補間
    戻り値
      n個のyの計算結果（配列）

    パラメータ
      入力
        init: 最初の点（配列）
        n: 最初の点の数
        x: xの値
*/
double *NewtonianInterpolation(vector2 *init, int n, double x)
{
  int t, i;
  double b, *y, **matrix;

  /* yの値用メモリの確保 */
  y = allocVector(n);

  /* 差分商保存行列 */
  matrix = allocMatrix(n, n);

  /* 計算 */
  for (t = 1; t <= n; t++)
  {
    /* 差分商 */
    matrix[t - 1][0] = init[t - 1].y;
    for (i = 1; i < t; i++)
    {
      matrix[t - 1 - i][i] =
          (matrix[t - i][i - 1] - matrix[t - 1 - i][i - 1]) / (init[t - 1].x - init[t - 1 - i].x);
    }
    b = matrix[0][t - 1];

    /* PI */
    if (t == 1)
      y[t - 1] = b;
    else
    {
      y[t - 1] = b;
      for (i = 0; i <= t - 2; i++)
      {
        y[t - 1] *= (x - init[i].x);
      }
      y[t - 1] = y[t - 1] + y[t - 2];
    }
  }

  /* メモリの開放 */
  freeMatrix(matrix);

  return y;
}