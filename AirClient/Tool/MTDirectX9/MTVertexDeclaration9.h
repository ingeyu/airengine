#ifndef	MTVERTEXDECLARATION9_HEAD_FILE
#define MTVERTEXDECLARATION9_HEAD_FILE

#include "MTHeader.h"


class MT_IDirect3DVertexDeclaration9	:	public	MT_IUnknown
{
public:
    /*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj){
		return	m_pIDirect3DVertexDeclaration9->QueryInterface(riid,ppvObj);
	};
    //STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    //STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3DVertexDeclaration9 methods ***/
    STDMETHOD(GetDevice)(THIS_ MT_IDirect3DDevice9** ppDevice);
	STDMETHOD(GetDeclaration)(THIS_ D3DVERTEXELEMENT9* pElement,UINT* pNumElements){
		return	m_pIDirect3DVertexDeclaration9->GetDeclaration(pElement,pNumElements);
	};
public:
	MT_IDirect3DVertexDeclaration9(MT_IDirect3DDevice9* pMT_IDirect3DDevice9,IDirect3DVertexDeclaration9* pIDirect3DVertexDeclaration9);
	virtual	~MT_IDirect3DVertexDeclaration9();
public:
	MT_IDirect3DDevice9*				m_pMT_IDirect3DDevice9;
	IDirect3DVertexDeclaration9*		m_pIDirect3DVertexDeclaration9;
};
#endif