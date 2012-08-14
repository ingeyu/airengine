#include "MTVertexShader9.h"
#include "MTDevice9.h"

MT_IDirect3DVertexShader9::MT_IDirect3DVertexShader9(MT_IDirect3DDevice9* pMT_IDirect3DDevice9,IDirect3DVertexShader9* pIDirect3DVertexShader9){
	m_pIDirect3DVertexShader9	=	pIDirect3DVertexShader9;
	m_pIDirect3DVertexShader9->AddRef();

	m_pMT_IDirect3DDevice9	=	pMT_IDirect3DDevice9;
	m_pMT_IDirect3DDevice9->AddRef();
}
MT_IDirect3DVertexShader9::~MT_IDirect3DVertexShader9(){
	m_pIDirect3DVertexShader9->Release();
	m_pMT_IDirect3DDevice9->Release();
};
HRESULT	MT_IDirect3DVertexShader9::GetDevice(THIS_ MT_IDirect3DDevice9** ppDevice){
	*ppDevice	=	m_pMT_IDirect3DDevice9;
	m_pMT_IDirect3DDevice9->AddRef();
	return	S_OK;
};
HRESULT	MT_IDirect3DVertexShader9::GetFunction(THIS_ void* pData,UINT* pSizeOfData){
	return	m_pIDirect3DVertexShader9->GetFunction(pData,pSizeOfData);
};