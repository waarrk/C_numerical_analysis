/* LU分解による連立方程式の計算 */

#include "NAbasic.h" /* 数値解析用基本関数群実装ファイル */

#define ARG_NUM 3    /* コマンドライン引数の数 */
#define LOOP_NUM 100 /* 反復回数 */
#define INIT_NUM 0.0 /* 初期値 */

/*
 argCheck(int argc, int num)
  コマンドライン引数の確認
    戻り値: 正しい：0，異なる：1

    パラメータ
    　入力
        argc: 入力されたコマンドライン引数の数
        num : 正しいコマンドライン引数の数
*/
int argCheck(int argc, int num)
{
    if (argc != num) /* コマンドライン引数の数が違う場合 */
    {
        fprintf(stderr, "コマンドライン引数の数が違います。\n");
        return 1;
    }
    else /* コマンドライン引数の数が正しい場合 */
    {
        return 0;
    }
}

/*
 fileOpen(FILE *fin, char *filename);
  ファイルを開く
    戻り値: 成功: 0，失敗: 1

    パラメータ
      入力
        filename: 開くファイルの名前
        mode    : ファイルを開くモード
      出力
        fin: ファイルの先頭ポインタ
*/
int fileOpen(FILE **fin, char *filename, char *mode)
{
    /* ファイルのオープン */
    *fin = fopen(filename, mode);

    if (*fin == NULL) /* ファイルが開けなかった場合 */
    {
        fprintf(stderr, "対象ファイル：%s\n", filename);
        fprintf(stderr, "ファイルを開けませんでした。\n");
        return 1;
    }
    else /* ファイルが開けた場合 */
    {
        return 0;
    }
}

/*
 vecInput(int *col, FILE *fin);
  csvファイルから列ベクトルの入力
    戻り値: 読み込んだ列ベクトルの先頭ポインタ

    パラメータ
      入力
        fin: ベクトルを含むファイルへのポインタ
      出力
        col: 列ベクトルの列数
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
  連立方程式の形の確認（行列の行数と列ベクトルの列数の比較）
    戻り値: 合致: 0, 異なる: 1

    パラメータ
      入力
        row: 行列の行数
        col: 列ベクトルの列数
*/
int simCheck(int row, int col)
{
    if (row != col) /* 異なる場合 */
    {
        fprintf(stderr, "入力された行列の行数と列ベクトルの列数が異なります。\n");
        return 1;
    }
    else /* 合致している場合 */
    {
        return 0;
    }
}

/*
 squCheck(int row, int col)
  行列が正方行列かどうかの確認
    戻り値: 正方行列: 0, それ以外: 1

    パラメータ
      入力
        row: 行列の行数
        col: 行列の列数
*/
int squCheck(int row, int col)
{
    if (row != col) /* 正方行列でない場合 */
    {
        fprintf(stderr, "入力された行列は正方行列ではありません。\n");
        return 1;
    }
    else /* 正方行列の場合 */
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

    /* コマンドライン引数の数の確認 */
    if (argCheck(argc, ARG_NUM))
    {
        return EXIT_FAILURE;
    }

    /* ファイル（行列）の入力 */
    if (fileOpen(&fin1, argv[1], "r"))
    {
        return EXIT_FAILURE;
    }

    /* ファイル（ベクトル）の入力 */
    if (fileOpen(&fin2, argv[2], "r"))
    {
        fclose(fin1);
        return EXIT_FAILURE;
    }

    /* 係数行列の入力 */
    matrix = vecInput(&rowM, &colM, fin1);

    /* ベクトルの入力 */
    vector = vecInput(&rowV, &colV, fin2);

    /* ファイルを閉じる */
    fclose(fin1);
    fclose(fin2);

    /* 入力データの大きさの確認 と 正方行列かどうかの確認*/
    if (simCheck(rowM, rowV * colV) || squCheck(rowM, colM))
    {
        freeVector(matrix);
        freeVector(vector);
        return EXIT_FAILURE;
    }

    /* ヤコビ法 */
    printf("ヤコビ法（反復回数：%d）\n", LOOP_NUM);
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

    /* ガウス・ザイデル法 */
    printf("ガウス・ザイデル法（反復回数：%d）\n", LOOP_NUM);
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

    /* メモリの開放 */
    freeVector(matrix);
    freeVector(vector);
    free(x);
    free(x2);

    /* 正常終了 */
    return EXIT_SUCCESS;
}