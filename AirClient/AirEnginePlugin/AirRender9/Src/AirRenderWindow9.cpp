#include "AirRenderWindow9.h"
#include "AirRenderSystem9.h"
namespace	Air{
	namespace	Client{
		namespace	Render{


			Window9::Window9( CAString& strName,Info* pInfo ):Window(strName,pInfo){
				m_pD3D		=	NULL;
				m_pDevice	=	NULL;
			}

			Air::U1 Window9::Create(){
				CreateWin32Window();


				System*	pSys	=	static_cast<System*>(m_pFactoryMgr);
				m_pDevice		=	pSys->GetDevice();
				m_pD3D			=	pSys->GetD3D();

				Texture::Info&	info	=	m_Info.vecTextureInfo[0];

				HWND	hWindow	=	m_WndHandle;
				if(m_Info.extraWnd!=NULL){
					hWindow		=	m_Info.extraWnd;
				}
				U32	uiWidth		=	info.width;
				U32	uiHeight	=	info.height;

				if(info.fScreenScale>0.0f){

				}

				if(!m_Info.bFullScreen){
					uiWidth		=	0;
					uiHeight	=	0;
				}



				m_D3D9Param.BackBufferWidth				=	uiWidth;
				m_D3D9Param.BackBufferHeight			=	uiHeight;
				m_D3D9Param.BackBufferCount				=	1;
				m_D3D9Param.BackBufferFormat			=	(D3DFORMAT)info.format;
				m_D3D9Param.EnableAutoDepthStencil		=	FALSE;
				m_D3D9Param.AutoDepthStencilFormat		=	D3DFMT_D24S8;
				m_D3D9Param.MultiSampleType				=	D3DMULTISAMPLE_NONE;
				m_D3D9Param.MultiSampleQuality			=	0;
				m_D3D9Param.hDeviceWindow				=	hWindow;
				m_D3D9Param.FullScreen_RefreshRateInHz	=	60;
				m_D3D9Param.PresentationInterval		=	D3DPRESENT_DONOTWAIT;
				m_D3D9Param.Windowed					=	m_Info.bFullScreen;
				m_D3D9Param.SwapEffect					=	D3DSWAPEFFECT_DISCARD;
				m_D3D9Param.Flags						=	0;

				if(m_pDevice==NULL){
					m_bMainWindow	=	true;
					CreateD3D();
				}else{
					CreateSwapChain();
				}
				return	true;
			}

			Air::U1 Window9::Destroy(){

				if(m_pSwapChain!=NULL){
					DestroySwapChain();
				}else{
					DestroyD3D();
				}

				DestroyWin32Window();
				return	true;
			}

			Air::U1 Window9::CreateD3D(){
				U32			AdapterToUse		=	D3DADAPTER_DEFAULT;
				D3DDEVTYPE	DeviceType			=	D3DDEVTYPE_HAL;
#define USE_PERFHUD
#ifdef	USE_PERFHUD
				// Look for 'NVIDIA PerfHUD' adapter
				// If it is present, override default settings
				for (U32 Adapter=0;Adapter<m_pD3D->GetAdapterCount();Adapter++)
				{
					D3DADAPTER_IDENTIFIER9 Identifier;
					HRESULT Res;
					Res = m_pD3D->GetAdapterIdentifier(Adapter,0,&Identifier);
					if (strstr(Identifier.Description,"PerfHUD") != 0)
					{
						AdapterToUse=Adapter;
						DeviceType=D3DDEVTYPE_REF;
						break;
					}
				}
#endif
				HRESULT	hr	=	S_OK;
				DWORD	flag	=	0;
				
#ifndef		NOUSE_FPU
				flag	|=	D3DCREATE_FPU_PRESERVE;
#endif
#ifndef		NOUSE_MULTITHREAD
				flag	|=	D3DCREATE_MULTITHREADED;
#endif
				HWND	hWindow	=	m_WndHandle;
				if(m_Info.extraWnd!=NULL)
					hWindow	=	m_Info.extraWnd;

				hr	=	m_pD3D->CreateDevice(	AdapterToUse,
												DeviceType,
												hWindow,
												D3DCREATE_HARDWARE_VERTEXPROCESSING	|	D3DCREATE_PUREDEVICE	|	flag,
												&m_D3D9Param,
												&m_pDevice);
				if(FAILED(hr)){
					hr	=	m_pD3D->CreateDevice(	AdapterToUse,
													DeviceType,
													hWindow,
													flag,
													&m_D3D9Param,
													&m_pDevice);
					if(FAILED(hr)){
						hr	=	m_pD3D->CreateDevice(	AdapterToUse,
														D3DDEVTYPE_REF,
														hWindow,
														flag,
														&m_D3D9Param,
														&m_pDevice);
						if(FAILED(hr)){
							return	false;
						}
					}
				}

				hr	=	m_pDevice->GetRenderTarget(0,&m_pBackBuffer);

				if(m_bMainWindow){
					System*	pSys	=	static_cast<System*>(m_pFactoryMgr);
					D3DSURFACE_DESC	desc;
					m_pBackBuffer->GetDesc(&desc);

					pSys->m_uiMainWindowWidth	=	desc.Width;
					pSys->m_uiMainWindowHeight	=	desc.Height;
				}

				return	true;
			}

			Air::U1 Window9::CreateSwapChain(){

				HRESULT	hr	=	m_pDevice->CreateAdditionalSwapChain(&m_D3D9Param,&m_pSwapChain);
				if(FAILED(hr)){
					return	false;
				}
				hr	=	m_pSwapChain->GetBackBuffer(0,D3DBACKBUFFER_TYPE_MONO,&m_pBackBuffer);


				return	true;
			}

			Air::U1 Window9::DestroyD3D(){
				SAF_R(m_pBackBuffer);
				SAF_R(m_pDevice);

				return	true;
			}

			Air::U1 Window9::DestroySwapChain(){
				SAF_R(m_pBackBuffer);
				SAF_R(m_pSwapChain);
				return	true;
			}

			Air::U1 Window9::Reset(){
				ISystem*	pSys	=	static_cast<ISystem*>(m_pFactoryMgr);
				pSys->OnD3DLostDevice();

				if(!m_Info.bFullScreen){
					m_D3D9Param.BackBufferWidth		=	0;
					m_D3D9Param.BackBufferHeight	=	0;
				}else{
					m_D3D9Param.BackBufferWidth		=	m_Info.vecTextureInfo[0].width;
					m_D3D9Param.BackBufferHeight	=	m_Info.vecTextureInfo[0].height;
				}

				m_D3D9Param.Windowed				=	!m_Info.bFullScreen;

				SAF_R(m_pBackBuffer);

				HRESULT	hr	=	m_pDevice->Reset(&m_D3D9Param);
				switch(hr){
					case	S_OK:{
						m_pDevice->GetRenderTarget(0,&m_pBackBuffer);
						DxSurfaceDesc	desc;
						m_pBackBuffer->GetDesc(&desc);
						m_Info.vecTextureInfo[0].width	=	desc.Width;
						m_Info.vecTextureInfo[0].height	=	desc.Height;

						pSys->m_uiMainWindowWidth		=	desc.Width;
						pSys->m_uiMainWindowHeight		=	desc.Height;

						pSys->OnD3DResetDevice();

						break;}
					case	D3DERR_DEVICELOST:{
						pSys->NotifyDeviceLost();
						break;}
					case	D3DERR_DEVICENOTRESET:{
						return	false;
						break;}
					case	D3DERR_DEVICEREMOVED:{

						break;}
				}

				return	true;
			}

			void Window9::OnLostDevice(){
				if(!m_bMainWindow){
					DestroySwapChain();
				}
			}

			void Window9::OnResetDevice(){
				if(!m_bMainWindow){
					CreateSwapChain();
				}
			}

			Air::U1 Window9::BeforeUpdate(){
				System*	pSys	=	static_cast<System*>(m_pFactoryMgr);

				if(m_bMainWindow){
					
					if(pSys->IsDeviceLost()){
						Reset();
					}

					HRESULT	hr	=	m_pDevice->TestCooperativeLevel();
					switch(hr){
						case	D3DERR_DEVICELOST:{
							pSys->NotifyDeviceLost();
							return	false;
							break;}
						case	D3DERR_DEVICENOTRESET:{
							Reset();
							break;}
					}
				}

				DWORD clearFlag	=	D3DCLEAR_TARGET;


				pSys->SetRenderTarget(0,m_pBackBuffer);
				pSys->SetRenderTarget(1,NULL);
				pSys->SetRenderTarget(2,NULL);
				pSys->SetRenderTarget(3,NULL);
				

				IDirect3DSurface9*	pDepthStencil	=	(IDirect3DSurface9*)GetDepthStencil();
				if(pDepthStencil!=NULL){
					clearFlag		|=	D3DCLEAR_ZBUFFER;
					clearFlag		|=	D3DCLEAR_STENCIL;
				}

				pSys->SetDepthStencilSurface(pDepthStencil);

				if(m_ClearFlag!=0){
					DWORD	clearColor	=	D3DCOLOR_COLORVALUE(m_Info.clearColor.x,
																m_Info.clearColor.y,
																m_Info.clearColor.z,
																m_Info.clearColor.w);
					m_pDevice->Clear(0,0,m_ClearFlag&clearFlag,clearColor,1.0f,0);
				}

				if(FAILED(m_pDevice->BeginScene()))
					return	false;
				return	true;
			}

			Air::U1 Window9::AfterUpdate(){
				m_pDevice->EndScene();
				if(m_bMainWindow){
					m_pDevice->Present(0,0,0,0);
				}else{
					m_pSwapChain->Present(0,0,0,0,0);
				}
				return	true;
			}
		}
	}
}