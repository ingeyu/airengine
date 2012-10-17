#ifndef MTBASETEXTURE9_HEAD
#define MTBASETEXTURE9_HEAD

#include "MTResource9.h"
#include "MTSurface9.h"

class MT_IDirect3DBaseTexture9	:	public	MT_IDirect3DResource9
{
    /*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj){
		return	m_pIDirect3DBaseTexture9->QueryInterface(riid,ppvObj);
	};


    /*** IDirect3DResource9 methods ***/
    //STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice) PURE;
    //STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    //STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    //STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    //STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    //STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    //STDMETHOD_(void, PreLoad)(THIS) PURE;
    //STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;
	STDMETHOD_(DWORD, SetLOD)(THIS_ DWORD LODNew){
		return	m_pIDirect3DBaseTexture9->SetLOD(LODNew);
	};
	STDMETHOD_(DWORD, GetLOD)(THIS){
		return	m_pIDirect3DBaseTexture9->GetLOD();
	};
    STDMETHOD_(DWORD, GetLevelCount)(THIS){
		return	m_pIDirect3DBaseTexture9->GetLevelCount();
	};
    STDMETHOD(SetAutoGenFilterType)(THIS_ D3DTEXTUREFILTERTYPE FilterType);
    STDMETHOD_(D3DTEXTUREFILTERTYPE, GetAutoGenFilterType)(THIS){
		return	m_pIDirect3DBaseTexture9->GetAutoGenFilterType();
	}
    STDMETHOD_(void, GenerateMipSubLevels)(THIS);
public:
	MT_IDirect3DBaseTexture9(MT_IDirect3DDevice9* pMT_IDirect3DDevice9,IDirect3DBaseTexture9* pIDirect3DBaseTexture9);
public:
	IDirect3DBaseTexture9*		m_pIDirect3DBaseTexture9;
};

#endif