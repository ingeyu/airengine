#include "MTSwapChain9.h"
#include "MTDevice9.h"

MT_IDirect3DSwapChain9::MT_IDirect3DSwapChain9(MT_IDirect3DDevice9* pMT_IDirect3DDevice9,IDirect3DSwapChain9* pIDirect3DSwapChain9){
	m_pIDirect3DSwapChain9	=	pIDirect3DSwapChain9;
	m_pIDirect3DSwapChain9->AddRef();

	m_pMT_IDirect3DDevice9	=	pMT_IDirect3DDevice9;
	m_pMT_IDirect3DDevice9->AddRef();
}
MT_IDirect3DSwapChain9::~MT_IDirect3DSwapChain9(){
	m_pIDirect3DSwapChain9->Release();
	m_pMT_IDirect3DDevice9->Release();
};
HRESULT	MT_IDirect3DSwapChain9::Present(THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags){
	return		m_pMT_IDirect3DDevice9->SwapChain_Present(m_pIDirect3DSwapChain9,pSourceRect,pDestRect,hDestWindowOverride,pDirtyRegion,dwFlags);
}

HRESULT	MT_IDirect3DSwapChain9::GetFrontBufferData(THIS_ MT_IDirect3DSurface9* pDestSurface){
	
	return	S_OK;
};
HRESULT	MT_IDirect3DSwapChain9::GetBackBuffer(THIS_ UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,MT_IDirect3DSurface9** ppBackBuffer){

	return	S_OK;
};
HRESULT	MT_IDirect3DSwapChain9::GetRasterStatus(THIS_ D3DRASTER_STATUS* pRasterStatus){
	return	m_pIDirect3DSwapChain9->GetRasterStatus(pRasterStatus);
};
HRESULT	MT_IDirect3DSwapChain9::GetDisplayMode(THIS_ D3DDISPLAYMODE* pMode){
	return	m_pIDirect3DSwapChain9->GetDisplayMode(pMode);
};
HRESULT	MT_IDirect3DSwapChain9::GetDevice(THIS_ MT_IDirect3DDevice9** ppDevice){
	*ppDevice	=	m_pMT_IDirect3DDevice9;
	m_pMT_IDirect3DDevice9->AddRef();
	return	S_OK;;
};
HRESULT	MT_IDirect3DSwapChain9::GetPresentParameters(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters){
	return	m_pIDirect3DSwapChain9->GetPresentParameters(pPresentationParameters);
};