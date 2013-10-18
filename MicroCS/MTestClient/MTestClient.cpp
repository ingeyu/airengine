// MTestClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MClientFile.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE	hMutex	=	CreateMutex(NULL,TRUE,_T("wzclient"));
	DllInit();
	printf("DllInit\n");
	getchar();
	void* buffer =	malloc(16*1048576);
	int size = LoadFile("F:\\WpfTool\\WpfTool\\ui\\image\\achi\\achiinfo_bg.png",buffer);
	printf("LoadFile\n");
	FILE* p=_wfopen(L"1.png",L"wb");
	fwrite(buffer,size,1,p);
	fclose(p);
	printf("WriteFile\n");
	getchar();
	DllRelease();
	printf("DllRelease\n");
	getchar();
	return 0;
}

