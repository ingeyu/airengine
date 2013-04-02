// Game.cpp : 定义 DLL 应用程序的入口点。
//

#include "AirGame.h"
#include "AirEngineHeader.h"
#include "AirGameSystem.h"
#include "AirGlobalSetting.h"




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
	
		Game::System*	pPlugin	=	NULL;
	
		extern "C" GAME_EXPORT U1 DllInit(void*		pParam)throw(){
			if(pPlugin==NULL){
				pPlugin = new Game::System();
				pPlugin->Initialization();
				//GetGlobalSetting().m_pGameSystem	=	dynamic_cast<Game::ISystem*>(pPlugin);
			}
			return	true;
		}
		extern "C" GAME_EXPORT U1 DllStart(void*		pParam)throw(){
			if(pPlugin!=NULL)
				pPlugin->Start();
			return	true;
		}
	
		extern "C" GAME_EXPORT U1 DllStop(void*		pParam)throw(){
			if(pPlugin!=NULL){
				pPlugin->Stop();
			}
			return	true;
		}
		extern "C" GAME_EXPORT U1 DllRelease(void*	pParam)throw(){
			pPlugin->Release();
			SAF_D(pPlugin);
			return	true;
		}
	}
};