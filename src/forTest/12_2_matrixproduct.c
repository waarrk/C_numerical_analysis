/* ? Yusaku WASHIO 2023 All rights reserved.*/

/* ���C�u�����̃C���N���[�h */
#include <stdio.h>
#include <stdlib.h>

#include "lib/NAbasic.h"

/* �s��όv�Z�֐� */
int matrixProduct(const double **matrixA, const double **matrixB,
                  double **matrixOut, int *rowA, int *colA, int *rowB,
                  int *colB, int *rowOut, int *colOut) {
  /* �s��̗v�f�v�Z�p�ϐ� */
  int element;
  int i;

  /* matrixA��matrixB�����matrixOut���v�Z*/
  for (*rowOut = 0; *rowOut < *rowA; (*rowOut)++) {
    for (*colOut = 0; *colOut < *colB; (*colOut)++) {
      /* �s��v�f�̌v�Z */
      /* A1*b1 + A2*B2 ....*/
      element = 0;
      for (i = 0; i < *rowB; i++) {
        element += matrixA[*rowOut][i] * matrixB[i][*colOut];
      }
      matrixOut[*rowOut][*colOut] = element;
    }
  }
  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  /* CSV�t�@�C���̃C���X�^���X */
  FILE *finA, *finB;
  /* �t�@�C���f�[�^�̓ǂݍ��݌�ۑ��̈� */
  double **matrixA, **matrixB, **matrixOut;
  /* �s��όv�Z�Ɏg�p����ϐ� */
  int rowA, colA, rowB, colB, rowOut, colOut;

  /* �����̃`�F�b�N */
  if (argc != 3) {
    fprintf(stderr, "ERR: �����̐����Ⴂ�܂��D%s\n", argv[0]);
    return 0;
  }
  printf("-- Info -- \n");
  printf("A�s��t�@�C����: %s\n", argv[1]);
  printf("B�s��t�@�C����: %s\n", argv[2]);

  /* CSV����s���ǂݍ��� */
  if ((finA = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "ERR: �t�@�C���𐳏�ɓǂݍ��܂���ł����D%s\n", argv[1]);
    return EXIT_FAILURE;
  }
  if ((finB = fopen(argv[2], "r")) == NULL) {
    fprintf(stderr, "ERR: �t�@�C���𐳏�ɓǂݍ��܂���ł����D%s\n", argv[2]);
    return EXIT_FAILURE;
  }

  matrixA = csvRead(&rowA, &colA, finA);
  matrixB = csvRead(&rowB, &colB, finB);
  fclose(finA);
  fclose(finB);

  printf("matrixA: \n");
  showMatrix((const double **)matrixA, rowA, colA);
  printf("matrixB: \n");
  showMatrix((const double **)matrixB, rowB, colB);

  /* �s��ς̌v�Z���\���m�F */
  if (colA != rowB) {
    printf("���̍s��̑g�ݍ��킹�Őς͌v�Z�ł��܂���D\n");
    return EXIT_FAILURE;
  }

  printf("--OutPut--\n");
  printf("matrixOut: \n");

  /* �s��̐ς��v�Z */
  matrixOut = allocMatrix(rowA, colB);
  matrixProduct((const double **)matrixA, (const double **)matrixB, matrixOut,
                &rowA, &colA, &rowB, &colB, &rowOut, &colOut);

  /* �t�@�C���f�[�^�̃������̈�J�� */
  freeMatrix(matrixA);
  freeMatrix(matrixB);

  /* �v�Z���ʂ̕\�� */
  showMatrix((const double **)matrixOut, rowOut, colOut);
  return EXIT_SUCCESS;
}