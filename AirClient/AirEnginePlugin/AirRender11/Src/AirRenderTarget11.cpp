#include "AirRenderTarget11.h"
#include "AirRenderDevice11.h"

#include "AirEngineCamera.h"
#include "AirEngineScene.h"
namespace Air{
	
	namespace	Client{
		extern	Render::Device11*	pDevice;
		namespace	Render{
	
	
			Target11::Target11( CAString& strName,Info* pInfo ):Target(strName,pInfo){
				m_pDepthBufferDSV	=	NULL;
				m_pDepthBufferSRV	=	NULL;
				m_pDepthBuffer		=	NULL;
	
			}
	
			U1 Target11::Destroy( ){

				Target::Destroy();
				DestroyDepthStencil();

				return true;
			}
	
	
			U1	Target11::BeforeUpdate(U32	uiFace){
	
				if(!Target::BeforeUpdate())
					return	false;

				D3DPERF_BeginEvent(0,L"RenderTarget");

				DxContext*	pContext	=	(DxContext*)pDevice->GetContext();

				DxRTV*	pRT[8]	=	{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
				U32	uiRTCount	=	m_vecTexture.size();

				DWORD	clearFlag	=	0;

				for(U32	i=0;i<uiRTCount;i++){
					pRT[i]	=	(DxRTV*)m_vecTexture[i]->GetRTV();
					if(m_ClearFlag&enTCF_TARGET){
						pContext->ClearRenderTargetView(pRT[i],(float*)&m_Info.clearColor);
					}
				}

				
				DxDSV*	pDSV	=	NULL;
				if(m_Info.bUseDepth){
					if(m_Info.extraDepth!=NULL){
						pDSV	=	(DxDSV*)m_Info.extraDepth->GetDepthRTV();
					}else{
						pDSV	=	m_pDepthBufferDSV;
					}
					if(pDSV!=NULL){
						if(m_ClearFlag&enTCF_ZBUFFER)
							clearFlag		|=	D3D11_CLEAR_DEPTH;
						if(m_ClearFlag&enTCF_STENCIL)
							clearFlag		|=	D3D11_CLEAR_STENCIL;
						if(clearFlag!=0){
							pContext->ClearDepthStencilView(pDSV,clearFlag,1.0f,0);
						}
					}

				}
				


				pContext->OMSetRenderTargets(8,pRT,pDSV);
				D3D11_VIEWPORT	v;
				v.Width			=	m_vecTexture[0]->GetWidth();
				v.Height		=	m_vecTexture[0]->GetHeight();
				v.TopLeftX		=	0;
				v.TopLeftY		=	0;
				v.MinDepth		=	0.0f;
				v.MaxDepth		=	1.0f;
				pContext->RSSetViewports(1,&v);

				
				return true;
			}
	
			void Target11::SetRenderObject( MovableObject* pObject ){
				//m_pTargetObject	=	pObject;
			}
	
			void Target11::ReCreate( Info& info ){

	
			}
	
			MovableObject* Target11::GetRenderObject(){
				return	NULL;//m_pTargetObject;
			}

			Air::U1 Target11::CreateDepthStencil(){
				if(m_Info.bUseDepth	&&	m_Info.extraDepth	==	NULL){
					U32	uiWidth		=	m_vecTexture[0]->GetWidth();
					U32	uiHeight	=	m_vecTexture[0]->GetHeight();

					D3D11_TEXTURE2D_DESC desc;
					desc.Width				= uiWidth;
					desc.Height				= uiHeight;
					desc.MipLevels			= 1;
					desc.ArraySize			= 1;
					desc.Format				= DXGI_FORMAT_R24G8_TYPELESS;
					desc.SampleDesc.Count	= 1;
					desc.SampleDesc.Quality	=	0;
					desc.Usage				= D3D11_USAGE_DEFAULT;
					desc.BindFlags			= D3D11_BIND_SHADER_RESOURCE	|	D3D11_BIND_DEPTH_STENCIL;
					desc.CPUAccessFlags		= 0;
					desc.MiscFlags			=	0;


					HRESULT	hr	=	((DxDevice*)pDevice->GetDevice())->CreateTexture2D( &desc, NULL, &m_pDepthBuffer );

					D3D11_SHADER_RESOURCE_VIEW_DESC	srvDesc;
					memset(&srvDesc,0,sizeof(srvDesc));

					srvDesc.ViewDimension				=	D3D11_SRV_DIMENSION_TEXTURE2D;
					srvDesc.Format						=	DXGI_FORMAT_R24_UNORM_X8_TYPELESS 
						;
					srvDesc.Texture2D.MostDetailedMip	= 0;
					srvDesc.Texture2D.MipLevels			= 1;

					hr	=	((DxDevice*)pDevice->GetDevice())->CreateShaderResourceView( m_pDepthBuffer, &srvDesc, &m_pDepthBufferSRV );


					D3D11_DEPTH_STENCIL_VIEW_DESC	dsvDesc;
					memset(&dsvDesc,0,sizeof(dsvDesc));
					dsvDesc.Format					=	DXGI_FORMAT_D24_UNORM_S8_UINT;
					dsvDesc.ViewDimension			=	D3D11_DSV_DIMENSION_TEXTURE2D;
					dsvDesc.Texture2D.MipSlice		=	0;

					hr	=	((DxDevice*)pDevice->GetDevice())->CreateDepthStencilView( m_pDepthBuffer, &dsvDesc, &m_pDepthBufferDSV );
				}
				return	true;
			}

			Air::U1 Target11::DestroyDepthStencil(){
				SAFE_RELEASE(m_pDepthBufferDSV);
				SAFE_RELEASE(m_pDepthBufferSRV);
				SAFE_RELEASE(m_pDepthBuffer);
				return	true;
			}

			void* Target11::GetDepthRTV()
			{
				return	m_pDepthBufferDSV;
			}

			void* Target11::GetDepthSRV()
			{
				return	m_pDepthBufferSRV;
			}

			void* Target11::GetDepthBuffer()
			{
				return	m_pDepthBuffer;
			}

			Air::U1 Target11::Create()
			{
				Target::Create();
				CreateDepthStencil();
				return	true;
			}

			void Target11::OnMainWindowSize( Window* pMainWindow )
			{
				Target::OnMainWindowSize(pMainWindow);
				if(m_Info.vecTextureInfo[0].fScreenScale	>	0.0f){
					DestroyDepthStencil();
					CreateDepthStencil();
				}
			}

			Air::U1 Target11::AfterUpdate()
			{
				U32	uiSize	=	m_vecTexture.size();
				for(U32	i=0;i<uiSize;i++){
					if(m_vecTexture[i]->IsAutoMipmap())
						m_vecTexture[i]->GenMipMap();
				}
				D3DPERF_EndEvent();
				return		true;
			}

		}
	}
};