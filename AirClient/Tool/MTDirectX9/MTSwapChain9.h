#ifndef MTSWAPCHAIN9_HEAD_FILE
#define	MTSWAPCHAIN9_HEAD_FILE

#include "MTHeader.h"

class MT_IDirect3DSwapChain9	:	public	MT_IUnknown
{
public:
    /*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj){
		return	m_pIDirect3DSwapChain9->QueryInterface(riid,ppvObj);
	};


    /*** IDirect3DSwapChain9 methods ***/
    STDMETHOD(Present)(THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags);
    STDMETHOD(GetFrontBufferData)(THIS_ MT_IDirect3DSurface9* pDestSurface) ;
    STDMETHOD(GetBackBuffer)(THIS_ UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,MT_IDirect3DSurface9** ppBackBuffer) ;
    STDMETHOD(GetRasterStatus)(THIS_ D3DRASTER_STATUS* pRasterStatus) ;
    STDMETHOD(GetDisplayMode)(THIS_ D3DDISPLAYMODE* pMode) ;
    STDMETHOD(GetDevice)(THIS_ MT_IDirect3DDevice9** ppDevice) ;
    STDMETHOD(GetPresentParameters)(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters) ;
public:
	MT_IDirect3DSwapChain9(MT_IDirect3DDevice9* pMT_IDirect3DDevice9,IDirect3DSwapChain9* pIDirect3DSwapChain9);
	virtual	~MT_IDirect3DSwapChain9();
public:
	MT_IDirect3DDevice9*	m_pMT_IDirect3DDevice9;
	IDirect3DSwapChain9*	m_pIDirect3DSwapChain9;
};


#endif