/*
    ����`�������̉��̌v�Z�i�Q���@���j���[�g���@�j
*/

/*
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
*/
#include <math.h>

#include "NAbasic.h"

#define MAX_STR_LENGTH 200 /* 1�s�̕������̍ő�l */
#define EQUATION(x) \
  (x * x * x * x - 3 * x * x + 5 * x - 9) /* ����^�������̍��� */
#define DEQUATION(x)                                                  \
  (4 * x * x * x - 6 * x + 5) /* ����^�������̍��ӂ̔��� \
                               */
#define REPEAT_TIME 10        /* �J��Ԃ��� */

/* ���̓t�@�C���̓ǂݍ��� */
/* �߂�l�i0�F�����C-1�F�t�@�C���ǂݍ��ݎ��s, -2�F���̓t�@�C���L�ڃ~�X�j */
int inputRange(double *a, double *b, char *fname) {
  FILE *file;
  file = fopen(fname, "r");
  if (file == NULL) {
    fprintf(stderr, "�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B\n");
    fprintf(stderr,
            "�t�@�C�������Ԉ���Ă��邩�C�t�@�C�����j�����Ă���\��������܂�"
            "�B\n");
    return -1;
  }

  double **matrix;

  int row, col;
  matrix = csvRead(&row, &col, file);
  fclose(file);

  if ((row != 1) || (col != 2)) {
    fprintf(stderr, "���̓t�@�C�����̋L�ڕ��@���قȂ�܂��B\n");
    freeMatrix(matrix);
    return -2;
  }

  *a = matrix[0][0];
  *b = matrix[0][1];

  freeMatrix(matrix);
  return 0;
}

/* �񕪖@ */
/* �߂�l�i0�F�����C-1�F��Ԃ̉����Ə�����������j */
int bisection(double a, double b) {
  /* ��Ԃ̏���Ɖ����ł̕����`�F�b�N */
  if (EQUATION(a) * EQUATION(b) > 0.0) {
    fprintf(stderr, "��Ԃ̉����Ə���̕������̉����������ł��B\n");
    return -1;
  }

  /* ��Ԃ̏���Ɖ����̐ݒ� */
  double left, right, middle;
  left = fmin(a, b);
  right = fmax(a, b);

  /* �񕪖@�̎�v�� */
  int i;
  printf("��    ��\n");
  for (i = 0; i < REPEAT_TIME; i++) {
    middle = (left + right) / 2.0;
    printf("%d  %f\n", i, middle);

    if (EQUATION(left) * EQUATION(middle) > 0.0)
      left = middle;
    else if (EQUATION(right) * EQUATION(middle) > 0.0)
      right = middle;
  }
  middle = (left + right) / 2.0;
  printf("�񕪖@ %d ��ŋ��߂����� %f �ł��B\n", REPEAT_TIME, middle);

  return 0;
}

/* �j���[�g���@ */
void newton(double a, double b) {
  int i;
  double x;
  x = (a + b) / 2.0; /* �����l�̐ݒ� */

  printf("��    ��\n");
  for (i = 0; i < REPEAT_TIME; i++) {
    x = x - (EQUATION(x) / DEQUATION(x));
    printf("%d  %f\n", i + 1, x);
  }
  printf("�j���[�g���@ %d ��ŋ��߂����� %f �ł��B\n", REPEAT_TIME, x);
}

int main(int argc, char *argv[]) {
  /* �R�}���h���C�������̃`�F�b�N */
  if (argc != 2) {
    fprintf(stderr, "�R�}���h���C�������̐����Ⴂ�܂��B\n");
    return EXIT_FAILURE;
  }

  /* ��Ԃ̏���Ɖ����̓ǂݍ��� */
  double a, b;
  if (inputRange(&a, &b, argv[1]) != 0) return EXIT_FAILURE;

  bisection(a, b);
  printf("\n");
  newton(a, b);

  return EXIT_SUCCESS;
}