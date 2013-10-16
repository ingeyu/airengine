
#include "MFileSystem.h"


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) 
{
	HANDLE	hMutex	=	CreateMutex(NULL,TRUE,_T("MFileSystem"));
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hMutex);
		return 1;
	}

	Air::Common::InitNet();

	MFileSystem::GetSingleton()->Initialization();

	





	MFileSystem::GetSingleton()->Release();
	MFileSystem::ReleaseSingleton();

	CloseHandle(hMutex);
	return 0;
}