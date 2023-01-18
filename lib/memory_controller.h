#ifndef MEMORY_CONTROLLER_H
#define MEMORY_CONTROLLER_H

#include <stdio.h>
#include <stdlib.h>

#include "NAbasic.h"

/* 動的確保分の構造体 */
typedef struct {
  char *name;
  char *argv;
  FILE *file;
  double **matrix;
  int row;
  int col;
} dynamicMemory;

/* 関数プロトタイプ */
int fileReader(dynamicMemory *data);
int allAllocatedMemoryFree(dynamicMemory *data);

#endif