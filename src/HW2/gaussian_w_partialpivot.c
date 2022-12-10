/* ���C�u�����̃C���N���[�h */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"
#include "lib/memory_controller.h"

/* �e��}�N����` */
#define ARGC_QUANTITY 3

/*�s���k��ڂ̐�΍ő�l��Ԃ�*/
double pivotSearch(int k, dynamicMemory *data) {
  double max = 0;
  int max_row = 0;

  /*�ő��Βl��T��*/
  for (int i = 0; i < data[0].col; i++) {
    if (data[0].matrix[i][k] > max) {
      max = data[0].matrix[i][k];
      max_row = i;
    }
  }

  printf("pivotSearch: %f\n", max);
  printf("pivotRow: %d\n", max_row);

  return max;
}

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

  pivotSearch(0, memory);

  /* �I������ */
  allAllocatedMemoryFree(memory);
  return EXIT_SUCCESS;
}