/*
�ő�E�ŏ��ŗL�l�̌v�Z
*/

#include "NAbasic.h"
#include "NAplus.h"
#include "LUfunction.h"

#define ARG_NUM 2    /* �R�}���h���C�������̐� */
#define ERROR 0.0001 /* ���������덷 */

/* �ő�ŗL�l�̌v�Z */
double maxEigenvalues(double **matrix, double *y0, int row, int col);

/* �ŏ��ŗL�l�̌v�Z */
double minEigenvalues(double **matrix, double *y1, int row, int col);

int main(int argc, char **argv)
{
  int i, j, row, col;
  double **matrix, **imatrix, *y0, lm_max, lm_min, *m;
  FILE *fin;

  /* �R�}���h���C�������̊m�F */
  if (argCheck(argc, ARG_NUM))
  {
    return EXIT_FAILURE;
  }

  /* csv�t�@�C����������s��̓ǂݍ��� */
  fin = fopen(argv[1], "r");
  if (fin == NULL)
  {
    return EXIT_FAILURE;
  }
  matrix = csvRead(&row, &col, fin);
  if (matrix == NULL)
  {
    free(fin);
    return EXIT_FAILURE;
  }

  /* �s�񂪐����s�񂩂ǂ����̊m�F */
  if (squareMatrixCheck(row, col))
  {
    free(fin);
    matrixFree(matrix, row);
    return EXIT_FAILURE;
  }

  /* �����l�̐ݒ� */
  y0 = arrayAlloc(col);
  if (y0 == NULL)
  {
    free(fin);
    matrixFree(matrix, row);
    return EXIT_FAILURE;
  }
  for (i = 0; i < col; i++)
  {
    y0[i] = 1.0;
  }

  /* �ő�ŗL�l�����߂� */
  lm_max = maxEigenvalues(matrix, y0, row, col);

  printf("�ő�ŗL�l�F%.1f\n", lm_max);

  /* �t�s������߂� */
  m = arrayAlloc(row * col);
  if (m == NULL)
  {
    matrixFree(matrix, row);
    return EXIT_FAILURE;
  }
  for (i = 0; i < row; i++)
  {
    for (j = 0; j < col; j++)
    {
      m[i * row + j] = matrix[i][j];
    }
  }
  imatrix = iMatrix(m, row);

  /* �����l�̐ݒ� */
  y0 = arrayAlloc(col);
  if (y0 == NULL)
  {
    free(fin);
    matrixFree(matrix, row);
    return EXIT_FAILURE;
  }
  for (i = 0; i < col; i++)
  {
    y0[i] = 1.0;
  }

  /* �ŏ��ŗL�l�����߂� */
  lm_min = maxEigenvalues(imatrix, y0, row, col);
  lm_min = 1.0 / lm_min;

  printf("�ŏ��ŗL�l�F%.1f\n", lm_min);

  /* �������̊J�� */
  freeMatrix(matrix);
  freeMatrix(imatrix);
  freeVector(m);

  return EXIT_SUCCESS;
}

/*
double maxEigenvalues()
  �ő�ŗL�l�̌v�Z
    �߂�l
      �ő�ŗL�l

    ����
      matrix: �s��
      y0: ���������x�N�g��
      row: �s��̍s��
      col: �s��̗� / �x�N�g���̗v�f��
*/
double maxEigenvalues(double **matrix, double *y0, int row, int col)
{
  int i;
  double *y1, lm0, lm1;

  for (i = 0;; i++)
  {
    y1 = MVmul(matrix, y0, row, col);
    lm1 = (vecInnerProduct(y1, y1, col)) / (vecInnerProduct(y1, y0, col));
    if (i != 0)
    {
      if (fabs(lm1 - lm0) / fabs(lm0) < ERROR)
      {
        free(y0);
        free(y1);
        break;
      }
    }
    free(y0);
    y0 = y1;
    lm0 = lm1;
  }

  return lm0;
}
