# zip内ファイル構成 -------------------------------------
 - NAbasic.h ... CSV読み取り用ヘッダファイル 
 - NAbasic.c ... CSV読み取り用ヘッダファイル
 - memory_controller.h ... メモリ管理用ヘッダファイル 
 - memory_controller.c ... メモリ管理用ヘッダファイル  
 - trapezoid_formula.c ... 
 - README.txt ... このファイル

# 注意 -------------------------------------
全てのファイルは指示に従いShift-JSによってエンコードしています．
UTF-8がデフォルト設定のエディタで確認する場合は各自設定を見直してください．

# 想定実行環境 -------------------------------------
Embarcadero C++ 7.30 for Win32 & Turbo Incremental Link 6.9にてコンパイル後
Windows11(64-bit)環境にて動作確認済み

# 想定入力ファイル -------------------------------------
## memory_controller.exe
1行1列目に分割数
1行2,3列目に積分区間をもつCSVファイル

# コンパイル・実行方法 -------------------------------------
bcc32c（Embarcadero C++）を使用する場合.
コンパイル後の各実行ファイルはコマンドライン引数にて環境変数を渡します．
コマンドライン引数間は半角スペースを空けてください.
以下に例を示します．

## decimal2bin.exe（第一引数：コマンド，第二引数：入力CSVファイルの相対パス）
bcc32c trapezoid_formula.c memory_controller.c NAbasic.c -o trapezoid_formula.exe
trapezoid_formula.exe k10-input.csv

# 想定出力 -------------------------------------
-- Info -- 
範囲ファイル名: k10-input.csv
分割数入力: [4]
積分範囲入力: [1, 3]
-- OUTPUT --
積分結果 [8.75]
-- EXIT --