# zip���t�@�C���\�� -------------------------------------
 - data/ ... �T���v���f�[�^�t�@�C��
 - NAbasic.h ... CSV�ǂݎ��p�w�b�_�t�@�C�� 
 - NAbasic.c ... CSV�ǂݎ��p�w�b�_�t�@�C�� 
 - memory_controller.h ... �������Ǘ��p�w�b�_�t�@�C�� 
 - memory_controller.c ... �������Ǘ��p�w�b�_�t�@�C�� 
 - nonlinearequation ... �{��
 - README.txt ... ���̃t�@�C��

# ���� -------------------------------------
�S�Ẵt�@�C���͎w���ɏ]��Shift-JS�ɂ���ăG���R�[�h���Ă��܂��D
UTF-8���f�t�H���g�ݒ�̃G�f�B�^�Ŋm�F����ꍇ�͊e���ݒ���������Ă��������D

# �z����s�� -------------------------------------
Embarcadero C++ 7.30 for Win32 & Turbo Incremental Link 6.9�ɂăR���p�C����
Windows11(64-bit)���ɂē���m�F�ς�

# �z����̓t�@�C�� -------------------------------------
## nonlinearequation.exe
### �֐�����csv
1�s�ڂɊe���̌W���C2�s�ڂɂ��̎������L������csv�t�@�C���Ƃ��܂��D
�e�s�̗v�f���͂��낦�Ă��������D

��jy = x^4 -3x^2 + 5x -9
default.csv
--
1, -3, 5, -9
4, 2, 1, 0

### ��ԓ���csv
1�s1��ڂɍ���ԁC1�s2��ڂɉE��Ԃ̐��l���L������csv�Ƃ��܂��D
��j[1, 3]
k3-input.csv
--
1, 3

# �G���[�n���h�����O�E�Ɛӎ��� -------------------------------------
## decimal2bin.exe
��̃t�@�C�����n���ꂽ�ꍇ�C�֐��̏ꍇ0�ő��s�C��Ԃ̏ꍇ�uERR: ���CSV�f�[�^ �� �ُ� �ł��D�v�̕\����G���[�ŏI���D
�����_�ȉ���7���𒴂����ꍇ�C6���Ɏl�̌ܓ�����v�Z���s�D
�����ł͂Ȃ�������n�����Ƃ��C0�Ƃ��ĔF�����ꐳ��I���D
��̃t�@�C�����n���ꂽ�ꍇ�C��s��Ƃ��Ĉ���ꐳ��I���D
�����ł͂Ȃ��������s��Ɋ܂܂�Ă����ꍇ�C0�Ƃ��ĔF�����ꐳ��I���D

# �R���p�C���E���s���@ -------------------------------------
bcc32c�iEmbarcadero C++�j���g�p����ꍇ.
�R���p�C����̊e���s�t�@�C���̓R�}���h���C�������ɂĊ��ϐ���n���܂��D
�R�}���h���C�������Ԃ͔��p�X�y�[�X���󂯂Ă�������.
�ȉ��ɗ�������܂��D

## decimal2bin.exe�i�������F�R�}���h�C�������F����CSV�t�@�C���̑��΃p�X�j
bcc32c nonlinearequation.c lib/NAbasic.c lib/memory_controller.c -o nonlinearequation.ex
./nonlinearequation.exe data/default.csv data/k3-input.csv

# �z��o�� -------------------------------------
## nonlinearequation.exe
-- Info -- 
�֐��t�@�C����: data/default.csv
��ԃt�@�C����: data/k3-input.csv
�֐�: y = +1x^4-3x^2+5x^1-9x^0
��ԓ���: [1, 3]
-- OutPut --
�񕪒T������...
att: 10, left: 1.000000, right: 2.000000, mid: 2.000000
att: 9, left: 1.500000, right: 2.000000, mid: 1.500000
att: 8, left: 1.750000, right: 2.000000, mid: 1.750000
att: 7, left: 1.750000, right: 1.875000, mid: 1.875000
att: 6, left: 1.750000, right: 1.812500, mid: 1.812500
att: 5, left: 1.750000, right: 1.781250, mid: 1.781250
att: 4, left: 1.750000, right: 1.765625, mid: 1.765625
att: 3, left: 1.750000, right: 1.757812, mid: 1.757812
att: 2, left: 1.750000, right: 1.753906, mid: 1.753906
att: 1, left: 1.751953, right: 1.753906, result: 1.751953
�j���[�g���@�T������...
att: 10, result: 1.800000
att: 9, result: 1.755637
att: 8, result: 1.753667
att: 7, result: 1.753664
att: 6, result: 1.753664
att: 5, result: 1.753664
att: 4, result: 1.753664
att: 3, result: 1.753664
att: 2, result: 1.753664
att: 1, result: 1.753664
-- EXIT --


# ���r���[�ϓ_ -------------------------------------
 -  typo �͂Ȃ����H
 -  �����K���Ƀo�����͂Ȃ����H�����ł�����̂ɂȂ��Ă��邩�H
 -  �������̊m�ہE�����K�؂ɍs���Ă��邩�H
 -  �������璷�łȂ����H
 -  �������̂��ߊ�������\���̋@�\�͂Ȃ����H
 -  �ۑ�����̂��߂ɃR�[�h�̐݌v���K�؂��H
 