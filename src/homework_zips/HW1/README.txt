# zip���t�@�C���\�� -------------------------------------
 - NAbasic.h ... CSV�ǂݎ��p�w�b�_�t�@�C�� 
 - NAbasic.c ... CSV�ǂݎ��p�w�b�_�t�@�C�� 
 - decimal2bin.c ... 
 - matrixproduct.c ...
 - README.txt ... ���̃t�@�C��

# ���� -------------------------------------
�S�Ẵt�@�C���͎w���ɏ]��Shift-JS�ɂ���ăG���R�[�h���Ă��܂��D
UTF-8���f�t�H���g�ݒ�̃G�f�B�^�Ŋm�F����ꍇ�͊e���ݒ���������Ă��������D

# �z����s�� -------------------------------------
Embarcadero C++ 7.30 for Win32 & Turbo Incremental Link 6.9�ɂăR���p�C����
Windows11(64-bit)���ɂē���m�F�ς�

# �z����̓t�@�C�� -------------------------------------
## decimal2bin.exe
1�s1��ڂɂЂƂ��������l���i�[���ꂽCSV�g���q�̃t�@�C���D

## matrixproduct.exe
�J���}��؂�Ŋe�s�C�e��̃f�[�^�������݂��C����CSV�g���q�̃t�@�C���D�s��A�ƍs��B��2�D

# �G���[�n���h�����O�E�Ɛӎ��� -------------------------------------
## decimal2bin.exe
��̃t�@�C�����n���ꂽ�ꍇ�C�uERR: matrix[0][0] �� NULL �ł��D�v�̕\����G���[�ŏI���D
�����v�f�����݂���CSV��n�����ꍇ�C1�s1��ڂ݂̂�ϊ�������I���D
�����_�ȉ���5���𒴂����ꍇ�C4���Ɏl�̌ܓ�����v�Z���s�D
�����ł͂Ȃ�������n�����Ƃ��C0�Ƃ��ĔF�����ꐳ��I���D

## matrixproduct.exe
��̃t�@�C�����n���ꂽ�ꍇ�C��s��Ƃ��Ĉ���ꐳ��I���D
�����_�ȉ���5���𒴂����ꍇ�C4���Ɏl�̌ܓ�����v�Z���s�D
�����ł͂Ȃ��������s��Ɋ܂܂�Ă����ꍇ�C0�Ƃ��ĔF�����ꐳ��I���D

# �R���p�C���E���s���@ -------------------------------------
bcc32c�iEmbarcadero C++�j���g�p����ꍇ.
�R���p�C����̊e���s�t�@�C���̓R�}���h���C�������ɂĊ��ϐ���n���܂��D
�R�}���h���C�������Ԃ͔��p�X�y�[�X���󂯂Ă�������.
�ȉ��ɗ�������܂��D

## decimal2bin.exe�i�������F�R�}���h�C�������F����CSV�t�@�C���̑��΃p�X�j
bcc32c decimal2bin.c NAbasic.c -o decimal2bin.exe
./decimal2bin.exe data/k1-input.csv

## matrixproduct.exe �i�������F�R�}���h�C�������F�s��A�̓���CSV�t�@�C���̑��΃p�X�C��O�����F�s��B�̓���CSV�t�@�C���̑��΃p�X�j
bcc32c matrixproduct.c NAbasic.c -o matrixproduct.exe 
./matrixproduct.exe data/k2-input1.csv data/k2-input2.csv

# �z��o�� -------------------------------------
## decimal2bin.exe
-- Info -- 
�t�@�C����: data/k1-input.csv
�����l: 53.375
-- OutPut -- 
sEEEEEEE EEEEdddd dddddddd... 
01000000 01001010 10110000 00000000 00000000 00000000 00000000 00000000

## matrixproduct.exe
-- Info -- 
A�s��t�@�C����: data/k2-input1.csv
B�s��t�@�C����: data/k2-input2.csv
matrixA: 
2.0000  8.0000  4.0000
3.0000  2.0000  -1.0000
7.0000  -1.0000         3.0000
matrixB:
3.0000
7.0000
-2.0000
--OutPut--
matrixOut:
54.0000
25.0000
8.0000

# ���r���[�ϓ_ -------------------------------------
 -  typo �͂Ȃ����H
 -  �����K���Ƀo�����͂Ȃ����H�����ł�����̂ɂȂ��Ă��邩�H
 -  �������̊m�ہE�����K�؂ɍs���Ă��邩�H
 -  �������璷�łȂ����H
 -  �������̂��ߊ�������\���̋@�\�͂Ȃ����H
 -  �ۑ�����̂��߂ɃR�[�h�̐݌v���K�؂��H
 