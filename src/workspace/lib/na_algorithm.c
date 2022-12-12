#include "na_algorithm.h"

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
    printf("att: %d, left: %lf, right: %lf, result: %lf\n", attempts, left,
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
  printf("att: %d, result: %f\n", attempts, solution);
#endif

  /* ���̐��x���\���ɍ����Ȃ�܂ōċA */
  if (attempts > 1) {
    return newton(solution, data, attempts - 1);
  } else {
    return solution;
  }
}