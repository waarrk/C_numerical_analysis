#ifndef MATRIX_CALCULATION_H
#define MATRIX_CALCULATION_H

/* ライブラリのインクルード */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "NAbasic.h"
#include "memory_controller.h"

/*行列のk列目の絶対最大値を返す*/
double pivotSearch(int k, dynamicMemory *data);
/*行列のk行目とp行目を入れ替える*/
int swapRows(int k, int p, dynamicMemory *data);
/*行列のピボットされている行(selected)使ってある行(target)を割る*/
int dashRows(int selected, int target, dynamicMemory *data);
/*上三角行列の生成*/
int triangulation(dynamicMemory *data);
/*上三角行列を解く*/
int backSubstitution(dynamicMemory *data, double *x);

#endif