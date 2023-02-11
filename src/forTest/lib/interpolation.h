/*
補間用関数群
*/

/* インクルードヘッダファイル */
#include "NAbasic.h"
#include "NAplus.h"

/* ラグランジュ補間 */
double LagrangeInterpolation(vector2 *init, int n, double x);
/* ニュートン補間 */
double *NewtonianInterpolation(vector2 *init, int n, double x);