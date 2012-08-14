#include "MTVolumeTexture9.h"
#include "MTVolume9.h"
#include "MTDevice9.h"

MT_IDirect3DVolumeTexture9::MT_IDirect3DVolumeTexture9(MT_IDirect3DDevice9* pMT_IDirect3DDevice9,IDirect3DVolumeTexture9* pIDirect3DVolumeTexture9)
:MT_IDirect3DBaseTexture9(pMT_IDirect3DDevice9,pIDirect3DVolumeTexture9)
{
	m_pIDirect3DVolumeTexture9	=	pIDirect3DVolumeTexture9;

	DWORD	dwCount	=	m_pIDirect3DVolumeTexture9->GetLevelCount();
	m_vecVolume.resize(dwCount);

	for(DWORD i=0;i<dwCount;i++){
		IDirect3DVolume9*	pVolume	=	NULL;
		m_pIDirect3DVolumeTexture9->GetVolumeLevel(i,&pVolume);
		if(pVolume==NULL){
			m_vecVolume[i]	=	NULL;	
		}else{
			m_vecVolume[i]	=	new MT_IDirect3DVolume9(pMT_IDirect3DDevice9,pVolume);
			m_vecVolume[i]->AddRef();
		}
	}

}
MT_IDirect3DVolumeTexture9::~MT_IDirect3DVolumeTexture9(){
	DWORD	dwCount	=	m_vecVolume.size();

	for(DWORD i=0;i<dwCount;i++){
		if(m_vecVolume[i]!=NULL){
			m_vecVolume[i]->Release();
		}
	}
};

HRESULT	MT_IDirect3DVolumeTexture9::GetLevelDesc(THIS_ UINT Level,D3DVOLUME_DESC *pDesc){
	return	m_pIDirect3DVolumeTexture9->GetLevelDesc(Level,pDesc);
};
HRESULT	MT_IDirect3DVolumeTexture9::GetVolumeLevel(THIS_ UINT Level,MT_IDirect3DVolume9** ppVolumeLevel){
	*ppVolumeLevel	=	m_vecVolume[Level];
	(*ppVolumeLevel)->AddRef();
	return	S_OK;
};
HRESULT	MT_IDirect3DVolumeTexture9::LockBox(THIS_ UINT Level,D3DLOCKED_BOX* pLockedVolume,CONST D3DBOX* pBox,DWORD Flags){

	return	m_pMT_IDirect3DDevice9->VolumeTexture_LockBox(m_pIDirect3DVolumeTexture9,Level,pLockedVolume,pBox,Flags);
};
HRESULT	MT_IDirect3DVolumeTexture9::UnlockBox(THIS_ UINT Level){

	return	m_pMT_IDirect3DDevice9->VolumeTexture_UnlockBox(m_pIDirect3DVolumeTexture9,Level);
};
HRESULT	MT_IDirect3DVolumeTexture9::AddDirtyBox(THIS_ CONST D3DBOX* pDirtyBox){

	return	m_pMT_IDirect3DDevice9->VolumeTexture_AddDirtyBox(m_pIDirect3DVolumeTexture9,pDirtyBox);
};