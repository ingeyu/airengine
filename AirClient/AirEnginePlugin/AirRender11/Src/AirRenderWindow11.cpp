#include "AirRenderWindow11.h"
#include "AirCommonWindow.h"
#include "AirRenderDevice11.h"
namespace	Air{
	namespace	Client{
		extern	Render::Device11*	pDevice;
		namespace	Render{



			Window11::Window11( CAString& strName,Info* pInfo ):Window(strName,pInfo)
			{

				m_pSwapChain		=	NULL;
				m_pBackBuffer		=	NULL;
				m_pDepthBuffer		=	NULL;
				m_pBackBufferRTV	=	NULL;
				m_pDepthBufferDSV	=	NULL;
				m_pBackBufferSRV	=	NULL;
				m_pDepthBufferSRV	=	NULL;
				//m_hWindow			=	NULL;

				memset(&m_SwapChainDesc,0,sizeof(m_SwapChainDesc));
			}

			Air::U1 Window11::Create()
			{

				Window::Create();

				CreateSwapChain();

				if(m_Info.bUseDepth){
					if(m_Info.extraDepth==NULL)
						CreateDepthStencil();
				}
				

				return	true;
			}

			Air::U1 Window11::Destroy()
			{


				if(m_Info.bUseDepth){
					DestroyDepthStencil();
				}
				DestroySwapChain();

				Window::Destroy();
				return	true;
			}
			Air::U1 Window11::CreateSwapChain()
			{
				HWND	hWindow	=	m_WndHandle;
				if(m_Info.extraWnd){
					hWindow		=	m_Info.extraWnd;
				}
				RECT	rect;
				GetClientRect(hWindow,&rect);
				U32		uiWidth		=	rect.right	-	rect.left;
				U32		uiHeight	=	rect.bottom	-	rect.top;

				m_SwapChainDesc.BufferCount			= 1;
				m_SwapChainDesc.BufferDesc.Width	= uiWidth;
				m_SwapChainDesc.BufferDesc.Height	= uiHeight;
				m_SwapChainDesc.BufferDesc.Format	= DXGI_FORMAT_R8G8B8A8_UNORM;
				m_SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
				m_SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
				m_SwapChainDesc.BufferUsage	= DXGI_USAGE_RENDER_TARGET_OUTPUT;
				m_SwapChainDesc.OutputWindow = hWindow;
				m_SwapChainDesc.SampleDesc.Count = 1;
				m_SwapChainDesc.SampleDesc.Quality = 0;
				m_SwapChainDesc.Windowed = TRUE;

				HRESULT	hr;
				if(pDevice->GetFactory1()!=NULL)
					hr	=	pDevice->GetFactory1()->CreateSwapChain((DxDevice*)pDevice->GetDevice(),&m_SwapChainDesc,&m_pSwapChain);
				else
					hr	=	pDevice->GetFactory()->CreateSwapChain((DxDevice*)pDevice->GetDevice(),&m_SwapChainDesc,&m_pSwapChain);

				m_pSwapChain->GetDesc(&m_SwapChainDesc);
				// Get a pointer to the back buffer
				hr = m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&m_pBackBuffer );

				// Create a render-target view
				hr = ((DxDevice*)pDevice->GetDevice())->CreateRenderTargetView( m_pBackBuffer, NULL,&m_pBackBufferRTV );

				D3D11_SHADER_RESOURCE_VIEW_DESC	srvDesc;
				memset(&srvDesc,0,sizeof(srvDesc));
				srvDesc.ViewDimension				=	D3D11_SRV_DIMENSION_TEXTURE2D;
				srvDesc.Format						=	DXGI_FORMAT_B8G8R8A8_UNORM;
				srvDesc.Texture2D.MostDetailedMip	= 0;
				srvDesc.Texture2D.MipLevels			= 1;

				m_Info.vecTextureInfo[0].width		=	m_SwapChainDesc.BufferDesc.Width;
				m_Info.vecTextureInfo[0].height		=	m_SwapChainDesc.BufferDesc.Height;


				// Create a render-target view
				//hr = ((DxDevice*)pDevice->GetDevice())->CreateShaderResourceView( m_pBackBuffer,&srvDesc,&m_pBackBufferSRV );

				return	true;
			}
			Air::U1 Window11::DestroySwapChain()
			{
				SAFE_RELEASE(m_pBackBufferSRV);
				SAFE_RELEASE(m_pBackBufferRTV);
				SAFE_RELEASE(m_pBackBuffer);
				SAFE_RELEASE(m_pSwapChain);
				return	true;
			}

			Air::U1 Window11::BeforeUpdate( U32 uiFace /*= 0*/ )
			{
				D3DPERF_BeginEvent(0,L"RenderWindow");

				Target::BeforeUpdate(uiFace);

				DxContext*	pContext	=	(DxContext*)pDevice->GetContext();
				if(m_ClearFlag&enTCF_TARGET){
					pContext->ClearRenderTargetView(m_pBackBufferRTV,(float*)&m_Info.clearColor);
				}
				

				DxDSV*	pDSV	=	m_pDepthBufferDSV;
				if(m_Info.bUseDepth){

					U32	Flag	=	0;
					if(m_ClearFlag&enTCF_ZBUFFER){
						Flag	|=		D3D11_CLEAR_DEPTH;
					}
					if(m_ClearFlag&enTCF_STENCIL){
						Flag	|=		D3D11_CLEAR_STENCIL;
					}
					if(m_Info.extraDepth!=NULL){
						pDSV	=	(DxDSV*)m_Info.extraDepth->GetDepthRTV();
					}
					if(Flag!=0&&pDSV!=NULL){
						pContext->ClearDepthStencilView(pDSV,Flag,1.0f,0);
					}
				}

				pContext->OMSetRenderTargets(1,&m_pBackBufferRTV,pDSV);


				return	true;
			}


			Air::U1 Window11::AfterUpdate()
			{
				m_pSwapChain->Present(0,0);
				D3DPERF_EndEvent();
				return	true;
			}

			Air::U1 Window11::CreateDepthStencil()
			{

				D3D11_TEXTURE2D_DESC desc;
				desc.Width				= m_SwapChainDesc.BufferDesc.Width;
				desc.Height				= m_SwapChainDesc.BufferDesc.Height;
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

				return	true;
			}

			Air::U1 Window11::DestroyDepthStencil()
			{
				SAFE_RELEASE(m_pDepthBufferDSV);
				SAFE_RELEASE(m_pDepthBufferSRV);
				SAFE_RELEASE(m_pDepthBuffer)
				return	true;
			}

			void* Window11::GetRTV(U32	uiIdx)
			{
				return	m_pBackBufferRTV;
			}

			void* Window11::GetSRV(U32	uiIdx)
			{
				return	m_pBackBufferSRV;
			}

			void* Window11::GetDepthRTV()
			{
				return	m_pDepthBufferDSV;
			}

			void* Window11::GetDepthSRV()
			{
				return	m_pDepthBufferSRV;
			}

			void* Window11::GetBackBuffer(U32	uiIdx)
			{
				return	m_pBackBuffer;
			}

			void* Window11::GetDepthBuffer()
			{
				return	m_pDepthBuffer;
			}

			void Window11::OnSize()
			{
				HWND	hWindow	=	m_WndHandle;
				if(m_Info.extraWnd){
					hWindow		=	m_Info.extraWnd;
				}
				RECT rect;
				GetClientRect(hWindow,&rect);
				U32	uiWidth		=	rect.right	-	rect.left;
				U32	uiHeight	=	rect.bottom	-	rect.top;
				if(	uiWidth		!=	m_SwapChainDesc.BufferDesc.Width	||
					uiHeight	!=	m_SwapChainDesc.BufferDesc.Height)
				{

					DestroyDepthStencil();
					SAFE_RELEASE(m_pBackBuffer);
					SAFE_RELEASE(m_pBackBufferRTV);
					SAFE_RELEASE(m_pBackBufferSRV);

					m_SwapChainDesc.BufferDesc.Width	=	0;//uiWidth;
					m_SwapChainDesc.BufferDesc.Height	=	0;//uiHeight;
					HRESULT	hr	=	m_pSwapChain->ResizeBuffers(1,uiWidth,uiHeight,m_SwapChainDesc.BufferDesc.Format,0);
					m_pSwapChain->GetDesc(&m_SwapChainDesc);

					hr = m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&m_pBackBuffer );

					// Create a render-target view
					hr = ((DxDevice*)pDevice->GetDevice())->CreateRenderTargetView( m_pBackBuffer, NULL,&m_pBackBufferRTV );


					if(m_Info.bUseDepth	&&	m_Info.extraDepth==NULL)
						CreateDepthStencil();

					RenderSystem::GetSingleton()->OnWindowChange(this);
				}
			}

			Air::U32 Window11::GetWidth(){
				return	m_SwapChainDesc.BufferDesc.Width;
			}	

			Air::U32 Window11::GetHeight(){
				return	m_SwapChainDesc.BufferDesc.Height;
			}

			Air::U32 Window11::GetDepth(){
				return	1;
			}

		}
	}
}