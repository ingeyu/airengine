#include "MTSurface9.h"
#include "MTDevice9.h"


MT_IDirect3DSurface9::MT_IDirect3DSurface9(MT_IDirect3DDevice9*	pMT_IDirect3DDevice9,IDirect3DSurface9* pIDirect3DSurface9)
:MT_IDirect3DResource9(pMT_IDirect3DDevice9,pIDirect3DSurface9)
{
	m_pIDirect3DSurface9	=	pIDirect3DSurface9;
};

HRESULT	MT_IDirect3DSurface9::LockRect(THIS_ D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags){

	return	m_pMT_IDirect3DDevice9->Surface_LockRect(m_pIDirect3DSurface9,pLockedRect,pRect,Flags);
}
HRESULT	MT_IDirect3DSurface9::UnlockRect(THIS){

	return	m_pMT_IDirect3DDevice9->Surface_UnlockRect(m_pIDirect3DSurface9);
}