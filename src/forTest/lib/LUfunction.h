/*
LU�����֐��Q
*/

#ifndef LUFUNCTION_H
#define LUFUNCTION_H

#include "NAbasic.h"

/* ��Βl�̌v�Z */
double abs_d(double x);
/* �Ίp�s��i�S�Ă̐������P�j�̍쐬 */
double **diaMake(int side);
/* �s��̍s�����ւ��� */
void rowChange(double **matrix, int row1, int row2, int col);
/* �t�s������߂� */
double **iMatrix(double *matrix, int side);

#endif