
#include "MTDevice9.h"
#include "MTSurface9.h"
#include "MTVertexBuffer9.h"
#include "MTCubeTexture9.h"
#include "MTPixelShader9.h"
#include "MTQuery9.h"
#include "MTStateBlock9.h"
#include "MTSwapChain9.h"
#include "MTTexture9.h"
#include "MTVertexDeclaration9.h"
#include "MTVertexShader9.h"
#include "MTVolume9.h"
#include "MTVolumeTexture9.h"
#include "MTIndexBuffer9.h"


UINT BitsPerPixel( D3DFORMAT fmt )
{
    UINT fmtU = ( UINT )fmt;
    switch( fmtU )
    {
        case D3DFMT_A32B32G32R32F:
            return 128;

        case D3DFMT_A16B16G16R16:
        case D3DFMT_Q16W16V16U16:
        case D3DFMT_A16B16G16R16F:
        case D3DFMT_G32R32F:
            return 64;

        case D3DFMT_A8R8G8B8:
        case D3DFMT_X8R8G8B8:
        case D3DFMT_A2B10G10R10:
        case D3DFMT_A8B8G8R8:
        case D3DFMT_X8B8G8R8:
        case D3DFMT_G16R16:
        case D3DFMT_A2R10G10B10:
        case D3DFMT_Q8W8V8U8:
        case D3DFMT_V16U16:
        case D3DFMT_X8L8V8U8:
        case D3DFMT_A2W10V10U10:
        case D3DFMT_D32:
        case D3DFMT_D24S8:
        case D3DFMT_D24X8:
        case D3DFMT_D24X4S4:
        case D3DFMT_D32F_LOCKABLE:
        case D3DFMT_D24FS8:
        case D3DFMT_INDEX32:
        case D3DFMT_G16R16F:
        case D3DFMT_R32F:
            return 32;

        case D3DFMT_R8G8B8:
            return 24;

        case D3DFMT_A4R4G4B4:
        case D3DFMT_X4R4G4B4:
        case D3DFMT_R5G6B5:
        case D3DFMT_L16:
        case D3DFMT_A8L8:
        case D3DFMT_X1R5G5B5:
        case D3DFMT_A1R5G5B5:
        case D3DFMT_A8R3G3B2:
        case D3DFMT_V8U8:
        case D3DFMT_CxV8U8:
        case D3DFMT_L6V5U5:
        case D3DFMT_G8R8_G8B8:
        case D3DFMT_R8G8_B8G8:
        case D3DFMT_D16_LOCKABLE:
        case D3DFMT_D15S1:
        case D3DFMT_D16:
        case D3DFMT_INDEX16:
        case D3DFMT_R16F:
        case D3DFMT_YUY2:
            return 16;

        case D3DFMT_R3G3B2:
        case D3DFMT_A8:
        case D3DFMT_A8P8:
        case D3DFMT_P8:
        case D3DFMT_L8:
        case D3DFMT_A4L4:
            return 8;

        case D3DFMT_DXT1:
            return 4;

        case D3DFMT_DXT2:
        case D3DFMT_DXT3:
        case D3DFMT_DXT4:
        case D3DFMT_DXT5:
            return  8;

            // From DX docs, reference/d3d/enums/d3dformat.asp
            // (note how it says that D3DFMT_R8G8_B8G8 is "A 16-bit packed RGB format analogous to UYVY (U0Y0, V0Y1, U2Y2, and so on)")
        case D3DFMT_UYVY:
            return 16;

            // http://msdn.microsoft.com/library/default.asp?url=/library/en-us/directshow/htm/directxvideoaccelerationdxvavideosubtypes.asp
        case MAKEFOURCC( 'A', 'I', '4', '4' ):
        case MAKEFOURCC( 'I', 'A', '4', '4' ):
            return 8;

        case MAKEFOURCC( 'Y', 'V', '1', '2' ):
            return 12;

#if !defined(D3D_DISABLE_9EX)
        case D3DFMT_D32_LOCKABLE:
            return 32;

        case D3DFMT_S8_LOCKABLE:
            return 8;

        case D3DFMT_A1:
            return 1;
#endif // !D3D_DISABLE_9EX

        default:

            return 0;
    }
}


MT_IDirect3D9::MT_IDirect3D9(IDirect3D9* pIDirect3D9){
	m_pIDirect3D9	=	pIDirect3D9;
	m_pIDirect3D9->AddRef();
}
MT_IDirect3D9::~MT_IDirect3D9(){
	m_pIDirect3D9->Release();
}

HRESULT	MT_IDirect3D9::CreateDevice(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,MT_IDirect3DDevice9** ppReturnedDeviceInterface)
{

	DWORD	dwNewBehaviorFlags	=	BehaviorFlags;
	dwNewBehaviorFlags			|=	D3DCREATE_MULTITHREADED;

	
	IDirect3DDevice9*	pIDirect3DDevice9	=	NULL;

	HRESULT	hr	=	m_pIDirect3D9->CreateDevice(Adapter,DeviceType,hFocusWindow,dwNewBehaviorFlags,pPresentationParameters,&pIDirect3DDevice9);
	if(SUCCEEDED(hr)){
		*ppReturnedDeviceInterface	=	new	MT_IDirect3DDevice9(this,pIDirect3DDevice9);
		(*ppReturnedDeviceInterface)->AddRef();
		pIDirect3DDevice9->Release();
	}
	return	hr;
}

MT_IDirect3D9Ex::MT_IDirect3D9Ex(IDirect3D9Ex* pIDirect3D9Ex)
:MT_IDirect3D9(pIDirect3D9Ex)
{
	m_pIDirect3D9Ex	=	pIDirect3D9Ex;
}

HRESULT	MT_IDirect3D9Ex::CreateDeviceEx(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,D3DDISPLAYMODEEX* pFullscreenDisplayMode,IDirect3DDevice9Ex** ppReturnedDeviceInterface){
	HRESULT	hr	=	S_OK;
	/*
	DWORD	dwNewBehaviorFlags	=	BehaviorFlags;
	dwNewBehaviorFlags			|=	D3DCREATE_MULTITHREADED;

	
	IDirect3DDevice9Ex*	pIDirect3DDevice9Ex	=	NULL;

	HRESULT	hr	=	m_pIDirect3D9Ex->CreateDeviceEx(Adapter,DeviceType,hFocusWindow,dwNewBehaviorFlags,pPresentationParameters,pFullscreenDisplayMode,&pIDirect3DDevice9Ex);
	if(SUCCEEDED(hr)){
		*ppReturnedDeviceInterface	=	NULL;//new	MT_IDirect3DDevice9(this,pIDirect3DDevice9);
		(*ppReturnedDeviceInterface)->AddRef();
		pIDirect3DDevice9Ex->Release();
	}
	*/
	return	hr;
}


MT_IDirect3DDevice9::MT_IDirect3DDevice9(MT_IDirect3D9*	pD3D9,IDirect3DDevice9* pIDirect3DDevice9)
:MT_RenderThread(pIDirect3DDevice9)
{
	m_pIDirect3DDevice9	=	pIDirect3DDevice9;
	m_pIDirect3DDevice9->AddRef();
	m_pMT_IDirect3D9	=	pD3D9;
	m_pMT_IDirect3D9->AddRef();
	m_iMainThreadId		=	GetCurrentThreadId();
	m_bDeviceLost		=	false;
};
MT_IDirect3DDevice9::~MT_IDirect3DDevice9(){
	m_pIDirect3DDevice9->Release();
	m_pMT_IDirect3D9->Release();
};

HRESULT	MT_IDirect3DDevice9::CreateAdditionalSwapChain(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters,MT_IDirect3DSwapChain9** pSwapChain){
	IDirect3DSwapChain9*	pIDirect3DSwapChain9	=	NULL;
	HRESULT	hr	=	m_pIDirect3DDevice9->CreateAdditionalSwapChain(pPresentationParameters,&pIDirect3DSwapChain9);
	if(SUCCEEDED(hr)){
		*pSwapChain	=	new	MT_IDirect3DSwapChain9(this,pIDirect3DSwapChain9);
		(*pSwapChain)->AddRef();
	}
	return	hr;
}
HRESULT	MT_IDirect3DDevice9::GetSwapChain(THIS_ UINT iSwapChain,MT_IDirect3DSwapChain9** pSwapChain){
	IDirect3DSwapChain9*	pIDirect3DSwapChain9	=	NULL;
	HRESULT	hr	=	m_pIDirect3DDevice9->GetSwapChain(iSwapChain,&pIDirect3DSwapChain9);
	if(SUCCEEDED(hr)){
		*pSwapChain	=	new	MT_IDirect3DSwapChain9(this,pIDirect3DSwapChain9);
		(*pSwapChain)->AddRef();
	}
	return	hr;
};
UINT	MT_IDirect3DDevice9::GetNumberOfSwapChains(THIS){
	return		m_pIDirect3DDevice9->GetNumberOfSwapChains();
}
HRESULT	MT_IDirect3DDevice9::Reset(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters){
	//Waiting Render Thread
	WaitRenderComplated();

	return	m_pIDirect3DDevice9->Reset(pPresentationParameters);
}
HRESULT	MT_IDirect3DDevice9::Present(THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion){
	//Send Present
	CmdPresent*	param			=	m_DBuffer.Request<CmdPresent>(enCF_Present);
	param->pSourceRect			=	pSourceRect;
	param->pDestRect			=	pDestRect;
	param->hDestWindowOverride	=	hDestWindowOverride;
	param->pDirtyRegion			=	pDirtyRegion;
	if(pSourceRect!=NULL)
		param->src		=	*pSourceRect;
	if(pDestRect!=NULL)
		param->dst		=	*pDestRect;
	if(pDirtyRegion!=NULL)
		param->dirty	=	*pDirtyRegion;
			
	//Waiting Render Thread Complated!
	Swap();

	return	S_OK;
}
HRESULT	MT_IDirect3DDevice9::GetBackBuffer(THIS_ UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,MT_IDirect3DSurface9** ppBackBuffer){
	IDirect3DSurface9*	pIDirect3DSurface9	=	NULL;
	HRESULT	hr	=	m_pIDirect3DDevice9->GetBackBuffer(iSwapChain,iBackBuffer,Type,&pIDirect3DSurface9);
	if(SUCCEEDED(hr)){
		*ppBackBuffer	=	new	MT_IDirect3DSurface9(this,pIDirect3DSurface9);
		(*ppBackBuffer)->AddRef();
	}
	return	hr;
}
HRESULT	MT_IDirect3DDevice9::GetRasterStatus(THIS_ UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus){
	return	m_pIDirect3DDevice9->GetRasterStatus(iSwapChain,pRasterStatus);
};
HRESULT	MT_IDirect3DDevice9::SetDialogBoxMode(THIS_ BOOL bEnableDialogs){
	CmdSetDialogBoxMode*	param			=	m_DBuffer.Request<CmdSetDialogBoxMode>(enCF_SetDialogBoxMode);
	(*param)	=	bEnableDialogs;
	return	S_OK;
}
void	MT_IDirect3DDevice9::SetGammaRamp(THIS_ UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp){
	if(pRamp==NULL)
		return;

	CmdSetGammaRamp*	param			=	m_DBuffer.Request<CmdSetGammaRamp>(enCF_SetGammaRamp);
	param->iSwapChain	=	iSwapChain;
	param->Flags		=	Flags;
	param->pRamp		=	*pRamp;
}
void	MT_IDirect3DDevice9::GetGammaRamp(THIS_ UINT iSwapChain,D3DGAMMARAMP* pRamp){

}

HRESULT MT_IDirect3DDevice9::CreateTexture(THIS_ UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,MT_IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle){
	IDirect3DTexture9*	pIDirect3DTexture9	=	NULL;
	HRESULT	hr	=	m_pIDirect3DDevice9->CreateTexture(Width,Height,Levels,Usage,Format,Pool,&pIDirect3DTexture9,pSharedHandle);
	if(SUCCEEDED(hr)){
		*ppTexture	=	new	MT_IDirect3DTexture9(this,pIDirect3DTexture9);
		(*ppTexture)->AddRef();
		pIDirect3DTexture9->Release();
	}
	return hr;
};
HRESULT MT_IDirect3DDevice9::CreateVolumeTexture(THIS_ UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,MT_IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle){
	IDirect3DVolumeTexture9*	pIDirect3DVolumeTexture9	=	NULL;
	HRESULT	hr	=	m_pIDirect3DDevice9->CreateVolumeTexture(Width,Height,Depth,Levels,Usage,Format,Pool,&pIDirect3DVolumeTexture9,pSharedHandle);
	if(SUCCEEDED(hr)){
		*ppVolumeTexture	=	new	MT_IDirect3DVolumeTexture9(this,pIDirect3DVolumeTexture9);
		(*ppVolumeTexture)->AddRef();
		pIDirect3DVolumeTexture9->Release();
	}
	return hr;
};
HRESULT MT_IDirect3DDevice9::CreateCubeTexture(THIS_ UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,MT_IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle){
	IDirect3DCubeTexture9*	pIDirect3DCubeTexture9	=	NULL;
	HRESULT	hr	=	m_pIDirect3DDevice9->CreateCubeTexture(EdgeLength,Levels,Usage,Format,Pool,&pIDirect3DCubeTexture9,pSharedHandle);
	if(SUCCEEDED(hr)){
		*ppCubeTexture	=	new	MT_IDirect3DCubeTexture9(this,pIDirect3DCubeTexture9);
		(*ppCubeTexture)->AddRef();
		pIDirect3DCubeTexture9->Release();
	}
	return hr;
};
HRESULT MT_IDirect3DDevice9::CreateVertexBuffer(THIS_ UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,MT_IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle){
	IDirect3DVertexBuffer9*	pIDirect3DVertexBuffer9	=	NULL;
	HRESULT	hr	=	m_pIDirect3DDevice9->CreateVertexBuffer(Length,Usage,FVF,Pool,&pIDirect3DVertexBuffer9,pSharedHandle);
	if(SUCCEEDED(hr)){
		*ppVertexBuffer	=	new	MT_IDirect3DVertexBuffer9(this,pIDirect3DVertexBuffer9);
		(*ppVertexBuffer)->AddRef();
		pIDirect3DVertexBuffer9->Release();
	}
	return hr;
};
HRESULT MT_IDirect3DDevice9::CreateIndexBuffer(THIS_ UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,MT_IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle){
	IDirect3DIndexBuffer9*	pIDirect3DIndexBuffer9	=	NULL;
	HRESULT	hr	=	m_pIDirect3DDevice9->CreateIndexBuffer(Length,Usage,Format,Pool,&pIDirect3DIndexBuffer9,pSharedHandle);
	if(SUCCEEDED(hr)){
		*ppIndexBuffer	=	new	MT_IDirect3DIndexBuffer9(this,pIDirect3DIndexBuffer9);
		(*ppIndexBuffer)->AddRef();
		pIDirect3DIndexBuffer9->Release();
	}
	return hr;
};
HRESULT MT_IDirect3DDevice9::CreateRenderTarget(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,MT_IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle){
	IDirect3DSurface9*	pIDirect3DSurface9	=	NULL;
	HRESULT	hr	=	m_pIDirect3DDevice9->CreateRenderTarget(Width,Height,Format,MultiSample,MultisampleQuality,Lockable,&pIDirect3DSurface9,pSharedHandle);
	if(SUCCEEDED(hr)){
		*ppSurface	=	new	MT_IDirect3DSurface9(this,pIDirect3DSurface9);
		(*ppSurface)->AddRef();
		pIDirect3DSurface9->Release();
	}
	return hr;
};
HRESULT MT_IDirect3DDevice9::CreateDepthStencilSurface(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,MT_IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle){
	IDirect3DSurface9*	pIDirect3DSurface9	=	NULL;
	HRESULT	hr	=	m_pIDirect3DDevice9->CreateDepthStencilSurface(Width,Height,Format,MultiSample,MultisampleQuality,Discard,&pIDirect3DSurface9,pSharedHandle);
	if(SUCCEEDED(hr)){
		*ppSurface	=	new	MT_IDirect3DSurface9(this,pIDirect3DSurface9);
		(*ppSurface)->AddRef();
		pIDirect3DSurface9->Release();
	}
	return hr;
};
HRESULT MT_IDirect3DDevice9::UpdateSurface(THIS_ MT_IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,MT_IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint){

	CmdUpdateSurface*	param			=	m_DBuffer.Request<CmdUpdateSurface>(enCF_UpdateSurface);
	
	param->pSourceSurface		=	pSourceSurface->m_pIDirect3DSurface9;
	param->pSourceRect			=	pSourceRect;
	param->pDestinationSurface	=	pDestinationSurface->m_pIDirect3DSurface9;
	param->pDestPoint			=	pDestPoint;

	if(pSourceRect!=NULL)
		param->src		=	*pSourceRect;
	if(pDestPoint!=NULL)
		param->dst		=	*pDestPoint;
	return	S_OK;
};
HRESULT MT_IDirect3DDevice9::UpdateTexture(THIS_ MT_IDirect3DBaseTexture9* pSourceTexture,MT_IDirect3DBaseTexture9* pDestinationTexture){

	CmdUpdateTexture*	param	=	m_DBuffer.Request<CmdUpdateTexture>(enCF_UpdateTexture);
	param->pSourceTexture		=	pSourceTexture->m_pIDirect3DBaseTexture9;
	param->pDestinationTexture	=	pDestinationTexture->m_pIDirect3DBaseTexture9;
	return S_OK;

};
HRESULT MT_IDirect3DDevice9::GetRenderTargetData(THIS_ MT_IDirect3DSurface9* pRenderTarget,MT_IDirect3DSurface9* pDestSurface){return S_OK;};
HRESULT MT_IDirect3DDevice9::GetFrontBufferData(THIS_ UINT iSwapChain,MT_IDirect3DSurface9* pDestSurface){return S_OK;};
HRESULT MT_IDirect3DDevice9::StretchRect(THIS_ MT_IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,MT_IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter){
	CmdStretchRect*	param	=	m_DBuffer.Request<CmdStretchRect>(enCF_StretchRect);
	param->pSourceSurface	=	pSourceSurface->m_pIDirect3DSurface9;
	param->pSourceRect		=	pSourceRect;
	param->pDestSurface		=	pDestSurface->m_pIDirect3DSurface9;
	param->pDestRect		=	pDestRect;
	param->Filter			=	Filter;
	if(pSourceRect!=NULL)
		param->src	=	*pSourceRect;
	if(pDestRect!=NULL)
		param->dst	=	*pDestRect;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::ColorFill(THIS_ MT_IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color){
	CmdColorFill*	param	=	m_DBuffer.Request<CmdColorFill>(enCF_ColorFill);
	param->pSurface			=	pSurface->m_pIDirect3DSurface9;
	param->pRect			=	pRect;
	param->color			=	color;
	if(pRect!=NULL)
		param->src			=	*pRect;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::CreateOffscreenPlainSurface(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,MT_IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle){
	IDirect3DSurface9*	pIDirect3DSurface9	=	NULL;
	HRESULT	hr	=	m_pIDirect3DDevice9->CreateOffscreenPlainSurface(Width,Height,Format,Pool,&pIDirect3DSurface9,pSharedHandle);
	if(SUCCEEDED(hr)){
		*ppSurface	=	new	MT_IDirect3DSurface9(this,pIDirect3DSurface9);
		(*ppSurface)->AddRef();
		pIDirect3DSurface9->Release();
	}
	return hr;
};
HRESULT MT_IDirect3DDevice9::SetRenderTarget(THIS_ DWORD RenderTargetIndex,MT_IDirect3DSurface9* pRenderTarget){
	CmdSetRenderTarget*	param	=	m_DBuffer.Request<CmdSetRenderTarget>(enCF_SetRenderTarget);
	param->RenderTargetIndex	=	RenderTargetIndex;
	if(pRenderTarget==NULL)
		param->pRenderTarget		=	NULL;
	else
		param->pRenderTarget		=	pRenderTarget->m_pIDirect3DSurface9;
	
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetRenderTarget(THIS_ DWORD RenderTargetIndex,MT_IDirect3DSurface9** ppRenderTarget){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetDepthStencilSurface(THIS_ MT_IDirect3DSurface9* pNewZStencil){
	CmdSetDepthStencilSurface*	param	=	m_DBuffer.Request<CmdSetDepthStencilSurface>(enCF_SetDepthStencilSurface);
	if(pNewZStencil==NULL)
		param->pNewZStencil	=	NULL;
	else
		param->pNewZStencil	=	pNewZStencil->m_pIDirect3DSurface9;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetDepthStencilSurface(THIS_ MT_IDirect3DSurface9** ppZStencilSurface){return S_OK;};
HRESULT MT_IDirect3DDevice9::BeginScene(THIS){
	m_DBuffer.Request(enCF_BeginScene);
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::EndScene(THIS){
	m_DBuffer.Request(enCF_EndScene);
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::Clear(THIS_ DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil){
	CmdClear*	param	=	NULL;
	if(pRects!=NULL && Count	>0){
		U32	uiBufferSize	=	sizeof(D3DRECT)*Count;
		void*	pBuffer		=	NULL;
		param	=	m_DBuffer.Request<CmdClear>(enCF_Clear,uiBufferSize,pBuffer);
		memcpy(pBuffer,pRects,uiBufferSize);
	}else{
		param	=	m_DBuffer.Request<CmdClear>(enCF_Clear);
	}
	
	param->Count	=	Count;
	param->pRects	=	pRects;
	param->Flags	=	Flags;
	param->Color	=	Color;
	param->Z		=	Z;
	param->Stencil	=	Stencil;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::SetTransform(THIS_ D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix){
	if(pMatrix==NULL)
		return	D3DERR_INVALIDCALL;
	CmdSetTransform*	param	=	m_DBuffer.Request<CmdSetTransform>(enCF_SetTransform);
	param->State	=	State;
	param->pMatrix	=	*pMatrix;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetTransform(THIS_ D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix){return S_OK;};
HRESULT MT_IDirect3DDevice9::MultiplyTransform(THIS_ D3DTRANSFORMSTATETYPE,CONST D3DMATRIX*){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetViewport(THIS_ CONST D3DVIEWPORT9* pViewport){
	if(pViewport==NULL)
		return	D3DERR_INVALIDCALL;
	CmdSetViewport*	param	=	m_DBuffer.Request<CmdSetViewport>(enCF_SetViewport);
	*param	=	*pViewport;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetViewport(THIS_ D3DVIEWPORT9* pViewport){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetMaterial(THIS_ CONST D3DMATERIAL9* pMaterial){
	if(pMaterial==NULL)
		return	D3DERR_INVALIDCALL;
	CmdSetMaterial*	param	=	m_DBuffer.Request<CmdSetMaterial>(enCF_SetMaterial);
	*param	=	*pMaterial;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetMaterial(THIS_ D3DMATERIAL9* pMaterial){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetLight(THIS_ DWORD Index,CONST D3DLIGHT9* pLight){
	if(pLight==NULL)
		return	D3DERR_INVALIDCALL;
	CmdSetLight*	param	=	m_DBuffer.Request<CmdSetLight>(enCF_SetLight);
	param->Index	=	Index;
	param->Light	=	*pLight;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetLight(THIS_ DWORD Index,D3DLIGHT9*){return S_OK;};
HRESULT MT_IDirect3DDevice9::LightEnable(THIS_ DWORD Index,BOOL Enable){
	CmdLightEnable*	param	=	m_DBuffer.Request<CmdLightEnable>(enCF_LightEnable);
	param->Index	=	Index;
	param->Enable	=	Enable;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetLightEnable(THIS_ DWORD Index,BOOL* pEnable){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetClipPlane(THIS_ DWORD Index,CONST float* pPlane){
	CmdSetClipPlane*	param	=	m_DBuffer.Request<CmdSetClipPlane>(enCF_SetClipPlane);
	param->Index	=	Index;
	memcpy(param->pPlane,pPlane,sizeof(float)*4);
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetClipPlane(THIS_ DWORD Index,float* pPlane){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetRenderState(THIS_ D3DRENDERSTATETYPE State,DWORD Value){
	CmdSetRenderState*	param	=	m_DBuffer.Request<CmdSetRenderState>(enCF_SetRenderState);
	param->State	=	State;
	param->Value	=	Value;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetRenderState(THIS_ D3DRENDERSTATETYPE State,DWORD* pValue){return S_OK;};
HRESULT MT_IDirect3DDevice9::CreateStateBlock(THIS_ D3DSTATEBLOCKTYPE Type,MT_IDirect3DStateBlock9** ppSB){
	IDirect3DStateBlock9*	pStateBlock=NULL;
	HRESULT	hr	=	m_pIDirect3DDevice9->CreateStateBlock(Type,&pStateBlock);
	if(SUCCEEDED(hr)){
		*ppSB	=	new MT_IDirect3DStateBlock9(this,pStateBlock);
		(*ppSB)->AddRef();
		pStateBlock->Release();
	}
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::BeginStateBlock(THIS){
	m_DBuffer.Request(enCF_BeginStateBlock);
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::EndStateBlock(THIS_ MT_IDirect3DStateBlock9** ppSB){
	*ppSB	=	new MT_IDirect3DStateBlock9(this,NULL);
	CmdEndStateBlock*	param	=	m_DBuffer.Request<CmdEndStateBlock>(enCF_EndStateBlock);
	*param	=	*ppSB;//&(*ppSB)->m_pIDirect3DStateBlock9;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::SetClipStatus(THIS_ CONST D3DCLIPSTATUS9* pClipStatus){
	CmdSetClipStatus*	param	=	m_DBuffer.Request<CmdSetClipStatus>(enCF_SetClipStatus);
	*param	=	*pClipStatus;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetClipStatus(THIS_ D3DCLIPSTATUS9* pClipStatus){return S_OK;};
HRESULT MT_IDirect3DDevice9::GetTexture(THIS_ DWORD Stage,MT_IDirect3DBaseTexture9** ppTexture){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetTexture(THIS_ DWORD Stage,MT_IDirect3DBaseTexture9* pTexture){
	CmdSetTexture*	param	=	m_DBuffer.Request<CmdSetTexture>(enCF_SetTexture);
	param->Stage			=	Stage;
	if(pTexture==NULL)
		param->pTexture	=	NULL;
	else
		param->pTexture	=	pTexture->m_pIDirect3DBaseTexture9;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetTextureStageState(THIS_ DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetTextureStageState(THIS_ DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value){
	CmdSetTextureStageState*	param	=	m_DBuffer.Request<CmdSetTextureStageState>(enCF_SetTextureStageState);
	param->Stage	=	Stage;
	param->Type		=	Type;
	param->Value	=	Value;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetSamplerState(THIS_ DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetSamplerState(THIS_ DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value){
	CmdSetSamplerState*	param	=	m_DBuffer.Request<CmdSetSamplerState>(enCF_SetSamplerState);
	param->Sampler	=	Sampler;
	param->Type		=	Type;
	param->Value	=	Value;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::ValidateDevice(THIS_ DWORD* pNumPasses){
	return m_pIDirect3DDevice9->ValidateDevice(pNumPasses);
};
HRESULT MT_IDirect3DDevice9::SetPaletteEntries(THIS_ UINT PaletteNumber,CONST PALETTEENTRY* pEntries){

	CmdSetPaletteEntries*	param	=	NULL;
	if(PaletteNumber>0&&pEntries!=NULL){
		U32		uiBufferSize	=	sizeof(PALETTEENTRY)*PaletteNumber;
		void*	pBuffer			=	NULL;
		param	=	m_DBuffer.Request<CmdSetPaletteEntries>(enCF_SetPaletteEntries,uiBufferSize,pBuffer);
		memcpy(pBuffer,pEntries,uiBufferSize);
	}else{
		param	=	m_DBuffer.Request<CmdSetPaletteEntries>(enCF_SetPaletteEntries);
	}
	param->PaletteNumber	=	PaletteNumber;
	param->pEntries			=	pEntries;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetPaletteEntries(THIS_ UINT PaletteNumber,PALETTEENTRY* pEntries){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetCurrentTexturePalette(THIS_ UINT PaletteNumber){
	CmdSetCurrentTexturePalette*	param	=	m_DBuffer.Request<CmdSetCurrentTexturePalette>(enCF_SetCurrentTexturePalette);
	*param	=	PaletteNumber;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetCurrentTexturePalette(THIS_ UINT *PaletteNumber){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetScissorRect(THIS_ CONST RECT* pRect){
	CmdSetScissorRect*	param	=	m_DBuffer.Request<CmdSetScissorRect>(enCF_SetScissorRect);
	*param	=	*pRect;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetScissorRect(THIS_ RECT* pRect){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetSoftwareVertexProcessing(THIS_ BOOL bSoftware){
	CmdSetSoftwareVertexProcessing*	param	=	m_DBuffer.Request<CmdSetSoftwareVertexProcessing>(enCF_SetSoftwareVertexProcessing);
	*param	=	bSoftware;
	return S_OK;
};
BOOL	MT_IDirect3DDevice9::GetSoftwareVertexProcessing(THIS){return FALSE;};
HRESULT MT_IDirect3DDevice9::SetNPatchMode(THIS_ float nSegments){
	CmdSetNPatchMode*	param	=	m_DBuffer.Request<CmdSetNPatchMode>(enCF_SetNPatchMode);
	*param	=	nSegments;
	return S_OK;
};
float	MT_IDirect3DDevice9::GetNPatchMode(THIS){return 1.0f;};
HRESULT MT_IDirect3DDevice9::DrawPrimitive(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount){
	CmdDrawPrimitive*	param	=	m_DBuffer.Request<CmdDrawPrimitive>(enCF_DrawPrimitive);
	param->PrimitiveType	=	PrimitiveType;
	param->StartVertex		=	StartVertex;
	param->PrimitiveCount	=	PrimitiveCount;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::DrawIndexedPrimitive(THIS_ D3DPRIMITIVETYPE PrimitiveType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount){
	CmdDrawIndexedPrimitive*	param	=	m_DBuffer.Request<CmdDrawIndexedPrimitive>(enCF_DrawIndexedPrimitive);
	param->PrimitiveType	=	PrimitiveType;
	param->BaseVertexIndex	=	BaseVertexIndex;
	param->MinVertexIndex	=	MinVertexIndex;
	param->NumVertices		=	NumVertices;
	param->startIndex		=	startIndex;
	param->primCount		=	primCount;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::DrawPrimitiveUP(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride){return S_OK;};
HRESULT MT_IDirect3DDevice9::DrawIndexedPrimitiveUP(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride){return S_OK;};
HRESULT MT_IDirect3DDevice9::ProcessVertices(THIS_ UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,MT_IDirect3DVertexBuffer9* pDestBuffer,MT_IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags){return S_OK;};
HRESULT MT_IDirect3DDevice9::CreateVertexDeclaration(THIS_ CONST D3DVERTEXELEMENT9* pVertexElements,MT_IDirect3DVertexDeclaration9** ppDecl){
	IDirect3DVertexDeclaration9*	pIDirect3DVertexDeclaration9	=	NULL;
	HRESULT	hr	=	m_pIDirect3DDevice9->CreateVertexDeclaration(pVertexElements,&pIDirect3DVertexDeclaration9);
	if(SUCCEEDED(hr)){
		*ppDecl	=	new	MT_IDirect3DVertexDeclaration9(this,pIDirect3DVertexDeclaration9);
		(*ppDecl)->AddRef();
		pIDirect3DVertexDeclaration9->Release();
	}
	return hr;
};
HRESULT MT_IDirect3DDevice9::SetVertexDeclaration(THIS_ MT_IDirect3DVertexDeclaration9* pDecl){
	CmdSetVertexDeclaration*	param	=	m_DBuffer.Request<CmdSetVertexDeclaration>(enCF_SetVertexDeclaration);
	if(pDecl==NULL)
		*param	=	NULL;
	else
		*param	=	pDecl->m_pIDirect3DVertexDeclaration9;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetVertexDeclaration(THIS_ MT_IDirect3DVertexDeclaration9** ppDecl){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetFVF(THIS_ DWORD FVF){
	CmdSetFVF*	param	=	m_DBuffer.Request<CmdSetFVF>(enCF_SetFVF);
	*param	=	FVF;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetFVF(THIS_ DWORD* pFVF){return S_OK;};
HRESULT MT_IDirect3DDevice9::CreateVertexShader(THIS_ CONST DWORD* pFunction,MT_IDirect3DVertexShader9** ppShader){
	IDirect3DVertexShader9*	pIDirect3DVertexShader9	=	NULL;
	HRESULT	hr	=	m_pIDirect3DDevice9->CreateVertexShader(pFunction,&pIDirect3DVertexShader9);
	if(SUCCEEDED(hr)){
		*ppShader	=	new	MT_IDirect3DVertexShader9(this,pIDirect3DVertexShader9);
		(*ppShader)->AddRef();
		pIDirect3DVertexShader9->Release();
	}
	return hr;
};
HRESULT MT_IDirect3DDevice9::SetVertexShader(THIS_ MT_IDirect3DVertexShader9* pShader){
	CmdSetVertexShader*	param	=	m_DBuffer.Request<CmdSetVertexShader>(enCF_SetVertexShader);
	if(pShader==NULL)
		*param	=	NULL;
	else
		*param	=	pShader->m_pIDirect3DVertexShader9;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetVertexShader(THIS_ MT_IDirect3DVertexShader9** ppShader){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetVertexShaderConstantF(THIS_ UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount){
	U32		uiBufferSize	=	sizeof(float)*4*Vector4fCount;
	void*	pBuffer			=	NULL;
	CmdSetVertexShaderConstantF*	param	=	m_DBuffer.Request<CmdSetVertexShaderConstantF>(enCF_SetVertexShaderConstantF,uiBufferSize,pBuffer);
	memcpy(pBuffer,pConstantData,uiBufferSize);
	param->StartRegister	=	StartRegister;
	param->Vector4fCount	=	Vector4fCount;

	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetVertexShaderConstantF(THIS_ UINT StartRegister,float* pConstantData,UINT Vector4fCount){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetVertexShaderConstantI(THIS_ UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount){
	U32		uiBufferSize	=	sizeof(int)*4*Vector4iCount;
	void*	pBuffer			=	NULL;
	CmdSetVertexShaderConstantI*	param	=	m_DBuffer.Request<CmdSetVertexShaderConstantI>(enCF_SetVertexShaderConstantI,uiBufferSize,pBuffer);
	memcpy(pBuffer,pConstantData,uiBufferSize);
	param->StartRegister	=	StartRegister;
	param->Vector4iCount	=	Vector4iCount;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetVertexShaderConstantI(THIS_ UINT StartRegister,int* pConstantData,UINT Vector4iCount){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetVertexShaderConstantB(THIS_ UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount){
	U32		uiBufferSize	=	sizeof(BOOL)*BoolCount;
	void*	pBuffer			=	NULL;
	CmdSetVertexShaderConstantB*	param	=	m_DBuffer.Request<CmdSetVertexShaderConstantB>(enCF_SetVertexShaderConstantB,uiBufferSize,pBuffer);
	memcpy(pBuffer,pConstantData,uiBufferSize);
	param->StartRegister	=	StartRegister;
	param->BoolCount	=	BoolCount;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetVertexShaderConstantB(THIS_ UINT StartRegister,BOOL* pConstantData,UINT BoolCount){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetStreamSource(THIS_ UINT StreamNumber,MT_IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride){
	CmdSetStreamSource*	param	=	m_DBuffer.Request<CmdSetStreamSource>(enCF_SetStreamSource);
	param->StreamNumber		=	StreamNumber;
	if(pStreamData==NULL)
		param->pStreamData	=	NULL;
	else
		param->pStreamData	=	pStreamData->m_pIDirect3DVertexBuffer9;
	param->OffsetInBytes	=	OffsetInBytes;
	param->Stride	=	Stride;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetStreamSource(THIS_ UINT StreamNumber,MT_IDirect3DVertexBuffer9** ppStreamData,UINT* pOffsetInBytes,UINT* pStride){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetStreamSourceFreq(THIS_ UINT StreamNumber,UINT Setting){
	CmdSetStreamSourceFreq*	param	=	m_DBuffer.Request<CmdSetStreamSourceFreq>(enCF_SetStreamSourceFreq);
	param->StreamNumber		=	StreamNumber;
	param->Setting	=	Setting;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetStreamSourceFreq(THIS_ UINT StreamNumber,UINT* pSetting){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetIndices(THIS_ MT_IDirect3DIndexBuffer9* pIndexData){
	CmdSetIndices*	param	=	m_DBuffer.Request<CmdSetIndices>(enCF_SetIndices);
	if(pIndexData==NULL)
		*param	=	NULL;
	else
		*param	=	pIndexData->m_pIDirect3DIndexBuffer9;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetIndices(THIS_ MT_IDirect3DIndexBuffer9** ppIndexData){return S_OK;};
HRESULT MT_IDirect3DDevice9::CreatePixelShader(THIS_ CONST DWORD* pFunction,MT_IDirect3DPixelShader9** ppShader){
	IDirect3DPixelShader9*	pIDirect3DPixelShader9	=	NULL;
	HRESULT	hr	=	m_pIDirect3DDevice9->CreatePixelShader(pFunction,&pIDirect3DPixelShader9);
	if(SUCCEEDED(hr)){
		*ppShader	=	new	MT_IDirect3DPixelShader9(this,pIDirect3DPixelShader9);
		(*ppShader)->AddRef();
		pIDirect3DPixelShader9->Release();
	}
	return hr;
};
HRESULT MT_IDirect3DDevice9::SetPixelShader(THIS_ MT_IDirect3DPixelShader9* pShader){
	CmdSetPixelShader*	param	=	m_DBuffer.Request<CmdSetPixelShader>(enCF_SetPixelShader);
	if(pShader==NULL)
		*param	=	NULL;
	else
		*param	=	pShader->m_pIDirect3DPixelShader9;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetPixelShader(THIS_ MT_IDirect3DPixelShader9** ppShader){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetPixelShaderConstantF(THIS_ UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount){
	U32		uiBufferSize	=	sizeof(float)*4*Vector4fCount;
	void*	pBuffer			=	NULL;
	CmdSetPixelShaderConstantF*	param	=	m_DBuffer.Request<CmdSetPixelShaderConstantF>(enCF_SetPixelShaderConstantF,uiBufferSize,pBuffer);
	memcpy(pBuffer,pConstantData,uiBufferSize);
	param->StartRegister	=	StartRegister;
	param->Vector4fCount	=	Vector4fCount;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetPixelShaderConstantF(THIS_ UINT StartRegister,float* pConstantData,UINT Vector4fCount){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetPixelShaderConstantI(THIS_ UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount){
	U32		uiBufferSize	=	sizeof(int)*4*Vector4iCount;
	void*	pBuffer			=	NULL;
	CmdSetPixelShaderConstantI*	param	=	m_DBuffer.Request<CmdSetPixelShaderConstantI>(enCF_SetPixelShaderConstantI,uiBufferSize,pBuffer);
	memcpy(pBuffer,pConstantData,uiBufferSize);
	param->StartRegister	=	StartRegister;
	param->Vector4iCount	=	Vector4iCount;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetPixelShaderConstantI(THIS_ UINT StartRegister,int* pConstantData,UINT Vector4iCount){return S_OK;};
HRESULT MT_IDirect3DDevice9::SetPixelShaderConstantB(THIS_ UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount){
	U32		uiBufferSize	=	sizeof(BOOL)*BoolCount;
	void*	pBuffer			=	NULL;
	CmdSetPixelShaderConstantB*	param	=	m_DBuffer.Request<CmdSetPixelShaderConstantB>(enCF_SetPixelShaderConstantB,uiBufferSize,pBuffer);
	memcpy(pBuffer,pConstantData,uiBufferSize);
	param->StartRegister	=	StartRegister;
	param->BoolCount	=	BoolCount;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::GetPixelShaderConstantB(THIS_ UINT StartRegister,BOOL* pConstantData,UINT BoolCount){return S_OK;};
HRESULT MT_IDirect3DDevice9::DrawRectPatch(THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo){return S_OK;};
HRESULT MT_IDirect3DDevice9::DrawTriPatch(THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo){return S_OK;};
HRESULT MT_IDirect3DDevice9::DeletePatch(THIS_ UINT Handle){return S_OK;};
HRESULT MT_IDirect3DDevice9::CreateQuery(THIS_ D3DQUERYTYPE Type,MT_IDirect3DQuery9** ppQuery){
	IDirect3DQuery9*	pIDirect3DQuery9	=	NULL;
	HRESULT	hr	=	m_pIDirect3DDevice9->CreateQuery(Type,&pIDirect3DQuery9);
	if(SUCCEEDED(hr)){
		*ppQuery	=	new	MT_IDirect3DQuery9(this,pIDirect3DQuery9);
		(*ppQuery)->AddRef();
		pIDirect3DQuery9->Release();
	}
	return hr;
};

HRESULT	MT_IDirect3DDevice9::SwapChain_Present(IDirect3DSwapChain9*	pSwapChain,THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags){
	CmdSwapChain_Present*	param	=	m_DBuffer.Request<CmdSwapChain_Present>(enCF_SwapChain_Present);
	param->pSwapChain		=	pSwapChain;
	param->pSourceRect		=	pSourceRect;
	param->pDestRect		=	pDestRect;
	param->hDestWindowOverride		=	hDestWindowOverride;
	param->pDirtyRegion		=	pDirtyRegion;
	param->dwFlags			=	dwFlags;
	param->pSourceRect		=	pSourceRect;
	if(pSourceRect!=NULL)
		param->src		=	*pSourceRect;
	if(pDestRect!=NULL)
		param->dst		=	*pDestRect;
	if(pDirtyRegion!=NULL)
		param->dirty	=	*pDirtyRegion;
	return S_OK;
};
HRESULT	MT_IDirect3DDevice9::Surface_LockRect(IDirect3DSurface9*	pSurface,THIS_ D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags){
	D3DSURFACE_DESC	desc;
	pSurface->GetDesc(&desc);
	
	U32	uiFormatSize	=	BitsPerPixel(desc.Format);
	U32	uiBufferSize	=	desc.Width*desc.Height;
	if(pRect!=NULL){
		uiBufferSize	=	(pRect->right	-	pRect->left)	*	(pRect->bottom	-	pRect->top);
	}
	uiBufferSize*=uiFormatSize;
	uiBufferSize/=8;
	void*	pBuffer		=	NULL;
	
	CmdSurface_LockRect*	param	=	m_DBuffer.Request<CmdSurface_LockRect>(enCF_Surface_LockRect,uiBufferSize,pBuffer);
	param->pSurface	=	pSurface;
	param->pRect	=	pRect;
	param->Flags	=	Flags;
	param->dwLockSize	=	uiBufferSize;
	if(pRect!=NULL)
		param->rData	=	*pRect;

	pLockedRect->pBits	=	pBuffer;
	return S_OK;
};
HRESULT	MT_IDirect3DDevice9::Surface_UnlockRect(IDirect3DSurface9*	pSurface){
	CmdSurface_UnlockRect*	param	=	m_DBuffer.Request<CmdSurface_UnlockRect>(enCF_Surface_UnlockRect);
	*param	=	pSurface;
	return S_OK;
};
HRESULT MT_IDirect3DDevice9::Volume_LockBox(IDirect3DVolume9*	pVolume,THIS_ D3DLOCKED_BOX * pLockedVolume,CONST D3DBOX* pBox,DWORD Flags){
	D3DVOLUME_DESC	desc;
	pVolume->GetDesc(&desc);
	
	U32	uiFormatSize	=	BitsPerPixel(desc.Format);
	U32	uiBufferSize	=	desc.Width*desc.Height*desc.Depth;
	if(pBox!=NULL){
		uiBufferSize	=	(pBox->Right	-	pBox->Left)		*	
							(pBox->Bottom	-	pBox->Top)		*
							(pBox->Back		-	pBox->Front);
	}
	uiBufferSize*=uiFormatSize;
	uiBufferSize/=8;
	void*	pBuffer		=	NULL;
	
	CmdVolume_LockBox*	param	=	m_DBuffer.Request<CmdVolume_LockBox>(enCF_Volume_LockBox,uiBufferSize,pBuffer);
	param->pVolume	=	pVolume;
	param->pBox		=	pBox;
	param->Flags	=	Flags;
	if(pBox!=NULL)
		param->boxData	=	*pBox;

	pLockedVolume->pBits	=	pBuffer;

	return S_OK;
};
HRESULT MT_IDirect3DDevice9::Volume_UnlockBox(IDirect3DVolume9*	pVolume){
	CmdVolume_UnlockBox*	param	=	m_DBuffer.Request<CmdVolume_UnlockBox>(enCF_Volume_UnlockBox);
	*param	=	pVolume;
	return S_OK;
};
HRESULT	MT_IDirect3DDevice9::VertexBuffer_Lock(IDirect3DVertexBuffer9*	pVB,THIS_ UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags){
	UINT	uiBufferSize	=	SizeToLock;
	if(uiBufferSize==0)
	{
		D3DVERTEXBUFFER_DESC	vbDesc;
		pVB->GetDesc(&vbDesc);
		uiBufferSize	=	vbDesc.Size;
	}
	void*	pBuffer	=	NULL;
	CmdVertexBuffer_Lock*	param	=	m_DBuffer.Request<CmdVertexBuffer_Lock>(enCF_VertexBuffer_Lock,uiBufferSize,pBuffer);
	param->pVB			=	pVB;
	param->OffsetToLock	=	OffsetToLock;
	param->SizeToLock	=	uiBufferSize;
	param->Flags		=	Flags;


	*ppbData			=	pBuffer;
	return S_OK;
};
HRESULT	MT_IDirect3DDevice9::VertexBuffer_Unlock(IDirect3DVertexBuffer9*	pVB){
	CmdVertexBuffer_Unlock*	param	=	m_DBuffer.Request<CmdVertexBuffer_Unlock>(enCF_VertexBuffer_Unlock);
	*param	=	pVB;
	return S_OK;
};
HRESULT	MT_IDirect3DDevice9::IndexBuffer_Lock(IDirect3DIndexBuffer9*	pIB,THIS_ UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags){
	UINT	uiBufferSize	=	SizeToLock;
	if(uiBufferSize==0)
	{
		D3DINDEXBUFFER_DESC	ibDesc;
		pIB->GetDesc(&ibDesc);
		uiBufferSize	=	ibDesc.Size;
	}

	void*	pBuffer	=	NULL;
	CmdIndexBuffer_Lock*	param	=	m_DBuffer.Request<CmdIndexBuffer_Lock>(enCF_IndexBuffer_Lock,uiBufferSize,pBuffer);
	param->pIB			=	pIB;
	param->OffsetToLock	=	OffsetToLock;
	param->SizeToLock	=	uiBufferSize;
	param->Flags		=	Flags;


	*ppbData			=	pBuffer;
	return S_OK;
};
HRESULT	MT_IDirect3DDevice9::IndexBuffer_Unlock(IDirect3DIndexBuffer9*	pIB){
	CmdIndexBuffer_Unlock*	param	=	m_DBuffer.Request<CmdIndexBuffer_Unlock>(enCF_IndexBuffer_Unlock);
	*param	=	pIB;
	return S_OK;
};
HRESULT	MT_IDirect3DDevice9::BaseTexture_SetAutoGenFilterType(IDirect3DBaseTexture9*	pTex,THIS_ D3DTEXTUREFILTERTYPE FilterType){
	CmdBaseTexture_SetAutoGenFilterType*	param	=	m_DBuffer.Request<CmdBaseTexture_SetAutoGenFilterType>(enCF_BaseTexture_SetAutoGenFilterType);
	param->pTex			=	pTex;
	param->FilterType	=	FilterType;
	return S_OK;
};
HRESULT	MT_IDirect3DDevice9::BaseTexture_GenerateMipSubLevels(IDirect3DBaseTexture9*	pTex){
	CmdBaseTexture_GenerateMipSubLevels*	param	=	m_DBuffer.Request<CmdBaseTexture_GenerateMipSubLevels>(enCF_BaseTexture_GenerateMipSubLevels);
	*param	=	pTex;
	return S_OK;
};
HRESULT	MT_IDirect3DDevice9::Texture_LockRect(IDirect3DTexture9*	pTex,THIS_ UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags){
	D3DSURFACE_DESC	desc;
	pTex->GetLevelDesc(Level,&desc);
	
	U32	uiFormatSize	=	BitsPerPixel(desc.Format);
	U32	uiBufferSize	=	desc.Width*desc.Height;
	if(pRect!=NULL){
		uiBufferSize	=	(pRect->right	-	pRect->left)	*	(pRect->bottom	-	pRect->top);
	}
	uiBufferSize*=uiFormatSize;
	uiBufferSize/=8;
	void*	pBuffer		=	NULL;
	
	CmdTexture_LockRect*	param	=	m_DBuffer.Request<CmdTexture_LockRect>(enCF_Texture_LockRect,uiBufferSize,pBuffer);
	param->pTex		=	pTex;
	param->Level	=	Level;
	param->pRect	=	pRect;
	param->Flags	=	Flags;
	param->dwLockSize	=	uiBufferSize;
	if(pRect!=NULL)
		param->rData	=	*pRect;

	pLockedRect->pBits	=	pBuffer;
	return S_OK;
};
HRESULT	MT_IDirect3DDevice9::Texture_UnLockRect(IDirect3DTexture9*	pTex,THIS_ UINT Level){
	CmdTexture_UnlockRect*	param	=	m_DBuffer.Request<CmdTexture_UnlockRect>(enCF_Texture_UnlockRect);
	param->pTex			=	pTex;
	param->Level		=	Level;
	return S_OK;
};
HRESULT	MT_IDirect3DDevice9::Texture_AddDirtyRect(IDirect3DTexture9*	pTex,THIS_ CONST RECT* pDirtyRect){
	CmdTexture_AddDirtyRect*	param	=	m_DBuffer.Request<CmdTexture_AddDirtyRect>(enCF_Texture_AddDirtyRect);
	param->pTex				=	pTex;
	param->pDirtyRect		=	*pDirtyRect;

	return S_OK;
};
HRESULT	MT_IDirect3DDevice9::CubeTexture_LockRect(IDirect3DCubeTexture9*	pTex,THIS_ D3DCUBEMAP_FACES FaceType,UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags){
	D3DSURFACE_DESC	desc;
	pTex->GetLevelDesc(Level,&desc);
	
	U32	uiFormatSize	=	BitsPerPixel(desc.Format);
	U32	uiBufferSize	=	desc.Width*desc.Height;
	if(pRect!=NULL){
		uiBufferSize	=	(pRect->right	-	pRect->left)	*	(pRect->bottom	-	pRect->top);
	}
	uiBufferSize*=uiFormatSize;
	uiBufferSize/=8;
	void*	pBuffer		=	NULL;
	
	CmdCubeTexture_LockRect*	param	=	m_DBuffer.Request<CmdCubeTexture_LockRect>(enCF_CubeTexture_LockRect,uiBufferSize,pBuffer);
	param->pCubeTex		=	pTex;
	param->FaceType	=	FaceType;
	param->Level	=	Level;
	param->pRect	=	pRect;
	param->Flags	=	Flags;
	param->dwLockSize	=	uiBufferSize;
	if(pRect!=NULL)
		param->rData	=	*pRect;

	pLockedRect->pBits	=	pBuffer;
	
	return S_OK;
};
HRESULT	MT_IDirect3DDevice9::CubeTexture_UnlockRect(IDirect3DCubeTexture9*	pTex,THIS_ D3DCUBEMAP_FACES FaceType,UINT Level){
	CmdCubeTexture_UnlockRect*	param	=	m_DBuffer.Request<CmdCubeTexture_UnlockRect>(enCF_CubeTexture_UnlockRect);
	param->pCubeTex		=	pTex;
	param->FaceType		=	FaceType;
	param->Level		=	Level;
	
	return S_OK;
};
HRESULT	MT_IDirect3DDevice9::CubeTexture_AddDirtyRect(IDirect3DCubeTexture9*	pTex,THIS_ D3DCUBEMAP_FACES FaceType,CONST RECT* pDirtyRect){
	CmdCubeTexture_AddDirtyRect*	param	=	m_DBuffer.Request<CmdCubeTexture_AddDirtyRect>(enCF_CubeTexture_AddDirtyRect);
	param->pCubeTex		=	pTex;
	param->FaceType		=	FaceType;
	param->pDirtyRect	=	*pDirtyRect;
	return S_OK;
};
HRESULT	MT_IDirect3DDevice9::VolumeTexture_LockBox(IDirect3DVolumeTexture9*	pVolumeTex,THIS_ UINT Level,D3DLOCKED_BOX* pLockedVolume,CONST D3DBOX* pBox,DWORD Flags){
	D3DVOLUME_DESC	desc;
	pVolumeTex->GetLevelDesc(Level,&desc);
	
	U32	uiFormatSize	=	BitsPerPixel(desc.Format);
	U32	uiBufferSize	=	desc.Width*desc.Height*desc.Depth;
	if(pBox!=NULL){
		uiBufferSize	=	(pBox->Right	-	pBox->Left)		*	
							(pBox->Bottom	-	pBox->Top)		*
							(pBox->Back		-	pBox->Front);
	}
	uiBufferSize*=uiFormatSize;
	uiBufferSize/=8;
	void*	pBuffer		=	NULL;
	
	CmdVolumeTexture_LockBox*	param	=	m_DBuffer.Request<CmdVolumeTexture_LockBox>(enCF_VolumeTexture_LockBox,uiBufferSize,pBuffer);
	param->pVolumeTex	=	pVolumeTex;
	param->Level	=	Level;
	param->pBox		=	pBox;
	param->Flags	=	Flags;
	param->dwLockSize	=	uiBufferSize;
	if(pBox!=NULL)
		param->boxData	=	*pBox;

	pLockedVolume->pBits	=	pBuffer;

	return S_OK;
};
HRESULT	MT_IDirect3DDevice9::VolumeTexture_UnlockBox(IDirect3DVolumeTexture9*	pVolumeTex,THIS_ UINT Level){
	CmdVolumeTexture_UnlockBox*	param	=	m_DBuffer.Request<CmdVolumeTexture_UnlockBox>(enCF_VolumeTexture_UnlockBox);
	param->pVolumeTex	=	pVolumeTex;
	param->Level		=	Level;
	
	return S_OK;
	return S_OK;
};
HRESULT	MT_IDirect3DDevice9::VolumeTexture_AddDirtyBox(IDirect3DVolumeTexture9*	pVolumeTex,THIS_ CONST D3DBOX* pDirtyBox){
	CmdVolumeTexture_AddDirtyBox*	param	=	m_DBuffer.Request<CmdVolumeTexture_AddDirtyBox>(enCF_VolumeTexture_AddDirtyBox);
	param->pVolumeTex	=	pVolumeTex;
	param->pDirtyBox	=	*pDirtyBox;

	return S_OK;
};
HRESULT	MT_IDirect3DDevice9::StateBlock_Apply(IDirect3DStateBlock9* pStateBlock){
	CmdStateBlock_Apply*	param	=	m_DBuffer.Request<CmdStateBlock_Apply>(enCF_StateBlock_Apply);
	*param	=	pStateBlock;
	return S_OK;
};
HRESULT	MT_IDirect3DDevice9::StateBlock_Capture(IDirect3DStateBlock9* pStateBlock){
	CmdStateBlock_Capture*	param	=	m_DBuffer.Request<CmdStateBlock_Capture>(enCF_StateBlock_Capture);
	*param	=	pStateBlock;
	return S_OK;
};

int		MT_IDirect3DDevice9::PIX_D3DPERF_BeginEvent(D3DCOLOR col,LPCWSTR wszName){
	static wchar_t	str[]	=	L"Unknown";
	if(wszName==NULL)
		wszName	=	str;
	U32	uiBufferSize	=	(wcslen(wszName)+1)*2;
	void*	pBuffer		=	NULL;
	CmdPIX_D3DPERF_BeginEvent*	param	=	m_DBuffer.Request<CmdPIX_D3DPERF_BeginEvent>(enCF_PIX_D3DPERF_BeginEvent,uiBufferSize,pBuffer);
	param->col			=	col;
	param->dwNameSize	=	uiBufferSize;
	memcpy(pBuffer,wszName,uiBufferSize);

	return	0;
}
int		MT_IDirect3DDevice9::PIX_D3DPERF_EndEvent(){
	m_DBuffer.Request(enCF_PIX_D3DPERF_EndEvent);
	return	0;
}
void	MT_IDirect3DDevice9::PIX_D3DPERF_SetMarker(D3DCOLOR col,LPCWSTR wszName){
	static wchar_t	str[]	=	L"UnknownMarker";
	if(wszName==NULL)
		wszName	=	str;
	U32	uiBufferSize	=	(wcslen(wszName)+1)*2;
	void*	pBuffer		=	NULL;
	CmdPIX_D3DPERF_SetMarker*	param	=	m_DBuffer.Request<CmdPIX_D3DPERF_SetMarker>(enCF_PIX_D3DPERF_SetMarker,uiBufferSize,pBuffer);
	param->col			=	col;
	param->dwNameSize	=	uiBufferSize;

	memcpy(pBuffer,wszName,uiBufferSize);
}

HRESULT	MT_IDirect3DDevice9::Effect_SetValue(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, LPCVOID pData, UINT Bytes){
	void*	pBuffer		=	NULL;
	CmdEffect_SetValue*	param	=	m_DBuffer.Request<CmdEffect_SetValue>(enCF_Effect_SetValue,Bytes,pBuffer);
	param->pID3DXEffect	=	pID3DXEffect;
	param->Bytes		=	Bytes;
	memcpy(pBuffer,pData,Bytes);
	return	S_OK;
}
HRESULT	MT_IDirect3DDevice9::Effect_SetBool(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, BOOL b){
	CmdEffect_SetBool*	param	=	m_DBuffer.Request<CmdEffect_SetBool>(enCF_Effect_SetBool);
	param->pID3DXEffect	=	pID3DXEffect;
	param->hParameter	=	hParameter;
	param->b			=	b;
	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_SetBoolArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST BOOL* pb, UINT Count){
	U32	uiBufferSize	=	sizeof(BOOL)*Count;
	void*	pBuffer		=	NULL;
	CmdEffect_SetBoolArray*	param	=	m_DBuffer.Request<CmdEffect_SetBoolArray>(enCF_Effect_SetBoolArray,uiBufferSize,pBuffer);
	param->pID3DXEffect	=	pID3DXEffect;
	param->hParameter	=	hParameter;
	param->Count		=	Count;
	memcpy(pBuffer,pb,uiBufferSize);
	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_SetInt(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, INT n){
	CmdEffect_SetInt*	param	=	m_DBuffer.Request<CmdEffect_SetInt>(enCF_Effect_SetInt);
	param->pID3DXEffect	=	pID3DXEffect;
	param->hParameter	=	hParameter;
	param->n			=	n;
	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_SetIntArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST INT* pn, UINT Count)
{
	U32	uiBufferSize	=	sizeof(INT)*Count;
	void*	pBuffer		=	NULL;
	CmdEffect_SetIntArray*	param	=	m_DBuffer.Request<CmdEffect_SetIntArray>(enCF_Effect_SetIntArray,uiBufferSize,pBuffer);
	param->pID3DXEffect	=	pID3DXEffect;
	param->hParameter	=	hParameter;
	param->Count		=	Count;
	memcpy(pBuffer,pn,uiBufferSize);
	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_SetFloat(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, FLOAT f){
	CmdEffect_SetFloat*	param	=	m_DBuffer.Request<CmdEffect_SetFloat>(enCF_Effect_SetFloat);
	param->pID3DXEffect	=	pID3DXEffect;
	param->hParameter	=	hParameter;
	param->f			=	f;
	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_SetFloatArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST FLOAT* pf, UINT Count){
	U32	uiBufferSize	=	sizeof(INT)*Count;
	void*	pBuffer		=	NULL;
	CmdEffect_SetFloatArray*	param	=	m_DBuffer.Request<CmdEffect_SetFloatArray>(enCF_Effect_SetFloatArray,uiBufferSize,pBuffer);
	param->pID3DXEffect	=	pID3DXEffect;
	param->hParameter	=	hParameter;
	param->Count		=	Count;
	memcpy(pBuffer,pf,uiBufferSize);
	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_SetVector(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector){
	CmdEffect_SetVector*	param	=	m_DBuffer.Request<CmdEffect_SetVector>(enCF_Effect_SetVector);
	param->pID3DXEffect	=	pID3DXEffect;
	param->hParameter	=	hParameter;
	param->pVector		=	*pVector;
	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_SetVectorArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector, UINT Count){
	U32	uiBufferSize	=	sizeof(D3DXVECTOR4)*Count;
	void*	pBuffer		=	NULL;
	CmdEffect_SetVectorArray*	param	=	m_DBuffer.Request<CmdEffect_SetVectorArray>(enCF_Effect_SetVectorArray,uiBufferSize,pBuffer);
	param->pID3DXEffect	=	pID3DXEffect;
	param->hParameter	=	hParameter;
	param->Count		=	Count;
	memcpy(pBuffer,pVector,uiBufferSize);
	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_SetMatrix(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix){
	CmdEffect_SetMatrix*	param	=	m_DBuffer.Request<CmdEffect_SetMatrix>(enCF_Effect_SetMatrix);
	param->pID3DXEffect	=	pID3DXEffect;
	param->hParameter	=	hParameter;
	param->pMatrix		=	*pMatrix;
	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_SetMatrixArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count){
	U32	uiBufferSize	=	sizeof(D3DXMATRIX)*Count;
	void*	pBuffer		=	NULL;
	CmdEffect_SetMatrixArray*	param	=	m_DBuffer.Request<CmdEffect_SetMatrixArray>(enCF_Effect_SetMatrixArray,uiBufferSize,pBuffer);
	param->pID3DXEffect	=	pID3DXEffect;
	param->hParameter	=	hParameter;
	param->Count		=	Count;
	memcpy(pBuffer,pMatrix,uiBufferSize);
	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_SetMatrixPointerArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count){
	//U32	uiBufferSize	=	sizeof(D3DXMATRIX)*Count;
	//void*	pBuffer		=	NULL;
	//CmdEffect_SetMatrixArray*	param	=	m_DBuffer.Request<CmdEffect_SetMatrixArray>(enCF_Effect_SetMatrixArray,uiBufferSize,pBuffer);
	//param->pID3DXEffect	=	pID3DXEffect;
	//param->hParameter	=	hParameter;
	//param->Count		=	Count;
	//memcpy(pBuffer,pMatrix,uiBufferSize);
	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_SetMatrixTranspose(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix){
	CmdEffect_SetMatrixTranspose*	param	=	m_DBuffer.Request<CmdEffect_SetMatrixTranspose>(enCF_Effect_SetMatrixTranspose);
	param->pID3DXEffect	=	pID3DXEffect;
	param->hParameter	=	hParameter;
	param->pMatrix		=	*pMatrix;
	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_SetMatrixTransposeArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count){
	U32	uiBufferSize	=	sizeof(D3DXMATRIX)*Count;
	void*	pBuffer		=	NULL;
	CmdEffect_SetMatrixTransposeArray*	param	=	m_DBuffer.Request<CmdEffect_SetMatrixTransposeArray>(enCF_Effect_SetMatrixTransposeArray,uiBufferSize,pBuffer);
	param->pID3DXEffect	=	pID3DXEffect;
	param->hParameter	=	hParameter;
	param->Count		=	Count;
	memcpy(pBuffer,pMatrix,uiBufferSize);
	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_SetMatrixTransposePointerArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count){
	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_SetString(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, LPCSTR pString){
	U32	uiBufferSize	=	strlen(pString)+1;
	void*	pBuffer		=	NULL;
	CmdEffect_SetString*	param	=	m_DBuffer.Request<CmdEffect_SetString>(enCF_Effect_SetString,uiBufferSize,pBuffer);
	param->pID3DXEffect	=	pID3DXEffect;
	param->hParameter	=	hParameter;
	param->uiBufferSize	=	uiBufferSize;
	memcpy(pBuffer,pString,uiBufferSize);
	return	S_OK;
}
HRESULT	MT_IDirect3DDevice9::Effect_SetTexture(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, LPDIRECT3DBASETEXTURE9 pTexture){
	CmdEffect_SetTexture*	param	=	m_DBuffer.Request<CmdEffect_SetTexture>(enCF_Effect_SetTexture);
	param->pID3DXEffect	=	pID3DXEffect;
	param->hParameter	=	hParameter;
	param->pTexture		=	pTexture;
	return	S_OK;
};

HRESULT	MT_IDirect3DDevice9::Effect_SetTechnique(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hTechnique){
	CmdEffect_SetTechnique*	param	=	m_DBuffer.Request<CmdEffect_SetTechnique>(enCF_Effect_SetTechnique);
	param->pID3DXEffect	=	pID3DXEffect;
	param->hTechnique	=	hTechnique;

	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_Begin(ID3DXEffect* pID3DXEffect,THIS_ UINT *pPasses, DWORD Flags){
	CmdEffect_Begin*	param	=	m_DBuffer.Request<CmdEffect_Begin>(enCF_Effect_Begin);
	param->pID3DXEffect			=	pID3DXEffect;
	param->Flags				=	Flags;
	//Not Allow Mutli Pass!So Return 1;
	*pPasses	=	1;

	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_BeginPass(ID3DXEffect* pID3DXEffect,THIS_ UINT Pass){
	CmdEffect_BeginPass*	param	=	m_DBuffer.Request<CmdEffect_BeginPass>(enCF_Effect_BeginPass);
	param->pID3DXEffect			=	pID3DXEffect;
	param->Pass				=	Pass;

	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_CommitChanges(ID3DXEffect* pID3DXEffect){
	CmdEffect_CommitChanges*	param	=	m_DBuffer.Request<CmdEffect_CommitChanges>(enCF_Effect_CommitChanges);
	(*param)	=	pID3DXEffect;
	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_EndPass(ID3DXEffect* pID3DXEffect){
	CmdEffect_EndPass*	param	=	m_DBuffer.Request<CmdEffect_EndPass>(enCF_Effect_EndPass);
	(*param)	=	pID3DXEffect;
	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_End(ID3DXEffect* pID3DXEffect){
	CmdEffect_End*	param	=	m_DBuffer.Request<CmdEffect_End>(enCF_Effect_End);
	(*param)	=	pID3DXEffect;
	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_SetStateManager(ID3DXEffect* pID3DXEffect,THIS_ LPD3DXEFFECTSTATEMANAGER pManager){
	CmdEffect_SetStateManager*	param	=	m_DBuffer.Request<CmdEffect_SetStateManager>(enCF_Effect_SetStateManager);
	param->pID3DXEffect				=	pID3DXEffect;
	param->pManager					=	pManager;
	return	S_OK;
};
HRESULT	MT_IDirect3DDevice9::Effect_SetRawValue(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, LPCVOID pData, UINT ByteOffset, UINT Bytes){

	void*	pBuffer		=	NULL;
	CmdEffect_SetRawValue*	param	=	m_DBuffer.Request<CmdEffect_SetRawValue>(enCF_Effect_SetRawValue,Bytes,pBuffer);
	param->pID3DXEffect	=	pID3DXEffect;
	param->hParameter	=	hParameter;
	param->ByteOffset	=	ByteOffset;
	param->Bytes		=	Bytes;
	memcpy(pBuffer,pData,Bytes);
	return	S_OK;
};