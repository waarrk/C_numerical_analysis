/*
�����o�[�O�@�ɂ��ϕ��֐��Q
*/

#include "romberg.h"

/*
�����o�[�O�@�ɂ��ϕ�
  �߂�l:
    �ϕ�����
  �p�����[�^
    double a: �ϕ��͈�(a<b)
    double b: �ϕ��͈�(a<b)
    int    k: �ő啪����
*/
double romberg(double a, double b, int k)
{
    int i, j, n, m;
    double **T, *h, result;

    if (a >= b)
    {
        fprintf(stderr, "There is an error in the integral range.\n");
        exit(EXIT_FAILURE);
    }

    /* �����o�[�O�\�̌v�Z */
    T = (double **)malloc(sizeof(double *) * (k + 1));
    if (T == NULL)
    {
        fprintf(stderr, "Failed to dynamically allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    h = (double *)calloc(k + 1, sizeof(double));
    if (h == NULL)
    {
        fprintf(stderr, "Failed to dynamically allocate memory.\n");
        free(T);
        exit(EXIT_FAILURE);
    }
    for (i = 0, n = 1; i <= k; i++, n *= 2)
    {

        /* �v���_�̌v�Z */
        h[i] = (b - a) / (double)n;

        T[i] = (double *)malloc(sizeof(double) * (i + 1));
        if (T[i] == NULL)
        {
            fprintf(stderr, "Failed to dynamically allocate memory.\n");
            free(h);
            for (i = i - 1; i >= 0; i--)
                free(T[i]);
            free(T);
            exit(EXIT_FAILURE);
        }

        /* m = 0 */
        if (i == 0)
        {
            T[i][0] = h[i] * (EQU(a) + EQU(b)) / 2.0;
        }
        else
        {
            T[i][0] = 0.0;
            for (j = 1; j <= n / 2; j++)
            {
                T[i][0] += EQU(a + (double)(2 * j - 1) * h[i]);
            }
            T[i][0] = T[i - 1][0] / 2.0 + h[i] * T[i][0];
        }

        /* m >= 1 */
        for (j = 1, m = 4; j <= i; j++, m *= 4)
            T[i][j] = T[i][j - 1] + (T[i][j - 1] - T[i - 1][j - 1]) / (m - 1);

        result = T[i][i];

        /* �K��l���ω����Ȃ������ꍇ */
        if ((i != 0) && (fabs(T[i][i] - T[i - 1][i - 1]) < ERR))
            break;
    }

    /* ���ʂ̏o�� */
    printf("�������F%d(k=%d), �����F%d(m=%d)\n", n / 2, k, n / 2, k);
    printf("Romberg Table:\n");
    for (n = 0; n < i; n++)
    {
        for (j = 0; j <= n; j++)
            printf("%2.10f ", T[n][j]);
        printf("\n");
    }
    printf("�ϕ��l:%f\n", result);

    /* �������̊J�� */
    free(h);

    for (; i >= 0; i--)
        free(T[i]);

    free(T);
    return result;
}