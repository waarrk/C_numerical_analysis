#include "LUfunction.h"

/*
 abs(double x);
  絶対値の計算
    戻り値: 絶対値

    パラメータ
      入力
        x: 実数値
*/
double abs_d(double x)
{
    return (x >= 0) ? x : -x; /* 最大絶対値の計算 */
}

/*
 diaMake(int side)
  対角行列（全ての成分が１）の作成
    戻り値: 対角行列の先頭ポインタ

    パラメータ
      入力
        side: 行数（もしくは列数）
*/
double **diaMake(int side)
{
    int i, j;
    double **matrix;

    matrix = allocMatrix(side, side);

    for (i = 0; i < side; i++)
    {
        for (j = 0; j < side; j++)
        {
            if (i == j)
            {
                matrix[i][j] = 1.0;
            }
            else
            {
                matrix[i][j] = 0.0;
            }
        }
    }

    return matrix;
}

/*
 rowChange(double **matrix, int row1, int row2, int col)
  行列の行を入れ替える
    パラメータ
      入力
        matrix: 入れ替え対象の行列
        row1:   入れ替える行1
        row2:   入れ替える行2
        col:    行列の列数
*/
void rowChange(double **matrix, int row1, int row2, int col)
{
    int i;
    double buf;

    for (i = 0; i < col; i++)
    {
        buf = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = buf;
    }
}

/*
 LUPMatrix(double *matrix, int side)
  逆行列を求める
    戻り値
      逆行列
    パラメータ
      入力
        side: 行列の行数（列数）
        matrix: 入力された行列
*/
double **iMatrix(double *matrix, int side)
{
    int i, j, k;
    int maxRow; /* 最大絶対値を含む行 */
    double buf;
    double *x, *y, *Pb;
    double **matrixL, **matrixU, **matrixP, **imatrixL, **imatrixU, **imatrixUL, **imatrix;

    /* U行列の用意 */
    matrixU = allocMatrix(side, side);
    for (i = 0; i < side; i++)
    {
        for (j = 0; j < side; j++)
        {
            matrixU[i][j] = matrix[i * side + j];
        }
    }

    /* L行列の用意 */
    matrixL = diaMake(side);

    /* P行列の用意 */
    matrixP = diaMake(side);

    for (i = 0; i < side - 1; i++)
    {
        /* 最大絶対値の探索 */
        for (maxRow = i, j = i + 1; j < side; j++)
        {
            if (abs_d(matrixU[j][i]) > abs_d(matrixU[maxRow][i]))
            {
                maxRow = j;
            }
        }

        /* 行の入れ替え */
        if (maxRow != i)
        {
            rowChange(matrixU, maxRow, i, side);
            rowChange(matrixP, maxRow, i, side);
            for (j = 0; j < i; j++)
            {
                buf = matrixL[maxRow][j];
                matrixL[maxRow][j] = matrixL[i][j];
                matrixL[i][j] = buf;
            }
        }

        /* 前進消去 */
        for (j = i + 1; j < side; j++)
        {
            /* L行列に代入 */
            matrixL[j][i] = matrixU[j][i] / matrixU[i][i];

            /* U行列の計算 */
            for (k = i; k < side; k++)
            {
                matrixU[j][k] -= matrixU[i][k] * matrixL[j][i];
            }
        }
    }

    /* 逆行列を求める */

    /* Lの逆行列を求める */
    imatrixL = diaMake(side);
    for (i = 0; i < side; i++)
    {
        for (j = i; j >= 0; j--)
        {
            if (i == j)
            {
                imatrixL[i][j] = 1.0 / matrixL[i][j];
            }
            else
            {
                imatrixL[i][j] = 0.0;
                for (k = 0; k < i; k++)
                {
                    imatrixL[i][j] -= matrixL[i][k] * imatrixL[k][j];
                }
                imatrixL[i][j] /= matrixL[i][k];
            }
        }
    }

    /* Uの逆行列を求める */
    imatrixU = diaMake(side);
    for (i = side - 1; i >= 0; i--)
    {
        for (j = i; j < side; j++)
        {
            if (i == j)
            {
                imatrixU[i][j] = 1.0 / matrixU[i][j];
            }
            else
            {
                imatrixL[i][j] = 0.0;
                for (k = side - 1; k > i; k--)
                {
                    imatrixU[i][j] -= matrixU[i][k] * imatrixU[k][j];
                }
                imatrixU[i][j] /= matrixU[i][k];
            }
        }
    }

    imatrixUL = allocMatrix(side, side);
    /* U^-1 L^-1 */
    for (i = 0; i < side; i++)
    {
        for (j = 0; j < side; j++)
        {
            imatrixUL[i][j] = 0.0;
            for (k = 0; k < side; k++)
            {
                imatrixUL[i][j] += imatrixU[i][k] * imatrixL[k][j];
            }
        }
    }

    imatrix = allocMatrix(side, side);
    /* U^-1 L^-1 P */
    for (i = 0; i < side; i++)
    {
        for (j = 0; j < side; j++)
        {
            imatrix[i][j] = 0.0;
            for (k = 0; k < side; k++)
            {
                imatrix[i][j] += imatrixUL[i][k] * matrixP[k][j];
            }
        }
    }

    freeMatrix(matrixL);
    freeMatrix(matrixU);
    freeMatrix(matrixP);
    freeMatrix(imatrixL);
    freeMatrix(imatrixU);
    freeMatrix(imatrixUL);

    return imatrix;
}