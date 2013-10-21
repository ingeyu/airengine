
#include "MFileSystem.h"


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) 
{
	

	U32 uiSize	=	sizeof(NT_Data<FileDataInfo>);

	HANDLE	hMutex	=	CreateMutex(NULL,TRUE,_T("MFileSystemMutex"));
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hMutex);
		return 1;
	}

	Air::Common::InitNet();

	MFileSystem::GetSingleton()->Initialization();

	

	
	DWORD dwTick	=	0;
	while(1){

		HANDLE	hClientMutex	=	OpenMutex(MUTEX_ALL_ACCESS,TRUE,_T("wzclient"));
		if(hClientMutex!=NULL){
			CloseHandle(hClientMutex);
		}else{
			break;
		}
		DWORD	newTick	=	GetTickCount();

		MFileSystem::GetSingleton()->Update(newTick);

		dwTick	=	newTick;
		
	}



	MFileSystem::GetSingleton()->Release();
	CloseHandle(hMutex);
	MFileSystem::ReleaseSingleton();

	
	return 0;
}