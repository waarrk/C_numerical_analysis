/*
ロンバーグ法による積分関数群
*/

#include "romberg.h"

/*
ロンバーグ法による積分
  戻り値:
    積分結果
  パラメータ
    double a: 積分範囲(a<b)
    double b: 積分範囲(a<b)
    int    k: 最大分割数
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

    /* ロンバーグ表の計算 */
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

        /* 計測点の計算 */
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

        /* 規定値より変化がなかった場合 */
        if ((i != 0) && (fabs(T[i][i] - T[i - 1][i - 1]) < ERR))
            break;
    }

    /* 結果の出力 */
    printf("分割数：%d(k=%d), 次数：%d(m=%d)\n", n / 2, k, n / 2, k);
    printf("Romberg Table:\n");
    for (n = 0; n < i; n++)
    {
        for (j = 0; j <= n; j++)
            printf("%2.10f ", T[n][j]);
        printf("\n");
    }
    printf("積分値:%f\n", result);

    /* メモリの開放 */
    free(h);

    for (; i >= 0; i--)
        free(T[i]);

    free(T);
    return result;
}