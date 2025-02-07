# ビルドする時に必要なもの

https://dxlib.xsrv.jp/dxinfo.html

こちらのライブラリで指定されているVisual Studioの環境であれば実行できるはずです

# このテンプレートができること

現状をリストで置いておきます
(ソースコードとのリンクは...いつかやります)

```
- シーン分け
  - シーンとして扱えるオブジェクトの型をテンプレート引数に渡して変更できる
- jsonファイルによるコンフィグ生成&編集
  - Storage::Data<filepath> // これをusingで短くするとものすごく扱いやすい
    - 指定されたオブジェクトが見つからなければ構築する
    - すでに書き出されたjsonファイルがあればそこから読み取る
    - デストラクタが呼ばれたらjsonファイルとして書き出し
  - Storage::Data<filepath>::Value<T, jsonpath>
    - staticメンバ変数で値を管理しているので、複数個同じjsonpathで宣言しても全て1つの値を指す
    - コンストラクタが呼ばれるとjsonから自身が持っている値に書き込む
    - デストラクタが呼ばれると自身が持っている値をjsonに書き込む
- DxLibのラップ
  - 構造体 (足りない機能があるかも？) // jsonとの相互変換可能
    - Val2D<T>
    - Val3D<T> (Wip)
    - Rect2D<T>
    - Rect3D<T> // 矩形???
    - Color3
    - Color4
    - Color4F
  - メディア (全体的にまだテコ入れが必要)
    - GraphData (Wip)
    - SoundData (Wip)
    - ScreenData (Wip)
    - FontData (未対応)
    - ModelData (未対応)
  - 入力
    - InputState // wtfなUpdate()関数がある
    - InputDevices::Keyboard // WM_KEYDOWN & WM_KEYUP式
    - inputDevices::Mouse // マウス座標の取得
  - 図形 (今のところ頂点データから作る方法が一番楽)
    - Square (Wip)
    - Triangle (Wip)
    - Vertex2D
    - IndexedVertex2D (Wip)
    - Vertex::Factory2D (Wip)
  - ヘルパー // ヘルパーと言っていいのだろうか...
    - DXHandle<DXHandleType> // メディア系のベース
  - システム (設計的な難あり...？)
    - SoundDevice // COMからいろんな道を渡りSimpleAudioVolumeを取得している
    - DXSystem (いろんな機能をここにいれると冗長になる...)
    - Timer // std::chronoによる時間計測
    - Window (None struct)

```
