/* ? Yusaku WASHIO 2023 All rights reserved.*/

/* ���C�u�����̃C���N���[�h */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"
#include "lib/matrix_calculation.h"
#include "lib/memory_controller.h"

/* �e��}�N����` */
#define ARGC_QUANTITY 3

#define SEARCH_ATTEMPTS 100

int main(int argc, char **argv) {
  /* �\���̂̏����� */
  dynamicMemory memory[3] = {
      {"�W���s��A", argv[1], NULL, NULL},
      {"�x�N�g��b", argv[2], NULL, NULL},
      {NULL, NULL, NULL, NULL},
  };

  /* �����̃`�F�b�N */
  if (argc != ARGC_QUANTITY) {
    fprintf(stderr, "ERR!: �����̐����Ⴂ�܂��@%s\n", argv[0]);
    return 0;
  }

  /* CSV��ǂݍ��ݓ��I�z��Ɋi�[ */
  fileReader(memory);

  printf("-- Info -- \n");
  printf("�W���s��A�t�@�C����: %s\n", argv[1]);
  showMatrix((const double **)memory[0].matrix, memory[0].row, memory[0].col);
  printf("�x�N�g��b�t�@�C����: %s\n", argv[2]);
  showMatrix((const double **)memory[1].matrix, memory[1].row, memory[1].col);

  printf("-- OutPut -- \n");
  /* �s���LU���� */
  printf("���R�r�@\n");
  jacobiMethod(memory, SEARCH_ATTEMPTS);
  printf("�K�E�X�U�C�f���@\n");
  gaussSeidelMethod(memory, SEARCH_ATTEMPTS);

  /* �I������ */
  allAllocatedMemoryFree(memory);
  return EXIT_SUCCESS;
}