/* ��4�T�ډۑ� �����s�{�b�g�I��t���K�E�X�̏����@ */

/*
#include <stdio.h>
#include <stdlib.h>
*/
#include "NAbasic.h"

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
int pvEli(double **matrix1, int row, int col, double **matrix2, int k)
{
    double x;

    int i, j;
    for (i = k + 1; i < row; i++)
    {
        x = matrix1[i][k] / matrix1[k][k];
        for (j = k; j < col; j++)
            matrix1[i][j] = matrix1[i][j] - matrix1[k][j] * x;
        matrix2[i][0] = matrix2[i][0] - matrix2[k][0] * x;
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
int answer(double **matrix1, int row, int col, double **matrix2, double *vector)
{
    int i, j;
    for (i = row - 1; i >= 0; i--)
    {
        vector[i] = matrix2[i][0];
        for (j = row - 1; j > i; j--)
        {
            vector[i] -= matrix1[i][j] * vector[j];
        }
        vector[i] /= matrix1[i][i];
    }

    return EXIT_SUCCESS;
}

/*
showVector(double **vector, int col)
  ���̗�f�[�^���o�͂���D
      �߂�l: �\������

      �p�����[�^
        �o��
          matrix: �o�͑Ώۗ�f�[�^

        ����
        �@col: �ϊ��O�̔z��̗v�f��
*/
int showVector(double *vector, int col)
{
    int i;

    for (i = 0; i < col; i++)
        printf("x%d: %.4f\n", i + 1, vector[i]);

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    FILE *fin1, *fin2;

    /* �����̐��̃`�F�b�N */
    if (argc != 3)
    {
        fprintf(stderr, "�R�}���h���C�������̐����Ԉ���Ă��܂��D\n");
        return EXIT_FAILURE;
    }

    /* �t�@�C���̓ǂݍ��� */
    fin1 = fopen(argv[1], "r");
    if (fin1 == NULL)
    {
        fprintf(stderr, "�t�@�C�����J���܂���ł����D\n");
        fprintf(stderr, "  file : %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    fin2 = fopen(argv[2], "r");
    if (fin2 == NULL)
    {
        fprintf(stderr, "�t�@�C�����J���܂���ł����D\n");
        fprintf(stderr, "  file : %s\n", argv[2]);
        fclose(fin1);
        return EXIT_FAILURE;
    }

    int row1, row2, col1, col2;
    double **matrix1, **matrix2;

    /* �f�[�^�̓ǂݍ��� */
    matrix1 = csvRead(&row1, &col1, fin1);
    matrix2 = csvRead(&row2, &col2, fin2);

    /* 2�̍s��̍s�������������`�F�b�N */
    if (row1 != row2)
    {
        fprintf(stderr, "���͂��ꂽ2�̍s��̍s�����قȂ�܂��D\n");

        /* �������̊J�� */
        fclose(fin1);
        fclose(fin2);
        freeMatrix(matrix1);
        freeMatrix(matrix2);
        return EXIT_FAILURE;
    }

    /* �E�ӂ̍s��1�񂩃`�F�b�N */
    if (col2 != 1)
    {
        fprintf(stderr, "���͂��ꂽ2�ڂ̍s��̗񂪈قȂ�܂��D\n");

        /* �������̊J�� */
        fclose(fin1);
        fclose(fin2);
        freeMatrix(matrix1);
        freeMatrix(matrix2);
        return EXIT_FAILURE;
    }

    /* ��v���� */
    int i, j;
    int row_max; /* �ő��Βl���܂ލs */
    for (i = 0; i < row1 - 1; i++)
    {
        /* �ő��Βl���܂ލs�̒T���D */
        for (j = row_max = i; j < row1; j++)
        {
            if (j == i)
                continue;
            if (abs_d(matrix1[row_max][i]) < abs_d(matrix1[j][i]))
                row_max = j;
        }

        /* i�si�񂪐�΍ő�l�ł͂Ȃ������ꍇ */
        if (row_max != i)
        {
            /* �s�̓���ւ� */
            changeRow(matrix1, row1, col1, i, row_max);
            changeRow(matrix2, row2, col2, i, row_max);
        }

        /* �s�{�b�g�I��t���O�i���� */
        pvEli(matrix1, row1, col1, matrix2, i);
    }

    /* ���̌v�Z */
    double *x;
    x = allocVector(row1);
    answer(matrix1, row1, col1, matrix2, x);

    /* ���̕\�� */
    showVector(x, row1);

    /* �������̊J�� */
    fclose(fin1);
    fclose(fin2);
    freeVector(x);
    freeMatrix(matrix1);
    freeMatrix(matrix2);

    return EXIT_SUCCESS;
}