#include "MTQuery9.h"
#include "MTDevice9.h"

MT_IDirect3DQuery9::MT_IDirect3DQuery9(MT_IDirect3DDevice9*	pMT_IDirect3DDevice9,IDirect3DQuery9* pIDirect3DQuery9)
{
	m_pIDirect3DQuery9	=	pIDirect3DQuery9;
	m_pIDirect3DQuery9->AddRef();

	m_pMT_IDirect3DDevice9	=	pMT_IDirect3DDevice9;
	m_pMT_IDirect3DDevice9->AddRef();
}
MT_IDirect3DQuery9::~MT_IDirect3DQuery9(){
	m_pIDirect3DQuery9->Release();
	m_pMT_IDirect3DDevice9->Release();
}
HRESULT	MT_IDirect3DQuery9::GetDevice(THIS_ MT_IDirect3DDevice9** ppDevice){
	*ppDevice	=	m_pMT_IDirect3DDevice9;
	m_pMT_IDirect3DDevice9->AddRef();
	return	S_OK;;
}
HRESULT	MT_IDirect3DQuery9::Issue(THIS_ DWORD dwIssueFlags){

	return	S_OK;
}
HRESULT	MT_IDirect3DQuery9::GetData(THIS_ void* pData,DWORD dwSize,DWORD dwGetDataFlags){

	return	S_OK;
}