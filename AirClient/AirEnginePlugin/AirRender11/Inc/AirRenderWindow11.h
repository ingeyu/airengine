/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InterfalHell	Xinhe
 \date      2011/09/12
 \version   ver 0.6.0.0
 \filepath  f:\Air\trunk\AirClient\AirEnginePlugin\AirRender9\Inc
 \filename  AirRenderWindow9.h
 \note     
       
 \attention:
			
 \remarks    created by InterfalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef AIRRENDERWINDOW11_HEAD_FILE
#define AIRRENDERWINDOW11_HEAD_FILE

#include "AirRenderHeader11.h"
#include "AirRenderWindow.h"

namespace	Air{
	namespace Engine{
	
		namespace	Render{
			class	Device11;
			class	Window11;
// 			struct WindowInfo{
// 				U32			uiWidth;
// 				U32			uiHeight;
// 				float		fScale;
// 				HWND		extraWindow;
// 				HWND		parentWindow;
// 				U32			format;
// 				U32			depthformat;
// 				Window11*	pExtraDepth;
// 				U1			bUseDepth;
// 				Float4		clearColor;
// 				U32			clearFlag;
// 			};
			
			class	Window11	:	
				public	Window{
			public:
				Window11(CAString&	strName,Info*	pInfo);

				virtual	U1			Create();
				virtual	U1			Destroy();

				U1					CreateSwapChain();
				U1					DestroySwapChain();
				U1					CreateDepthStencil();
				U1					DestroyDepthStencil();

				virtual	U1			BeforeUpdate(U32	uiFace	=	0);
				virtual	U1			AfterUpdate(U1 bSwapBuffer);

				virtual	U32			GetWidth();
				virtual	U32			GetHeight();
				virtual	U32			GetDepth();

				virtual		void	OnSize();

				virtual		void*	GetRTV(U32	uiIdx);
				virtual		void*	GetSRV(U32	uiIdx);
				virtual		void*	GetDepthRTV();
				virtual		void*	GetDepthSRV();
				virtual		void*	GetBackBuffer(U32	uiIdx);
				virtual		void*	GetDepthBuffer();

				DxSwapChain*			m_pSwapChain;
				DxTexture*				m_pBackBuffer;
				DxTexture*				m_pDepthBuffer;
				DxRTV*					m_pBackBufferRTV;
				DxDSV*					m_pDepthBufferDSV;
				DxSRV*					m_pBackBufferSRV;
				DxSRV*					m_pDepthBufferSRV;

				DXGI_SWAP_CHAIN_DESC	m_SwapChainDesc;
			};
		}
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // AIRRENDERWINDOW9_HEAD_FILE