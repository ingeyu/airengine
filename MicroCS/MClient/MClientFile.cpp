#include "MClientFile.h"
#include "MClient.h"

BOOL APIENTRY DllMain( HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call){
	case DLL_PROCESS_ATTACH:{

							}break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:

		break;
	case DLL_PROCESS_DETACH:

		break;
	}
	return TRUE;
}

extern "C"	MCLIENT_EXPORT	unsigned int LoadFile( const char* strName,void* pBuffer )
{
	return MClient::GetSingleton()->LoadFile(strName,pBuffer);
}

extern "C"	MCLIENT_EXPORT	bool DllInit()
{
	MClient::GetSingleton()->Initialization();
	return true;
}

extern "C"	MCLIENT_EXPORT	bool DllRelease()
{
	MClient::GetSingleton()->Release();
	MClient::ReleaseSingleton();
	return true;
}
