#include "matrix_calculation.h"

int matrixProduct(int left, int right, dynamicMemory *data, double **matrixOut,
                  int *rowOut, int *colOut) {
  /* 行列の要素計算用変数 */
  int element;
  int i;

  /* matrixAとmatrixBから積matrixOutを計算*/
  for (*rowOut = 0; *rowOut < data[0].row; (*rowOut)++) {
    for (*colOut = 0; *colOut < data[1].col; (*colOut)++) {
      /* 行列要素の計算 */
      /* A1*b1 + A2*B2 ....*/
      element = 0;
      for (i = 0; i < data[1].row; i++) {
        element += data[0].matrix[*rowOut][i] * data[1].matrix[i][*colOut];
      }
      matrixOut[*rowOut][*colOut] = element;
    }
  }
  return EXIT_SUCCESS;
}

int innerProduct(int left, int right, dynamicMemory *data, double **matrixOut,
                 int *rowOut, int *colOut) {
  /* 行列の要素計算用変数 */
  int element;
  int i, j;

  double **trans = allocMatrix(data[0].row, data[0].col);

  for (i = 0; i < data[0].row; i++) {
    for (j = 0; j < data[0].col; j++) {
      trans[j][i] = data[0].matrix[i][j];
    }
  }

  /* matrixAとmatrixBから積matrixOutを計算*/
  for (*rowOut = 0; *rowOut < data[0].col; (*rowOut)++) {
    for (*colOut = 0; *colOut < data[1].col; (*colOut)++) {
      /* 行列要素の計算 */
      /* A1*b1 + A2*B2 ....*/
      element = 0;
      for (i = 0; i < data[1].row; i++) {
        element += trans[*rowOut][i] * data[1].matrix[i][*colOut];
      }
      matrixOut[*rowOut][*colOut] = element;
    }
  }
  return EXIT_SUCCESS;
}

double pivotSearch(int k, dynamicMemory *data) {
  double max = 0;
  int max_row = 0;

  /*最大絶対値を探索*/
  for (int i = k; i < data[0].col; i++) {
    if (data[0].matrix[i][k] > max) {
      max = data[0].matrix[i][k];
      max_row = i;
    }
  }
  if (max == 0) {
    exit(0);
  }
  return max_row;
}

int swapRows(int k, int p, dynamicMemory *data) {
  double tmp;
  tmp = data[1].matrix[k][0];
  data[1].matrix[k][0] = data[1].matrix[p][0];
  data[1].matrix[p][0] = tmp;
  for (int i = 0; i < data[0].col; i++) {
    tmp = data[0].matrix[k][i];
    data[0].matrix[k][i] = data[0].matrix[p][i];
    data[0].matrix[p][i] = tmp;
  }
  return EXIT_SUCCESS;
}

int dashRows(int selected, int target, dynamicMemory *data) {
  double tmp;
  double r =
      data[0].matrix[target][selected] / data[0].matrix[selected][selected];
  for (int i = 0; i < data[0].col; i++) {
    tmp = data[0].matrix[target][i];
    data[0].matrix[target][i] =
        data[0].matrix[target][i] - r * data[0].matrix[selected][i];
  }
  data[1].matrix[target][0] =
      data[1].matrix[target][0] - r * data[1].matrix[selected][0];
  return EXIT_SUCCESS;
}

int triangulation(dynamicMemory *data) {
  double pivot = 0;
  for (int i = 0; i < data[0].col; i++) {
    pivot = pivotSearch(i, data);
    swapRows(i, pivot, data);
    for (int j = i + 1; j < data[0].col; j++) {
      dashRows(i, j, data);
    }
  }
  return EXIT_SUCCESS;
}

int backSubstitution(dynamicMemory *data, double *x) {
  double tmp = 0;
  /*行*/
  for (int i = data[0].col - 1; i >= 0; i--) {
    tmp = 0;
    /*列*/
    for (int j = i + 1; j < data[0].col; j++) {
      tmp += data[0].matrix[i][j] * x[j];
    }
    x[i] = (data[1].matrix[i][0] - tmp) / data[0].matrix[i][i];
  }
  return EXIT_SUCCESS;
}

int sortMatrix(double **matrix, double **matrixP, int row, int col) {
  for (int i = 0; i < row - 1; i++) {
    /* 最大絶対値探索 */
    int max = 0;
    int maxRow = 0;
    for (int j = i; j < row; j++) {
      if (fabs(matrix[j][i]) > max) {
        max = fabs(matrix[j][i]);
        maxRow = j;
      }
    }

    /* 最大絶対値順に行を入れ替え */
    double tmp;
    double tmpP;
    for (int j = 0; j < col; j++) {
      tmp = matrix[i][j];
      matrix[i][j] = matrix[maxRow][j];
      matrix[maxRow][j] = tmp;
    }
    for (int j = 0; j < col; j++) {
      tmpP = matrixP[i][j];
      matrixP[i][j] = matrixP[maxRow][j];
      matrixP[maxRow][j] = tmpP;
    }
  }
  return EXIT_SUCCESS;
}

int LUdecomposition(dynamicMemory *data) {
  double **L = allocMatrix(data[0].row, data[0].col);
  double **U = allocMatrix(data[0].row, data[0].col);
  double **P = allocMatrix(data[0].row, data[0].col);

  double *x, *y, *Pb;

  double **A = allocMatrix(data[0].row, data[0].col);
  double **vec = allocMatrix(data[1].row, data[1].col);

  /* 行列のコピー */
  for (int i = 0; i < data[0].row; i++) {
    for (int j = 0; j < data[0].col; j++) {
      A[i][j] = data[0].matrix[i][j];
    }
  }

  for (int i = 0; i < data[1].row; i++) {
    for (int j = 0; j < data[1].col; j++) {
      vec[i][j] = data[1].matrix[i][j];
    }
  }

  /* Pを単位行列に初期化 */
  for (int i = 0; i < data[0].row; i++) {
    for (int j = 0; j < data[0].col; j++) {
      if (i == j) {
        P[i][j] = 1;
      } else {
        P[i][j] = 0;
      }
    }
  }

  /* AとPをあわせて最大絶対値順に行を並び替え */
  sortMatrix(A, P, data[0].row, data[0].col);

  /* 前進消去 */
  for (int i = 0; i < data[0].col; i++) {
    /* Lの対角成分を1に */
    L[i][i] = 1;
    /* Uの対角成分をAの対角成分に */
    U[i][i] = A[i][i];
    /* Uの対角成分以外の成分をAの対角成分以外の成分に */
    for (int j = i + 1; j < data[0].col; j++) {
      U[i][j] = A[i][j];
    }
    /* Lの対角成分以外の成分をAの対角成分以外の成分に */
    for (int j = i + 1; j < data[0].col; j++) {
      L[j][i] = A[j][i] / U[i][i];
    }
    /* Aの対角成分以外の成分を0に */
    for (int j = i + 1; j < data[0].col; j++) {
      A[j][i] = 0;
    }
    /* Aの対角成分以外の成分をUの対角成分以外の成分とLの対角成分以外の成分の積に
     */
    for (int j = i + 1; j < data[0].col; j++) {
      for (int k = i + 1; k < data[0].col; k++) {
        A[j][k] = A[j][k] - L[j][i] * U[i][k];
      }
    }
  }

  int side = data[0].row;

  /* P*bの計算 */
  Pb = (double *)malloc(sizeof(double) * side);

  for (int i = 0; i < side; i++) {
    Pb[i] = 0.0;
    for (int j = 0; j < side; j++) {
      Pb[i] += P[i][j] * vec[j][0];
    }
  }

  y = (double *)malloc(sizeof(double) * side);

  for (int i = 0; i < side; i++) {
    y[i] = Pb[i];
    for (int j = 0; j < i; j++) {
      y[i] -= L[i][j] * y[j];
    }
    y[i] /= L[i][i];
  }
  freeVector(Pb);
  freeMatrix(L);

  x = (double *)malloc(sizeof(double) * side);

  for (int i = side - 1; i >= 0; i--) {
    x[i] = y[i];
    for (int j = side - 1; j > i; j--) {
      x[i] -= U[i][j] * x[j];
    }
    x[i] /= U[i][i];
  }

  printf("A = \n");
  showMatrix((const double **)A, data[0].row, data[0].col);

  printf("L = \n");
  showMatrix((const double **)L, data[0].row, data[0].col);
  printf("U = \n");
  showMatrix((const double **)U, data[0].row, data[0].col);
  printf("P = \n");
  showMatrix((const double **)P, data[0].row, data[0].col);

  for (int i = 0; i < side; i++) {
    printf("x%d: %f\n", i + 1, x[i]);
  }

  freeMatrix(A);
  freeMatrix(L);
  freeMatrix(U);
  freeMatrix(P);
  freeVector(x);
  freeVector(y);

  return EXIT_SUCCESS;
}

int jacobiMethod(dynamicMemory *data, int attempt) {
  double **A = allocMatrix(data[0].row, data[0].col);
  double **vec = allocMatrix(data[1].row, data[1].col);

  /* 行列のコピー */
  for (int i = 0; i < data[0].row; i++) {
    for (int j = 0; j < data[0].col; j++) {
      A[i][j] = data[0].matrix[i][j];
    }
  }

  for (int i = 0; i < data[1].row; i++) {
    for (int j = 0; j < data[1].col; j++) {
      vec[i][j] = data[1].matrix[i][j];
    }
  }

  double *x = (double *)malloc(sizeof(double) * data[0].row);
  double *y = (double *)malloc(sizeof(double) * data[0].row);

  for (int i = 0; i < data[0].row; i++) {
    x[i] = 0;
  }

  double *tmp = (double *)malloc(sizeof(double) * data[0].row);

  for (int i = 0; i < attempt; i++) {
    for (int j = 0; j < data[0].row; j++) {
      tmp[j] = vec[j][0];
      for (int k = 0; k < data[0].col; k++) {
        if (j != k) {
          tmp[j] -= A[j][k] * x[k];
        }
      }
      tmp[j] /= A[j][j];
    }
    for (int j = 0; j < data[0].row; j++) {
      x[j] = tmp[j];
    }
  }

  for (int i = 0; i < data[0].row; i++) {
    printf("x%d: %f\n", i + 1, x[i]);
  }

  freeMatrix(A);
  freeMatrix(vec);
  freeVector(x);
  freeVector(y);
  freeVector(tmp);

  return EXIT_SUCCESS;
}

int gaussSeidelMethod(dynamicMemory *data, int attempt) {
  double **A = allocMatrix(data[0].row, data[0].col);
  double **vec = allocMatrix(data[1].row, data[1].col);

  /* 行列のコピー */
  for (int i = 0; i < data[0].row; i++) {
    for (int j = 0; j < data[0].col; j++) {
      A[i][j] = data[0].matrix[i][j];
    }
  }

  for (int i = 0; i < data[1].row; i++) {
    for (int j = 0; j < data[1].col; j++) {
      vec[i][j] = data[1].matrix[i][j];
    }
  }

  double *x = (double *)malloc(sizeof(double) * data[0].row);
  double *y = (double *)malloc(sizeof(double) * data[0].row);

  for (int i = 0; i < data[0].row; i++) {
    x[i] = 0;
  }

  double *tmp = (double *)malloc(sizeof(double) * data[0].row);

  for (int i = 0; i < attempt; i++) {
    for (int j = 0; j < data[0].row; j++) {
      tmp[j] = vec[j][0];
      for (int k = 0; k < data[0].col; k++) {
        if (j != k) {
          tmp[j] -= A[j][k] * x[k];
        }
      }
      tmp[j] /= A[j][j];
      x[j] = tmp[j];
    }
  }

  for (int i = 0; i < data[0].row; i++) {
    printf("x%d: %f\n", i + 1, x[i]);
  }

  freeMatrix(A);
  freeMatrix(vec);
  freeVector(x);
  freeVector(y);
  freeVector(tmp);

  return EXIT_SUCCESS;
}