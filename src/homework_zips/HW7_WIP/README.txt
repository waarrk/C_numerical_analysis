# zip内ファイル構成 -------------------------------------
 - NAbasic.h ... CSV読み取り用ヘッダファイル 
 - NAbasic.c ... CSV読み取り用ヘッダファイル 
 - power_itr.c ... 
 - README.txt ... このファイル

# 想定実行環境 -------------------------------------
Embarcadero C++ 7.30 for Win32 & Turbo Incremental Link 6.9にてコンパイル後
Windows11(64-bit)環境にて動作確認済み

# コンパイル・実行方法 -------------------------------------
bcc32c（Embarcadero C++）を使用する場合.
コンパイル後の各実行ファイルはコマンドライン引数にて環境変数を渡します．
コマンドライン引数間は半角スペースを空けてください.
以下に例を示します．

## power_itr.exe（第一引数：コマンド，第二引数：入力CSVファイルの相対パス）
bcc32c power_itr.c NAbasic.c -o power_itr.exe
./power_itr.exe k7-input.csv

# 想定出力 -------------------------------------
11.0000         7.0000  -5.0000 
0.0000  10.0000         -1.0000
2.0000  8.0000  3.0000
Largest eigenvalue: 9
Smallest eigenvalue: 7