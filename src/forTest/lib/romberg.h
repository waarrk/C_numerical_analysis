/*
ロンバーグ法による積分関数群
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ERR 0.00000000001 /* 終了判定用規定値 */
#define EQU(x) exp(x)     /* 積分対象の関数 */

/* ロンバーグ法による積分 */
double romberg(double a, double b, int k);