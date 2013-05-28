#include "AirAIRecast.h"
#include <Windows.h>
#include "AirAISystem.h"


BOOL APIENTRY DllMain( HANDLE hModule, 
	DWORD  ul_reason_for_call, 
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

namespace	Air{
	namespace	Engine{

		

		extern "C" AIRAIRECAST_EXPORT U1 DllInit(void*		pParam)throw(){

			return	true;
		}
		extern "C" AIRAIRECAST_EXPORT U1 DllStart(void*		pParam)throw(){

			return	true;
		}

		extern "C" AIRAIRECAST_EXPORT U1 DllStop(void*		pParam)throw(){

			return	true;
		}
		extern "C" AIRAIRECAST_EXPORT U1 DllRelease(void*	pParam)throw(){

			return	true;
		}
	}
}