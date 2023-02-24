#include "LUfunction.h"

/*
 abs(double x);
  ��Βl�̌v�Z
    �߂�l: ��Βl

    �p�����[�^
      ����
        x: �����l
*/
double abs_d(double x)
{
    return (x >= 0) ? x : -x; /* �ő��Βl�̌v�Z */
}

/*
 diaMake(int side)
  �Ίp�s��i�S�Ă̐������P�j�̍쐬
    �߂�l: �Ίp�s��̐擪�|�C���^

    �p�����[�^
      ����
        side: �s���i�������͗񐔁j
*/
double **diaMake(int side)
{
    int i, j;
    double **matrix;

    matrix = allocMatrix(side, side);

    for (i = 0; i < side; i++)
    {
        for (j = 0; j < side; j++)
        {
            if (i == j)
            {
                matrix[i][j] = 1.0;
            }
            else
            {
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
void rowChange(double **matrix, int row1, int row2, int col)
{
    int i;
    double buf;

    for (i = 0; i < col; i++)
    {
        buf = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = buf;
    }
}

/*
 LUPMatrix(double *matrix, int side)
  �t�s������߂�
    �߂�l
      �t�s��
    �p�����[�^
      ����
        side: �s��̍s���i�񐔁j
        matrix: ���͂��ꂽ�s��
*/
double **iMatrix(double *matrix, int side)
{
    int i, j, k;
    int maxRow; /* �ő��Βl���܂ލs */
    double buf;
    double *x, *y, *Pb;
    double **matrixL, **matrixU, **matrixP, **imatrixL, **imatrixU, **imatrixUL, **imatrix;

    /* U�s��̗p�� */
    matrixU = allocMatrix(side, side);
    for (i = 0; i < side; i++)
    {
        for (j = 0; j < side; j++)
        {
            matrixU[i][j] = matrix[i * side + j];
        }
    }

    /* L�s��̗p�� */
    matrixL = diaMake(side);

    /* P�s��̗p�� */
    matrixP = diaMake(side);

    for (i = 0; i < side - 1; i++)
    {
        /* �ő��Βl�̒T�� */
        for (maxRow = i, j = i + 1; j < side; j++)
        {
            if (abs_d(matrixU[j][i]) > abs_d(matrixU[maxRow][i]))
            {
                maxRow = j;
            }
        }

        /* �s�̓���ւ� */
        if (maxRow != i)
        {
            rowChange(matrixU, maxRow, i, side);
            rowChange(matrixP, maxRow, i, side);
            for (j = 0; j < i; j++)
            {
                buf = matrixL[maxRow][j];
                matrixL[maxRow][j] = matrixL[i][j];
                matrixL[i][j] = buf;
            }
        }

        /* �O�i���� */
        for (j = i + 1; j < side; j++)
        {
            /* L�s��ɑ�� */
            matrixL[j][i] = matrixU[j][i] / matrixU[i][i];

            /* U�s��̌v�Z */
            for (k = i; k < side; k++)
            {
                matrixU[j][k] -= matrixU[i][k] * matrixL[j][i];
            }
        }
    }

    /* �t�s������߂� */

    /* L�̋t�s������߂� */
    imatrixL = diaMake(side);
    for (i = 0; i < side; i++)
    {
        for (j = i; j >= 0; j--)
        {
            if (i == j)
            {
                imatrixL[i][j] = 1.0 / matrixL[i][j];
            }
            else
            {
                imatrixL[i][j] = 0.0;
                for (k = 0; k < i; k++)
                {
                    imatrixL[i][j] -= matrixL[i][k] * imatrixL[k][j];
                }
                imatrixL[i][j] /= matrixL[i][k];
            }
        }
    }

    /* U�̋t�s������߂� */
    imatrixU = diaMake(side);
    for (i = side - 1; i >= 0; i--)
    {
        for (j = i; j < side; j++)
        {
            if (i == j)
            {
                imatrixU[i][j] = 1.0 / matrixU[i][j];
            }
            else
            {
                imatrixL[i][j] = 0.0;
                for (k = side - 1; k > i; k--)
                {
                    imatrixU[i][j] -= matrixU[i][k] * imatrixU[k][j];
                }
                imatrixU[i][j] /= matrixU[i][k];
            }
        }
    }

    imatrixUL = allocMatrix(side, side);
    /* U^-1 L^-1 */
    for (i = 0; i < side; i++)
    {
        for (j = 0; j < side; j++)
        {
            imatrixUL[i][j] = 0.0;
            for (k = 0; k < side; k++)
            {
                imatrixUL[i][j] += imatrixU[i][k] * imatrixL[k][j];
            }
        }
    }

    imatrix = allocMatrix(side, side);
    /* U^-1 L^-1 P */
    for (i = 0; i < side; i++)
    {
        for (j = 0; j < side; j++)
        {
            imatrix[i][j] = 0.0;
            for (k = 0; k < side; k++)
            {
                imatrix[i][j] += imatrixUL[i][k] * matrixP[k][j];
            }
        }
    }

    freeMatrix(matrixL);
    freeMatrix(matrixU);
    freeMatrix(matrixP);
    freeMatrix(imatrixL);
    freeMatrix(imatrixU);
    freeMatrix(imatrixUL);

    return imatrix;
}