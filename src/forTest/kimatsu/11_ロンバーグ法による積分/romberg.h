/*
�����o�[�O�@�ɂ��ϕ��֐��Q
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ERR 0.00000000001                        /* �I������p�K��l */
#define EQU(x) (exp(x) - pow(x, 3) + 5 * sin(x)) /* �ϕ��Ώۂ̊֐� */

/* �����o�[�O�@�ɂ��ϕ� */
double romberg(double a, double b, int k);