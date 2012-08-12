#include "AirRenderTarget9.h"
#include "AirRenderGlobal9.h"
#include "AirRenderTexture9.h"
#include "AirRenderSystem9.h"

#include "AirEngineCamera.h"
#include "AirEngineScene.h"
namespace Air{
	
	namespace	Client{
		namespace	Render{
	
	
			Target9::Target9( CAString& strName,Info* pInfo ):ITarget(strName,pInfo){
				m_pSurface	=	NULL;

				m_pTargetObject	=	NULL;
	
			}
	
			U1 Target9::Destroy( ){

				ITarget::Destroy();
				SAFE_RELEASE(m_pSurface);
				return true;
			}
	
	
			U1 Target9::BeforeUpdate(){
	
				if(!ITarget::BeforeUpdate())
					return	false;

				System*		pSys	=	static_cast<System*>(m_pFactoryMgr);
				DxDevice*	pDevice	=	pSys->GetDevice();

				IDirect3DSurface9*	pRT[4]	=	{NULL,NULL,NULL,NULL};
				U32	uiRTCount	=	m_vecTexture.size();

				DWORD	clearFlag	=	0;

				for(U32	i=0;i<uiRTCount;i++){
					pRT[i]	=	(IDirect3DSurface9*)m_vecTexture[i]->GetSurface();
					if(pRT[i]!=NULL){
						clearFlag	|=	D3DCLEAR_TARGET;
					}
				}

				for(U32	i=0;i<4;i++){
					pSys->SetRenderTarget(i,pRT[i]);
				}

				IDirect3DSurface9*	pDepthStencil	=	(IDirect3DSurface9*)GetDepthStencil();
				if(pDepthStencil!=NULL){
					clearFlag		|=	D3DCLEAR_ZBUFFER;
					clearFlag		|=	D3DCLEAR_STENCIL;
				}

				pSys->SetDepthStencilSurface(pDepthStencil);

				


				if(m_ClearFlag!=0){
					D3DCOLOR	c	=	D3DCOLOR_COLORVALUE(	m_Info.clearColor.x,
																m_Info.clearColor.y,
																m_Info.clearColor.z,
																m_Info.clearColor.w);
					pDevice->Clear(0,NULL,m_ClearFlag&clearFlag,c,1.0f,0);
				}

				if(FAILED(pDevice->BeginScene())){
					return	false;
				}
	
	
				return true;
			}
	
			void Target9::SetRenderObject( MovableObject* pObject ){
				m_pTargetObject	=	pObject;
			}
	
			void Target9::ReCreate( Info& info ){

	
			}
	
			MovableObject* Target9::GetRenderObject(){
				return	m_pTargetObject;
			}

			Air::U1 Target9::CreateDepthStencil(){
				if(m_Info.bUseDepth){
					U32	uiWidth		=	m_vecTexture[0]->GetWidth();
					U32	uiHeight	=	m_vecTexture[0]->GetHeight();
					GetGlobal().m_pDevice->CreateDepthStencilSurface(uiWidth,uiHeight,(D3DFORMAT)m_Info.depthFormat,D3DMULTISAMPLE_NONE,0,TRUE,&m_pSurface,NULL);
				}
				return	true;
			}

			Air::U1 Target9::DestroyDepthStencil(){
				SAFE_RELEASE(m_pSurface);
				return	true;
			}

			void* Target9::GetDepthStencil(){
				if(!m_Info.bUseDepth){
					return	NULL;
				}
				if(m_Info.extraDepth!=NULL){
					return	m_Info.extraDepth->GetDepthStencil();
				}
				if(m_pSurface==NULL){
					CreateDepthStencil();
				}
				return	m_pSurface;
			}

			Air::U1 Target9::AfterUpdate(){
				System*	pSys	=	static_cast<System*>(m_pFactoryMgr);
				pSys->GetDevice()->EndScene();
				return	true;
			}

			void Target9::OnLostDevice(){
				DestroyDepthStencil();
			}

			void Target9::OnResetDevice(){
				CreateDepthStencil();
			}
			Target9Factory::Target9Factory(){
				m_strTypeName	=	"Target";
			}
	
			IProduct* Target9Factory::NewProduct( CAString& strName,IFactoryParamList* lstParam /*= NULL*/ ){
				if(lstParam ==NULL)
					return NULL;
				Target9::Info*	pInfo	=	(Target9::Info*)lstParam;
				Target9*	pBuff			=	new	Target9(strName,pInfo);
				return	pBuff;
			}
		}
	}
};