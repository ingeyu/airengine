#ifndef MTRESOURCE9_HEAD_FILE
#define MTRESOURCE9_HEAD_FILE


#include "MTHeader.h"


class MT_IDirect3DResource9	:	public	MT_IUnknown
{
    /*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj){
		return	m_pIDirect3DResource9->QueryInterface(riid,ppvObj);
	};

    /*** IDirect3DResource9 methods ***/
	STDMETHOD(GetDevice)(THIS_ MT_IDirect3DDevice9** ppDevice);
	STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags){
		return	m_pIDirect3DResource9->SetPrivateData(refguid,pData,SizeOfData,Flags);
	};
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData){
		return	m_pIDirect3DResource9->GetPrivateData(refguid,pData,pSizeOfData);
	};
	STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid){
		return	m_pIDirect3DResource9->FreePrivateData(refguid);
	};
	STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew){
		return	m_pIDirect3DResource9->SetPriority(PriorityNew);
	};
    STDMETHOD_(DWORD, GetPriority)(THIS){
		return	m_pIDirect3DResource9->GetPriority();
	};
    STDMETHOD_(void, PreLoad)(THIS){
		return	m_pIDirect3DResource9->PreLoad();
	};
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS){
		return	m_pIDirect3DResource9->GetType();
	};
public:
	MT_IDirect3DResource9(MT_IDirect3DDevice9* pMT_IDirect3DDevice9,IDirect3DResource9* pIDirect3DResource9);
	virtual	~MT_IDirect3DResource9();
public:
	MT_IDirect3DDevice9*	m_pMT_IDirect3DDevice9;
	IDirect3DResource9*		m_pIDirect3DResource9;
};
    

#endif