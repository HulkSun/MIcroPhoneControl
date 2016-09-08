#include "MicroPhoneControl.h"
//��̬��Ա


//������
//MicroPhoneControl::MicroPhoneControl() :endpointVolume(NULL), volumeNotification(NULL)
MicroPhoneControl::MicroPhoneControl() : endpointVolume(NULL)
{
}

//��ʼ������
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
	//eRender �����Ƶ�豸(����) eCapture������Ƶ�豸(¼��)
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

//������
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

//ע���ϵͳ�����ļ���
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


//����ϵͳ���������
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

//����ϵͳ��������С
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

//��������
void MicroPhoneControl::setVolumeUp()
{
	if (endpointVolume)
	{
		endpointVolume->VolumeStepUp(NULL);
	}
}

//��С����
void MicroPhoneControl::setVolumeDown()
{
	if (endpointVolume)
	{
		endpointVolume->VolumeStepDown(NULL);
	}
}

//���þ��� ����isMuteΪtrue��ʾ���� false�������
void MicroPhoneControl::setMute(bool isMute)
{
	if (endpointVolume)
	{
		if (isMute)
			endpointVolume->SetMute(TRUE, NULL); //����
		else
			endpointVolume->SetMute(FALSE, NULL); //�������
	}
}

//��ȡ��ǰϵͳ����
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

//ͨ����ֵ��������
void MicroPhoneControl::setVolumeByValue(int value)
{
	float F_value = (float)value / 100;
	if (endpointVolume)
	{
		endpointVolume->SetMasterVolumeLevelScalar(F_value, NULL);
	}
}

