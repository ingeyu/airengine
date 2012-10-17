#include "MTBaseTexture9.h"
#include "MTDevice9.h"

MT_IDirect3DBaseTexture9::MT_IDirect3DBaseTexture9(MT_IDirect3DDevice9* pMT_IDirect3DDevice9,IDirect3DBaseTexture9* pIDirect3DBaseTexture9)
:MT_IDirect3DResource9(pMT_IDirect3DDevice9,pIDirect3DBaseTexture9)
{
	m_pIDirect3DBaseTexture9	=	pIDirect3DBaseTexture9;
}

HRESULT	MT_IDirect3DBaseTexture9::SetAutoGenFilterType(THIS_ D3DTEXTUREFILTERTYPE FilterType){
	m_pMT_IDirect3DDevice9->BaseTexture_SetAutoGenFilterType(m_pIDirect3DBaseTexture9,FilterType);
	return	S_OK;
}

void	MT_IDirect3DBaseTexture9::GenerateMipSubLevels(THIS){
	m_pMT_IDirect3DDevice9->BaseTexture_GenerateMipSubLevels(m_pIDirect3DBaseTexture9);
}