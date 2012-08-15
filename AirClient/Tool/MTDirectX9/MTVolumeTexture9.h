#ifndef MTVOLUMETEXTURE9_HEAD_FILE
#define MTVOLUMETEXTURE9_HEAD_FILE

#include "MTBaseTexture9.h"


class MT_IDirect3DVolumeTexture9	:	public	MT_IDirect3DBaseTexture9
{
public:
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj){
		return	m_pIDirect3DVolumeTexture9->QueryInterface(riid,ppvObj);	
	};

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
    STDMETHOD(GetLevelDesc)(THIS_ UINT Level,D3DVOLUME_DESC *pDesc);
    STDMETHOD(GetVolumeLevel)(THIS_ UINT Level,MT_IDirect3DVolume9** ppVolumeLevel);
    STDMETHOD(LockBox)(THIS_ UINT Level,D3DLOCKED_BOX* pLockedVolume,CONST D3DBOX* pBox,DWORD Flags);
    STDMETHOD(UnlockBox)(THIS_ UINT Level);
    STDMETHOD(AddDirtyBox)(THIS_ CONST D3DBOX* pDirtyBox);
    
public:
	MT_IDirect3DVolumeTexture9(MT_IDirect3DDevice9* pMT_IDirect3DDevice9,IDirect3DVolumeTexture9* pIDirect3DVolumeTexture9);
	virtual	~MT_IDirect3DVolumeTexture9();
public:
	IDirect3DVolumeTexture9*	m_pIDirect3DVolumeTexture9;
	VolumeVector				m_vecVolume;
};

#endif