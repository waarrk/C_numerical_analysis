/*
数値解析処理基本関数群実装ファイル
*/

#ifndef NAPLUS_H
#define NAPLUS_H

/* ヘッダファイル */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* 動的確保した文字列から一文字消す */
char *charRemove(char *str, int *size, int n);
/* 配列の動的確保(実数) */
double *arrayAlloc(int size);
/* 二次元配列の動的確保(実数) */
double **matrixAlloc(int row, int col);
/* 配列に要素の追加(実数) */
int append(double **array, int *size, double x);
/* 配列に要素の追加(整数) */
int intAppend(int **array, int *size, int n);
/* 配列の中身を表示(実数) */
void arrayShow(double *array, int size);
/* コマンドライン引数の数を確認 */
int argCheck(int argc, int n);
/* 正方行列かどうかの確認 */
int squareMatrixCheck(int row, int col);
/* 二次元配列のメモリを解放 */
void matrixFree(double **matrix, int row);
/* 行列とベクトルの積 */
double *MVmul(double **matrix, double *vector, int row, int col);
/* ベクトルの内積 */
double vecInnerProduct(double *vec1, double *vec2, int n);
/* ベクトルの大きさ */
double vabs(double *vector, int n);

#endif