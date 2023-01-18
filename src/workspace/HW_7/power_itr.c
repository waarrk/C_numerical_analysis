#include <math.h>
#include <stdio.h>

#include "NAbasic.h"

#define MAX_ITER 1000
#define TOL 1e-5

FILE *fin;
double **matrix;
double At[3][3];  // �]�u�s��At
int row, col;

int i, j, k;
double x[3] = {1, 0, 0};  // �����l
double lambda = 0;        // �ő�ŗL�l
double lambda_prev = 0;   // 1�O�̍ő�ŗL�l

void largest() {
  // Power Iteration
  for (k = 0; k < MAX_ITER; k++) {
    // �s��A�ƃx�N�g��x�̐ς��v�Z
    double Ax[3] = {0, 0, 0};
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        Ax[i] += matrix[i][j] * x[j];
      }
    }

    // �x�N�g��x�̍X�V
    double x_norm = 0;
    for (i = 0; i < 3; i++) {
      x_norm += x[i] * x[i];
    }
    x_norm = sqrt(x_norm);
    for (i = 0; i < 3; i++) {
      x[i] = Ax[i] / x_norm;
    }

    // �ő�ŗL�l�̍X�V
    lambda_prev = lambda;
    lambda = 0;
    for (i = 0; i < 3; i++) {
      lambda += x[i] * Ax[i];
    }

    // ��������
    if (fabs(lambda - lambda_prev) < TOL) {
      break;
    }
  }

  printf("Largest eigenvalue: %f\n", lambda);
}

void smallest() {
  // Power Iteration
  for (k = 0; k < MAX_ITER; k++) {
    // �s��At�ƃx�N�g��x�̐ς��v�Z
    double Atx[3] = {0, 0, 0};
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        Atx[i] += At[i][j] * x[j];
      }
    }

    // �x�N�g��x�̍X�V
    double x_norm = 0;
    for (i = 0; i < 3; i++) {
      x_norm += x[i] * x[i];
    }
    x_norm = sqrt(x_norm);
    for (i = 0; i < 3; i++) {
      x[i] = Atx[i] / x_norm;
    }

    // �ŏ��ŗL�l�̍X�V
    lambda_prev = lambda;
    lambda = 0;
    for (i = 0; i < 3; i++) {
      lambda += x[i] * Atx[i];
    }

    // ��������
    if (fabs(lambda - lambda_prev) < TOL) {
      break;
    }
  }

  printf("Smallest eigenvalue: %f\n", lambda);
}

int main(int argc, char *argv[]) {
  /* �����̃`�F�b�N */
  if (argc != 2) {
    fprintf(stderr, "ERR: �����̐����Ⴂ�܂��D%s\n", argv[0]);
    return 0;
  }

  /* CSV����s���ǂݍ��� */
  if ((fin = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "ERR: �t�@�C���𐳏�ɓǂݍ��܂���ł����D%s\n", argv[1]);
    return EXIT_FAILURE;
  }

  matrix = csvRead(&row, &col, fin);
  showMatrix((const double **)matrix, row, col);

  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      At[i][j] = matrix[j][i];
    }
  }

  largest();
  smallest();

  freeMatrix(matrix);
  return 0;
}
