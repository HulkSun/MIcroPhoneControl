/*******************类VolumeListener实现对系统音量的控制*********************/
#pragma once
/*******************导入的头文件*********************/
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

	//初始化工作
	bool initMicroPhoneControl();
	//清理工作
	void clearMicroPhoneControl();
	

	//设置系统音量到最大
	void setMaxVolume();
	//设置系统音量到最小
	void setMinVolume();
	//调大音量
	void setVolumeUp();
	//调小音量
	void setVolumeDown();
	//设置静音 参数isMute为true表示静音 false解除静音
	void setMute(bool isMute);
	//获取当前系统音量
	UINT getCurrentVloume();

	void setVolumeByValue(int value);
	//该类实现单例模式
	

	MicroPhoneControl();

private:

	//控制系统音量和静音的接口IAudioEndpointVolume
	IAudioEndpointVolume *endpointVolume;
	//监听系统音量变化的回调类变量
	//CVolumeNotification *volumeNotification;
};
