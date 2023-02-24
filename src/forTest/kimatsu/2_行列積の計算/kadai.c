/* 
�ۑ�2.
  �s��ς��v�Z����v���O����
*/
#include <stdio.h>
#include <stdlib.h>
#include "NAbasic.h"

int main(int argc, char *argv[]) {
  FILE *fin1, *fin2;
  double **matrix_A, **matrix_x, **matrix_ans;
  int row1, col1, row2, col2;

  int i, j, k;

  /* �R�}���h���C�������̊m�F */
  if (argc != 3) {
    fprintf(stderr, "�R�}���h���C���������Ԉ���Ă��܂��D<*.exe> <input_file1> <input_file2>\n");
		return EXIT_FAILURE;
  }

  /* CSV�t�@�C���̓ǂݍ��� */
  if ((fin1 = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "\"%s\"���J���܂���ł���.\n", argv[1]);
		return EXIT_FAILURE;
  }
  if ((fin2 = fopen(argv[2], "r")) == NULL) {
    fprintf(stderr, "\"%s\"���J���܂���ł���.\n", argv[2]);
    return EXIT_FAILURE;
  }

  /* CSV�t�@�C������s��f�[�^�̓ǂݍ��� */
  matrix_A = csvRead(&row1, &col1, fin1);
  matrix_x = csvRead(&row2, &col2, fin2);

  printf("A:\n");
  showMatrix((const double**)matrix_A, row1, col1);
  printf("x:\n");
  showMatrix((const double**)matrix_x, row2, col2);

  /* �s��ς��\���̊m�F */
  if (col1 != row2) {
    fprintf(stderr, "�s��ς̌v�Z���s���Ȃ��s��̑g�ݍ��킹�ł��D\n");
    return EXIT_FAILURE;
  }

  /* �v�Z���ʗp�s��̗p�� */
  matrix_ans = allocMatrix(row1, col2);

  for (i = 0; i < row1; i++) {
    for (j = 0; j < col2; j++) {
      matrix_ans[i][j] = 0.0;
    }
  }

  /* �s��ς̌v�Z */
  for (i = 0; i < row1; i++) {
    for (j = 0; j < col2; j++) {
      for (k = 0; k < row2; k++) {
        matrix_ans[i][j] += matrix_A[i][k] * matrix_x[k][j];
      }
    }
  }

  /* �v�Z���ʂ̏o�� */
  printf("ans:\n");
  showMatrix((const double**)matrix_ans, row1, col2);

  /* �������̊J�� */
  fclose(fin1);
  fclose(fin2);
  freeMatrix(matrix_A);
  freeMatrix(matrix_x);
  freeMatrix(matrix_ans);

  return 0;
}