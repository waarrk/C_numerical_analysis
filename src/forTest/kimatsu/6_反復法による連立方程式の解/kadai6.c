/* LU�����ɂ��A���������̌v�Z */

#include "NAbasic.h" /* ���l��͗p��{�֐��Q�����t�@�C�� */

#define ARG_NUM 3    /* �R�}���h���C�������̐� */
#define LOOP_NUM 100 /* ������ */
#define INIT_NUM 0.0 /* �����l */

/*
 argCheck(int argc, int num)
  �R�}���h���C�������̊m�F
    �߂�l: �������F0�C�قȂ�F1

    �p�����[�^
    �@����
        argc: ���͂��ꂽ�R�}���h���C�������̐�
        num : �������R�}���h���C�������̐�
*/
int argCheck(int argc, int num)
{
    if (argc != num) /* �R�}���h���C�������̐����Ⴄ�ꍇ */
    {
        fprintf(stderr, "�R�}���h���C�������̐����Ⴂ�܂��B\n");
        return 1;
    }
    else /* �R�}���h���C�������̐����������ꍇ */
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
 vecInput(int *col, FILE *fin);
  csv�t�@�C�������x�N�g���̓���
    �߂�l: �ǂݍ��񂾗�x�N�g���̐擪�|�C���^

    �p�����[�^
      ����
        fin: �x�N�g�����܂ރt�@�C���ւ̃|�C���^
      �o��
        col: ��x�N�g���̗�
*/
double *vecInput(int *row, int *col, FILE *fin)
{
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
int simCheck(int row, int col)
{
    if (row != col) /* �قȂ�ꍇ */
    {
        fprintf(stderr, "���͂��ꂽ�s��̍s���Ɨ�x�N�g���̗񐔂��قȂ�܂��B\n");
        return 1;
    }
    else /* ���v���Ă���ꍇ */
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
int squCheck(int row, int col)
{
    if (row != col) /* �����s��łȂ��ꍇ */
    {
        fprintf(stderr, "���͂��ꂽ�s��͐����s��ł͂���܂���B\n");
        return 1;
    }
    else /* �����s��̏ꍇ */
    {
        return 0;
    }
}

int main(int argc, char *argv[])
{
    int i, j, k;
    int rowM, colM, rowV, colV;
    double *matrix, *vector, LpU, *x, *x2;
    FILE *fin1, *fin2;

    /* �R�}���h���C�������̐��̊m�F */
    if (argCheck(argc, ARG_NUM))
    {
        return EXIT_FAILURE;
    }

    /* �t�@�C���i�s��j�̓��� */
    if (fileOpen(&fin1, argv[1], "r"))
    {
        return EXIT_FAILURE;
    }

    /* �t�@�C���i�x�N�g���j�̓��� */
    if (fileOpen(&fin2, argv[2], "r"))
    {
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
    if (simCheck(rowM, rowV * colV) || squCheck(rowM, colM))
    {
        freeVector(matrix);
        freeVector(vector);
        return EXIT_FAILURE;
    }

    /* ���R�r�@ */
    printf("���R�r�@�i�����񐔁F%d�j\n", LOOP_NUM);
    x = (double *)malloc(sizeof(double) * rowM);
    x2 = (double *)malloc(sizeof(double) * rowM);
    for (j = 0; j < rowM; j++)
        x[j] = INIT_NUM;
    for (i = 0; i <= LOOP_NUM; i++)
    {
        for (j = 0; j < rowM; j++)
            x2[j] = x[j];
        for (j = 0; j < rowM; j++)
        {
            LpU = vector[j];

            for (k = 0; k < rowM; k++)
            {
                if (j != k)
                    LpU -= matrix[k * rowM + j] * x2[k];
            }

            x[j] = LpU / matrix[j * rowM + j];
        }
    }
    for (i = 0; i < rowM; i++)
        printf("x[%d] = %lf\n", i, x[i]);

    /* �K�E�X�E�U�C�f���@ */
    printf("�K�E�X�E�U�C�f���@�i�����񐔁F%d�j\n", LOOP_NUM);
    for (j = 0; j < rowM; j++)
        x[j] = INIT_NUM;
    for (i = 0; i <= LOOP_NUM; i++)
    {
        for (j = 0; j < rowM; j++)
            x2[j] = x[j];
        for (j = 0; j < rowM; j++)
        {
            LpU = vector[j];

            for (k = 0; k < j; k++)
                LpU -= matrix[k * rowM + j] * x[k];
            for (k = j + 1; k < rowM; k++)
                LpU -= matrix[k * rowM + j] * x2[k];

            x[j] = LpU / matrix[j * rowM + j];
        }
    }
    for (i = 0; i < rowM; i++)
        printf("x[%d] = %lf\n", i, x[i]);

    /* �������̊J�� */
    freeVector(matrix);
    freeVector(vector);
    free(x);
    free(x2);

    /* ����I�� */
    return EXIT_SUCCESS;
}