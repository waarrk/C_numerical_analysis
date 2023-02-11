/* Hisho SEKI
�E�������ꂽ���s�t�@�C�����ȉ��̌`���Ŏ��s���Ă��������B
> (���s�t�@�C��) �i�_�f�[�^�t�@�C���j�ix�̒l�j*/

#include "lib/NAbasic.h"       /* ���l��͗p��{�֐��Q */
#include "lib/NAplus.h"        /* ���l��͗p�ǉ��֐��Q */
#include "lib/interpolation.h" /* ��ԗp�֐��Q */

#define ARGC_NUM 3 /* �R�}���h���C�������̐� */

int main(int argc, char **argv) {
  int row, col, i;
  double **matrix, x, *y;
  FILE *fp;
  vector2 *init;

  /* �R�}���h���C�������`�F�b�N */
  if (argCheck(argc, ARGC_NUM)) return 0;

  /* �t�@�C�����J�� */
  if (fileOpen(&fp, argv[1], "r")) return 0;

  /* �t�@�C���̃f�[�^���擾 */
  matrix = csvRead(&row, &col, fp);
  if (matrix == NULL) return 0;

  /* �f�[�^�̊m�F */
  if (col != 2) {
    fprintf(stderr, "Input data must be in two columns.\n");
    freeMatrix(matrix);
    return 0;
  }

  /* �ŏ��̓_�̏��� */
  init = (vector2 *)malloc(sizeof(vector2) * row);
  for (i = 0; i < row; i++) {
    init[i].x = matrix[i][0];
    init[i].y = matrix[i][1];
  }

  /* x�̒l */
  x = atof(argv[2]);
  printf("x = %f\n", x);

  /* ��Ԃ̌v�Z */
  y = NewtonianInterpolation(init, row, x);

  /* ���ʂ̕\�� */
  printf("                    | y�̒l\n");
  for (i = 1; i <= row; i++) {
    printf("%3d�s�ڂ܂ł̃f�[�^ | %f\n", i, y[i - 1]);
  }

  /* �������̊J�� */
  freeMatrix(matrix);
  free(init);
  free(y);
  fclose(fp);
}