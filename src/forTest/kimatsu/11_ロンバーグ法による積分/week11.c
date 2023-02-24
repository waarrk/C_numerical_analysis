/*
ロンバーグ法による積分
*/

#include "romberg.h"
#include "NAbasic.h"

int main(int argc, char *argv[])
{
    int row, col;
    double result, **range;
    FILE *fp;

    /* コマンドライン引数のチェック */
    if (argc != 3)
    {
        fprintf(stderr, "Usage :  %s Integral_range divisions\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* ファイルの入力 */
    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Could not open file\n");
        return EXIT_FAILURE;
    }

    /* 積分範囲の読み込み */
    range = csvRead(&row, &col, fp);
    fclose(fp);

    /* 入力データのチェック */
    if ((row != 1) || (col != 2))
    {
        fprintf(stderr, "There is an error in the input data.\n");
        freeMatrix(range);
        return EXIT_FAILURE;
    }

    /* 積分 */
    result = romberg(range[0][0], range[0][1], atoi(argv[2]));

    freeMatrix(range);

    return EXIT_SUCCESS;
}
