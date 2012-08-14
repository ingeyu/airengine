#ifndef	MTQUERY9_HEAD_FILE
#define MTQUERY9_HEAD_FILE

#include "MTHeader.h"

class MT_IDirect3DQuery9	:public	MT_IUnknown
{
    /*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj){
		return	m_pIDirect3DQuery9->QueryInterface(riid,ppvObj);
	};
    //STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    //STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DQuery9 methods ***/
    STDMETHOD(GetDevice)(THIS_ MT_IDirect3DDevice9** ppDevice);
	STDMETHOD_(D3DQUERYTYPE, GetType)(THIS){
		return	m_pIDirect3DQuery9->GetType();
	};
	STDMETHOD_(DWORD, GetDataSize)(THIS){
		return	m_pIDirect3DQuery9->GetDataSize();
	};
    STDMETHOD(Issue)(THIS_ DWORD dwIssueFlags);
    STDMETHOD(GetData)(THIS_ void* pData,DWORD dwSize,DWORD dwGetDataFlags);
    
public:
	MT_IDirect3DQuery9(MT_IDirect3DDevice9*	pMT_IDirect3DDevice9,IDirect3DQuery9* pIDirect3DQuery9);
	virtual	~MT_IDirect3DQuery9();

public:
	MT_IDirect3DDevice9*	m_pMT_IDirect3DDevice9;
	IDirect3DQuery9*		m_pIDirect3DQuery9;
};

#endif