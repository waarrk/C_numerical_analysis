/*
台形公式による数値積分
*/

#include "NAbasic.h"
#define EQU(x) (x) * (x) /* 式 */

int main(int argc, char **argv)
{
    int i, row, col;
    double **matrix, h, A;
    FILE *fin;

    /* csvファイルから行列の読み込み */
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

    h = (matrix[0][2] - matrix[0][1]) / matrix[0][0];

    A = 0.0;
    for (i = 0; i < matrix[0][0]; i++)
        A += (EQU(matrix[0][1] + h * i) + EQU(matrix[0][1] + h * (i + 1))) * h / 2.0;

    printf("面積：%f\n", A);

    /* メモリの開放 */
    freeMatrix(matrix);

    return EXIT_SUCCESS;
}