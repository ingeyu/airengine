#ifndef MTSURFACE9_HEAD_FILE
#define	MTSURFACE9_HEAD_FILE

#include "MTResource9.h"


class MT_IDirect3DSurface9	:	public	MT_IDirect3DResource9
{
public:
    /*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj){
		return	m_pIDirect3DSurface9->QueryInterface(riid,ppvObj);
	};


    /*** IDirect3DResource9 methods ***/
    //STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice);
	STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags){
		return	m_pIDirect3DSurface9->SetPrivateData(refguid,pData,SizeOfData,Flags);
	};
	STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData){
		return	m_pIDirect3DSurface9->GetPrivateData(refguid,pData,pSizeOfData);
	};
	STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid){
		return	m_pIDirect3DSurface9->FreePrivateData(refguid);
	};
	STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew){
		return	m_pIDirect3DSurface9->SetPriority(PriorityNew);
	};
	STDMETHOD_(DWORD, GetPriority)(THIS){
		return	m_pIDirect3DSurface9->GetPriority();
	};
	STDMETHOD_(void, PreLoad)(THIS){
		return	m_pIDirect3DSurface9->PreLoad();
	};
	STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS){
		return	m_pIDirect3DSurface9->GetType();
	};
	STDMETHOD(GetContainer)(THIS_ REFIID riid,void** ppContainer){
		return	m_pIDirect3DSurface9->GetContainer(riid,ppContainer);
	};
	STDMETHOD(GetDesc)(THIS_ D3DSURFACE_DESC *pDesc){
		return	m_pIDirect3DSurface9->GetDesc(pDesc);
	};
    STDMETHOD(LockRect)(THIS_ D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags);
    STDMETHOD(UnlockRect)(THIS);
	STDMETHOD(GetDC)(THIS_ HDC *phdc){
		return	m_pIDirect3DSurface9->GetDC(phdc);
	};
	STDMETHOD(ReleaseDC)(THIS_ HDC hdc){
		return	m_pIDirect3DSurface9->ReleaseDC(hdc);
	};
public:
	MT_IDirect3DSurface9(MT_IDirect3DDevice9*	pMT_IDirect3DDevice9,IDirect3DSurface9* pIDirect3DSurface9);
public:
	IDirect3DSurface9* m_pIDirect3DSurface9;
};

typedef	std::vector<MT_IDirect3DSurface9*>	SurfaceVector;
#endif