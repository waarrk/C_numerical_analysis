=========================================
|                                       |
| 課題1．実数値の2進数（IEEE754形式）変換     |
|                                       |
=========================================

1．ファイル
  ・readme.txt	: このファイル
  ・kadai.c		: mainソースファイル
  ・NAbasic.c		: 行列データ処理関数のソースファイル 
  ・NAbasic.h		: NAbasic用ヘッダファイル
  ・k1-input.csv	: 入力データCSVファイル

2．処理内容
入力ファイルより実数値を読み取り，IEEE754形式の2進数で出力します．

3．コンパイル方法
"kadai.c"と"NAbasic.c"をコンパイルする．
例）Embarcadero C++ Compiler
  > bcc32c kadai.c NAbasic.c

4．実行方法
コンパイルによって生成された実行ファイルに引数として入力CSVファイルを渡して実行する．
例）実行ファイル：kadai.exe，入力ファイル："k1-input.csv"の場合
  > kadai.exe k1-input.csv

5．入力ファイル
ファイル形式：CSV
内容：実数