
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

	Air::Common::Event evt;

	
	HANDLE	hClientMutex	=	OpenMutex(MUTEX_ALL_ACCESS,TRUE,_T("wzclient"));
	while(1){

		if(hClientMutex==NULL){
			break;
		}
		CloseHandle(hClientMutex);

		MFileSystem::GetSingleton()->Update(0);

		evt.Wait(10);
	}



	MFileSystem::GetSingleton()->Release();
	MFileSystem::ReleaseSingleton();

	CloseHandle(hMutex);
	return 0;
}