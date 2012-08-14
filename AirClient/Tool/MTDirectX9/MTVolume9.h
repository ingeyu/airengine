#ifndef	MTVOLUME9_HEAD_FILE
#define	MTVOLUME9_HEAD_FILE

#include "MTHeader.h"

class MT_IDirect3DVolume9	:	public	MT_IUnknown
{
public:
    /*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj){
		return	m_pIDirect3DVolume9->QueryInterface(riid,ppvObj);
	};
    //STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    //STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DVolume9 methods ***/
    STDMETHOD(GetDevice)(THIS_ MT_IDirect3DDevice9** ppDevice) ;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags);
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData);
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid);
    STDMETHOD(GetContainer)(THIS_ REFIID riid,void** ppContainer);
    STDMETHOD(GetDesc)(THIS_ D3DVOLUME_DESC *pDesc);
    STDMETHOD(LockBox)(THIS_ D3DLOCKED_BOX * pLockedVolume,CONST D3DBOX* pBox,DWORD Flags);
    STDMETHOD(UnlockBox)(THIS);
public:
	MT_IDirect3DVolume9(MT_IDirect3DDevice9* pMT_IDirect3DDevice9,IDirect3DVolume9* pIDirect3DVolume9);
	virtual	~MT_IDirect3DVolume9();
public:
	MT_IDirect3DDevice9*	m_pMT_IDirect3DDevice9;
	IDirect3DVolume9*		m_pIDirect3DVolume9;
};




#endif