#ifndef MTSTATEBLOCK9_HEAD_FILE
#define	MTSTATEBLOCK9_HEAD_FILE

#include "MTHeader.h"


struct MT_IDirect3DStateBlock9 :	IDirect3DStateBlock9{ 
	IDirect3DStateBlock9*					m_pIDirect3DStateBlock9;
	IDirect3DDevice9*						m_pIDirect3DDevice9;
	LONG									m_uiRef;
	D3DSTATEBLOCKTYPE						m_Type;
}; 




MT_IDirect3DStateBlock9* NewMT_IDirect3DStateBlock9(IDirect3DDevice9* pIDirect3DDevice9,D3DSTATEBLOCKTYPE	type,IDirect3DStateBlock9* pIDirect3DStateBlock9);

#endif