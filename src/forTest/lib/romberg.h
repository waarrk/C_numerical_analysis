/*
�����o�[�O�@�ɂ��ϕ��֐��Q
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ERR 0.00000000001 /* �I������p�K��l */
#define EQU(x) exp(x)     /* �ϕ��Ώۂ̊֐� */

/* �����o�[�O�@�ɂ��ϕ� */
double romberg(double a, double b, int k);