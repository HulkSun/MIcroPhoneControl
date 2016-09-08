#include "MicroPhoneControl.h"
//静态成员


//构造器
//MicroPhoneControl::MicroPhoneControl() :endpointVolume(NULL), volumeNotification(NULL)
MicroPhoneControl::MicroPhoneControl() : endpointVolume(NULL)
{
}

//初始化工作
bool MicroPhoneControl::initMicroPhoneControl()
{
	CoInitialize(NULL);

	HRESULT hr;
	IMMDevice *defaultDevice = NULL;
	IMMDeviceEnumerator *deviceEnumerator = NULL;

	//Instantiate an endpoint volume object.
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
	if (hr != S_OK)
	{
		printf_s("Instantiate an endpoint volume object error\n");
		return false;
	}
	//eRender 输出音频设备(放声) eCapture输入音频设备(录声)
	hr = deviceEnumerator->GetDefaultAudioEndpoint(eCapture, eConsole, &defaultDevice);
	if (hr != S_OK)
	{
		printf_s("GetDefaultAudioEndpoint error\n");
		return false;
	}


	//CVolumeNotification *volumeNotification = new CVolumeNotification();
	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
	if (hr != S_OK)
	{
		printf_s("get IAudioEndpointVolume error\n");
		return false;
	}

	return true;
}

//清理工作
void MicroPhoneControl::clearMicroPhoneControl()
{
	if (endpointVolume)
	{
		/*if (volumeNotification) {
		endpointVolume->UnregisterControlChangeNotify(volumeNotification);
		volumeNotification->Release();
		}*/
		endpointVolume->Release();
	}

	CoUninitialize();


}

//注册对系统音量的监听
//bool MicroPhoneControl::RegisterEndpointNotification()
//{
//	HRESULT hr;
//	if (endpointVolume)
//	{
//		volumeNotification = new CVolumeNotification();
//		hr = endpointVolume->RegisterControlChangeNotify(volumeNotification);
//		if (hr != S_OK)
//		{
//			printf_s("RegisterEndpointNotification error\n");
//			return false;
//		}
//	}
//	return true;
//}


//设置系统音量到最大
void MicroPhoneControl::setMaxVolume()
{
	UINT currentStep, stepCount;
	if (endpointVolume)
	{
		endpointVolume->GetVolumeStepInfo(&currentStep, &stepCount);
		this->setMute(false);
		for (UINT index = currentStep; index < stepCount; index++)
		{
			setVolumeUp();
		}
	}
}

//设置系统音量到最小
void MicroPhoneControl::setMinVolume()
{
	UINT currentStep, stepCount;
	if (endpointVolume)
	{
		endpointVolume->GetVolumeStepInfo(&currentStep, &stepCount);
		endpointVolume->SetMute(FALSE, NULL);
		for (UINT index = currentStep; index > 0; index--)
		{
			setVolumeDown();
		}
	}
}

//调大音量
void MicroPhoneControl::setVolumeUp()
{
	if (endpointVolume)
	{
		endpointVolume->VolumeStepUp(NULL);
	}
}

//调小音量
void MicroPhoneControl::setVolumeDown()
{
	if (endpointVolume)
	{
		endpointVolume->VolumeStepDown(NULL);
	}
}

//设置静音 参数isMute为true表示静音 false解除静音
void MicroPhoneControl::setMute(bool isMute)
{
	if (endpointVolume)
	{
		if (isMute)
			endpointVolume->SetMute(TRUE, NULL); //静音
		else
			endpointVolume->SetMute(FALSE, NULL); //解除静音
	}
}

//获取当前系统音量
UINT MicroPhoneControl::getCurrentVloume()
{
	//UINT currentStep, stepCount, currentVolume;
	float FLcurrentVolume;
	UINT IcurrentVolume = 0;
	//currentVolume = 0;
	if (endpointVolume)
	{
		//endpointVolume->GetVolumeStepInfo(&currentStep, &stepCount);
		//currentVolume = (UINT)((currentStep*1.0 / stepCount) * 100);
		//currentVolume = (UINT)((currentStep*1.0 / stepCount) * 100  );
		endpointVolume->GetMasterVolumeLevelScalar(&FLcurrentVolume);
		IcurrentVolume = (FLcurrentVolume + 0.000001) * 100;
	}
	return IcurrentVolume;
}

//通过数值调节音量
void MicroPhoneControl::setVolumeByValue(int value)
{
	float F_value = (float)value / 100;
	if (endpointVolume)
	{
		endpointVolume->SetMasterVolumeLevelScalar(F_value, NULL);
	}
}

