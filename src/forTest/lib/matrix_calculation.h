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
int innerProduct(int left, int right, dynamicMemory *data, double **matrixOut,
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
/*�s����ő��Βl���ɕ��בւ���*/
int sortMatrix(double **matrix, double **matrixP, int row, int col);
/*LU����*/
int LUdecomposition(dynamicMemory *data);
/*���R�r�@*/
int jacobiMethod(dynamicMemory *data, int attempt);
/*�K�E�X�U�C�f���@*/
int gaussSeidelMethod(dynamicMemory *data, int attempt);

#endif