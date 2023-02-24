#include <math.h>
#include <stdio.h>

/* e^x = 1/x */

#define EQU(x) (exp(x) - (1 / x))       /* �Ώۂ̊֐� EQU(x)=0 */
#define DIF(x) (exp(x) + (1 / (x * x))) /* �Ώۂ̊֐��̔��� DIF(x)=0 */
#define ERR 0.00001                     /* �I������p�K��l */

int main() {
  double x;
  double z;

  x = 1; /* �����l(��) */
  z = EQU(x);

  while (fabs(z) > ERR) {
    x -= z / DIF(x);
    z = EQU(x);
  }

  printf("is: %f", x);

  return 0;
}