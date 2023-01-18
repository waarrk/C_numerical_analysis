#include "memory_controller.h"

/* ファイル入力関数 */
int fileReader(dynamicMemory *data) {
  int i = 0;
  /* 構造体配列の全要素に対して適用 */
  while (data[i].name != NULL) {
    if ((data[i].file = fopen(data[i].argv, "r")) == NULL) {
      fprintf(stderr, "ERR: ファイルを正常に読み込ませんでした．%s\n",
              data[i].argv);
      return EXIT_FAILURE;
    }
    data[i].matrix = csvRead(&data[i].row, &data[i].col, data[i].file);
    fclose(data[i].file);
    i++;
  }
  return EXIT_SUCCESS;
}

/* 動的メモリ全開放 */
int allAllocatedMemoryFree(dynamicMemory *data) {
  int i = 0;
  /* 構造体配列の全要素に対して適用 */
  while (data[i].name != NULL) {
    freeMatrix(data[i].matrix);
    i++;
  }
  return EXIT_SUCCESS;
}