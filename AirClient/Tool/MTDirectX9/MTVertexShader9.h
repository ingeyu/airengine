#ifndef MTVERTEXSHADER9_HEAD_FILE
#define MTVERTEXSHADER9_HEAD_FILE

#include "MTHeader.h"

class MT_IDirect3DVertexShader9	:	public	MT_IUnknown
{
public:
    /*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj){
		return	m_pIDirect3DVertexShader9->QueryInterface(riid,ppvObj);
	}
    //STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    //STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DVertexShader9 methods ***/
	STDMETHOD(GetDevice)(THIS_ MT_IDirect3DDevice9** ppDevice);
    STDMETHOD(GetFunction)(THIS_ void* pData,UINT* pSizeOfData);
public:
	MT_IDirect3DVertexShader9(MT_IDirect3DDevice9* pMT_IDirect3DDevice9,IDirect3DVertexShader9* pIDirect3DVertexShader9);
	virtual	~MT_IDirect3DVertexShader9();
public:
	MT_IDirect3DDevice9*		m_pMT_IDirect3DDevice9;
	IDirect3DVertexShader9*		m_pIDirect3DVertexShader9;
};

#endif