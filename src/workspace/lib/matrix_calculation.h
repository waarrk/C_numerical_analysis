#ifndef MATRIX_CALCULATION_H
#define MATRIX_CALCULATION_H

/* ���C�u�����̃C���N���[�h */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "NAbasic.h"
#include "memory_controller.h"

/* �s��όv�Z�֐� */
int matrixProduct(int left, int right, dynamicMemory *data, double **matrixOut,
                  int *rowOut, int *colOut);
/*�s���k��ڂ̐�΍ő�l��Ԃ�*/
double pivotSearch(int k, dynamicMemory *data);
/*�s���k�s�ڂ�p�s�ڂ����ւ���*/
int swapRows(int k, int p, dynamicMemory *data);
/*�s��̃s�{�b�g����Ă���s(selected)�g���Ă���s(target)������*/
int dashRows(int selected, int target, dynamicMemory *data);
/*��O�p�s��̐���*/
int triangulation(dynamicMemory *data);
/*��O�p�s�������*/
int backSubstitution(dynamicMemory *data, double *x);

#endif