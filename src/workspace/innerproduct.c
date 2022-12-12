/* ���C�u�����̃C���N���[�h */
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"
#include "lib/matrix_calculation.h"
#include "lib/memory_controller.h"

/* �e��}�N����` */
#define ARGC_QUANTITY 3

int main(int argc, char **argv) {
  /* �t�@�C���f�[�^�̓ǂݍ��݌�ۑ��̈� */
  double **matrixOut;
  /* �s��όv�Z�Ɏg�p����ϐ� */
  int rowOut, colOut;

  /* �\���̂̏����� */
  dynamicMemory memory[3] = {
      {"�s��1", argv[1], NULL, NULL},
      {"�s��2", argv[2], NULL, NULL},
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

  printf("matrixA: \n");
  showMatrix((const double **)memory[0].matrix, memory[0].row, memory[0].col);
  printf("matrixB: \n");
  showMatrix((const double **)memory[1].matrix, memory[0].row, memory[0].col);

  /* ���ς̌v�Z���\���m�F */
  if (memory[0].row != memory[1].row) {
    printf("���̍s��̑g�ݍ��킹�Őς͌v�Z�ł��܂���D\n");
    return EXIT_FAILURE;
  }

  printf("--OutPut--\n");
  printf("matrixOut: \n");

  /* �s��̐ς��v�Z */
  matrixOut = allocMatrix(memory[0].col, memory[1].row);
  innerProduct(0, 1, memory, matrixOut, &rowOut, &colOut);

  /* �v�Z���ʂ̕\�� */
  showMatrix((const double **)matrixOut, rowOut, colOut);

  /* �I������ */
  allAllocatedMemoryFree(memory);
  freeMatrix(matrixOut);
  return EXIT_SUCCESS;
}