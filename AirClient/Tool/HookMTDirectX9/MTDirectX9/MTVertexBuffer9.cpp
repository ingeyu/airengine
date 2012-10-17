#include "MTVertexBuffer9.h"
#include "MTDevice9.h"
MT_IDirect3DVertexBuffer9::MT_IDirect3DVertexBuffer9(MT_IDirect3DDevice9* pMT_IDirect3DDevice9,IDirect3DVertexBuffer9* pIDirect3DVertexBuffer9)
:MT_IDirect3DResource9(pMT_IDirect3DDevice9,pIDirect3DVertexBuffer9)
{
	m_pIDirect3DVertexBuffer9	=	pIDirect3DVertexBuffer9;
}

HRESULT	MT_IDirect3DVertexBuffer9::Lock(THIS_ UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags){
	return	m_pMT_IDirect3DDevice9->VertexBuffer_Lock(m_pIDirect3DVertexBuffer9,OffsetToLock,SizeToLock,ppbData,Flags);
}
HRESULT	MT_IDirect3DVertexBuffer9::Unlock(THIS){
	return	m_pMT_IDirect3DDevice9->VertexBuffer_Unlock(m_pIDirect3DVertexBuffer9);
}