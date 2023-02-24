/* 
�ۑ�1.
  ������IEEE754�`����2�i���ɕϊ�����v���O����
  double�^��64bit��IEEE754�`���Ŋi�[����Ă��邱�Ƃ𗘗p����
*/
#include <stdio.h>
#include <stdlib.h>
#include "NAbasic.h"

int main(int argc, char *argv[]) {
    FILE *fin;
    double **matrix;
    int row, col;

    char c[sizeof(double)];
    int i, j, k;

    /* �R�}���h���C�������̊m�F */
    if (argc != 2) {
        fprintf(stderr, "�R�}���h���C���������Ԉ���Ă��܂��D<*.exe> <input_file>\n");
		return EXIT_FAILURE;
    }

    /* CSV�t�@�C���̓ǂݍ��� */
    if ((fin = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "\"%s\"���J���܂���ł���.\n", argv[1]);
		return EXIT_FAILURE;
	}

    /* CSV�t�@�C������s��f�[�^�i�����l�j�̓ǂݍ��� */
    matrix = csvRead(&row, &col, fin);

    /* �s��f�[�^�i�����l�j�𕶎���Ƀ������̃R�s�[ */
    memcpy(c, &matrix[0][0], sizeof(double));

    /* IEEE754�`���̊T�� */
    printf("sEEEEEEE EEEEdddd dddddddd... \n");

    /* �\���ϊ� */
    for (i = sizeof(double) - 1; i >= 0; i--) { /* double�^(64bit)1���̏��� */
        for (j = sizeof(c[i]) * 8 - 1; j >= 0; j--) { /* char�^(8bit)1���̏��� */
            k = c[i] & (1 << j);
            printf("%d", k ? 1 : 0);
        }
        printf(" ");
    }
    printf("\n");

    /* �������̊J�� */
    freeMatrix(matrix);

    return 0;
}