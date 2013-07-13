// DumpAnalyze.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DumpFile.h"

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc < 2){
		wprintf(L"DumpAnalyze.exe dumpfile\n");
		getchar();
		return -1;
	}


	HRESULT hr = CoInitialize(NULL);

	DumpFile	file;
	file.Open(argv[1]);

	CoUninitialize();
	getchar();
	return 0;
}

