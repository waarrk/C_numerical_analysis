#include <math.h>
#include <stdio.h>

/* e^x = 1/x */

#define EQU(x) (exp(x) - (1 / x))       /* 対象の関数 EQU(x)=0 */
#define DIF(x) (exp(x) + (1 / (x * x))) /* 対象の関数の微分 DIF(x)=0 */
#define ERR 0.00001                     /* 終了判定用規定値 */

int main() {
  double x;
  double z;

  x = 1; /* 初期値(上) */
  z = EQU(x);

  while (fabs(z) > ERR) {
    x -= z / DIF(x);
    z = EQU(x);
  }

  printf("is: %f", x);

  return 0;
}