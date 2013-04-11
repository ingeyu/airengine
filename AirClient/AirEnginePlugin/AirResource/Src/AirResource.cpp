// Resource.cpp : 定义 DLL 应用程序的导出函数。
//


#include "AirResource.h"
#include "AirResourceSystem.h"
#include "AirResourceRarPackage.h"
#include "AirResourceZipPackage.h"

BOOL APIENTRY DllMain( HMODULE hModule,
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

namespace Air{
	
	
	namespace	Engine{
	
		Resource::System*	pPlugin	=	NULL;
	
		extern "C" RESOURCE_EXPORT U1 DllInit(void*		pParam)throw(){
			ResourceSystem::GetSingleton()->AddFactory(new NoParamFactory<Resource::ZipPackage>());
			ResourceSystem::GetSingleton()->AddFactory(new NoParamFactory<Resource::RarPackage>());
			return	true;
		}
		extern "C" RESOURCE_EXPORT U1 DllStart(void*		pParam)throw(){

			return	true;
		}
	
		extern "C" RESOURCE_EXPORT U1 DllStop(void*		pParam)throw(){

			return	true;
		}
		extern "C" RESOURCE_EXPORT U1 DllRelease(void*	pParam)throw(){
			//EngineSystem::GetSingleton()->RemoveSystem(pPlugin);
			return	true;
		}
	}
	
};
