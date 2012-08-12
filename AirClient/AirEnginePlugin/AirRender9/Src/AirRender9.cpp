// Render.cpp : 定义 DLL 应用程序的入口点。
//


#include "AirRender9.h"
#include "AirCommonHeader.h"
#include "AirRenderSystem9.h"



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		//SAF_D(pPlugin);
		return TRUE;
		break;
	}
    return TRUE;
}
namespace Air{
	
	namespace	Client{
	
		Render::System*	pSys	=	NULL;
	
		extern "C" RENDER_EXPORT U1 DllInit(void*		pParam)throw(){
	 		if(pSys==NULL){
	 			pSys = new Render::System();
	 		}
			EngineSystem::GetSingleton()->AddSystem(pSys);

			return	true;
		}
		extern "C" RENDER_EXPORT U1 DllStart(void*		pParam)throw(){

			return	true;
		}
	
		extern "C" RENDER_EXPORT U1 DllStop(void*		pParam)throw(){

			return	true;
		}
		extern "C" RENDER_EXPORT U1 DllRelease(void*	pParam)throw(){

// 			EngineSystem::GetSingleton()->RemoveSystem(pSys);
// 
// 			if(pSys!=NULL){
// 				SAF_D(pSys);
// 			}
			return	true;
		}
	}
};