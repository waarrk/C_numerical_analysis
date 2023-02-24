/*
数値解析処理用関数群実装ファイル
*/

/* ヘッダファイル */
#include "NAplus.h"

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
int charRemove(char *char, int n)
  動的確保した文字列から一文字消す
    戻り値:
      削除後の文字列へのポインタ
      失敗した場合NULL

    パラメータ
      入力:
        str: 操作する文字列
        size: 文字列の長さ(\0を含めない=strlen())
        n: 消す文字の要素数
      出力:
        str: 解放
        size: 一文字消した後の文字列の長さ
*/
char *charRemove(char *str, int *size, int n)
{
  int i;
  char *str1;

  /* nの確認 */
  if ((n < 0) || (n >= *size))
  {
    fprintf(stderr, "A value exceeding the size of the string is specified. (charRemove)\n");
    return 0;
  }

  /* メモリの動的確保 */
  str1 = (char *)malloc(sizeof(char) * (*size));
  if (str1 == NULL)
  {
    fprintf(stderr, "Failed to dynamically allocate memory. (arrayAlloc)\n");
    return NULL;
  }

  *size -= 1;

  /* 1文字ずつずらす */
  memcpy(str1, str, n);
  for (i = n; i < *size; i++)
  {
    str1[i] = str[i + 1];
  }
  str[*size] = '\0';

  /* 元の文字列の解放 */
  free(str);

  return str1;
}

/*
arrayAlloc(int size)
  配列の動的確保(実数)
    戻り値:
      配列の先頭ポインタ
      失敗した場合はNULL

    パラメータ
      入力:
        配列のサイズ
*/
double *arrayAlloc(int size)
{
  double *array;

  /* メモリの動的確保 */
  array = (double *)malloc(sizeof(double) * size);
  if (array == NULL)
  {
    fprintf(stderr, "Failed to dynamically allocate memory. (arrayAlloc)\n");
  }

  return array;
}

/*
matrixAlloc(int row, int col)
  行列(二次元配列)の動的確保(実数)
    戻り値:
      確保した行列の先頭ポインタ
      失敗した場合はNULL

    パラメータ
      入力:
        row: 確保する行列の行数
        col: 確保する行列の列数
*/
double **matrixAlloc(int row, int col)
{
  int i;
  double **matrix;

  /* 行数と列数の確認 */
  if ((row <= 0) || (col <= 0))
  {
    fprintf(stderr, "The number of rows and columns must be natural numbers. (matrixAlloc)\n");
    return NULL;
  }

  /* 二次元配列の動的確保 */
  matrix = (double **)malloc(sizeof(double *) * row);
  if (matrix == NULL)
  {
    fprintf(stderr, "Failed to dynamically allocate memory. (matrixAlloc)\n");
    return NULL;
  }

  /* 配列の動的確保 */
  for (i = 0; i < row; i++)
  {
    matrix[i] = arrayAlloc(col);
    if (matrix[i] == NULL)
    {
      for (i = i - 1; i >= 0; i--)
      {
        free(matrix[i]);
      }
      free(matrix);
      return NULL;
    }
  }

  return matrix;
}

/*
append(double **array, int size, double x)
  配列に要素の追加(実数)
    パラメータ
      戻り値:
        正常終了: 0, エラー終了 : 1

      入力:
        array: 追加元の配列のアドレス
        size: 追加元の配列の大きさ
        x: 追加する値
      出力:
        array: 追加後の配列の先頭ポインタ
*/
int append(double **array, int *size, double x)
{
  int i;
  double *array1;

  /* メモリの動的確保 */
  array1 = arrayAlloc(*size + 1);
  if (array1 == NULL)
  {
    return 1;
  }

  /* 配列内要素のコピー */
  memcpy(array1, *array, *size);

  /* 元の配列のメモリを解放 */
  free(*array);

  /* 末尾に値を追加 */
  array1[*size] = x;

  /* サイズを更新 */
  *size += 1;

  /* 追加後の配列の先頭ポインタを渡されたポインタに代入 */
  *array = array1;

  return 0;
}

/*
intAppend(int **array, int size, int x)
  配列に要素の追加(実数)
    パラメータ
      戻り値:
        正常終了: 0, エラー終了 : 1

      入力:
        array: 追加元の配列のアドレス
        size: 追加元の配列の大きさ
        n: 追加する値
      出力:
        array: 追加後の配列の先頭アドレス
*/
int intAppend(int **array, int *size, int n)
{
  int i;
  int *array1;

  /* メモリの動的確保 */
  array1 = (int *)malloc(sizeof(int) * (*size + 1));
  if (array1 == NULL)
  {
    fprintf(stderr, "Failed to dynamically allocate memory. (intAppend)\n");
    return 1;
  }

  /* 配列内要素のコピー */
  memcpy(array1, *array, *size);

  /* 元の配列のメモリを解放 */
  free(*array);

  /* 末尾に値を追加 */
  array1[*size] = n;

  /* サイズを更新 */
  *size += 1;

  /* 追加後の配列の先頭ポインタを渡されたポインタに代入 */
  *array = array1;

  return 0;
}

/*
void arrayShow(double *array, int size)
  配列の中身を表示(実数)
    パラメータ
      入力:
        *array: 配列の先頭ポインタ
        size: 配列の大きさ
*/
void arrayShow(double *array, int size)
{
  int i;

  printf("[");
  for (i = 0; i < size - 1; i++)
  {
    printf("%.4f, ", array[i]);
  }
  printf("%.4f", array[size - 1]);
  printf("]\n");
}

/*
int argCheck(int argc, int n)
  コマンドライン引数の数を確認
    戻り値
      正常：0，異常：1

    パラメータ
      入力
        argc: コマンドラインの数
        n: 理想のコマンドラインの数
*/
int argCheck(int argc, int n)
{
  if (argc == n)
  {
    return 0;
  }
  else
  {
    fprintf(stderr, "Command line argument is incorrect.");
    return 1;
  }
}

/*
int squareMatrixCheck(int row, int col)
  正方行列かどうかの確認
    戻り値
      正方行列：1，それ以外：0

    入力
      row：行数
      col：列数
*/
int squareMatrixCheck(int row, int col)
{
  if (row == col)
  {
    return 0;
  }
  else
  {
    fprintf(stderr, "Input matrix is not square.");
    return 1;
  }
}

/*
double fAbs(double x)
  実数値の絶対値
    戻り値
      実数値の絶対値

    パラメータ
      入力
        実数値
*/
double fAbs(double x)
{
  return (x < 0.0) ? -x : x;
}

/*
double MVmul(double **matrix, double *vector, int n);
  行列とベクトルの積
    戻り値
      積、失敗時はNULL

    パラメータ
      入力
        matrix: 行列
        vector: ベクトル
        row: 行列の行数
        col: 行列の列数・ベクトルの要素数
*/
double *MVmul(double **matrix, double *vector, int row, int col)
{
  int i, j;
  double *vec;

  vec = (double *)calloc(col, sizeof(double));
  if (vec == NULL)
  {
    fprintf(stderr, "Failed to dynamically allocate memory.\n");
    return NULL;
  }

  for (i = 0; i < col; i++)
  {
    vec[i] = 0.0;
  }

  for (i = 0; i < row; i++)
  {
    for (j = 0; j < col; j++)
    {
      vec[i] += matrix[i][j] * vector[j];
    }
  }

  return vec;
}

/*
vecInnerProduct(double *vec1, double *vec2, int n)
  ベクトルの内積
    戻り値
      内積

    パラメータ
      入力
        *vec1: ベクトル1
        *vec2: ベクトル2
        n: ベクトルの要素数
*/
double vecInnerProduct(double *vec1, double *vec2, int n)
{
  int i;
  double ans;

  ans = 0.0;
  for (i = 0; i < n; i++)
  {
    ans += vec1[i] * vec2[i];
  }

  return ans;
}

/*
double vabs(double *vector)
  ベクトルの大きさ
    戻り値
      ベクトルの大きさ

    パラメータ
      入力
        *vector: ベクトル
        n: ベクトルの要素数
*/
double vabs(double *vector, int n)
{
  int i;
  double a;

  a = 0;
  for (i = 0; i < n; i++)
  {
    a += vector[i] * vector[i];
  }
  a = sqrt(a);

  return a;
}