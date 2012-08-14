#include "MTResource9.h"
#include "MTDevice9.h"

MT_IDirect3DResource9::MT_IDirect3DResource9(MT_IDirect3DDevice9* pMT_IDirect3DDevice9,IDirect3DResource9* pIDirect3DResource9)
{
	m_pIDirect3DResource9	=	pIDirect3DResource9;
	m_pIDirect3DResource9->AddRef();

	m_pMT_IDirect3DDevice9	=	pMT_IDirect3DDevice9;
	m_pMT_IDirect3DDevice9->AddRef();
}
MT_IDirect3DResource9::~MT_IDirect3DResource9(){
	m_pIDirect3DResource9->Release();
	m_pMT_IDirect3DDevice9->Release();
};

HRESULT	MT_IDirect3DResource9::GetDevice(THIS_ MT_IDirect3DDevice9** ppDevice){
	*ppDevice	=	m_pMT_IDirect3DDevice9;
	m_pMT_IDirect3DDevice9->AddRef();
	return	S_OK;
}