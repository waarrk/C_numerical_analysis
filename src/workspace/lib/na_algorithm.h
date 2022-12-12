#ifndef NA_ALGORITHM_H
#define NA_ALGORITHM_H

/* ライブラリのインクルード */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "NAbasic.h"
#include "memory_controller.h"

/* 各種マクロ定義 */
#define DEBUG 0             // デバッグモード
#define SEARCH_ATTEMPTS 10  // 探索系の試行回数

/* 関数プロトタイプ */
/**
 * @param x 関数のxがわかっている際入力
 * @param data 動的確保した構造体配列のポインタ
 * @param left 二分探索区間の左端
 * @param right 二分探索区間の右端
 * @param newton_default　ニュートン法の初期値
 * @param attempts 探索の試行回数
 */
double equationSolver(double x, dynamicMemory *data);
double dichotomy(double left, double right, dynamicMemory *data, int attempts);
double differential(double x, dynamicMemory *data);
double newton(double newton_default, dynamicMemory *data, int attempts);

#endif