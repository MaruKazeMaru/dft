# dft
書きかけです。
## 概要
離散フーリエ変換（以下 DFT）のレポート課題用に作成したリポジトリです。<br>
WAV形式の音源を読み込みPNG形式の時系列波形、スペクトル、スペクトログラムを出力します。<br>
プログラム言語はWAV入力、PNG出力、DFTがc++でグラフの装飾がPythonです。<br>
課題のために作成したものであり汎用性はありません。

## 依存
### c++
* zlib
* libpng
### Python
* Matplotlib

## 使い方
### ビルド
```
make
```

### 時系列波形の出力
```
build/bin/create_time_graph
```
とした後、標準入力で
```
<WAVファイルのパス>
<出力ファイルをしまうディレクトリ>
```
<出力ファイルをしまうディレクトリ>以下に時系列波形の```time_graph_0.png```というファイルと、その軸の情報が記載された```time_graph_info_0.png```というファイルが作成されます。

### スペクトルの出力
```
build/bin/create_spec_graph
```
とした後、標準入力で
```
<WAVファイルのパス>
<出力ファイルをしまうディレクトリ>
<窓長[s]>
<窓の開始時点[s]>
```
<出力ファイルをしまうディレクトリ>以下にスペクトルの```spec_graph_0.png```というファイルと、その軸の情報が記載された```spec_graph_info_0.png```というファイルが作成されます。

### スペクトログラムの出力
```
build/bin/create_spectrogram
```
とした後、標準入力で
```
<WAVファイルのパス>
<出力ファイルをしまうディレクトリ>
<窓長[s]>
```
<出力ファイルをしまうディレクトリ>以下にスペクトログラムの```spectrogram_0.png```というファイルと、その軸の情報が記載された```spectrogram_info_0.png```というファイルが作成されます。

### グラフの装飾
上3つのプログラムを動かした段階ではまだ目盛りもラベルもないグラフなのでPythonのプログラムで装飾します。
```python3
python3 arrange_graph.py <軸情報ファイルのパス> <出力ファイルのパス>
```

## ライセンス
MITライセンスです。<br>
[LICENSE](./LICENSE)をお読みください。

## 参考
### c++関連
* だえうホームページ 【C言語】libpngのインストールと使用方法・使用例
 https://daeudaeu.com/libpng/
### DFT関連
* wikipedia 離散フーリエ変換 https://ja.wikipedia.org/wiki/%E9%9B%A2%E6%95%A3%E3%83%95%E3%83%BC%E3%83%AA%E3%82%A8%E5%A4%89%E6%8F%9B
* wikipedia 高速フーリエ変換 https://ja.wikipedia.org/wiki/%E9%AB%98%E9%80%9F%E3%83%95%E3%83%BC%E3%83%AA%E3%82%A8%E5%A4%89%E6%8F%9B
* 工業大学生ももやまのうさぎ塾 うさぎでもわかる信号処理・制御工学　第14羽　高速フーリエ変換(FFT) https://www.momoyama-usagi.com/entry/math-seigyo14
### 音声関連
* 小野測器 音とそのセンサについて https://www.onosokki.co.jp/HP-WK/c_support/newreport/sound/soundsensor_1.htm