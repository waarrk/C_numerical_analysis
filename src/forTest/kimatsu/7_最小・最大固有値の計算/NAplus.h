/*
���l��͏�����{�֐��Q�����t�@�C��
*/

#ifndef NAPLUS_H
#define NAPLUS_H

/* �w�b�_�t�@�C�� */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* ���I�m�ۂ��������񂩂�ꕶ������ */
char *charRemove(char *str, int *size, int n);
/* �z��̓��I�m��(����) */
double *arrayAlloc(int size);
/* �񎟌��z��̓��I�m��(����) */
double **matrixAlloc(int row, int col);
/* �z��ɗv�f�̒ǉ�(����) */
int append(double **array, int *size, double x);
/* �z��ɗv�f�̒ǉ�(����) */
int intAppend(int **array, int *size, int n);
/* �z��̒��g��\��(����) */
void arrayShow(double *array, int size);
/* �R�}���h���C�������̐����m�F */
int argCheck(int argc, int n);
/* �����s�񂩂ǂ����̊m�F */
int squareMatrixCheck(int row, int col);
/* �񎟌��z��̃���������� */
void matrixFree(double **matrix, int row);
/* �s��ƃx�N�g���̐� */
double *MVmul(double **matrix, double *vector, int row, int col);
/* �x�N�g���̓��� */
double vecInnerProduct(double *vec1, double *vec2, int n);
/* �x�N�g���̑傫�� */
double vabs(double *vector, int n);

#endif