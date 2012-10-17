#include "MTTexture9.h"
#include "MTDevice9.h"

MT_IDirect3DTexture9::MT_IDirect3DTexture9(MT_IDirect3DDevice9* pMT_IDirect3DDevice9,IDirect3DTexture9* pIDirect3DTexture9)
:MT_IDirect3DBaseTexture9(pMT_IDirect3DDevice9,pIDirect3DTexture9)
{
	m_pIDirect3DTexture9	=	pIDirect3DTexture9;
	DWORD	dwCount	=	m_pIDirect3DTexture9->GetLevelCount();
	m_vecSurface.resize(dwCount);

	for(DWORD i=0;i<dwCount;i++){
		IDirect3DSurface9*	pSurface	=	NULL;
		m_pIDirect3DTexture9->GetSurfaceLevel(i,&pSurface);
		if(pSurface==NULL)
			m_vecSurface[i]	=	NULL;
		else{
			m_vecSurface[i]	=	new	MT_IDirect3DSurface9(pMT_IDirect3DDevice9,pSurface);
			m_vecSurface[i]->AddRef();
		}
	}
}
MT_IDirect3DTexture9::~MT_IDirect3DTexture9(){
	DWORD	dwCount	=	(DWORD)m_vecSurface.size();

	for(DWORD i=0;i<dwCount;i++){
		if(m_vecSurface[i]!=NULL){
			m_vecSurface[i]->Release();
		}
	}
};

HRESULT	MT_IDirect3DTexture9::GetLevelDesc(THIS_ UINT Level,D3DSURFACE_DESC *pDesc){
	return	m_pIDirect3DTexture9->GetLevelDesc(Level,pDesc);
}

HRESULT	MT_IDirect3DTexture9::GetSurfaceLevel(THIS_ UINT Level,MT_IDirect3DSurface9** ppSurfaceLevel)
{
	*ppSurfaceLevel	=	m_vecSurface[Level];
	(*ppSurfaceLevel)->AddRef();
	return	S_OK;
}
HRESULT	MT_IDirect3DTexture9::LockRect(THIS_ UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags){
	
	return	m_pMT_IDirect3DDevice9->Texture_LockRect(m_pIDirect3DTexture9,Level,pLockedRect,pRect,Flags);
};
HRESULT	MT_IDirect3DTexture9::UnlockRect(THIS_ UINT Level){

	return	m_pMT_IDirect3DDevice9->Texture_UnLockRect(m_pIDirect3DTexture9,Level);
};
HRESULT	MT_IDirect3DTexture9::AddDirtyRect(THIS_ CONST RECT* pDirtyRect){
	
	return	m_pMT_IDirect3DDevice9->Texture_AddDirtyRect(m_pIDirect3DTexture9,pDirtyRect);
};