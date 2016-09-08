#include "MicroPhoneControl.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
void control()
{
	using namespace std;
	MicroPhoneControl microPhoneControl;
	microPhoneControl.initMicroPhoneControl();

	//int input;
	while (true)
	{
		microPhoneControl.setVolumeByValue(50);
		Sleep(1000);
		cout << "current volume:";
		cout << microPhoneControl.getCurrentVloume() << endl;
	}
	microPhoneControl.clearMicroPhoneControl();
}



int main()
{
	control();
	return 0;
}