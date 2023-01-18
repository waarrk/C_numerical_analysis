/* ���C�u�����̃C���N���[�h */
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"
#include "lib/memory_controller.h"
#include "lib/na_algorithm.h"

#define ARGC_QUANTITY 3

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