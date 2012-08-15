#include "MTD3D9.h"

MT_IDirect3D9* MT_Direct3DCreate9( UINT SDKVersion )
{
	IDirect3D9*	pD3D9	=	Direct3DCreate9(D3D_SDK_VERSION);
	if(pD3D9==NULL)
		return	NULL;
	MT_IDirect3D9*	pMTD3D9		=	new	MT_IDirect3D9(pD3D9);
	pMTD3D9->AddRef();
	pD3D9->Release();
	return	pMTD3D9;
}

HRESULT Direct3DCreate9Ex( UINT SDKVersion ,MT_IDirect3D9Ex**	ppD3D9)
{
 	IDirect3D9Ex*	pD3D9	=	NULL;
	HRESULT	hr	=	Direct3DCreate9Ex(D3D_SDK_VERSION,&pD3D9);
 	if(pD3D9==NULL)
 		return	NULL;
 	*ppD3D9	=	new	MT_IDirect3D9Ex(pD3D9);
	(*ppD3D9)->AddRef();
	pD3D9->Release();

	return	hr;
}
