#include "MTStateBlock9.h"
#include "MTDevice9.h"


MT_IDirect3DStateBlock9::MT_IDirect3DStateBlock9(MT_IDirect3DDevice9* pMT_IDirect3DDevice9,IDirect3DStateBlock9* pIDirect3DStateBlock9){
	m_pIDirect3DStateBlock9	=	pIDirect3DStateBlock9;
	if(m_pIDirect3DStateBlock9!=NULL)
		m_pIDirect3DStateBlock9->AddRef();

	m_pMT_IDirect3DDevice9	=	pMT_IDirect3DDevice9;
	m_pMT_IDirect3DDevice9->AddRef();
};
MT_IDirect3DStateBlock9::~MT_IDirect3DStateBlock9(){
	if(m_pIDirect3DStateBlock9!=NULL)
		m_pIDirect3DStateBlock9->Release();
	m_pMT_IDirect3DDevice9->Release();

};
HRESULT	MT_IDirect3DStateBlock9::GetDevice(MT_IDirect3DDevice9** ppDevice){
	*ppDevice	=	m_pMT_IDirect3DDevice9;
	m_pMT_IDirect3DDevice9->AddRef();
	return	S_OK;
};

HRESULT	MT_IDirect3DStateBlock9::Capture(){
	//SEND
	return	m_pMT_IDirect3DDevice9->StateBlock_Capture(m_pIDirect3DStateBlock9);
};

HRESULT	MT_IDirect3DStateBlock9::Apply(){
	//SEND
	return	m_pMT_IDirect3DDevice9->StateBlock_Apply(m_pIDirect3DStateBlock9);
};

void MT_IDirect3DStateBlock9::SetIDirect3DStateBlock9( IDirect3DStateBlock9* pStateBlock )
{
	if(pStateBlock!=NULL)
		pStateBlock->AddRef();
	if(m_pIDirect3DStateBlock9!=NULL)
		m_pIDirect3DStateBlock9->Release();
	m_pIDirect3DStateBlock9	=	pStateBlock;
	
}
