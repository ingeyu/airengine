#include "MTCubeTexture9.h"
#include "MTDevice9.h"

MT_IDirect3DCubeTexture9::MT_IDirect3DCubeTexture9(MT_IDirect3DDevice9* pMT_IDirect3DDevice9,IDirect3DCubeTexture9* pIDirect3DCubeTexture9)
:MT_IDirect3DBaseTexture9(pMT_IDirect3DDevice9,pIDirect3DCubeTexture9)
{
	m_pIDirect3DCubeTexture9	=	pIDirect3DCubeTexture9;
	DWORD	dwCount	=	m_pIDirect3DCubeTexture9->GetLevelCount();
	m_vecSurface.resize(dwCount);

	for(DWORD i=0;i<dwCount;i++){
		IDirect3DSurface9*	pSurface[6]={NULL,NULL,NULL,NULL,NULL,NULL};
		for(DWORD j=0;j<6;j++){
			m_pIDirect3DCubeTexture9->GetCubeMapSurface((D3DCUBEMAP_FACES)j,i,&pSurface[j]);
			if(pSurface[j]!=NULL){
				m_vecSurface[i].pSurfaceArray[j]	=	new	MT_IDirect3DSurface9(pMT_IDirect3DDevice9,pSurface[j]);
				m_vecSurface[i].pSurfaceArray[j]->AddRef();
			}
		}
	}
}
MT_IDirect3DCubeTexture9::~MT_IDirect3DCubeTexture9(){
	DWORD	dwCount	=	(DWORD)m_vecSurface.size();

	for(DWORD i=0;i<dwCount;i++){
		m_vecSurface[i].Release();
	}
}


HRESULT	MT_IDirect3DCubeTexture9::GetLevelDesc(THIS_ UINT Level,D3DSURFACE_DESC *pDesc){
	return	m_pIDirect3DCubeTexture9->GetLevelDesc(Level,pDesc);
}
HRESULT	MT_IDirect3DCubeTexture9::GetCubeMapSurface(THIS_ D3DCUBEMAP_FACES FaceType,UINT Level,MT_IDirect3DSurface9** ppCubeMapSurface)
{
	*ppCubeMapSurface	=	m_vecSurface[Level].pSurfaceArray[FaceType];
	(*ppCubeMapSurface)->AddRef();
	return	S_OK;
}
HRESULT	MT_IDirect3DCubeTexture9::LockRect(THIS_ D3DCUBEMAP_FACES FaceType,THIS_ UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags){
	
	return	m_pMT_IDirect3DDevice9->CubeTexture_LockRect(m_pIDirect3DCubeTexture9,FaceType,Level,pLockedRect,pRect,Flags);
};
HRESULT	MT_IDirect3DCubeTexture9::UnlockRect(THIS_ D3DCUBEMAP_FACES FaceType,THIS_ UINT Level){

	return	m_pMT_IDirect3DDevice9->CubeTexture_UnlockRect(m_pIDirect3DCubeTexture9,FaceType,Level);
};
HRESULT	MT_IDirect3DCubeTexture9::AddDirtyRect(THIS_ D3DCUBEMAP_FACES FaceType,THIS_ CONST RECT* pDirtyRect){
	
	return	m_pMT_IDirect3DDevice9->CubeTexture_AddDirtyRect(m_pIDirect3DCubeTexture9,FaceType,pDirtyRect);
};