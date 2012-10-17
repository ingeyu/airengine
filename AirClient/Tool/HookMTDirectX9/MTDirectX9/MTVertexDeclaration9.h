#ifndef	MTVERTEXDECLARATION9_HEAD_FILE
#define MTVERTEXDECLARATION9_HEAD_FILE

#include "MTHeader.h"


struct MT_IDirect3DVertexDeclaration9	:	IDirect3DVertexDeclaration9
{
	IDirect3DVertexDeclaration9*		GetVD();
	IDirect3DDevice9*					m_pIDirect3DDevice9;
	IDirect3DVertexDeclaration9*		m_pIDirect3DVertexDeclaration9;
	std::vector<D3DVERTEXELEMENT9>		m_vecElement;
};

MT_IDirect3DVertexDeclaration9*	NewMT_IDirect3DVertexDeclaration9(IDirect3DDevice9* pIDirect3DDevice9,CONST D3DVERTEXELEMENT9* pVertexElements,UINT uiNumElement);
#endif