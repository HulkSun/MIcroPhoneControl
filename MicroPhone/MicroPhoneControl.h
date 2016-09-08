/*******************��VolumeListenerʵ�ֶ�ϵͳ�����Ŀ���*********************/
#pragma once
/*******************�����ͷ�ļ�*********************/
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <Tchar.h>
#include <functiondiscoverykeys.h>
#include <strsafe.h>
class MicroPhoneControl
{
public:
	//static VolumeListener* getInstance();

	//��ʼ������
	bool initMicroPhoneControl();
	//������
	void clearMicroPhoneControl();
	

	//����ϵͳ���������
	void setMaxVolume();
	//����ϵͳ��������С
	void setMinVolume();
	//��������
	void setVolumeUp();
	//��С����
	void setVolumeDown();
	//���þ��� ����isMuteΪtrue��ʾ���� false�������
	void setMute(bool isMute);
	//��ȡ��ǰϵͳ����
	UINT getCurrentVloume();

	void setVolumeByValue(int value);
	//����ʵ�ֵ���ģʽ
	

	MicroPhoneControl();

private:

	//����ϵͳ�����;����Ľӿ�IAudioEndpointVolume
	IAudioEndpointVolume *endpointVolume;
	//����ϵͳ�����仯�Ļص������
	//CVolumeNotification *volumeNotification;
};
