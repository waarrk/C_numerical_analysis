/*
�ŏ����ߎ�
*/

#include "NAbasic.h"
#define DIMENSION 3 /* n�������� */

/*
  abs_d(double x)
    �����̐�Βl�����߂�D
      �߂�l: �����̐�Βl

    �p�����[�^
    �@����
        x: ����
*/
double abs_d(double x)
{
  double a;
  a = x;

  if (a < 0.0)
    a *= -1;

  return a;
}

/*
 changeRow(double **matrix, int row1, int row2)
  �s��f�[�^�i�����s��j��2�s�����ւ���D
    �߂�l: ����ւ���̍s��

    �p�����[�^
      �o��
        matrix: ����Ώۂ̍s��

    �@����
        row: ����Ώۂ̍s��̍s
        col: ����Ώۂ̍s��̗�
        row1: ����ւ���s�i1�ځj
        row2: ����ւ���s�i2�ځj
*/
int changeRow(double **matrix, int row, int col, int row1, int row2)
{
  /* ���͒l�̃`�F�b�N */
  if ((row < row1) || (row < row2))
  {
    fprintf(stderr, "����ւ���s�ɔ͈͊O�̍s���w�肵�Ă��܂��D\n");
    return 1;
  }

  double *buf;
  buf = allocVector(col);

  /* �s�̓���ւ� */
  int i;
  for (i = 0; i < col; i++)
  {
    buf[i] = matrix[row1][i];
    matrix[row1][i] = matrix[row2][i];
    matrix[row2][i] = buf[i];
  }

  freeVector(buf);

  return 0;
}

/*
 pvEli(double **matrix1, int row, int col, double **matrix2, int k)
  �s�{�b�g�I��t���O�i����
    �߂�l: �I���X�e�[�^�X

    �p�����[�^
      �o��
        matrix1: ����Ώۂ̍s��i1�ځj
        matrix2: ����Ώۂ̍s��i2�ځj

      ����
        row: matrix1�̍s���imatrix2�̍s���j
        col: matrix1�̗�
        k: �Ώۂ̍���ik�sk��j
*/
int pvEli(double **matrix, int row, int col, double *vector, int k)
{
  double x;

  int i, j;
  for (i = k + 1; i < row; i++)
  {
    x = matrix[i][k] / matrix[k][k];
    for (j = k; j < col; j++)
      matrix[i][j] = matrix[i][j] - matrix[k][j] * x;
    vector[i] = vector[i] - vector[k] * x;
  }

  return EXIT_SUCCESS;
}

/*
 answer(double **matrix1, int row, int col, double **matrix2, double *vector)
  �s�{�b�g�I��t���O�i����
    �߂�l: �I���X�e�[�^�X

    �p�����[�^
    �@�o��
        vector : ��

      ����
        matrix1: ���ӂ̍s��i���̍s�񂪂������Ă�����j
        matrix2: �E�ӂ̍s��
        row: matrix1�̍s���imatrix2�̍s���j
        col: matrix1�̗�
*/
int answer(double **matrix, int row, int col, double *vector, double *ans)
{
  int i, j;
  for (i = row - 1; i >= 0; i--)
  {
    ans[i] = vector[i];
    for (j = row - 1; j > i; j--)
    {
      ans[i] -= matrix[i][j] * ans[j];
    }
    ans[i] /= matrix[i][i];
  }

  return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
  int i, j, k, l, row, col, row_max;
  double **matrix, x, *left, **right, *a;
  FILE *fin;

  /* csv�t�@�C������s��̓ǂݍ��� */
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

  /* �� */
  left = (double *)malloc(sizeof(double) * DIMENSION);
  for (i = 0; i < row; i++)
  {
    left[i] = 0.0;
    for (k = 0; k < row; k++)
    {
      x = 1.0;
      for (l = 0; l < i; l++)
      {
        x *= matrix[k][0];
      }
      left[i] += matrix[k][1] * x;
    }
  }
  /* �E */
  right = allocMatrix(DIMENSION, DIMENSION);
  for (i = 0; i < DIMENSION; i++)
  {
    for (j = 0; j < DIMENSION; j++)
    {
      right[i][j] = 0.0;
      for (k = 0; k < row; k++)
      {
        x = 1.0;
        for (l = 0; l < j; l++)
        {
          x *= matrix[k][0];
        }
        for (l = 0; l < i; l++)
        {
          x *= matrix[k][0];
        }
        right[i][j] += x;
      }
    }
  }
  /* �����s�{�b�g */
  for (i = 0; i < DIMENSION - 1; i++)
  {
    /* �ő��Βl���܂ލs�̒T���D */
    for (j = row_max = i; j < DIMENSION; j++)
    {
      if (j == i)
        continue;
      if (abs_d(right[row_max][i]) < abs_d(right[j][i]))
        row_max = j;
    }

    /* i�si�񂪐�΍ő�l�ł͂Ȃ������ꍇ */
    if (row_max != i)
    {
      /* �s�̓���ւ� */
      changeRow(right, DIMENSION, DIMENSION, i, row_max);
      changeRow(right, DIMENSION, DIMENSION, i, row_max);
    }

    /* �s�{�b�g�I��t���O�i���� */
    pvEli(right, DIMENSION, DIMENSION, left, i);
  }
  a = (double *)malloc(sizeof(double) * DIMENSION);
  answer(right, DIMENSION, DIMENSION, left, a);

  printf("�ߎ��Ȑ�\ny = ");
  for (i = DIMENSION - 1; i >= 0; i--)
  {
    printf("a[%d] ", i);
    if (i != 0)
    {
      printf("* x");
      if (i != 1)
        printf("^%d ", i);
      printf(" + ");
    }
  }
  printf("\n");

  for (i = 0; i < DIMENSION; i++)
    printf("a[%d] : %f\n", i, a[i]);

  /* �������̊J�� */
  freeMatrix(matrix);
  freeMatrix(right);
  free(left);
  free(a);

  return EXIT_SUCCESS;
}