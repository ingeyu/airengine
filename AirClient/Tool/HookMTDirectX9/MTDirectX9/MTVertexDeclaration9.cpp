#include "MTVertexDeclaration9.h"
#include "MTDevice9.h"

extern T_CreateVertexDeclaration	ST_CreateVertexDeclaration;

HRESULT	STDMETHODCALLTYPE	MT_IDirect3DVertexDeclaration9_QueryInterface(IDirect3DVertexDeclaration9* pThis,REFIID riid,void** ppvObj)
{
	HRESULT	hr	=	E_FAIL;

	MT_IDirect3DVertexDeclaration9* p	=	static_cast<MT_IDirect3DVertexDeclaration9*>(pThis);
	if(p->m_pIDirect3DVertexDeclaration9!=NULL){
		hr	=	p->m_pIDirect3DVertexDeclaration9->lpVtbl->QueryInterface(p->m_pIDirect3DVertexDeclaration9,riid,ppvObj);
		if(SUCCEEDED(hr)){
			*ppvObj	=	p;
		}
	}
	return hr;
}
ULONG		STDMETHODCALLTYPE	MT_IDirect3DVertexDeclaration9_AddRef(IDirect3DVertexDeclaration9* pThis){
	return	2;
};
ULONG		STDMETHODCALLTYPE	MT_IDirect3DVertexDeclaration9_Release(IDirect3DVertexDeclaration9* pThis){
	return	1;
};
HRESULT		STDMETHODCALLTYPE	MT_IDirect3DVertexDeclaration9_GetDevice(IDirect3DVertexDeclaration9* pThis,  IDirect3DDevice9** ppDevice){
	MT_IDirect3DVertexDeclaration9* p	=	static_cast<MT_IDirect3DVertexDeclaration9*>(pThis);
	*ppDevice	=	p->m_pIDirect3DDevice9;
 	T_AddRef(p->m_pIDirect3DDevice9);
	return S_OK;
};

HRESULT		STDMETHODCALLTYPE	MT_IDirect3DVertexDeclaration9_GetDeclaration(IDirect3DVertexDeclaration9* pThis,  D3DVERTEXELEMENT9* pElement,UINT* pNumElements){
	MT_IDirect3DVertexDeclaration9* p	=	static_cast<MT_IDirect3DVertexDeclaration9*>(pThis);
	*pNumElements	=	p->m_vecElement.size();
	if(pElement!=NULL){
		memcpy(pElement,&p->m_vecElement[0],sizeof(D3DVERTEXELEMENT9)*(*pNumElements));
	}
	return S_OK;
};
IDirect3DVertexDeclaration9*	MT_IDirect3DVertexDeclaration9::GetVD(){
	if(m_pIDirect3DVertexDeclaration9==NULL){
		HRESULT	hr	=	ST_CreateVertexDeclaration(m_pIDirect3DDevice9,&m_vecElement[0],&m_pIDirect3DVertexDeclaration9);
	}
	return	m_pIDirect3DVertexDeclaration9;
}

IDirect3DVertexDeclaration9Vtbl	MT_lpVtbl={
MT_IDirect3DVertexDeclaration9_QueryInterface,
MT_IDirect3DVertexDeclaration9_AddRef,
MT_IDirect3DVertexDeclaration9_Release,
MT_IDirect3DVertexDeclaration9_GetDevice,
MT_IDirect3DVertexDeclaration9_GetDeclaration
};

MT_IDirect3DVertexDeclaration9*	NewMT_IDirect3DVertexDeclaration9(IDirect3DDevice9* pIDirect3DDevice9,CONST D3DVERTEXELEMENT9* pVertexElements,UINT uiNumElement){
	if(	pVertexElements		==NULL	||
		pIDirect3DDevice9	==NULL)
	{
		return	NULL;
	}
	MT_IDirect3DVertexDeclaration9* p	=	new	MT_IDirect3DVertexDeclaration9;

	p->m_pIDirect3DVertexDeclaration9	=	NULL;
	p->m_pIDirect3DDevice9				=	pIDirect3DDevice9;
	p->lpVtbl							=	&MT_lpVtbl;
	p->m_vecElement.resize(uiNumElement);
	memcpy(&p->m_vecElement[0],pVertexElements,sizeof(D3DVERTEXELEMENT9)*uiNumElement);

	return	p;
}