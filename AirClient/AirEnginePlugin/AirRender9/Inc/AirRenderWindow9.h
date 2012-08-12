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
#ifndef AIRRENDERWINDOW9_HEAD_FILE
#define AIRRENDERWINDOW9_HEAD_FILE

#include "AirRenderHeader9.h"
#include "AirRenderWindow.h"

namespace	Air{
	namespace Client{
	
		namespace	Render{
			class	Window9	:	
				public	Window{
			public:
				Window9(CAString&	strName,Info*	pInfo);

				virtual	U1	Create();
				virtual	U1	Destroy();

				U1			CreateD3D();
				U1			CreateSwapChain();
				U1			DestroyD3D();
				U1			DestroySwapChain();

				virtual	U1			BeforeUpdate();
				virtual	U1			AfterUpdate();

				virtual	void		OnLostDevice();
				virtual	void		OnResetDevice();

				U1			Reset();

				D3DPRESENT_PARAMETERS	m_D3D9Param;
				DxDevice*				m_pDevice;
				IDirect3D9*				m_pD3D;
				IDirect3DSwapChain9*	m_pSwapChain;
				DxSurface*				m_pBackBuffer;
				U1						m_bMainWindow;
			};
		}
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // AIRRENDERWINDOW9_HEAD_FILE