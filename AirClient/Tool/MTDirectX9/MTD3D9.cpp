#include "MTD3D9.h"

MT_IDirect3D9* MT_Direct3DCreate9( UINT SDKVersion )
{
	IDirect3D9*	pD3D9	=	Direct3DCreate9(D3D_SDK_VERSION);
	if(pD3D9==NULL)
		return	NULL;
	MT_IDirect3D9*	pMTD3D9		=	new	MT_IDirect3D9(pD3D9);
	pD3D9->Release();
	return	pMTD3D9;
}

MT_IDirect3D9Ex* MT_Direct3DCreate9Ex( UINT SDKVersion )
{
// 	IDirect3D9Ex*	pD3D	=	Direct3DCreate9Ex(D3D_SDK_VERSION);
// 	if(pD3D==NULL)
// 		return	NULL;
// 	return	new	MT_IDirect3D9Ex(pD3D);
	return	NULL;
}
