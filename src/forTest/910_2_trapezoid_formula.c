/* ? Yusaku WASHIO 2023 All rights reserved.*/

/* ���C�u�����̃C���N���[�h */
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"
#include "lib/memory_controller.h"

/* �e��}�N����` */
#define DEBUG 1
#define ARGC_QUANTITY 2

#define SEARCH_ATTEMPTS 10

/* �֐��v���g�^�C�v */
float f(float x);
float trapezoid_integral(int division, float a, float b);

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
      &memory[0].matrix[0][2] != NULL) {
    printf("����������: [%g]\n", memory[0].matrix[0][0]);
    printf("�ϕ��͈͓���: [%g, %g]\n", memory[0].matrix[0][1],
           memory[0].matrix[0][2]);

  } else {
    printf("ERR: CSV�f�[�^ �� �ُ� �ł��D\n");
    /* �ُ�ŏI�� */
    allAllocatedMemoryFree(memory);
    return EXIT_FAILURE;
  }

  printf("-- OUTPUT -- \n");
  answer = trapezoid_integral(memory[0].matrix[0][0], memory[0].matrix[0][1],
                              memory[0].matrix[0][2]);

  printf("�ϕ����� [%g]\n", answer);

  printf("-- EXIT -- \n");

  /* �I������ */
  allAllocatedMemoryFree(memory);
  return EXIT_SUCCESS;
}

/* �֐� */
float f(float x) { return x * x; }

/*  division �������i�ߎ��Q�ߘa�̏ڍדx�j
    a b �ϕ��͈�*/

float trapezoid_integral(int division, float a, float b) {
  float delta = (b - a) / division;
  float s = 0;
  s = f(a) + f(b);

  int i;
  for (i = 1; i <= division - 1; i++) {
    s = s + 2 * f(a + i * delta);
  }

  s = delta / 2 * s;
  return s;
}