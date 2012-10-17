#include "MTEffect.h"
#include "MTDevice9.h"

MT_ID3DXEffect::MT_ID3DXEffect(MT_IDirect3DDevice9*	pMT_IDirect3DDevice9,ID3DXEffect*			pID3DXEffect){
	m_pMT_IDirect3DDevice9	=	pMT_IDirect3DDevice9;
	m_pID3DXEffect			=	pID3DXEffect;
	pMT_IDirect3DDevice9->AddRef();
	pID3DXEffect->AddRef();
}
MT_ID3DXEffect::~MT_ID3DXEffect(){
	m_pMT_IDirect3DDevice9->Release();
	m_pID3DXEffect->Release();
};

HRESULT	MT_ID3DXEffect::GetDevice(THIS_ MT_LPDIRECT3DDEVICE9* ppDevice){
	m_pMT_IDirect3DDevice9->AddRef();
	(*ppDevice)	=	m_pMT_IDirect3DDevice9;
	return	S_OK;
};

HRESULT	MT_ID3DXEffect::CloneEffect(THIS_ MT_LPDIRECT3DDEVICE9 pDevice, MT_LPD3DXEFFECT* ppEffect){
	LPD3DXEFFECT	pEffect	=	NULL;
	HRESULT	hr	=	m_pID3DXEffect->CloneEffect(pDevice->m_pIDirect3DDevice9,&pEffect);
	if(SUCCEEDED(hr)){
		(*ppEffect)	=	new	MT_ID3DXEffect(pDevice,pEffect);
		(*ppEffect)->AddRef();
		pEffect->Release();
	}
	return	hr;
};

HRESULT	MT_ID3DXEffect::SetValue(THIS_ D3DXHANDLE hParameter, LPCVOID pData, UINT Bytes){
	return	m_pMT_IDirect3DDevice9->Effect_SetValue(m_pID3DXEffect,hParameter,pData,Bytes);
}

HRESULT	MT_ID3DXEffect::SetBool(THIS_ D3DXHANDLE hParameter, BOOL b){
	return	m_pMT_IDirect3DDevice9->Effect_SetBool(m_pID3DXEffect,hParameter,b);
}

HRESULT	MT_ID3DXEffect::SetBoolArray(THIS_ D3DXHANDLE hParameter, CONST BOOL* pb, UINT Count){
	return	m_pMT_IDirect3DDevice9->Effect_SetBoolArray(m_pID3DXEffect,hParameter,pb,Count);
}

HRESULT	MT_ID3DXEffect::SetInt(THIS_ D3DXHANDLE hParameter, INT n){
	return	m_pMT_IDirect3DDevice9->Effect_SetInt(m_pID3DXEffect,hParameter,n);
}

HRESULT	MT_ID3DXEffect::SetIntArray(THIS_ D3DXHANDLE hParameter, CONST INT* pn, UINT Count){
	return	m_pMT_IDirect3DDevice9->Effect_SetIntArray(m_pID3DXEffect,hParameter,pn,Count);
}

HRESULT	MT_ID3DXEffect::SetFloat(THIS_ D3DXHANDLE hParameter, FLOAT f){
	return	m_pMT_IDirect3DDevice9->Effect_SetFloat(m_pID3DXEffect,hParameter,f);
}

HRESULT	MT_ID3DXEffect::SetFloatArray(THIS_ D3DXHANDLE hParameter, CONST FLOAT* pf, UINT Count){
	return	m_pMT_IDirect3DDevice9->Effect_SetFloatArray(m_pID3DXEffect,hParameter,pf,Count);
}

HRESULT	MT_ID3DXEffect::SetVector(THIS_ D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector){
	return	m_pMT_IDirect3DDevice9->Effect_SetVector(m_pID3DXEffect,hParameter,pVector);
}

HRESULT	MT_ID3DXEffect::SetVectorArray(THIS_ D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector, UINT Count){
	return	m_pMT_IDirect3DDevice9->Effect_SetVectorArray(m_pID3DXEffect,hParameter,pVector,Count);
}

HRESULT	MT_ID3DXEffect::SetMatrix(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix){
	return	m_pMT_IDirect3DDevice9->Effect_SetMatrix(m_pID3DXEffect,hParameter,pMatrix);
}

HRESULT	MT_ID3DXEffect::SetMatrixArray(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count){
	return	m_pMT_IDirect3DDevice9->Effect_SetMatrixArray(m_pID3DXEffect,hParameter,pMatrix,Count);
}

HRESULT	MT_ID3DXEffect::SetMatrixPointerArray(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count){
	return	m_pMT_IDirect3DDevice9->Effect_SetMatrixPointerArray(m_pID3DXEffect,hParameter,ppMatrix,Count);
}

HRESULT	MT_ID3DXEffect::SetMatrixTranspose(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix){
	return	m_pMT_IDirect3DDevice9->Effect_SetMatrixTranspose(m_pID3DXEffect,hParameter,pMatrix);
}

HRESULT	MT_ID3DXEffect::SetMatrixTransposeArray(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count){
	return	m_pMT_IDirect3DDevice9->Effect_SetMatrixTransposeArray(m_pID3DXEffect,hParameter,pMatrix,Count);
}

HRESULT	MT_ID3DXEffect::SetMatrixTransposePointerArray(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count){
	return	m_pMT_IDirect3DDevice9->Effect_SetMatrixTransposePointerArray(m_pID3DXEffect,hParameter,ppMatrix,Count);
}

HRESULT	MT_ID3DXEffect::SetString(THIS_ D3DXHANDLE hParameter, LPCSTR pString){
	return	m_pMT_IDirect3DDevice9->Effect_SetString(m_pID3DXEffect,hParameter,pString);
}

HRESULT	MT_ID3DXEffect::SetTexture(THIS_ D3DXHANDLE hParameter, LPDIRECT3DBASETEXTURE9 pTexture){
	return	m_pMT_IDirect3DDevice9->Effect_SetTexture(m_pID3DXEffect,hParameter,pTexture);
}
HRESULT	MT_ID3DXEffect::SetTechnique(THIS_ D3DXHANDLE hTechnique){
	return	m_pMT_IDirect3DDevice9->Effect_SetTechnique(m_pID3DXEffect,hTechnique);
}
HRESULT	MT_ID3DXEffect::Begin(THIS_ UINT *pPasses, DWORD Flags) {
	return	m_pMT_IDirect3DDevice9->Effect_Begin(m_pID3DXEffect,pPasses,Flags);
}
HRESULT	MT_ID3DXEffect::BeginPass(THIS_ UINT Pass) {
	return	m_pMT_IDirect3DDevice9->Effect_BeginPass(m_pID3DXEffect,Pass);
}
HRESULT	MT_ID3DXEffect::CommitChanges(THIS) {
	return	m_pMT_IDirect3DDevice9->Effect_CommitChanges(m_pID3DXEffect);
}
HRESULT	MT_ID3DXEffect::EndPass(THIS) {
	return	m_pMT_IDirect3DDevice9->Effect_EndPass(m_pID3DXEffect);
}
HRESULT	MT_ID3DXEffect::End(THIS) {
	return	m_pMT_IDirect3DDevice9->Effect_End(m_pID3DXEffect);
}
HRESULT	MT_ID3DXEffect::SetStateManager(THIS_ LPD3DXEFFECTSTATEMANAGER pManager){
	return	m_pMT_IDirect3DDevice9->Effect_SetStateManager(m_pID3DXEffect,pManager);
}
HRESULT	MT_ID3DXEffect::SetRawValue(THIS_ D3DXHANDLE hParameter, LPCVOID pData, UINT ByteOffset, UINT Bytes){
	return	m_pMT_IDirect3DDevice9->Effect_SetRawValue(m_pID3DXEffect,hParameter,pData,ByteOffset,Bytes);
}
