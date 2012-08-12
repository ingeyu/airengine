// Engine.cpp : 定义 DLL 应用程序的入口点。
//


#include "AirEngine.h"
#include "Windows.h"
#include "AirEngineSystem.h"
#include "AirGlobalSetting.h"
#include "AirRenderSystem.h"
#include "AirStaticMesh.h"
#include "AirCommonWindow.h"



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call){
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:

		break;
		case DLL_PROCESS_DETACH:
			//SAF_D(pPlugin);
		break;
	}
    return TRUE;
}


namespace Air{
	
	namespace	Client{
// 		Common::Plugin	renderPlugin("AirRender11.dll",NULL);
// 		Shader*			pVS	=	NULL;
// 		Shader*			pPS	=	NULL;
// 		Render::Window*	pWindow	=	NULL;
// 		Render::Target*	pMRT	=	NULL;
// 		StaticMesh*		pmesh=NULL;
// 		Buffer*			pCameraBuffer	=	NULL;
// 		Render::State*	pDS=NULL;
// 		Matrix	vp;
		extern "C" ENGINE_EXPORT U1 DllInit(void*		pParam)throw(){
 	 		EngineParam*	pEngineParam	=	(EngineParam*)pParam;
 	 		UInt	uiSize	=	sizeof(EngineParam);
 	 		EngineParam*	pDst			=	&GetGlobalSetting().m_EngineParam;
 	 		if(pEngineParam!=NULL)
 	 			memcpy(pDst,pEngineParam,uiSize);
 	 
 	 		//OutputDebugStringA(pDst->strDisplay);
 			
 			EngineSystem::GetSingleton()->Initialization();

			//Render::System*	pSys	=	Render::System::GetSingleton();
			

// 			renderPlugin.Create();
// 			renderPlugin.Excute(Common::Plugin::enInit);
// 
// 			pSys->Initialization();
// 			Texture::Info	info;
// 			info.SetRenderToTexture(512,512);
// 			info.SetViewFlag(enVF_SRV|enVF_RTV);
// 			Texture*	p	=	pSys->CreateProduct<Texture*>("RT","Texture",&info);
// 			
// 			Render::Window::Info	winfo;
// 			winfo.SetRenderWindow(512,512);
// 			winfo.bUseDepth	=	true;
// 
// 			pWindow			=	pSys->CreateProduct<Render::Window*>("MainWindow","Window",&winfo);
// 			pWindow->SetClearFlag(true,true,true);
// 
// 
// 			Render::Target::Info	mrtInfo;
// 			enumTextureFormat	fmtArray[4]={
// 				enTFMT_R32_FLOAT,
// 				enTFMT_R8G8B8A8_UNORM,
// 				enTFMT_R8G8B8A8_UNORM,
// 				enTFMT_R8G8B8A8_UNORM
// 			};
// 			mrtInfo.SetMutilTarget(496,474,4,fmtArray,true,pWindow);
// 			pMRT	=	pSys->CreateProduct<Render::Target*>("MRT","Target",&mrtInfo);
// 			pMRT->SetClearFlag(1,1,1);
// 
// 			pVS				=	pSys->CreateProduct<Shader*>("..\\Data\\Shader\\Object.vs11","Shader");
// 			pPS				=	pSys->CreateProduct<Shader*>("..\\Data\\Shader\\DeferredShading.ps11","Shader");
// 			Buffer::Info	cbInfo;
// 			cbInfo.SetConstantBuffer(sizeof(Matrix));
// 			Matrix	view;
// 			view.ViewAL(Float3(150,100,150),Float3(0,0,0),Float3(0,1,0));
// 			Matrix	proj;
// 			proj.ProjectFL(XM_PIDIV4,1,1,1000);
// 			vp	=	view*proj;
// 			cbInfo.InitData	=	&vp;
// 			pCameraBuffer	=	pSys->CreateProduct<Buffer*>("CameraViewproj","Buffer",&cbInfo);
// 			pmesh	=	new StaticMesh("..\\Data\\AirMesh\\Car.ame");
// 			pmesh->Create();
// 
// 			PassStateInfo	dsInfo;
// 			dsInfo.type		=	enRST_DS;
// 			//dsInfo.ds.DepthWriteMask	=	Render::enDWM_ZERO;
// 			pDS				=	pSys->CreateProduct<Render::State*>("ds","State",&dsInfo);

			return	true;
		}
		extern "C" ENGINE_EXPORT U1 DllStart(void*		pParam)throw(){
			EngineSystem::GetSingleton()->Start();
// 			MSG msg;
// 			::ZeroMemory(&msg, sizeof(MSG));
// 
// 			//SetCursor(LoadCursor(0, IDC_ARROW));
// 			Render::Device*	pDevice	=	Render::System::GetSingleton()->GetDevice();
// 
// 
// 			while(true){
// 
// 					if(::PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
// 						::TranslateMessage(&msg);
// 						::DispatchMessage(&msg);
// 					}else{
// 
// 						if(pMRT->BeforeUpdate()){
// 
// 							pDevice->SetShader(enVS,pVS);
// 							pDevice->SetShader(enPS,pPS);
// 							// 
// 							// 						pDevice->SetVB(0,pBuffer[0]);
// 							// 						pDevice->SetIB(pBuffer[1]);
// 							// 						pDevice->SetVD(pDeclare);
// 
// 							pDevice->SetDSS(pDS);
// 							pDevice->SetCB(0,pCameraBuffer);
// 
// 							pDevice->DrawObject(pmesh);
// 
// 							pMRT->AfterUpdate();
// 						}
// 						pWindow->BeforeUpdate();
// 
// 
// 						
// 
// 
// 						pWindow->AfterUpdate();
// 					}
// 					if(msg.message	==	WM_QUIT){
// 						break;
// 					}
// 			}
			
			return	true;
		}
	
		extern "C" ENGINE_EXPORT U1 DllStop(void*		pParam)throw(){
	
			EngineSystem::GetSingleton()->Stop();
			return	true;
		}
		extern "C" ENGINE_EXPORT U1 DllRelease(void*	pParam)throw(){
			
 			EngineSystem::GetSingleton()->Release();
 			EngineSystem::ReleaseSingleton();
// 			Render::System::GetSingleton()->Release();
// 			Render::System::ReleaseSingleton();
// 
// 			renderPlugin.Excute(Common::Plugin::enRelease);
// 			renderPlugin.Destroy();
			return	true;
		}
	}
};
