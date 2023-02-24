/* 
課題1.
  実数をIEEE754形式の2進数に変換するプログラム
  double型が64bitのIEEE754形式で格納されていることを利用する
*/
#include <stdio.h>
#include <stdlib.h>
#include "NAbasic.h"

int main(int argc, char *argv[]) {
    FILE *fin;
    double **matrix;
    int row, col;

    char c[sizeof(double)];
    int i, j, k;

    /* コマンドライン引数の確認 */
    if (argc != 2) {
        fprintf(stderr, "コマンドライン引数が間違っています．<*.exe> <input_file>\n");
		return EXIT_FAILURE;
    }

    /* CSVファイルの読み込み */
    if ((fin = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "\"%s\"を開けませんでした.\n", argv[1]);
		return EXIT_FAILURE;
	}

    /* CSVファイルから行列データ（実数値）の読み込み */
    matrix = csvRead(&row, &col, fin);

    /* 行列データ（実数値）を文字列にメモリのコピー */
    memcpy(c, &matrix[0][0], sizeof(double));

    /* IEEE754形式の概略 */
    printf("sEEEEEEE EEEEdddd dddddddd... \n");

    /* 表示変換 */
    for (i = sizeof(double) - 1; i >= 0; i--) { /* double型(64bit)1つ分の処理 */
        for (j = sizeof(c[i]) * 8 - 1; j >= 0; j--) { /* char型(8bit)1つ分の処理 */
            k = c[i] & (1 << j);
            printf("%d", k ? 1 : 0);
        }
        printf(" ");
    }
    printf("\n");

    /* メモリの開放 */
    freeMatrix(matrix);

    return 0;
}