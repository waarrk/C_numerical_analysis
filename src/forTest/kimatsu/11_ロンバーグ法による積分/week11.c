/*
�����o�[�O�@�ɂ��ϕ�
*/

#include "romberg.h"
#include "NAbasic.h"

int main(int argc, char *argv[])
{
    int row, col;
    double result, **range;
    FILE *fp;

    /* �R�}���h���C�������̃`�F�b�N */
    if (argc != 3)
    {
        fprintf(stderr, "Usage :  %s Integral_range divisions\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* �t�@�C���̓��� */
    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Could not open file\n");
        return EXIT_FAILURE;
    }

    /* �ϕ��͈͂̓ǂݍ��� */
    range = csvRead(&row, &col, fp);
    fclose(fp);

    /* ���̓f�[�^�̃`�F�b�N */
    if ((row != 1) || (col != 2))
    {
        fprintf(stderr, "There is an error in the input data.\n");
        freeMatrix(range);
        return EXIT_FAILURE;
    }

    /* �ϕ� */
    result = romberg(range[0][0], range[0][1], atoi(argv[2]));

    freeMatrix(range);

    return EXIT_SUCCESS;
}
