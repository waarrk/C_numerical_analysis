/* LU分解による連立方程式の計算 */

#include "NAbasic.h" /* 数値解析用基本関数群実装ファイル */

#define ARG_NUM 3 /* コマンドライン引数の数 */

/*
 abs(double x);
  絶対値の計算
    戻り値: 絶対値

    パラメータ
      入力
        x: 実数値
*/
double abs_d(double x)
{
    return (x >= 0) ? x : -x; /* 最大絶対値の計算 */
}

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

/*
 diaMake(int side)
  対角行列（全ての成分が１）の作成
    戻り値: 対角行列の先頭ポインタ

    パラメータ
      入力
        side: 行数（もしくは列数）
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
  行列の行を入れ替える
    パラメータ
      入力
        matrix: 入れ替え対象の行列
        row1:   入れ替える行1
        row2:   入れ替える行2
        col:    行列の列数
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
 LUPMatrix(double *matrix, int row, int col)
  L，U，P行列を求める
    パラメータ
      入力
        side: 行列の行数（列数）
        matrix: 入力された行列
        vector: 入力されたベクトル
      出力
        各行列と連立方程式の解
*/
void LUPMatrix(double *matrix, double *vector, int side)
{
    int i, j, k;
    int maxRow; /* 最大絶対値を含む行 */
    double buf;
    double *x, *y, *Pb;
    double **matrixL, **matrixU, **matrixP;
    double **imatrixL, **imatrixU, **matrixUL, **imatrix, **matrixCheck;

    /* U行列の用意 */
    matrixU = allocMatrix(side, side);
    for (i = 0; i < side; i++)
    {
        for (j = 0; j < side; j++)
        {
            matrixU[i][j] = matrix[j * side + i];
        }
    }

    /* L行列の用意 */
    matrixL = diaMake(side);

    /* P行列の用意 */
    matrixP = diaMake(side);

    for (i = 0; i < side - 1; i++)
    {
        /* 最大絶対値の探索 */
        for (maxRow = i, j = i + 1; j < side; j++)
        {
            if (abs_d(matrixU[j][i]) > abs_d(matrixU[maxRow][i]))
            {
                maxRow = j;
            }
        }

        /* 行の入れ替え */
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

        /* 前進消去 */
        for (j = i + 1; j < side; j++)
        {
            /* L行列に代入 */
            matrixL[j][i] = matrixU[j][i] / matrixU[i][i];

            /* U行列の計算 */
            for (k = i; k < side; k++)
            {
                matrixU[j][k] -= matrixU[i][k] * matrixL[j][i];
            }
        }
    }

    /* 行列の表示 */
    printf("L:\n");
    showMatrix((const double **)matrixL, side, side);
    printf("U:\n");
    showMatrix((const double **)matrixU, side, side);
    printf("P:\n");
    showMatrix((const double **)matrixP, side, side);

    /* P*bの計算 */
    Pb = (double *)malloc(sizeof(double) * side);

    for (i = 0; i < side; i++)
    {
        Pb[i] = 0.0;
        for (j = 0; j < side; j++)
        {
            Pb[i] += matrixP[i][j] * vector[j];
        }
    }

    /* 連立方程式の計算 (y) */
    y = (double *)malloc(sizeof(double) * side);

    for (i = 0; i < side; i++)
    {
        y[i] = Pb[i];
        for (j = 0; j < i; j++)
        {
            y[i] -= matrixL[i][j] * y[j];
        }
        y[i] /= matrixL[i][i];
    }
    freeVector(Pb);

    /* 連立方程式の計算 (x) */
    x = (double *)malloc(sizeof(double) * side);

    for (i = side - 1; i >= 0; i--)
    {
        x[i] = y[i];
        for (j = side - 1; j > i; j--)
        {
            x[i] -= matrixU[i][j] * x[j];
        }
        x[i] /= matrixU[i][i];
    }
    freeVector(y);

    /* 解の表示 */
    for (i = 0; i < side; i++)
    {
        printf("x%d: %f\n", i + 1, x[i]);
    }
    freeVector(x);

    /* Lの逆行列を求める */
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

    /* Uの逆行列を求める */
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

    matrixUL = allocMatrix(side, side);
    /* U^-1 L^-1 */
    for (i = 0; i < side; i++)
    {
        for (j = 0; j < side; j++)
        {
            matrixUL[i][j] = 0.0;
            for (k = 0; k < side; k++)
            {
                matrixUL[i][j] += imatrixU[i][k] * imatrixL[k][j];
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
                imatrix[i][j] += matrixUL[i][k] * matrixP[k][j];
            }
        }
    }

    matrixCheck = allocMatrix(side, side);
    /* A A^-1 */
    for (i = 0; i < side; i++)
    {
        for (j = 0; j < side; j++)
        {
            matrixCheck[i][j] = 0.0;
            for (k = 0; k < side; k++)
            {
                matrixCheck[i][j] += matrix[k * side + i] * imatrix[k][j];
            }
        }
    }

    /* 行列の表示 */
    printf("iL:\n");
    showMatrix((const double **)imatrixL, side, side);
    printf("iU:\n");
    showMatrix((const double **)imatrixU, side, side);
    printf("UL:\n");
    showMatrix((const double **)matrixUL, side, side);
    printf("i:\n");
    showMatrix((const double **)imatrix, side, side);
    printf("check:\n");
    showMatrix((const double **)matrixCheck, side, side);

    /* メモリの開放 */
    freeMatrix(matrixL);
    freeMatrix(matrixU);
    freeMatrix(matrixP);

    freeMatrix(imatrixL);
    freeMatrix(imatrixU);
    freeMatrix(matrixUL);
    freeMatrix(imatrix);
    freeMatrix(matrixCheck);
}

int main(int argc, char *argv[])
{
    int i, j;
    int rowM, colM, rowV, colV;
    double *matrix, *vector;
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

    /* L, U, P行列の計算と表示，連立方程式の計算 */
    LUPMatrix(matrix, vector, rowM);

    /* メモリの開放 */
    freeVector(matrix);
    freeVector(vector);

    /* 正常終了 */
    return EXIT_SUCCESS;
}