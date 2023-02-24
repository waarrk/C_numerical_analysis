/*
最大・最小固有値の計算
*/

#include "NAbasic.h"
#include "NAplus.h"
#include "LUfunction.h"

#define ARG_NUM 2    /* コマンドライン引数の数 */
#define ERROR 0.0001 /* 収束条件誤差 */

/* 最大固有値の計算 */
double maxEigenvalues(double **matrix, double *y0, int row, int col);

/* 最小固有値の計算 */
double minEigenvalues(double **matrix, double *y1, int row, int col);

int main(int argc, char **argv)
{
  int i, j, row, col;
  double **matrix, **imatrix, *y0, lm_max, lm_min, *m;
  FILE *fin;

  /* コマンドライン引数の確認 */
  if (argCheck(argc, ARG_NUM))
  {
    return EXIT_FAILURE;
  }

  /* csvファイルから実数行列の読み込み */
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

  /* 行列が正方行列かどうかの確認 */
  if (squareMatrixCheck(row, col))
  {
    free(fin);
    matrixFree(matrix, row);
    return EXIT_FAILURE;
  }

  /* 初期値の設定 */
  y0 = arrayAlloc(col);
  if (y0 == NULL)
  {
    free(fin);
    matrixFree(matrix, row);
    return EXIT_FAILURE;
  }
  for (i = 0; i < col; i++)
  {
    y0[i] = 1.0;
  }

  /* 最大固有値を求める */
  lm_max = maxEigenvalues(matrix, y0, row, col);

  printf("最大固有値：%.1f\n", lm_max);

  /* 逆行列を求める */
  m = arrayAlloc(row * col);
  if (m == NULL)
  {
    matrixFree(matrix, row);
    return EXIT_FAILURE;
  }
  for (i = 0; i < row; i++)
  {
    for (j = 0; j < col; j++)
    {
      m[i * row + j] = matrix[i][j];
    }
  }
  imatrix = iMatrix(m, row);

  /* 初期値の設定 */
  y0 = arrayAlloc(col);
  if (y0 == NULL)
  {
    free(fin);
    matrixFree(matrix, row);
    return EXIT_FAILURE;
  }
  for (i = 0; i < col; i++)
  {
    y0[i] = 1.0;
  }

  /* 最小固有値を求める */
  lm_min = maxEigenvalues(imatrix, y0, row, col);
  lm_min = 1.0 / lm_min;

  printf("最小固有値：%.1f\n", lm_min);

  /* メモリの開放 */
  freeMatrix(matrix);
  freeMatrix(imatrix);
  freeVector(m);

  return EXIT_SUCCESS;
}

/*
double maxEigenvalues()
  最大固有値の計算
    戻り値
      最大固有値

    入力
      matrix: 行列
      y0: 初期条件ベクトル
      row: 行列の行数
      col: 行列の列数 / ベクトルの要素数
*/
double maxEigenvalues(double **matrix, double *y0, int row, int col)
{
  int i;
  double *y1, lm0, lm1;

  for (i = 0;; i++)
  {
    y1 = MVmul(matrix, y0, row, col);
    lm1 = (vecInnerProduct(y1, y1, col)) / (vecInnerProduct(y1, y0, col));
    if (i != 0)
    {
      if (fabs(lm1 - lm0) / fabs(lm0) < ERROR)
      {
        free(y0);
        free(y1);
        break;
      }
    }
    free(y0);
    y0 = y1;
    lm0 = lm1;
  }

  return lm0;
}
