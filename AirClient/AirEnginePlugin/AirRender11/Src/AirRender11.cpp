// Render.cpp : 定义 DLL 应用程序的入口点。
//


#include "AirRender11.h"
#include "AirCommonHeader.h"
#include "AirRenderDevice11.h"
#include "AirRenderWindow11.h"
#include "AirRenderTexture11.h"
#include "AirRenderBuffer11.h"
#include "AirRenderShader11.h"
#include "AirRenderVertexDeclare11.h"
#include "AirStaticMesh.h"
#include "AirRenderSystem.h"


//Air::Client::Render::Device11*	pDevice	=	NULL;

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
	
		Render::Device11*	pDevice	=	NULL;
// 		Render::Window11*	pWindow	=	NULL;
// 		StaticMesh*	pMesh			=	NULL;
// 		Render::Buffer11*	pBuffer[3];
// 		Render::VertexDeclare11*	pDeclare	=	NULL;
// 		Render::Shader11*	pVS		=	NULL;
// 		Render::Shader11*	pPS		=	NULL;
// 		Matrix	vp;
		extern "C" RENDER_EXPORT U1 DllInit(void*		pParam)throw(){

 			if(pDevice==NULL){
 				pDevice	=	new	Air::Client::Render::Device11();
 				Air::Client::Render::System::GetSingleton()->AddDevice(pDevice);
 				//pDevice->Create();
 			}
			/*
			Render::Target::Info	info;
			info.SetRenderWindow(1280,720,true,NULL,NULL);
			info.bUseDepth	=	true;
			info.depthFormat	=	(enumTextureFormat)DXGI_FORMAT_D24_UNORM_S8_UINT;

			pWindow	=	new Render::Window11("",&info);
			pWindow->Create();
			pWindow->SetClearFlag(7);

			Render::Texture11	t("..\\Data\\Test\\ice_1_diffuse.png",NULL);
			t.Create();

			pMesh	=	new	StaticMesh("..\\Data\\AirMesh\\car.ame");
			pMesh->Create();

			Render::Buffer11::Info	info0;
			info0.SetVertexBuffer(pMesh->GetVertexCount(),44);
			info0.InitData	=	pMesh->GetVB();
			pBuffer[0]	=	new	Render::Buffer11("0",&info0);pBuffer[0]->Create();
			info0.SetIndexBuffer32(pMesh->GetFaceCount()*3);
			info0.InitData	=	pMesh->GetIB();
			pBuffer[1]	=	new	Render::Buffer11("1",&info0);pBuffer[1]->Create();


			Matrix	view;
			view.ViewAL(Float3(150,100,150),Float3(0,0,0),Float3(0,1,0));
			Matrix	proj;
			proj.ProjectFL(XM_PIDIV4,128.0f/72.0f,1,1000);
			vp	=	view*proj;
			info0.SetConstantBuffer(sizeof(Matrix));
			info0.InitData		=	&vp;
			pBuffer[2]	=	new	Render::Buffer11("2",&info0);pBuffer[2]->Create();

			Render::Vertex::IDeclare::Info	dinfo;
			dinfo.SetDeclPNTT();
			pDeclare	=	new	Render::VertexDeclare11("0",&dinfo);
			pDeclare->Create();

			pVS			=	new	Render::Shader11("..\\Data\\Shader\\Object.vs11");
			pVS->Create();
			pPS			=	new	Render::Shader11("..\\Data\\Shader\\Dot.ps11");
			pPS->Create();
			*/
			return	true;
		}
		extern "C" RENDER_EXPORT U1 DllStart(void*		pParam)throw(){
			/*
			MSG msg;
			::ZeroMemory(&msg, sizeof(MSG));

			//SetCursor(LoadCursor(0, IDC_ARROW));


			while(true){

					if(::PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
						::TranslateMessage(&msg);
						::DispatchMessage(&msg);
					}else{	
						pWindow->BeforeUpdate();

						pDevice->SetShader(enVS,pVS);
						pDevice->SetShader(enPS,pPS);

						pDevice->SetVB(0,pBuffer[0]);
						pDevice->SetIB(pBuffer[1]);
						pDevice->SetVD(pDeclare);

						pDevice->SetCB(0,pBuffer[2]);

						DxContext*	pContext	=	(DxContext*)pDevice->GetContext();

						pContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
						pContext->DrawIndexed(pMesh->GetFaceCount()*3,0,0);
						


						pWindow->AfterUpdate();
					}
					if(msg.message	==	WM_QUIT){
						break;
					}
			}
			*/
			return	true;
		}
	
		extern "C" RENDER_EXPORT U1 DllStop(void*		pParam)throw(){
// 			pBuffer[0]->Destroy();
// 			delete pBuffer[0];
// 			pBuffer[1]->Destroy();
// 			delete pBuffer[1];
// 			pBuffer[2]->Destroy();
// 			delete pBuffer[2];
// 			pDeclare->Destroy();
// 			delete pDeclare;
// 			pVS->Destroy();delete	pVS;
// 			pPS->Destroy();delete	pPS;
			return	true;
		}
		extern "C" RENDER_EXPORT U1 DllRelease(void*	pParam)throw(){
// 			if(pWindow!=NULL){
// 				pWindow->Destroy();
// 				delete pWindow;
// 				pWindow=NULL;
// 			}
 			if(pDevice!=NULL){
 				delete	pDevice;
 				pDevice	=	NULL;
 			}
			return	true;
		}
	}
};