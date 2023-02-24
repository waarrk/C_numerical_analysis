#include <stdio.h>

#define EXTRA_BUF 30

typedef union {
  double d;
  unsigned char c[sizeof(double) + 1];
} Converter;

int main(void) {
  int i, j, n;
  char buf[sizeof(double) * 8 + 1 + EXTRA_BUF];
  Converter cvr;

  /* ����(2�i��) */
  printf("input: ");
  fgets(buf, sizeof(buf), stdin);

  /* 2�i�� -> 10�i���@�ϊ� */
  for (i = 0, n = 0; i < 8; i++) {
    cvr.c[7 - i] = 0;
    for (j = 0; j < sizeof(double); j++, n++) {
      if ((buf[n] == '0') || (buf[n] == '1'))
        cvr.c[7 - i] += (buf[n] - '0') << (sizeof(double) - 1 - j);
      else
        j--;
    }
  }

  /* �o��(10�i��) */
  printf("result: %f\n", cvr.d);

  return 0;
}