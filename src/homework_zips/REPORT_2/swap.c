/* ���C�u�����̃C���N���[�h */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"
#include "lib/matrix_calculation.h"
#include "lib/memory_controller.h"

/* �e��}�N����` */
#define ARGC_QUANTITY 3

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

  /* CSV��ǂݍ��ݓ��I�z��Ɋi�[ */
  fileReader(memory);

  printf("-- Original -- \n");
  printf("matrixA: \n");
  showMatrix((const double **)memory[0].matrix, memory[0].row, memory[0].col);

  swapRows(0, 2, memory);

  printf("-- Swap -- \n");
  showMatrix((const double **)memory[0].matrix, memory[0].row, memory[0].col);

  /* �I������ */
  allAllocatedMemoryFree(memory);

  return EXIT_SUCCESS;
}