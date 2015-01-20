// VolumeTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <mmdeviceapi.h>
#include <endpointvolume.h>

bool ChangeVolume(int nVolume)
{
    CoInitialize(NULL);

    IMMDeviceEnumerator *deviceEnumerator;
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
        __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    IMMDevice *defaultDevice;

    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();

    IAudioEndpointVolume *endpointVolume;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), 
        CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
    defaultDevice->Release();

    hr = endpointVolume->SetMasterVolumeLevelScalar(nVolume / 100.0f, NULL);

    endpointVolume->Release();
    CoUninitialize();

    return FALSE;
}

//float currentVolume = 0;
//endpointVolume->GetMasterVolumeLevel(&currentVolume);

int _tmain(int argc, _TCHAR* argv[])
{
    ChangeVolume(80);

	return 0;
}

