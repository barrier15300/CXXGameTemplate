[Japanese／日本語]
# ビルドする時に必要なもの

https://dxlib.xsrv.jp/dxinfo.html

こちらのライブラリで指定されているVisual Studioの環境であれば実行できるはずです

# このテンプレートができること

現状をリストで置いておきます 
(ソースコードとのリンクは...いつかやります) 

丸括弧 -> 未完成または実装が怪しい

コメント -> シンプルにコメント

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
  - 入力 (少し設計的に難あり)
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

# TODO: 

```
- GUI制御
  - シークバー
  - ボタン
  - テキストボックス
  - コンボボックス
  - ラジオボタン
  - チェックボックス
```

[English／英語]
# Build Requirements

https://dxlib.xsrv.jp/dxinfo.html

You should be able to run it if you are in the Visual Studio environment specified in this library.

# What this template can do:

I'll leave a list of the current status.
(link to source code... well, i'll do it someday)

Round brackets -> Incomplete or questionable implementation

Comments -> Simple comments

```
- Scene Separation
  - Change the types of objects that can be handled as scenes by passing template arguments
- Configuration generation and editing by json file
  - Storage::Data<filepath> // Shorten this by using to make it very easy to handle
    - If the specified object is not found, build it.
    - If there is a json file already written out, read from it
    - If destructor is called, write out as json file
  - Storage::Data<filepath>::Value<T, jsonpath>
    - Because the value is managed by static member variables, even if multiple values are declared in the same jsonpath, they all point to a single value.
    - When the constructor is called, it writes from json to its own value.
    - When the destructor is called, it writes the value it has to json.
- Wrapping DxLib
  - structure (maybe some functionality is missing?) // Can be converted to/from json
    - Val2D<T>
    - Val3D<T> (Wip)
    - Rect2D<T>
    - Rect3D<T> // Rectangle?
    - Color3
    - Color4
    - Color4F
  - Media (still needs to be tweaked overall)
    - GraphData (Wip)
    - SoundData (Wip)
    - ScreenData (Wip)
    - FontData (Not yet supported)
    - ModelData (Not supported)
  - Input (a little difficult to design)
    - InputState // wtf update() function
    - InputDevices::Keyboard // WM_KEYDOWN & WM_KEYUP expressions
    - inputDevices::Mouse // get mouse coordinates
  - Shapes (the easiest way so far is to create them from vertex data)
    - Square (Wip)
    - Triangle (Wip)
    - Vertex2D
    - IndexedVertex2D (Wip)
    - Vertex::Factory2D (Wip)
  - Helper // I don't know if I'd call it a helper...
    - DXHandle<DXHandleType> // base for media system
  - system (design difficulties...?)
    - SoundDevice // getting SimpleAudioVolume from COM over various paths...
    - DXSystem (too many functions are redundant here...)
    - Timer // time measurement by std::chrono
    - Window (None struct)

```

# TODO: 

```
- GUI Control
  - Seek Bar
  - Buttons
  - Text Box
  - Combo Box
  - Radio Button
  - Check box
```
