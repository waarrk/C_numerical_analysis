/*
LU分解関数群
*/

#ifndef LUFUNCTION_H
#define LUFUNCTION_H

#include "NAbasic.h"

/* 絶対値の計算 */
double abs_d(double x);
/* 対角行列（全ての成分が１）の作成 */
double **diaMake(int side);
/* 行列の行を入れ替える */
void rowChange(double **matrix, int row1, int row2, int col);
/* 逆行列を求める */
double **iMatrix(double *matrix, int side);

#endif