// Game.cpp : 定义 DLL 应用程序的入口点。
//

#include "AirGame.h"
#include "AirEngineHeader.h"
#include "AirGameSystem.h"
#include "AirGlobalSetting.h"
#include "AirGameSection.h"
#include "AirEditorSystem.h"



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
	
		Game::Section*	pSection	=	NULL;
		extern "C" GAME_EXPORT U1 DllInit(void*		pParam)throw(){
			if(pSection==NULL){
				pSection	=	GameSystem::GetSingleton()->CreateProduct<Game::Section>("Test");
				GameSystem::GetSingleton()->SetCurrentSection(pSection);
			}
			if(Engine::GetGlobalSetting().m_EngineParam.EditorMode==1){
				EditorSystem::GetSingleton()->Initialization();
			}else{
				pSection->LoadScene("AirMesh/Scene/Test.Scene2");
			}
			return	true;
		}
		extern "C" GAME_EXPORT U1 DllStart(void*		pParam)throw(){
			
			return	true;
		}
	
		extern "C" GAME_EXPORT U1 DllStop(void*		pParam)throw(){
			
			return	true;
		}
		extern "C" GAME_EXPORT U1 DllRelease(void*	pParam)throw(){
			if(Engine::GetGlobalSetting().m_EngineParam.EditorMode==1){
				EditorSystem::GetSingleton()->Release();
				EditorSystem::ReleaseSingleton();
			}
			if(pSection!=NULL){
				GameSystem::GetSingleton()->SetCurrentSection(NULL);
				pSection->ReleaseRef();
			}
			return	true;
		}
};