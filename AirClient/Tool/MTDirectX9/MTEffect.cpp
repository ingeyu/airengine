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