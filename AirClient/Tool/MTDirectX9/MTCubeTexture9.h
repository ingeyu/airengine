#ifndef MTCUBETEXTURE9_HEAD_FILE
#define MTCUBETEXTURE9_HEAD_FILE

#include "MTBaseTexture9.h"

struct CubeSurface{
	CubeSurface(){
		for(DWORD i=0;i<6;i++){
			pSurfaceArray[i]	=	NULL;
		}
	}
	void	Release(){
		for(DWORD i=0;i<6;i++){
			if(pSurfaceArray[i]	!=	NULL){
				pSurfaceArray[i]->Release();
			}
		}
	}
	MT_IDirect3DSurface9*	pSurfaceArray[6];
};
typedef	std::vector<CubeSurface>	CubeSurfaceVector;

class MT_IDirect3DCubeTexture9	:	public	MT_IDirect3DBaseTexture9
{
    /*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj){
		return	m_pIDirect3DCubeTexture9->QueryInterface(riid,ppvObj);	
	};
    //STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    //STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DBaseTexture9 methods ***/
    //STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice) PURE;
    //STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    //STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    //STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    //STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    //STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    //STDMETHOD_(void, PreLoad)(THIS) PURE;
    //STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;
    //STDMETHOD_(DWORD, SetLOD)(THIS_ DWORD LODNew) PURE;
    //STDMETHOD_(DWORD, GetLOD)(THIS) PURE;
    //STDMETHOD_(DWORD, GetLevelCount)(THIS) PURE;
    //STDMETHOD(SetAutoGenFilterType)(THIS_ D3DTEXTUREFILTERTYPE FilterType) PURE;
    //STDMETHOD_(D3DTEXTUREFILTERTYPE, GetAutoGenFilterType)(THIS) PURE;
    //STDMETHOD_(void, GenerateMipSubLevels)(THIS) PURE;
    STDMETHOD(GetLevelDesc)(THIS_ UINT Level,D3DSURFACE_DESC *pDesc);
    STDMETHOD(GetCubeMapSurface)(THIS_ D3DCUBEMAP_FACES FaceType,UINT Level,MT_IDirect3DSurface9** ppCubeMapSurface);
    STDMETHOD(LockRect)(THIS_ D3DCUBEMAP_FACES FaceType,UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags);
    STDMETHOD(UnlockRect)(THIS_ D3DCUBEMAP_FACES FaceType,UINT Level);
    STDMETHOD(AddDirtyRect)(THIS_ D3DCUBEMAP_FACES FaceType,CONST RECT* pDirtyRect);
public:
	MT_IDirect3DCubeTexture9(MT_IDirect3DDevice9* pMT_IDirect3DDevice9,IDirect3DCubeTexture9* pIDirect3DCubeTexture9);
	virtual	~MT_IDirect3DCubeTexture9();
public:
	IDirect3DCubeTexture9*	m_pIDirect3DCubeTexture9;
	CubeSurfaceVector		m_vecSurface;
};

#endif