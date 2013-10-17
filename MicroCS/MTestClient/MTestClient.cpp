// MTestClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MClientFile.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	DllInit();
	void* buffer =	malloc(16*1048576);
	bool b = LoadFile("F:\\WpfTool\\WpfTool\\ui\\image\\achi\\achiinfo_bg.png",buffer);

	DllRelease();
	return 0;
}

