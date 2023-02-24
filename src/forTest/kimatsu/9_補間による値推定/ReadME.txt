＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
　補間による値推定　ReadMe
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

はじめに
・このプログラムはニュートン補間を用いた値推定のプログラムです。
・同梱されたプログラム等を用いて発生したいかなる問題も自己責任の上でご利用ください。

[関連ファイル]
・enshu.csv             :講義資料内で使われている点データ
・k9-input.csv          :確認用点データ
・interpolation.c(.h)   :補間処理用関数群
・NAbasic.c(.h)         :数値解析用基本関数群
・NAplus.c(.h)          :数値解析用追加関数群
・week9.c               :補間による値推定プログラム

[コンパイル方法]
・week9.c，interpolation.c，NAbasic.c，NAplus.cをまとめてコンパイルしてください。

Embarcadero C++ 7.30 for Win32の場合
> bcc32c ./week9.c ./interpolation.c ./NAbasic.c ./NAplus.c

[実行方法]
・生成された実行ファイルを以下の形式で実行してください。
> (実行ファイル) （点データファイル）（xの値）

例）
> ./week9.exe k9-input.csv 2.0

[出力内容]
・入力された点データを上から1つずつ用いて値推定を行います。4点の値を入力した場合，1-4点による補間の結果を順に表示します。

[開発環境]
OS          :Microsoft Windows 11 Home
OS ver.     :10.0.22621 build 22621
Processor   :AMD Ryzen 3 5300U