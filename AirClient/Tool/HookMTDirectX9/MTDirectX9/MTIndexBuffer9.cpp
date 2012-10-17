#include "MTIndexBuffer9.h"
#include "MTDevice9.h"


MT_IDirect3DIndexBuffer9::MT_IDirect3DIndexBuffer9(MT_IDirect3DDevice9* pMT_IDirect3DDevice9,IDirect3DIndexBuffer9* pIDirect3DIndexBuffer9)
:MT_IDirect3DResource9(pMT_IDirect3DDevice9,pIDirect3DIndexBuffer9)
{
	m_pIDirect3DIndexBuffer9	=	pIDirect3DIndexBuffer9;
}

HRESULT	MT_IDirect3DIndexBuffer9::Lock(THIS_ UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags){
	return	m_pMT_IDirect3DDevice9->IndexBuffer_Lock(m_pIDirect3DIndexBuffer9,OffsetToLock,SizeToLock,ppbData,Flags);
}
HRESULT	MT_IDirect3DIndexBuffer9::Unlock(THIS){
	return	m_pMT_IDirect3DDevice9->IndexBuffer_Unlock(m_pIDirect3DIndexBuffer9);
}