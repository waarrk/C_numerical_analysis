#include "memory_controller.h"

/* �t�@�C�����͊֐� */
int fileReader(dynamicMemory *data) {
  int i = 0;
  /* �\���̔z��̑S�v�f�ɑ΂��ēK�p */
  while (data[i].name != NULL) {
    if ((data[i].file = fopen(data[i].argv, "r")) == NULL) {
      fprintf(stderr, "ERR: �t�@�C���𐳏�ɓǂݍ��܂���ł����D%s\n",
              data[i].argv);
      return EXIT_FAILURE;
    }
    data[i].matrix = csvRead(&data[i].row, &data[i].col, data[i].file);
    fclose(data[i].file);
    i++;
  }
  return EXIT_SUCCESS;
}

/* ���I�������S�J�� */
int allAllocatedMemoryFree(dynamicMemory *data) {
  int i = 0;
  /* �\���̔z��̑S�v�f�ɑ΂��ēK�p */
  while (data[i].name != NULL) {
    freeMatrix(data[i].matrix);
    i++;
  }
  return EXIT_SUCCESS;
}