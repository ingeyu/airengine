// Input.cpp : 定义 DLL 应用程序的入口点。
//


#include "AirInput.h"
#include "AirInputHeader.h"
#include "AirInputSystem.h"




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
	
		
		Input::System*	pPlugin	=	NULL;
	
		extern "C" INPUT_EXPORT U1 DllInit(void*		pParam)throw(){
			if(pPlugin==NULL){
				pPlugin = new Input::System();
			}

			EngineSystem::GetSingleton()->AddSystem(pPlugin);
			return	true;
		}
		extern "C" INPUT_EXPORT U1 DllStart(void*		pParam)throw(){
	
			return	true;
		}
	
		extern "C" INPUT_EXPORT U1 DllStop(void*		pParam)throw(){
	
			return	true;
		}
		extern "C" INPUT_EXPORT U1 DllRelease(void*	pParam)throw(){
// 			EngineSystem::GetSingleton()->RemoveSystem(pPlugin);
// 
// 			if(pPlugin!=NULL){
// 				delete pPlugin;
// 				pPlugin	=	NULL;
// 			}
			return	true;
		}
	}
};