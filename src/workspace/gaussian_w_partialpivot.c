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