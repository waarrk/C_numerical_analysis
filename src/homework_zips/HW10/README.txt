# zip���t�@�C���\�� -------------------------------------
 - NAbasic.h ... CSV�ǂݎ��p�w�b�_�t�@�C�� 
 - NAbasic.c ... CSV�ǂݎ��p�w�b�_�t�@�C��
 - memory_controller.h ... �������Ǘ��p�w�b�_�t�@�C�� 
 - memory_controller.c ... �������Ǘ��p�w�b�_�t�@�C��  
 - trapezoid_formula.c ... 
 - README.txt ... ���̃t�@�C��

# ���� -------------------------------------
�S�Ẵt�@�C���͎w���ɏ]��Shift-JS�ɂ���ăG���R�[�h���Ă��܂��D
UTF-8���f�t�H���g�ݒ�̃G�f�B�^�Ŋm�F����ꍇ�͊e���ݒ���������Ă��������D

# �z����s�� -------------------------------------
Embarcadero C++ 7.30 for Win32 & Turbo Incremental Link 6.9�ɂăR���p�C����
Windows11(64-bit)���ɂē���m�F�ς�

# �z����̓t�@�C�� -------------------------------------
## memory_controller.exe
1�s1��ڂɕ�����
1�s2,3��ڂɐϕ���Ԃ�����CSV�t�@�C��

# �R���p�C���E���s���@ -------------------------------------
bcc32c�iEmbarcadero C++�j���g�p����ꍇ.
�R���p�C����̊e���s�t�@�C���̓R�}���h���C�������ɂĊ��ϐ���n���܂��D
�R�}���h���C�������Ԃ͔��p�X�y�[�X���󂯂Ă�������.
�ȉ��ɗ�������܂��D

## decimal2bin.exe�i�������F�R�}���h�C�������F����CSV�t�@�C���̑��΃p�X�j
bcc32c trapezoid_formula.c memory_controller.c NAbasic.c -o trapezoid_formula.exe
trapezoid_formula.exe k10-input.csv

# �z��o�� -------------------------------------
-- Info -- 
�͈̓t�@�C����: k10-input.csv
����������: [4]
�ϕ��͈͓���: [1, 3]
-- OUTPUT --
�ϕ����� [8.75]
-- EXIT --