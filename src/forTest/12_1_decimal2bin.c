/* ? Yusaku WASHIO 2023 All rights reserved.*/

/* ���C�u�����̃C���N���[�h */
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"

int main(int argc, char *argv[]) {
  /* CSV�t�@�C���̃C���X�^���X */
  FILE *fin;
  /* �t�@�C���f�[�^�̓ǂݍ��݌�ۑ��̈� */
  double **matrix;
  int row, col;
  /* 2�i���ϊ����Ɏg�p����ϐ� */
  char buf[sizeof(double)];
  int i, j, k;

  /* �����̃`�F�b�N */
  if (argc != 2) {
    fprintf(stderr, "ERR: �����̐����Ⴂ�܂��D%s\n", argv[0]);
    return 0;
  }
  printf("-- Info -- \n");
  printf("�t�@�C����: %s\n", argv[1]);

  /* �t�@�C���̓ǂݍ��� */
  if ((fin = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "ERR: �t�@�C���𐳏�ɓǂݍ��܂���ł����D%s\n", argv[1]);
    return EXIT_FAILURE;
  }

  /* CSV��񎟌��z��ɃR�s�[ */;
  matrix = csvRead(&row, &col, fin);
  fclose(fin);

  /* 1�s1��ڂ̃f�[�^�̑��݊m�F */
  if (&matrix[0][0] != NULL) {
    printf("�����l: %g\n", matrix[0][0]);
  } else {
    printf("ERR: matrix[0][0] �� NULL �ł��D\n");
    return EXIT_FAILURE;
  }

  /* �������A�h���X�������p�o�b�t�@�ɃR�s�[ */
  memcpy(buf, &matrix[0][0], sizeof(double));

  /* �t�@�C���f�[�^�̃������̈�J�� */
  freeMatrix(matrix);

  /* �o�b�t�@�̒��g��IEEE754�`���Ƀ_���v */
  printf("-- OutPut -- \n");
  printf("sEEEEEEE EEEEdddd dddddddd... \n");
  for (i = sizeof(double) - 1; i >= 0; i--) {
    for (j = sizeof(buf[i]) * 8 - 1; j >= 0; j--) {
      k = buf[i] & (1 << j);
      printf("%d", k ? 1 : 0);
    }
    printf(" ");
  }
  printf("\n");
  return EXIT_SUCCESS;
}