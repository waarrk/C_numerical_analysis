/* LU�����ɂ��A���������̌v�Z */

#include "NAbasic.h" /* ���l��͗p��{�֐��Q�����t�@�C�� */

#define ARG_NUM 3 /* �R�}���h���C�������̐� */

/*
 abs(double x);
  ��Βl�̌v�Z
    �߂�l: ��Βl

    �p�����[�^
      ����
        x: �����l
*/
double abs_d(double x) { return (x >= 0) ? x : -x; /* �ő��Βl�̌v�Z */ }

/*
 argCheck(int argc, int num)
  �R�}���h���C�������̊m�F
    �߂�l: �������F0�C�قȂ�F1

    �p�����[�^
    �@����
        argc: ���͂��ꂽ�R�}���h���C�������̐�
        num : �������R�}���h���C�������̐�
*/
int argCheck(int argc, int num) {
  if (argc != num) /* �R�}���h���C�������̐����Ⴄ�ꍇ */
  {
    fprintf(stderr, "�R�}���h���C�������̐����Ⴂ�܂��B\n");
    return 1;
  } else /* �R�}���h���C�������̐����������ꍇ */
  {
    return 0;
  }
}

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
int fileOpen(FILE **fin, char *filename, char *mode) {
  /* �t�@�C���̃I�[�v�� */
  *fin = fopen(filename, mode);

  if (*fin == NULL) /* �t�@�C�����J���Ȃ������ꍇ */
  {
    fprintf(stderr, "�Ώۃt�@�C���F%s\n", filename);
    fprintf(stderr, "�t�@�C�����J���܂���ł����B\n");
    return 1;
  } else /* �t�@�C�����J�����ꍇ */
  {
    return 0;
  }
}

/*
 vecInput(int *col, FILE *fin);
  csv�t�@�C�������x�N�g���̓���
    �߂�l: �ǂݍ��񂾗�x�N�g���̐擪�|�C���^

    �p�����[�^
      ����
        fin: �x�N�g�����܂ރt�@�C���ւ̃|�C���^
      �o��
        col: ��x�N�g���̗�
*/
double *vecInput(int *row, int *col, FILE *fin) {
  double **matrix, *vector;

  matrix = csvRead(row, col, fin);
  vector = matrix2colVector((const double **)matrix, *row, *col);

  freeMatrix(matrix);

  return vector;
}

/*
 simCheck(int row, int col)
  �A���������̌`�̊m�F�i�s��̍s���Ɨ�x�N�g���̗񐔂̔�r�j
    �߂�l: ���v: 0, �قȂ�: 1

    �p�����[�^
      ����
        row: �s��̍s��
        col: ��x�N�g���̗�
*/
int simCheck(int row, int col) {
  if (row != col) /* �قȂ�ꍇ */
  {
    fprintf(stderr, "���͂��ꂽ�s��̍s���Ɨ�x�N�g���̗񐔂��قȂ�܂��B\n");
    return 1;
  } else /* ���v���Ă���ꍇ */
  {
    return 0;
  }
}

/*
 squCheck(int row, int col)
  �s�񂪐����s�񂩂ǂ����̊m�F
    �߂�l: �����s��: 0, ����ȊO: 1

    �p�����[�^
      ����
        row: �s��̍s��
        col: �s��̗�
*/
int squCheck(int row, int col) {
  if (row != col) /* �����s��łȂ��ꍇ */
  {
    fprintf(stderr, "���͂��ꂽ�s��͐����s��ł͂���܂���B\n");
    return 1;
  } else /* �����s��̏ꍇ */
  {
    return 0;
  }
}

/*
 diaMake(int side)
  �Ίp�s��i�S�Ă̐������P�j�̍쐬
    �߂�l: �Ίp�s��̐擪�|�C���^

    �p�����[�^
      ����
        side: �s���i�������͗񐔁j
*/
double **diaMake(int side) {
  int i, j;
  double **matrix;

  matrix = allocMatrix(side, side);

  for (i = 0; i < side; i++) {
    for (j = 0; j < side; j++) {
      if (i == j) {
        matrix[i][j] = 1.0;
      } else {
        matrix[i][j] = 0.0;
      }
    }
  }

  return matrix;
}

/*
 rowChange(double **matrix, int row1, int row2, int col)
  �s��̍s�����ւ���
    �p�����[�^
      ����
        matrix: ����ւ��Ώۂ̍s��
        row1:   ����ւ���s1
        row2:   ����ւ���s2
        col:    �s��̗�
*/
void rowChange(double **matrix, int row1, int row2, int col) {
  int i;
  double buf;

  for (i = 0; i < col; i++) {
    buf = matrix[row1][i];
    matrix[row1][i] = matrix[row2][i];
    matrix[row2][i] = buf;
  }
}

/*
 LUPMatrix(double *matrix, int row, int col)
  L�CU�CP�s������߂�
    �p�����[�^
      ����
        side: �s��̍s���i�񐔁j
        matrix: ���͂��ꂽ�s��
        vector: ���͂��ꂽ�x�N�g��
      �o��
        �e�s��ƘA���������̉�
*/
void LUPMatrix(double *matrix, double *vector, int side) {
  int i, j, k;
  int maxRow; /* �ő��Βl���܂ލs */
  double buf;
  double *x, *y, *Pb;
  double **L, **U, **matrixP;

  /* U�s��̗p�� */
  U = allocMatrix(side, side);
  for (i = 0; i < side; i++) {
    for (j = 0; j < side; j++) {
      U[i][j] = matrix[j * side + i];
    }
  }

  /* L�s��̗p�� */
  L = diaMake(side);

  /* P�s��̗p�� */
  matrixP = diaMake(side);

  for (i = 0; i < side - 1; i++) {
    /* �ő��Βl�̒T�� */
    for (maxRow = i, j = i + 1; j < side; j++) {
      if (abs_d(U[j][i]) > abs_d(U[maxRow][i])) {
        maxRow = j;
      }
    }

    /* �s�̓���ւ� */
    if (maxRow != i) {
      rowChange(U, maxRow, i, side);
      rowChange(matrixP, maxRow, i, side);
      for (j = 0; j < i; j++) {
        buf = L[maxRow][j];
        L[maxRow][j] = L[i][j];
        L[i][j] = buf;
      }
    }

    /* �O�i���� */
    for (j = i + 1; j < side; j++) {
      /* L�s��ɑ�� */
      L[j][i] = U[j][i] / U[i][i];

      /* U�s��̌v�Z */
      for (k = i; k < side; k++) {
        U[j][k] -= U[i][k] * L[j][i];
      }
    }
  }

  /* �s��̕\�� */
  printf("L:\n");
  showMatrix((const double **)L, side, side);
  printf("U:\n");
  showMatrix((const double **)U, side, side);
  printf("P:\n");
  showMatrix((const double **)matrixP, side, side);

  /* P*b�̌v�Z */
  Pb = (double *)malloc(sizeof(double) * side);

  for (i = 0; i < side; i++) {
    Pb[i] = 0.0;
    for (j = 0; j < side; j++) {
      Pb[i] += matrixP[i][j] * vector[j];
    }
  }

  /* �A���������̌v�Z (y) */
  y = (double *)malloc(sizeof(double) * side);

  for (i = 0; i < side; i++) {
    y[i] = Pb[i];
    for (j = 0; j < i; j++) {
      y[i] -= L[i][j] * y[j];
    }
    y[i] /= L[i][i];
  }
  freeVector(Pb);
  freeMatrix(L);

  /* �A���������̌v�Z (x) */
  x = (double *)malloc(sizeof(double) * side);

  for (i = side - 1; i >= 0; i--) {
    x[i] = y[i];
    for (j = side - 1; j > i; j--) {
      x[i] -= U[i][j] * x[j];
    }
    x[i] /= U[i][i];
  }
  freeVector(y);
  freeMatrix(U);

  /* ���̕\�� */
  for (i = 0; i < side; i++) {
    printf("x%d: %f\n", i + 1, x[i]);
  }
  freeVector(x);

  freeMatrix(matrixP);
}

int main(int argc, char *argv[]) {
  int i, j;
  int rowM, colM, rowV, colV;
  double *matrix, *vector;
  FILE *fin1, *fin2;

  /* �R�}���h���C�������̐��̊m�F */
  if (argCheck(argc, ARG_NUM)) {
    return EXIT_FAILURE;
  }

  /* �t�@�C���i�s��j�̓��� */
  if (fileOpen(&fin1, argv[1], "r")) {
    return EXIT_FAILURE;
  }

  /* �t�@�C���i�x�N�g���j�̓��� */
  if (fileOpen(&fin2, argv[2], "r")) {
    fclose(fin1);
    return EXIT_FAILURE;
  }

  /* �W���s��̓��� */
  matrix = vecInput(&rowM, &colM, fin1);

  /* �x�N�g���̓��� */
  vector = vecInput(&rowV, &colV, fin2);

  /* �t�@�C������� */
  fclose(fin1);
  fclose(fin2);

  /* ���̓f�[�^�̑傫���̊m�F �� �����s�񂩂ǂ����̊m�F*/
  if (simCheck(rowM, rowV * colV) || squCheck(rowM, colM)) {
    freeVector(matrix);
    freeVector(vector);
    return EXIT_FAILURE;
  }

  /* L, U, P�s��̌v�Z�ƕ\���C�A���������̌v�Z */
  LUPMatrix(matrix, vector, rowM);

  /* �������̊J�� */
  freeVector(matrix);
  freeVector(vector);

  /* ����I�� */
  return EXIT_SUCCESS;
}