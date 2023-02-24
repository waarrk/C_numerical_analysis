/*
���l��͏����p�֐��Q�����t�@�C��
*/

/* �w�b�_�t�@�C�� */
#include "NAplus.h"

/*
 fileOpen(FILE *fin, char *filename);
  �t�@�C�����J��
    �߂�l: ����: 0�C���s: 1

    �p�����[�^
      ����
        filename: �J���t�@�C���̖��O
        mode    : �t�@�C�����J�����[�h
      �o��
        fin: �t�@�C���̐擪�|�C���^
*/
int fileOpen(FILE **fin, char *filename, char *mode)
{
  /* �t�@�C���̃I�[�v�� */
  *fin = fopen(filename, mode);

  if (*fin == NULL) /* �t�@�C�����J���Ȃ������ꍇ */
  {
    fprintf(stderr, "�Ώۃt�@�C���F%s\n", filename);
    fprintf(stderr, "�t�@�C�����J���܂���ł����B\n");
    return 1;
  }
  else /* �t�@�C�����J�����ꍇ */
  {
    return 0;
  }
}

/*
int charRemove(char *char, int n)
  ���I�m�ۂ��������񂩂�ꕶ������
    �߂�l:
      �폜��̕�����ւ̃|�C���^
      ���s�����ꍇNULL

    �p�����[�^
      ����:
        str: ���삷�镶����
        size: ������̒���(\0���܂߂Ȃ�=strlen())
        n: ���������̗v�f��
      �o��:
        str: ���
        size: �ꕶ����������̕�����̒���
*/
char *charRemove(char *str, int *size, int n)
{
  int i;
  char *str1;

  /* n�̊m�F */
  if ((n < 0) || (n >= *size))
  {
    fprintf(stderr, "A value exceeding the size of the string is specified. (charRemove)\n");
    return 0;
  }

  /* �������̓��I�m�� */
  str1 = (char *)malloc(sizeof(char) * (*size));
  if (str1 == NULL)
  {
    fprintf(stderr, "Failed to dynamically allocate memory. (arrayAlloc)\n");
    return NULL;
  }

  *size -= 1;

  /* 1���������炷 */
  memcpy(str1, str, n);
  for (i = n; i < *size; i++)
  {
    str1[i] = str[i + 1];
  }
  str[*size] = '\0';

  /* ���̕�����̉�� */
  free(str);

  return str1;
}

/*
arrayAlloc(int size)
  �z��̓��I�m��(����)
    �߂�l:
      �z��̐擪�|�C���^
      ���s�����ꍇ��NULL

    �p�����[�^
      ����:
        �z��̃T�C�Y
*/
double *arrayAlloc(int size)
{
  double *array;

  /* �������̓��I�m�� */
  array = (double *)malloc(sizeof(double) * size);
  if (array == NULL)
  {
    fprintf(stderr, "Failed to dynamically allocate memory. (arrayAlloc)\n");
  }

  return array;
}

/*
matrixAlloc(int row, int col)
  �s��(�񎟌��z��)�̓��I�m��(����)
    �߂�l:
      �m�ۂ����s��̐擪�|�C���^
      ���s�����ꍇ��NULL

    �p�����[�^
      ����:
        row: �m�ۂ���s��̍s��
        col: �m�ۂ���s��̗�
*/
double **matrixAlloc(int row, int col)
{
  int i;
  double **matrix;

  /* �s���Ɨ񐔂̊m�F */
  if ((row <= 0) || (col <= 0))
  {
    fprintf(stderr, "The number of rows and columns must be natural numbers. (matrixAlloc)\n");
    return NULL;
  }

  /* �񎟌��z��̓��I�m�� */
  matrix = (double **)malloc(sizeof(double *) * row);
  if (matrix == NULL)
  {
    fprintf(stderr, "Failed to dynamically allocate memory. (matrixAlloc)\n");
    return NULL;
  }

  /* �z��̓��I�m�� */
  for (i = 0; i < row; i++)
  {
    matrix[i] = arrayAlloc(col);
    if (matrix[i] == NULL)
    {
      for (i = i - 1; i >= 0; i--)
      {
        free(matrix[i]);
      }
      free(matrix);
      return NULL;
    }
  }

  return matrix;
}

/*
append(double **array, int size, double x)
  �z��ɗv�f�̒ǉ�(����)
    �p�����[�^
      �߂�l:
        ����I��: 0, �G���[�I�� : 1

      ����:
        array: �ǉ����̔z��̃A�h���X
        size: �ǉ����̔z��̑傫��
        x: �ǉ�����l
      �o��:
        array: �ǉ���̔z��̐擪�|�C���^
*/
int append(double **array, int *size, double x)
{
  int i;
  double *array1;

  /* �������̓��I�m�� */
  array1 = arrayAlloc(*size + 1);
  if (array1 == NULL)
  {
    return 1;
  }

  /* �z����v�f�̃R�s�[ */
  memcpy(array1, *array, *size);

  /* ���̔z��̃���������� */
  free(*array);

  /* �����ɒl��ǉ� */
  array1[*size] = x;

  /* �T�C�Y���X�V */
  *size += 1;

  /* �ǉ���̔z��̐擪�|�C���^��n���ꂽ�|�C���^�ɑ�� */
  *array = array1;

  return 0;
}

/*
intAppend(int **array, int size, int x)
  �z��ɗv�f�̒ǉ�(����)
    �p�����[�^
      �߂�l:
        ����I��: 0, �G���[�I�� : 1

      ����:
        array: �ǉ����̔z��̃A�h���X
        size: �ǉ����̔z��̑傫��
        n: �ǉ�����l
      �o��:
        array: �ǉ���̔z��̐擪�A�h���X
*/
int intAppend(int **array, int *size, int n)
{
  int i;
  int *array1;

  /* �������̓��I�m�� */
  array1 = (int *)malloc(sizeof(int) * (*size + 1));
  if (array1 == NULL)
  {
    fprintf(stderr, "Failed to dynamically allocate memory. (intAppend)\n");
    return 1;
  }

  /* �z����v�f�̃R�s�[ */
  memcpy(array1, *array, *size);

  /* ���̔z��̃���������� */
  free(*array);

  /* �����ɒl��ǉ� */
  array1[*size] = n;

  /* �T�C�Y���X�V */
  *size += 1;

  /* �ǉ���̔z��̐擪�|�C���^��n���ꂽ�|�C���^�ɑ�� */
  *array = array1;

  return 0;
}

/*
void arrayShow(double *array, int size)
  �z��̒��g��\��(����)
    �p�����[�^
      ����:
        *array: �z��̐擪�|�C���^
        size: �z��̑傫��
*/
void arrayShow(double *array, int size)
{
  int i;

  printf("[");
  for (i = 0; i < size - 1; i++)
  {
    printf("%.4f, ", array[i]);
  }
  printf("%.4f", array[size - 1]);
  printf("]\n");
}

/*
int argCheck(int argc, int n)
  �R�}���h���C�������̐����m�F
    �߂�l
      ����F0�C�ُ�F1

    �p�����[�^
      ����
        argc: �R�}���h���C���̐�
        n: ���z�̃R�}���h���C���̐�
*/
int argCheck(int argc, int n)
{
  if (argc == n)
  {
    return 0;
  }
  else
  {
    fprintf(stderr, "Command line argument is incorrect.");
    return 1;
  }
}

/*
int squareMatrixCheck(int row, int col)
  �����s�񂩂ǂ����̊m�F
    �߂�l
      �����s��F1�C����ȊO�F0

    ����
      row�F�s��
      col�F��
*/
int squareMatrixCheck(int row, int col)
{
  if (row == col)
  {
    return 0;
  }
  else
  {
    fprintf(stderr, "Input matrix is not square.");
    return 1;
  }
}

/*
double fAbs(double x)
  �����l�̐�Βl
    �߂�l
      �����l�̐�Βl

    �p�����[�^
      ����
        �����l
*/
double fAbs(double x)
{
  return (x < 0.0) ? -x : x;
}

/*
double MVmul(double **matrix, double *vector, int n);
  �s��ƃx�N�g���̐�
    �߂�l
      �ρA���s����NULL

    �p�����[�^
      ����
        matrix: �s��
        vector: �x�N�g��
        row: �s��̍s��
        col: �s��̗񐔁E�x�N�g���̗v�f��
*/
double *MVmul(double **matrix, double *vector, int row, int col)
{
  int i, j;
  double *vec;

  vec = (double *)calloc(col, sizeof(double));
  if (vec == NULL)
  {
    fprintf(stderr, "Failed to dynamically allocate memory.\n");
    return NULL;
  }

  for (i = 0; i < col; i++)
  {
    vec[i] = 0.0;
  }

  for (i = 0; i < row; i++)
  {
    for (j = 0; j < col; j++)
    {
      vec[i] += matrix[i][j] * vector[j];
    }
  }

  return vec;
}

/*
vecInnerProduct(double *vec1, double *vec2, int n)
  �x�N�g���̓���
    �߂�l
      ����

    �p�����[�^
      ����
        *vec1: �x�N�g��1
        *vec2: �x�N�g��2
        n: �x�N�g���̗v�f��
*/
double vecInnerProduct(double *vec1, double *vec2, int n)
{
  int i;
  double ans;

  ans = 0.0;
  for (i = 0; i < n; i++)
  {
    ans += vec1[i] * vec2[i];
  }

  return ans;
}

/*
double vabs(double *vector)
  �x�N�g���̑傫��
    �߂�l
      �x�N�g���̑傫��

    �p�����[�^
      ����
        *vector: �x�N�g��
        n: �x�N�g���̗v�f��
*/
double vabs(double *vector, int n)
{
  int i;
  double a;

  a = 0;
  for (i = 0; i < n; i++)
  {
    a += vector[i] * vector[i];
  }
  a = sqrt(a);

  return a;
}