/* ? Yusaku WASHIO 2023 All rights reserved.*/

/* ���C�u�����̃C���N���[�h */
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"
#include "lib/memory_controller.h"

/* �e��}�N����` */
#define DEBUG 1
#define ARGC_QUANTITY 3

#define SEARCH_ATTEMPTS 10

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

int main(int argc, char **argv) {
  /* �\���̂̏����� */
  dynamicMemory memory[3] = {
      {"�֐�", argv[1], NULL, NULL},
      {"���", argv[2], NULL, NULL},
      {NULL, NULL, NULL, NULL},
  };

  double newton_default;
  double dichotomy_result;
  double newton_result;

  /* �����̃`�F�b�N */
  if (argc != ARGC_QUANTITY) {
    fprintf(stderr, "ERR: �����̐����Ⴂ�܂��D%s\n", argv[0]);
    return 0;
  }

#if DEBUG
  printf("-- Info -- \n");
  printf("�֐��t�@�C����: %s\n", argv[1]);
  printf("��ԃt�@�C����: %s\n", argv[2]);
#endif

  /* CSV��ǂݍ��ݓ��I�z��Ɋi�[ */
  fileReader(memory);

  /* �֐��̕\�� */
#if DEBUG
  printf("�֐�: y = ");
  for (int i = 0; i < memory[0].col; i++) {
    if (memory[0].matrix[0][i] > 0) {
      printf("+%g", memory[0].matrix[0][i]);
    } else {
      printf("%g", memory[0].matrix[0][i]);
    }
    printf("x^%g", memory[0].matrix[1][i]);
  }
  printf("\n");
#endif

  /* ��ԃf�[�^�̑��݊m�F */
  if (&memory[1].matrix[0][0] != NULL && &memory[1].matrix[0][1] != NULL) {
    printf("��ԓ���: [%g, %g]\n", memory[1].matrix[0][0],
           memory[1].matrix[0][1]);
  } else {
    printf("ERR: ���CSV�f�[�^ �� �ُ� �ł��D\n");
    /* �ُ�ŏI�� */
    allAllocatedMemoryFree(memory);
    return EXIT_FAILURE;
  }

#if DEBUG
  printf("-- OutPut -- \n");
  printf("�񕪒T������...\n");
#endif
  /* �񕪒T�� */
  dichotomy_result = dichotomy(memory[1].matrix[0][0], memory[1].matrix[0][1],
                               memory, SEARCH_ATTEMPTS);

#if DEBUG
  printf("�j���[�g���@�T������...\n");
#endif
  /* �j���[�g���@ */
  newton_default = (memory[1].matrix[0][0] + memory[1].matrix[0][1]) / 2;
  newton_result = newton(newton_default, memory, SEARCH_ATTEMPTS);

#if DEBUG
  printf("-- EXIT -- \n");
#endif

  /* �I������ */
  allAllocatedMemoryFree(memory);
  return EXIT_SUCCESS;
}

/* x���킩���Ă���Ƃ�y���v�Z����֐� */
double equationSolver(double x, dynamicMemory *data) {
  double tmp = 1;
  double solution = 0;

  /* ���̌v�Z */
  for (int i = 0; i < data[0].col; i++) {
    for (int j = 0; j < (data[0].matrix[1][i]); j++) {
      tmp *= x;
    }
    tmp *= data[0].matrix[0][i];
    solution += tmp;
    tmp = 1;
  }
  return solution;
}

/* �񕪒T���ŉ��𐄒� */
double dichotomy(double left, double right, dynamicMemory *data, int attempts) {
  double mid;
  mid = (left + right) / 2;
  /* �������]�����ɏ]�����̋�Ԃ��Ďw�� */
  if ((equationSolver(mid, data) * equationSolver(left, data)) < 0) {
    right = mid;
  } else if ((equationSolver(mid, data) * equationSolver(right, data)) < 0) {
    left = mid;
  }

  /* ���̐��x���\���ɍ����Ȃ�܂ōċA */
  if (attempts > 1) {
#if DEBUG
    printf("att: %d, left: %lf, right: %lf, mid: %lf\n", attempts, left, right,
           mid);
#endif
    return dichotomy(left, right, data, attempts - 1);
  } else {
    printf("att: %d, left: %lf, right: %lf, result: %.9lf\n", attempts, left,
           right, mid);
    return mid;
  }
}

/* �����̔��W���𓱏o */
double differential(double x, dynamicMemory *data) {
  double tmp = 1;
  double solution = 0;

  /* ���W���̓��o */
  for (int i = 0; i < data[0].col; i++) {
    for (int j = 0; j < (data[0].matrix[1][i] - 1); j++) {
      /* �������ЂƂ�����x^N���v�Z*/
      tmp *= x;
    }
    /* �e�������߂� */
    tmp *= data[0].matrix[0][i] * data[0].matrix[1][i];
    solution += tmp;
    tmp = 1;
  }
  return solution;
}

/* �j���[�g���@ */
double newton(double newton_default, dynamicMemory *data, int attempts) {
  double solution = 0;

  /* �Q������p���ċߎ��l���v�Z */
  solution = newton_default - (equationSolver(newton_default, data) /
                               differential(newton_default, data));

#if DEBUG
  printf("att: %d, result: %.9f\n", attempts, solution);
#endif

  /* ���̐��x���\���ɍ����Ȃ�܂ōċA */
  if (attempts > 1) {
    return newton(solution, data, attempts - 1);
  } else {
    return solution;
  }
}