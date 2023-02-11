/* ���C�u�����̃C���N���[�h */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"
#include "lib/memory_controller.h"

/* �e��}�N����` */
#define ARGC_QUANTITY 3

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

int main(int argc, char **argv) {
  /* �\���̂̏����� */
  dynamicMemory memory[3] = {
      {"�W���s��A", argv[1], NULL, NULL},
      {"�x�N�g��Y", argv[2], NULL, NULL},
      {NULL, NULL, NULL, NULL},
  };

  /* �����̃`�F�b�N */
  if (argc != ARGC_QUANTITY) {
    fprintf(stderr, "ERR!: �����̐����Ⴂ�܂��@%s\n", argv[0]);
    return 0;
  }

  printf("-- Info -- \n");
  printf("�W���s��A�t�@�C����: %s\n", argv[1]);
  printf("�x�N�g��Y�t�@�C����: %s\n", argv[2]);

  /* CSV��ǂݍ��ݓ��I�z��Ɋi�[ */
  fileReader(memory);
  double *answer = (double *)malloc(sizeof(double) * 3);

  /* �s��̎O�p�� */
  triangulation(memory);
  /* ��O�p�s�������*/
  backSubstitution(memory, answer);

  /*���̕\��*/
  for (int i = 0; i < memory[0].col; i++) {
    printf("x%d = %g\n", i, answer[i]);
  }

  /* �I������ */
  free(answer);
  allAllocatedMemoryFree(memory);
  return EXIT_SUCCESS;
}

/*���[�U�[��`�֐��Q*/

double pivotSearch(int k, dynamicMemory *data) {
  double max = 0;
  int max_row = 0;

  /*�ő��Βl��T��*/
  for (int i = k; i < data[0].col; i++) {
    if (data[0].matrix[i][k] > max) {
      max = data[0].matrix[i][k];
      max_row = i;
    }
  }
  if (max == 0) {
    exit(0);
  }
  return max_row;
}

int swapRows(int k, int p, dynamicMemory *data) {
  double tmp;
  tmp = data[1].matrix[k][0];
  data[1].matrix[k][0] = data[1].matrix[p][0];
  data[1].matrix[p][0] = tmp;
  for (int i = 0; i < data[0].col; i++) {
    tmp = data[0].matrix[k][i];
    data[0].matrix[k][i] = data[0].matrix[p][i];
    data[0].matrix[p][i] = tmp;
  }
  return EXIT_SUCCESS;
}

int dashRows(int selected, int target, dynamicMemory *data) {
  double tmp;
  double r =
      data[0].matrix[target][selected] / data[0].matrix[selected][selected];
  for (int i = 0; i < data[0].col; i++) {
    tmp = data[0].matrix[target][i];
    data[0].matrix[target][i] =
        data[0].matrix[target][i] - r * data[0].matrix[selected][i];
  }
  data[1].matrix[target][0] =
      data[1].matrix[target][0] - r * data[1].matrix[selected][0];
  return EXIT_SUCCESS;
}

int triangulation(dynamicMemory *data) {
  double pivot = 0;
  for (int i = 0; i < data[0].col; i++) {
    pivot = pivotSearch(i, data);
    swapRows(i, pivot, data);
    for (int j = i + 1; j < data[0].col; j++) {
      dashRows(i, j, data);
    }
  }
  return EXIT_SUCCESS;
}

int backSubstitution(dynamicMemory *data, double *x) {
  double tmp = 0;
  /*�s*/
  for (int i = data[0].col - 1; i >= 0; i--) {
    tmp = 0;
    /*��*/
    for (int j = i + 1; j < data[0].col; j++) {
      tmp += data[0].matrix[i][j] * x[j];
    }
    x[i] = (data[1].matrix[i][0] - tmp) / data[0].matrix[i][i];
  }
  return EXIT_SUCCESS;
}