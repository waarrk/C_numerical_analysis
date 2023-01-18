#ifndef NA_ALGORITHM_H
#define NA_ALGORITHM_H

/* ���C�u�����̃C���N���[�h */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "NAbasic.h"
#include "memory_controller.h"

/* �e��}�N����` */
#define DEBUG 0             // �f�o�b�O���[�h
#define SEARCH_ATTEMPTS 10  // �T���n�̎��s��

/* �֐��v���g�^�C�v */
/**
 * @param x �֐���x���킩���Ă���ۓ���
 * @param data ���I�m�ۂ����\���̔z��̃|�C���^
 * @param left �񕪒T����Ԃ̍��[
 * @param right �񕪒T����Ԃ̉E�[
 * @param newton_default�@�j���[�g���@�̏����l
 * @param attempts �T���̎��s��
 */
double equationSolver(double x, dynamicMemory *data);
double dichotomy(double left, double right, dynamicMemory *data, int attempts);
double differential(double x, dynamicMemory *data);
double newton(double newton_default, dynamicMemory *data, int attempts);

#endif