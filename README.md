# m5stack-avatar-on-WinPC

## 想定環境

- OS：Windows (10で検証済み)
- ビルド環境：VC Code

★使ってないかも
- コンパイラ：MinGW-w64
  - 環境変数のパスにインストール先のbinが通してあること
    - 例： `C:\mingw64\bin`
  - MinGW-w64の [インストール方法はこちらを参考](https://www.javadrive.jp/cstart/install/index6.html)

## 音声取得の仕組み

Windows用のAPI `EndpointVolume API` の `IAudioMeterInformation` クラスの `GetPeakValue()` 関数を使用してデスクトップ上の音量を取得しています。

音量が 0 - 1 の間のfloatで取得されるため、それを `m5stack-avatar` の `avatar.setMouthOpenRatio()` にセットすることでアバターの口の開閉を行っています。

### 実装上の注意点

#### 1

ライブラリの読み込み順序に一部制約があり、関連する以下のライブラリ群では `Windows.h` を最上位に読み込む必要があります。

``` cpp
#include <Windows.h>          // Windows API
#include <mmdeviceapi.h>      // IMMDeviceEnumerator, IMMDevice など
#include <endpointvolume.h>   // IAudioMeterInformation
#include <Audioclient.h>      // WASAPI
#include <iostream>           // std::cerr などの標準入出力
```

#### 2

`.vscode/c_cpp_properties.json` に記載されているMinGW-w64のパスは、インストールしたものに合わせる必要があります。

``` json
            "defines": [
                "PLATFORMIO=60116",
                "M5GFX_BOARD=board_M5Stack",
                "M5GFX_SCALE=3",
                "__PLATFORMIO_BUILD_DEBUG__",
                ""
            ],
            "cppStandard": "c++17",
            "compilerPath": "C:/msys64/ucrt64/bin/gcc.exe",
            "compilerArgs": [
                ""
            ]
```

#### 3

`platformio.ini` に記載されているビルド設定

#### 4

MinGW には IAudioMeterInformation の完全な構造定義がないようです。
PortAudio リポジトリから IAudioMeterInformation の完全な定義をコピーし、必要な __CRT_UUID_DECL を追加して、コンパイル エラー「_GUID const& __mingw_uuidof への未定義の参照」を回避しています。

出典：
https://stackoverflow.com/questions/62012071/why-is-iaudiometerinformation-an-incomplete-type

以下のコードが上記の説明に該当します。

``` cpp
__CRT_UUID_DECL(IAudioMeterInformation, 0xC02216F6, 0x8C67, 0x4B5B, 0x9D, 0x00, 0xD0, 0x08, 0xE7, 0x3E, 0x00, 0x64);

// Define the IAudioMeterInformation interface
MIDL_INTERFACE("C02216F6-8C67-4B5B-9D00-D008E73E0064")
IAudioMeterInformation : public IUnknown
{
public:
    virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPeakValue(
        /* [out] */ float *pfPeak) = 0;

    virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetMeteringChannelCount(
        /* [out] */ UINT *pnChannelCount) = 0;

    virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetChannelsPeakValues(
        /* [in] */ UINT32 u32ChannelCount,
        /* [size_is][out] */ float *afPeakValues) = 0;

    virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE QueryHardwareSupport(
        /* [out] */ DWORD *pdwHardwareSupportMask) = 0;
};
```

このコードが無い場合、main関数内の以下のコードでコンパイルエラーが発生します。

``` cpp
    hr = pMeterInfo->GetPeakValue(&peakValue);
    pMeterInfo->Release();
```

エラーの表示例

``` sh
main.cpp:47:47: error: invalid use of incomplete type 'IAudioMeterInformation' {aka 'struct IAudioMeterInformation'}
     hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
          ~~~~~~~~~~~
```
