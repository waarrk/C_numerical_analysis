#ifndef MEMORY_CONTROLLER_H
#define MEMORY_CONTROLLER_H

#include <stdio.h>
#include <stdlib.h>

#include "NAbasic.h"

/* ���I�m�ە��̍\���� */
typedef struct {
  char *name;
  char *argv;
  FILE *file;
  double **matrix;
  int row;
  int col;
} dynamicMemory;

/* �֐��v���g�^�C�v */
int fileReader(dynamicMemory *data);
int allAllocatedMemoryFree(dynamicMemory *data);

#endif