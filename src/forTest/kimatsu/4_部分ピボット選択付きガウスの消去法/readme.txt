課題4．部分ピボット選択付きガウスの消去法

1．ファイル
  readme.txt	: このファイル
  gauss.c		: mainソースファイル
  NAbasic.c		: 行列データ処理関数のソースファイル 
  NAbasic.h		: NAbasic用ヘッダファイル
  k4-input1.csv	: 入力データCSVファイル(3x3)
  k4-input2.csv	: 入力データCSVファイル(3x1)

2．処理内容
入力ファイルから2つの行列を読み取り，部分ピボット選択付きガウスの消去法を用いて連立方程式を解く．

例）
入力ファイル1：行列A
入力ファイル2：行列y
解：行列x

Ax=y

3．コンパイル方法
"gauss.c"と"NAbasic.c"をコンパイルする．
例）Embarcadero C++ Compiler
  > bcc32c gauss.c NAbasic.c

4．実行方法
コンパイルによって生成された実行ファイルに引数として入力CSVファイルを渡して実行する．
例）実行ファイル：gauss.exe，入力ファイル1："k4-input1.csv"，入力ファイル2："k4-input2.csv"の場合
  > gauss.exe k4-input1.csv k4-input2.csv

5．入力ファイル
ファイル形式：CSV
内容：実数行列