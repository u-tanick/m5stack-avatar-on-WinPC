#include <Windows.h>          // Windows API
#include <mmdeviceapi.h>      // IMMDeviceEnumerator, IMMDevice など
#include <endpointvolume.h>   // IAudioMeterInformation
#include <Audioclient.h>      // WASAPI
#include <iostream>           // std::cerr などの標準入出力

#include <M5Unified.h>
#include <M5GFX.h>
#include <Avatar.h>

using namespace m5avatar;

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

float getVolumeLevel() {
    CoInitialize(NULL);

    IMMDeviceEnumerator* pEnumerator = NULL;
    IMMDevice* pDevice = NULL;
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pEnumerator));
    if (FAILED(hr)) {
        std::cerr << "IMMDeviceEnumeratorの作成に失敗しました。" << std::endl;
        return -1;
    }

    hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDevice);
    if (FAILED(hr)) {
        std::cerr << "デフォルトオーディオエンドポイントの取得に失敗しました。" << std::endl;
        pEnumerator->Release();
        return -1;
    }

    IAudioMeterInformation* pMeterInfo = NULL;
    hr = pDevice->Activate(__uuidof(IAudioMeterInformation), CLSCTX_INPROC_SERVER, nullptr, (void**)&pMeterInfo);
    if (FAILED(hr)) {
        std::cerr << "IAudioMeterInformationの取得に失敗しました。" << std::endl;
        pDevice->Release();
        pEnumerator->Release();
        return -1;
    }

    float peakLevel = 0.0f;
    hr = pMeterInfo->GetPeakValue(&peakLevel);
    if (FAILED(hr)) {
        std::cerr << "音量レベルの取得に失敗しました。" << std::endl;
    }

    pMeterInfo->Release();
    pDevice->Release();
    pEnumerator->Release();
    CoUninitialize();

    return peakLevel;
}

Avatar avatar;

void setup() {
    M5.begin();
    avatar.init(8);
}

using lgfx::v1::delay;
void loop() {
    M5.update();
    float volumeLevel = getVolumeLevel();
    if (volumeLevel >= 0) {
        avatar.setMouthOpenRatio(volumeLevel);
    }
    delay(100);
}