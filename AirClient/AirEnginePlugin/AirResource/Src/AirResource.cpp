// Resource.cpp : 定义 DLL 应用程序的导出函数。
//


#include "AirResource.h"
#include "AirResourceSystem.h"
#include "AirGlobalSetting.h"
#include "AirEngineSystem.h"


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
	
	
	namespace	Client{
	
		Resource::System*	pPlugin	=	NULL;
	
		extern "C" RESOURCE_EXPORT U1 DllInit(void*		pParam)throw(){
			if(pPlugin==NULL){
				pPlugin	= new Resource::System();
 				GetGlobalSetting().m_pResourceSystem	=	pPlugin;
// 				pPlugin->Initialization();
			}
			EngineSystem::GetSingleton()->AddSystem(pPlugin);
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
