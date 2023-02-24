/* 第4週目課題 部分ピボット選択付きガウスの消去法 */

/*
#include <stdio.h>
#include <stdlib.h>
*/
#include "NAbasic.h"

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
int pvEli(double **matrix1, int row, int col, double **matrix2, int k)
{
    double x;

    int i, j;
    for (i = k + 1; i < row; i++)
    {
        x = matrix1[i][k] / matrix1[k][k];
        for (j = k; j < col; j++)
            matrix1[i][j] = matrix1[i][j] - matrix1[k][j] * x;
        matrix2[i][0] = matrix2[i][0] - matrix2[k][0] * x;
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
int answer(double **matrix1, int row, int col, double **matrix2, double *vector)
{
    int i, j;
    for (i = row - 1; i >= 0; i--)
    {
        vector[i] = matrix2[i][0];
        for (j = row - 1; j > i; j--)
        {
            vector[i] -= matrix1[i][j] * vector[j];
        }
        vector[i] /= matrix1[i][i];
    }

    return EXIT_SUCCESS;
}

/*
showVector(double **vector, int col)
  解の列データを出力する．
      戻り値: 表示結果

      パラメータ
        出力
          matrix: 出力対象列データ

        入力
        　col: 変換前の配列の要素数
*/
int showVector(double *vector, int col)
{
    int i;

    for (i = 0; i < col; i++)
        printf("x%d: %.4f\n", i + 1, vector[i]);

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    FILE *fin1, *fin2;

    /* 引数の数のチェック */
    if (argc != 3)
    {
        fprintf(stderr, "コマンドライン引数の数が間違っています．\n");
        return EXIT_FAILURE;
    }

    /* ファイルの読み込み */
    fin1 = fopen(argv[1], "r");
    if (fin1 == NULL)
    {
        fprintf(stderr, "ファイルを開けませんでした．\n");
        fprintf(stderr, "  file : %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    fin2 = fopen(argv[2], "r");
    if (fin2 == NULL)
    {
        fprintf(stderr, "ファイルを開けませんでした．\n");
        fprintf(stderr, "  file : %s\n", argv[2]);
        fclose(fin1);
        return EXIT_FAILURE;
    }

    int row1, row2, col1, col2;
    double **matrix1, **matrix2;

    /* データの読み込み */
    matrix1 = csvRead(&row1, &col1, fin1);
    matrix2 = csvRead(&row2, &col2, fin2);

    /* 2つの行列の行数が等しいかチェック */
    if (row1 != row2)
    {
        fprintf(stderr, "入力された2つの行列の行数が異なります．\n");

        /* メモリの開放 */
        fclose(fin1);
        fclose(fin2);
        freeMatrix(matrix1);
        freeMatrix(matrix2);
        return EXIT_FAILURE;
    }

    /* 右辺の行列が1列かチェック */
    if (col2 != 1)
    {
        fprintf(stderr, "入力された2つ目の行列の列が異なります．\n");

        /* メモリの開放 */
        fclose(fin1);
        fclose(fin2);
        freeMatrix(matrix1);
        freeMatrix(matrix2);
        return EXIT_FAILURE;
    }

    /* 主要処理 */
    int i, j;
    int row_max; /* 最大絶対値を含む行 */
    for (i = 0; i < row1 - 1; i++)
    {
        /* 最大絶対値を含む行の探索． */
        for (j = row_max = i; j < row1; j++)
        {
            if (j == i)
                continue;
            if (abs_d(matrix1[row_max][i]) < abs_d(matrix1[j][i]))
                row_max = j;
        }

        /* i行i列が絶対最大値ではなかった場合 */
        if (row_max != i)
        {
            /* 行の入れ替え */
            changeRow(matrix1, row1, col1, i, row_max);
            changeRow(matrix2, row2, col2, i, row_max);
        }

        /* ピボット選択付き前進消去 */
        pvEli(matrix1, row1, col1, matrix2, i);
    }

    /* 解の計算 */
    double *x;
    x = allocVector(row1);
    answer(matrix1, row1, col1, matrix2, x);

    /* 解の表示 */
    showVector(x, row1);

    /* メモリの開放 */
    fclose(fin1);
    fclose(fin2);
    freeVector(x);
    freeMatrix(matrix1);
    freeMatrix(matrix2);

    return EXIT_SUCCESS;
}