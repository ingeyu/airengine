// Game.cpp : 定义 DLL 应用程序的入口点。
//

#include "AirGame.h"
#include "AirEngineHeader.h"
#include "AirGameSystem.h"
#include "AirGlobalSetting.h"
#include "AirGameSection.h"
#include "AirEditorSystem.h"
#include "AirGameDefaultSection.h"



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
			
			EngineSystem::GetSingleton()->AddFactory(new NoParamFactory<Game::EditorSection>());
			EngineSystem::GetSingleton()->AddFactory(new NoParamFactory<Game::DefaultSection>());
			

			if(pSection==NULL){
				if(Engine::GetGlobalSetting().m_EngineParam.EditorMode==1){
					pSection	=	EngineSystem::GetSingleton()->CreateProduct<Game::EditorSection>("Test");
				}else{
					pSection	=	EngineSystem::GetSingleton()->CreateProduct<Game::DefaultSection>("Test");
				}
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
			GameSystem::GetSingleton()->DestroyAllProduct();
			if(pSection!=NULL){
				GameSystem::GetSingleton()->SetCurrentSection(NULL);
				pSection->ReleaseRef();
				pSection=NULL;
			}


			EngineSystem::GetSingleton()->RemoveFactory(Game::EditorSection::ProductTypeName);
			EngineSystem::GetSingleton()->RemoveFactory(Game::DefaultSection::ProductTypeName);
			
			return	true;
		}
};