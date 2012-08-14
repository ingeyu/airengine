#include "MTVolume9.h"
#include "MTDevice9.h"

MT_IDirect3DVolume9::MT_IDirect3DVolume9(MT_IDirect3DDevice9* pMT_IDirect3DDevice9,IDirect3DVolume9* pIDirect3DVolume9){
	m_pIDirect3DVolume9	=	pIDirect3DVolume9;
	m_pIDirect3DVolume9->AddRef();

	m_pMT_IDirect3DDevice9	=	pMT_IDirect3DDevice9;
	m_pMT_IDirect3DDevice9->AddRef();
}
MT_IDirect3DVolume9::~MT_IDirect3DVolume9(){
	m_pIDirect3DVolume9->Release();
	m_pMT_IDirect3DDevice9->Release();
}

HRESULT	MT_IDirect3DVolume9::GetDevice(THIS_ MT_IDirect3DDevice9** ppDevice){
	*ppDevice	=	m_pMT_IDirect3DDevice9;
	m_pMT_IDirect3DDevice9->AddRef();
	return	S_OK;
}
HRESULT	MT_IDirect3DVolume9::SetPrivateData(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags){
	return	m_pIDirect3DVolume9->SetPrivateData(refguid,pData,SizeOfData,Flags);
};
HRESULT	MT_IDirect3DVolume9::GetPrivateData(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData){
	return	m_pIDirect3DVolume9->GetPrivateData(refguid,pData,pSizeOfData);
};
HRESULT	MT_IDirect3DVolume9::FreePrivateData(THIS_ REFGUID refguid){
	return	m_pIDirect3DVolume9->FreePrivateData(refguid);
};
HRESULT	MT_IDirect3DVolume9::GetContainer(THIS_ REFIID riid,void** ppContainer){
	return	m_pIDirect3DVolume9->GetContainer(riid,ppContainer);
};
HRESULT	MT_IDirect3DVolume9::GetDesc(THIS_ D3DVOLUME_DESC *pDesc){
	return	m_pIDirect3DVolume9->GetDesc(pDesc);
};
HRESULT	MT_IDirect3DVolume9::LockBox(THIS_ D3DLOCKED_BOX * pLockedVolume,CONST D3DBOX* pBox,DWORD Flags){
	return	m_pMT_IDirect3DDevice9->Volume_LockBox(m_pIDirect3DVolume9,pLockedVolume,pBox,Flags);
};
HRESULT	MT_IDirect3DVolume9::UnlockBox(THIS){
	return	m_pMT_IDirect3DDevice9->Volume_UnlockBox(m_pIDirect3DVolume9);
};