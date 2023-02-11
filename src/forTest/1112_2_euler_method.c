/* ? Yusaku WASHIO 2023 All rights reserved.*/

/* ���C�u�����̃C���N���[�h */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"
#include "lib/memory_controller.h"

/* �e��}�N����` */
#define ARGC_QUANTITY 2

/* �֐��v���g�^�C�v */
float f(float x, float y);
float euler(float x_start, float h, float x_end, float y_start);

int main(int argc, char **argv) {
  /* �\���̂̏����� */
  dynamicMemory memory[2] = {
      {"�͈�", argv[1], NULL, NULL},
      {NULL, NULL, NULL, NULL},
  };

  float answer;

  /* �����̃`�F�b�N */
  if (argc != ARGC_QUANTITY) {
    fprintf(stderr, "ERR: �����̐����Ⴂ�܂��D%s\n", argv[0]);
    return 0;
  }

  printf("-- Info -- \n");
  printf("�͈̓t�@�C����: %s\n", argv[1]);

  /* CSV��ǂݍ��ݓ��I�z��Ɋi�[ */
  fileReader(memory);

  /* ��ԃf�[�^�̑��݊m�F */
  if (&memory[0].matrix[0][0] != NULL && &memory[0].matrix[0][1] != NULL &&
      &memory[0].matrix[0][2] != NULL && &memory[0].matrix[0][3] != NULL) {
    printf("x�̏����l����: [%g]\n", memory[0].matrix[0][0]);
    printf("�X�e�b�v������: [%g]\n", memory[0].matrix[0][1]);
    printf("x�̍ŏI�l����: [%g]\n", memory[0].matrix[0][2]);
    printf("y�̏����l����: [%g]\n", memory[0].matrix[0][3]);

  } else {
    printf("ERR: CSV�f�[�^ �� �ُ� �ł��D\n");
    /* �ُ�ŏI�� */
    allAllocatedMemoryFree(memory);
    return EXIT_FAILURE;
  }

  printf("-- OUTPUT -- \n");
  answer = euler(memory[0].matrix[0][0], memory[0].matrix[0][1],
                 memory[0].matrix[0][2], memory[0].matrix[0][3]);

  printf("-- EXIT -- \n");

  /* �I������ */
  allAllocatedMemoryFree(memory);
  return EXIT_SUCCESS;
}

/* �֐� */
float f(float x, float y) { return (x * (1 - y)); }

/*����
  x_start : x�̏����l
  h       : �X�e�b�v��
  x_end   : x�̍ŏI�l
  y_start : y�̏����l
�߂�l
  y_end   : x�̍ŏI�l�ɂ�����y�̒l*/
float euler(float x_start, float h, float x_end, float y_start) {
  while (x_start < (x_end + h)) {
    printf("���� [x, y]  =  [%.6f, %.6f]\n", x_start, y_start);
    y_start += h * f(x_start, y_start);
    x_start += h;
  }

  printf("x�̍ŏI�l�ɒB���܂���\n");
  return y_start;
}
