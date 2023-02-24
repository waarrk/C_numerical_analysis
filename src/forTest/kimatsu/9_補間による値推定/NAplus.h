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

/* xy�x�N�g�� */
typedef struct _VECTOR2
{
    double x;
    double y;
} vector2;

/* xyz�x�N�g�� */
typedef struct _VECTOR3
{
    double x;
    double y;
    double z;
} vector3;

/* �t�@�C�����J�� */
int fileOpen(FILE **fin, char *filename, char *mode);
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
/* �s��ƃx�N�g���̐� */
double *MVmul(double **matrix, double *vector, int row, int col);
/* �x�N�g���̓��� */
double vecInnerProduct(double *vec1, double *vec2, int n);
/* �x�N�g���̑傫�� */
double vabs(double *vector, int n);

#endif