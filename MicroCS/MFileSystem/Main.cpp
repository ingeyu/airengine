
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

	
	
	while(1){
		evt.Wait(10);
		HANDLE	hClientMutex	=	OpenMutex(MUTEX_ALL_ACCESS,TRUE,_T("wzclient"));
		if(hClientMutex!=NULL){
			CloseHandle(hClientMutex);
		}else{
			//break;
		}
		

		MFileSystem::GetSingleton()->Update(0);

		
	}



	MFileSystem::GetSingleton()->Release();
	MFileSystem::ReleaseSingleton();

	CloseHandle(hMutex);
	return 0;
}