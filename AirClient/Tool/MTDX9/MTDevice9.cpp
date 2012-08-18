
#include "MTDevice9.h"
//#include "MTSurface9.h"
//#include "MTVertexBuffer9.h"
//#include "MTCubeTexture9.h"
//#include "MTPixelShader9.h"
//#include "MTQuery9.h"
//#include "MTStateBlock9.h"
//#include "MTSwapChain9.h"
//#include "MTTexture9.h"
//#include "MTVertexDeclaration9.h"
//#include "MTVertexShader9.h"
//#include "MTVolume9.h"
//#include "MTVolumeTexture9.h"
//#include "MTIndexBuffer9.h"

extern T_TestCooperativeLevel				ST_TestCooperativeLevel					;
extern T_EvictManagedResources				ST_EvictManagedResources				;
extern T_SetCursorProperties				ST_SetCursorProperties					;
extern T_SetCursorPosition					ST_SetCursorPosition					;
extern T_ShowCursor						ST_ShowCursor							;
extern T_CreateAdditionalSwapChain			ST_CreateAdditionalSwapChain			;
extern T_GetSwapChain						ST_GetSwapChain							;
extern T_GetNumberOfSwapChains				ST_GetNumberOfSwapChains				;
extern T_Reset								ST_Reset								;
extern T_Present							ST_Present								;
extern T_GetBackBuffer						ST_GetBackBuffer						;
extern T_GetRasterStatus					ST_GetRasterStatus						;
extern T_SetDialogBoxMode					ST_SetDialogBoxMode						;
extern T_SetGammaRamp						ST_SetGammaRamp							;
extern T_GetGammaRamp						ST_GetGammaRamp							;
extern T_CreateTexture						ST_CreateTexture						;
extern T_CreateVolumeTexture				ST_CreateVolumeTexture					;
extern T_CreateCubeTexture					ST_CreateCubeTexture					;
extern T_CreateVertexBuffer				ST_CreateVertexBuffer					;
extern T_CreateIndexBuffer					ST_CreateIndexBuffer					;
extern T_CreateRenderTarget				ST_CreateRenderTarget					;
extern T_CreateDepthStencilSurface			ST_CreateDepthStencilSurface			;
extern T_UpdateSurface						ST_UpdateSurface						;
extern T_UpdateTexture						ST_UpdateTexture						;
extern T_GetRenderTargetData				ST_GetRenderTargetData					;
extern T_GetFrontBufferData				ST_GetFrontBufferData					;
extern T_StretchRect						ST_StretchRect							;
extern T_ColorFill							ST_ColorFill							;
extern T_CreateOffscreenPlainSurface		ST_CreateOffscreenPlainSurface			;
extern T_SetRenderTarget					ST_SetRenderTarget						;
extern T_GetRenderTarget					ST_GetRenderTarget						;
extern T_SetDepthStencilSurface			ST_SetDepthStencilSurface				;
extern T_GetDepthStencilSurface			ST_GetDepthStencilSurface				;
extern T_BeginScene						ST_BeginScene							;
extern T_EndScene							ST_EndScene								;
extern T_Clear								ST_Clear								;
extern T_SetTransform						ST_SetTransform							;
extern T_GetTransform						ST_GetTransform							;
extern T_MultiplyTransform					ST_MultiplyTransform					;
extern T_SetViewport						ST_SetViewport							;
extern T_GetViewport						ST_GetViewport							;
extern T_SetMaterial						ST_SetMaterial							;
extern T_GetMaterial						ST_GetMaterial							;
extern T_SetLight							ST_SetLight								;
extern T_GetLight							ST_GetLight								;
extern T_LightEnable						ST_LightEnable							;
extern T_GetLightEnable					ST_GetLightEnable						;
extern T_SetClipPlane						ST_SetClipPlane							;
extern T_GetClipPlane						ST_GetClipPlane							;
extern T_SetRenderState					ST_SetRenderState						;
extern T_GetRenderState					ST_GetRenderState						;
extern T_CreateStateBlock					ST_CreateStateBlock						;
extern T_BeginStateBlock					ST_BeginStateBlock						;
extern T_EndStateBlock						ST_EndStateBlock						;
extern T_SetClipStatus						ST_SetClipStatus						;
extern T_GetClipStatus						ST_GetClipStatus						;
extern T_GetTexture						ST_GetTexture							;
extern T_SetTexture						ST_SetTexture							;
extern T_GetTextureStageState				ST_GetTextureStageState					;
extern T_SetTextureStageState				ST_SetTextureStageState					;
extern T_GetSamplerState					ST_GetSamplerState						;
extern T_SetSamplerState					ST_SetSamplerState						;
extern T_ValidateDevice					ST_ValidateDevice						;
extern T_SetPaletteEntries					ST_SetPaletteEntries					;
extern T_GetPaletteEntries					ST_GetPaletteEntries					;
extern T_SetCurrentTexturePalette			ST_SetCurrentTexturePalette				;
extern T_GetCurrentTexturePalette			ST_GetCurrentTexturePalette				;
extern T_SetScissorRect					ST_SetScissorRect						;
extern T_GetScissorRect					ST_GetScissorRect						;
extern T_SetSoftwareVertexProcessing		ST_SetSoftwareVertexProcessing			;
extern T_GetSoftwareVertexProcessing		ST_GetSoftwareVertexProcessing			;
extern T_SetNPatchMode						ST_SetNPatchMode						;
extern T_GetNPatchMode						ST_GetNPatchMode						;
extern T_DrawPrimitive						ST_DrawPrimitive						;
extern T_DrawIndexedPrimitive				ST_DrawIndexedPrimitive					;
extern T_DrawPrimitiveUP					ST_DrawPrimitiveUP						;
extern T_DrawIndexedPrimitiveUP			ST_DrawIndexedPrimitiveUP				;
extern T_ProcessVertices					ST_ProcessVertices						;
extern T_CreateVertexDeclaration			ST_CreateVertexDeclaration				;
extern T_SetVertexDeclaration				ST_SetVertexDeclaration					;
extern T_GetVertexDeclaration				ST_GetVertexDeclaration					;
extern T_SetFVF							ST_SetFVF								;
extern T_GetFVF							ST_GetFVF								;
extern T_CreateVertexShader				ST_CreateVertexShader					;
extern T_SetVertexShader					ST_SetVertexShader						;
extern T_GetVertexShader					ST_GetVertexShader						;
extern T_SetVertexShaderConstantF			ST_SetVertexShaderConstantF				;
extern T_GetVertexShaderConstantF			ST_GetVertexShaderConstantF				;
extern T_SetVertexShaderConstantI			ST_SetVertexShaderConstantI				;
extern T_GetVertexShaderConstantI			ST_GetVertexShaderConstantI				;
extern T_SetVertexShaderConstantB			ST_SetVertexShaderConstantB				;
extern T_GetVertexShaderConstantB			ST_GetVertexShaderConstantB				;
extern T_SetStreamSource					ST_SetStreamSource						;
extern T_GetStreamSource					ST_GetStreamSource						;
extern T_SetStreamSourceFreq				ST_SetStreamSourceFreq					;
extern T_GetStreamSourceFreq				ST_GetStreamSourceFreq					;
extern T_SetIndices						ST_SetIndices							;
extern T_GetIndices						ST_GetIndices							;
extern T_CreatePixelShader					ST_CreatePixelShader					;
extern T_SetPixelShader					ST_SetPixelShader						;
extern T_GetPixelShader					ST_GetPixelShader						;
extern T_SetPixelShaderConstantF			ST_SetPixelShaderConstantF				;
extern T_GetPixelShaderConstantF			ST_GetPixelShaderConstantF				;
extern T_SetPixelShaderConstantI			ST_SetPixelShaderConstantI				;
extern T_GetPixelShaderConstantI			ST_GetPixelShaderConstantI				;
extern T_SetPixelShaderConstantB			ST_SetPixelShaderConstantB				;
extern T_GetPixelShaderConstantB			ST_GetPixelShaderConstantB				;
extern T_DrawRectPatch						ST_DrawRectPatch						;
extern T_DrawTriPatch						ST_DrawTriPatch							;
extern T_DeletePatch						ST_DeletePatch							;
extern T_CreateQuery						ST_CreateQuery							;



extern T_SwapChain_Present							ST_SwapChain_Present		;
extern T_Surface_LockRect							ST_Surface_LockRect			;
extern T_Surface_UnlockRect							ST_Surface_UnlockRect		;

extern T_Volume_LockBox								ST_Volume_LockBox						;
extern T_Volume_UnlockBox							ST_Volume_UnlockBox						;
extern T_VertexBuffer_Lock							ST_VertexBuffer_Lock					;
extern T_VertexBuffer_Unlock						ST_VertexBuffer_Unlock					;
extern T_IndexBuffer_Lock							ST_IndexBuffer_Lock						;
extern T_IndexBuffer_Unlock							ST_IndexBuffer_Unlock					;


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
HRESULT(STDMETHODCALLTYPE MT_TestCooperativeLevel)(IDirect3DDevice9* pThis){

	return	ST_TestCooperativeLevel(pThis);
}
HRESULT(STDMETHODCALLTYPE MT_EvictManagedResources)(IDirect3DDevice9* pThis){
	return	ST_EvictManagedResources(pThis);
}
HRESULT(STDMETHODCALLTYPE MT_SetCursorProperties)(IDirect3DDevice9* pThis, UINT XHotSpot,UINT YHotSpot,IDirect3DSurface9* pCursorBitmap){
	return	ST_SetCursorProperties(pThis,XHotSpot,YHotSpot,pCursorBitmap);
}
void(	STDMETHODCALLTYPE MT_SetCursorPosition)(IDirect3DDevice9* pThis, int X,int Y,DWORD Flags){

}
BOOL(	STDMETHODCALLTYPE MT_ShowCursor)(IDirect3DDevice9* pThis, BOOL bShow){
	return	ST_ShowCursor(pThis,bShow);
}
HRESULT(STDMETHODCALLTYPE MT_CreateAdditionalSwapChain)(IDirect3DDevice9* pThis, D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain9** pSwapChain)
{
	return	ST_CreateAdditionalSwapChain(pThis,pPresentationParameters,pSwapChain);
}


HRESULT STDMETHODCALLTYPE MT_GetSwapChain(IDirect3DDevice9* pThis, UINT iSwapChain,IDirect3DSwapChain9** pSwapChain){

	HRESULT	hr	=	ST_GetSwapChain(pThis,iSwapChain,pSwapChain);
	if(SUCCEEDED(hr)){

	}
	return	hr;
};
UINT	STDMETHODCALLTYPE MT_GetNumberOfSwapChains(IDirect3DDevice9* pThis){
	return		ST_GetNumberOfSwapChains(pThis);
}
HRESULT	STDMETHODCALLTYPE MT_Reset(IDirect3DDevice9* pThis, D3DPRESENT_PARAMETERS* pPresentationParameters){
	//Waiting Render Thread
	MT_RenderThread::GetSingleton().WaitRenderComplated();

	return	ST_Reset(pThis,pPresentationParameters);
}
HRESULT	STDMETHODCALLTYPE MT_Present(IDirect3DDevice9* pThis, CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion){
	//Send Present
	CmdPresent*	param			=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdPresent>(enCF_Present);
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
	MT_RenderThread::GetSingleton().Swap();

	return	S_OK;
}
HRESULT STDMETHODCALLTYPE MT_GetBackBuffer(IDirect3DDevice9* pThis, UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer){

	HRESULT	hr	=	ST_GetBackBuffer(pThis,iSwapChain,iBackBuffer,Type,ppBackBuffer);
	if(SUCCEEDED(hr)){
// 		*ppBackBuffer	=	new	MT_IDirect3DSurface9(this,pIDirect3DSurface9);
// 		(*ppBackBuffer)->AddRef();
	}
	return	hr;
}
HRESULT	STDMETHODCALLTYPE MT_GetRasterStatus(IDirect3DDevice9* pThis, UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus){
	return	ST_GetRasterStatus(pThis,iSwapChain,pRasterStatus);
};
HRESULT	STDMETHODCALLTYPE MT_SetDialogBoxMode(IDirect3DDevice9* pThis, BOOL bEnableDialogs){
	CmdSetDialogBoxMode*	param			=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetDialogBoxMode>(enCF_SetDialogBoxMode);
	(*param)	=	bEnableDialogs;
	return	S_OK;
}
void	STDMETHODCALLTYPE MT_SetGammaRamp(IDirect3DDevice9* pThis, UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp){
	if(pRamp==NULL)
		return;

	CmdSetGammaRamp*	param			=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetGammaRamp>(enCF_SetGammaRamp);
	param->iSwapChain	=	iSwapChain;
	param->Flags		=	Flags;
	param->pRamp		=	*pRamp;
}
void	STDMETHODCALLTYPE MT_GetGammaRamp(IDirect3DDevice9* pThis, UINT iSwapChain,D3DGAMMARAMP* pRamp){
	ST_GetGammaRamp(pThis,iSwapChain,pRamp);
}

HRESULT STDMETHODCALLTYPE MT_CreateTexture(IDirect3DDevice9* pThis, UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle){

	HRESULT	hr	=	ST_CreateTexture(pThis,Width,Height,Levels,Usage,Format,Pool,ppTexture,pSharedHandle);
	if(SUCCEEDED(hr)){

	}
	return hr;
};
HRESULT STDMETHODCALLTYPE MT_CreateVolumeTexture(IDirect3DDevice9* pThis, UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle){

	HRESULT	hr	=	ST_CreateVolumeTexture(pThis,Width,Height,Depth,Levels,Usage,Format,Pool,ppVolumeTexture,pSharedHandle);
	if(SUCCEEDED(hr)){

	}
	return hr;
};
HRESULT STDMETHODCALLTYPE MT_CreateCubeTexture(IDirect3DDevice9* pThis, UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle){

	HRESULT	hr	=	ST_CreateCubeTexture(pThis,EdgeLength,Levels,Usage,Format,Pool,ppCubeTexture,pSharedHandle);
	if(SUCCEEDED(hr)){

	}
	return hr;
};
HRESULT STDMETHODCALLTYPE MT_CreateVertexBuffer(IDirect3DDevice9* pThis, UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle){

	HRESULT	hr	=	ST_CreateVertexBuffer(pThis,Length,Usage,FVF,Pool,ppVertexBuffer,pSharedHandle);
	if(SUCCEEDED(hr)){

	}
	return hr;
};
HRESULT STDMETHODCALLTYPE MT_CreateIndexBuffer(IDirect3DDevice9* pThis, UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle){

	HRESULT	hr	=	ST_CreateIndexBuffer(pThis,Length,Usage,Format,Pool,ppIndexBuffer,pSharedHandle);
	if(SUCCEEDED(hr)){

	}
	return hr;
};
HRESULT STDMETHODCALLTYPE MT_CreateRenderTarget(IDirect3DDevice9* pThis, UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle){

	HRESULT	hr	=	ST_CreateRenderTarget(pThis,Width,Height,Format,MultiSample,MultisampleQuality,Lockable,ppSurface,pSharedHandle);
	if(SUCCEEDED(hr)){

	}
	return hr;
};
HRESULT STDMETHODCALLTYPE MT_CreateDepthStencilSurface(IDirect3DDevice9* pThis, UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle){

	HRESULT	hr	=	ST_CreateDepthStencilSurface(pThis,Width,Height,Format,MultiSample,MultisampleQuality,Discard,ppSurface,pSharedHandle);
	if(SUCCEEDED(hr)){

	}
	return hr;
};
HRESULT STDMETHODCALLTYPE MT_UpdateSurface(IDirect3DDevice9* pThis, IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint){

	CmdUpdateSurface*	param			=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdUpdateSurface>(enCF_UpdateSurface);
	
	param->pSourceSurface		=	pSourceSurface;
	param->pSourceRect			=	pSourceRect;
	param->pDestinationSurface	=	pDestinationSurface;
	param->pDestPoint			=	pDestPoint;

	if(pSourceRect!=NULL)
		param->src		=	*pSourceRect;
	if(pDestPoint!=NULL)
		param->dst		=	*pDestPoint;
	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_UpdateTexture(IDirect3DDevice9* pThis, IDirect3DBaseTexture9* pSourceTexture,IDirect3DBaseTexture9* pDestinationTexture){

	CmdUpdateTexture*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdUpdateTexture>(enCF_UpdateTexture);
	param->pSourceTexture		=	pSourceTexture;
	param->pDestinationTexture	=	pDestinationTexture;
	return S_OK;

};
HRESULT STDMETHODCALLTYPE MT_GetRenderTargetData(IDirect3DDevice9* pThis, IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_GetFrontBufferData(IDirect3DDevice9* pThis, UINT iSwapChain,IDirect3DSurface9* pDestSurface){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_StretchRect(IDirect3DDevice9* pThis, IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter){
	CmdStretchRect*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdStretchRect>(enCF_StretchRect);
	param->pSourceSurface	=	pSourceSurface;
	param->pSourceRect		=	pSourceRect;
	param->pDestSurface		=	pDestSurface;
	param->pDestRect		=	pDestRect;
	param->Filter			=	Filter;
	if(pSourceRect!=NULL)
		param->src	=	*pSourceRect;
	if(pDestRect!=NULL)
		param->dst	=	*pDestRect;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_ColorFill(IDirect3DDevice9* pThis, IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color){
	CmdColorFill*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdColorFill>(enCF_ColorFill);
	param->pSurface			=	pSurface;
	param->pRect			=	pRect;
	param->color			=	color;
	if(pRect!=NULL)
		param->src			=	*pRect;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_CreateOffscreenPlainSurface(IDirect3DDevice9* pThis, UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle){

	HRESULT	hr	=	ST_CreateOffscreenPlainSurface(pThis,Width,Height,Format,Pool,ppSurface,pSharedHandle);
	if(SUCCEEDED(hr)){

	}
	return hr;
};
HRESULT STDMETHODCALLTYPE MT_SetRenderTarget(IDirect3DDevice9* pThis, DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget){
	CmdSetRenderTarget*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetRenderTarget>(enCF_SetRenderTarget);
	param->RenderTargetIndex	=	RenderTargetIndex;
	if(pRenderTarget==NULL)
		param->pRenderTarget		=	NULL;
	else
		param->pRenderTarget		=	pRenderTarget;
	
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetRenderTarget(IDirect3DDevice9* pThis, DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetDepthStencilSurface(IDirect3DDevice9* pThis, IDirect3DSurface9* pNewZStencil){
	CmdSetDepthStencilSurface*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetDepthStencilSurface>(enCF_SetDepthStencilSurface);
	if(pNewZStencil==NULL)
		param->pNewZStencil	=	NULL;
	else
		param->pNewZStencil	=	pNewZStencil;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetDepthStencilSurface(IDirect3DDevice9* pThis, IDirect3DSurface9** ppZStencilSurface){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_BeginScene(IDirect3DDevice9* pThis){
	MT_RenderThread::GetSingleton().GetDBuffer().Request(enCF_BeginScene);
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_EndScene(IDirect3DDevice9* pThis){
	MT_RenderThread::GetSingleton().GetDBuffer().Request(enCF_EndScene);
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Clear(IDirect3DDevice9* pThis, DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil){
	CmdClear*	param	=	NULL;
	if(pRects!=NULL && Count	>0){
		U32	uiBufferSize	=	sizeof(D3DRECT)*Count;
		void*	pBuffer		=	NULL;
		param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdClear>(enCF_Clear,uiBufferSize,pBuffer);
		memcpy(pBuffer,pRects,uiBufferSize);
	}else{
		param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdClear>(enCF_Clear);
	}
	
	param->Count	=	Count;
	param->pRects	=	pRects;
	param->Flags	=	Flags;
	param->Color	=	Color;
	param->Z		=	Z;
	param->Stencil	=	Stencil;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_SetTransform(IDirect3DDevice9* pThis, D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix){
	if(pMatrix==NULL)
		return	D3DERR_INVALIDCALL;
	CmdSetTransform*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetTransform>(enCF_SetTransform);
	param->State	=	State;
	param->pMatrix	=	*pMatrix;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetTransform(IDirect3DDevice9* pThis, D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_MultiplyTransform(IDirect3DDevice9* pThis, D3DTRANSFORMSTATETYPE,CONST D3DMATRIX*){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetViewport(IDirect3DDevice9* pThis, CONST D3DVIEWPORT9* pViewport){
	if(pViewport==NULL)
		return	D3DERR_INVALIDCALL;
	CmdSetViewport*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetViewport>(enCF_SetViewport);
	*param	=	*pViewport;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetViewport(IDirect3DDevice9* pThis, D3DVIEWPORT9* pViewport){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetMaterial(IDirect3DDevice9* pThis, CONST D3DMATERIAL9* pMaterial){
	if(pMaterial==NULL)
		return	D3DERR_INVALIDCALL;
	CmdSetMaterial*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetMaterial>(enCF_SetMaterial);
	*param	=	*pMaterial;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetMaterial(IDirect3DDevice9* pThis, D3DMATERIAL9* pMaterial){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetLight(IDirect3DDevice9* pThis, DWORD Index,CONST D3DLIGHT9* pLight){
	if(pLight==NULL)
		return	D3DERR_INVALIDCALL;
	CmdSetLight*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetLight>(enCF_SetLight);
	param->Index	=	Index;
	param->Light	=	*pLight;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetLight(IDirect3DDevice9* pThis, DWORD Index,D3DLIGHT9*){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_LightEnable(IDirect3DDevice9* pThis, DWORD Index,BOOL Enable){
	CmdLightEnable*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdLightEnable>(enCF_LightEnable);
	param->Index	=	Index;
	param->Enable	=	Enable;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetLightEnable(IDirect3DDevice9* pThis, DWORD Index,BOOL* pEnable){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetClipPlane(IDirect3DDevice9* pThis, DWORD Index,CONST float* pPlane){
	CmdSetClipPlane*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetClipPlane>(enCF_SetClipPlane);
	param->Index	=	Index;
	memcpy(param->pPlane,pPlane,sizeof(float)*4);
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetClipPlane(IDirect3DDevice9* pThis, DWORD Index,float* pPlane){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetRenderState(IDirect3DDevice9* pThis, D3DRENDERSTATETYPE State,DWORD Value){
	CmdSetRenderState*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetRenderState>(enCF_SetRenderState);
	param->State	=	State;
	param->Value	=	Value;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetRenderState(IDirect3DDevice9* pThis, D3DRENDERSTATETYPE State,DWORD* pValue){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_CreateStateBlock(IDirect3DDevice9* pThis, D3DSTATEBLOCKTYPE Type,IDirect3DStateBlock9** ppSB){
	HRESULT	hr	=	ST_CreateStateBlock(pThis,Type,ppSB);
	if(SUCCEEDED(hr)){

	}
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_BeginStateBlock(IDirect3DDevice9* pThis){
	MT_RenderThread::GetSingleton().GetDBuffer().Request(enCF_BeginStateBlock);
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_EndStateBlock(IDirect3DDevice9* pThis, IDirect3DStateBlock9** ppSB){
	CmdEndStateBlock*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEndStateBlock>(enCF_EndStateBlock);
	*param	=	ppSB;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_SetClipStatus(IDirect3DDevice9* pThis, CONST D3DCLIPSTATUS9* pClipStatus){
	CmdSetClipStatus*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetClipStatus>(enCF_SetClipStatus);
	*param	=	*pClipStatus;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetClipStatus(IDirect3DDevice9* pThis, D3DCLIPSTATUS9* pClipStatus){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_GetTexture(IDirect3DDevice9* pThis, DWORD Stage,IDirect3DBaseTexture9** ppTexture){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetTexture(IDirect3DDevice9* pThis, DWORD Stage,IDirect3DBaseTexture9* pTexture){
	CmdSetTexture*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetTexture>(enCF_SetTexture);
	param->Stage			=	Stage;
	if(pTexture==NULL)
		param->pTexture	=	NULL;
	else
		param->pTexture	=	pTexture;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetTextureStageState(IDirect3DDevice9* pThis, DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetTextureStageState(IDirect3DDevice9* pThis, DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value){
	CmdSetTextureStageState*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetTextureStageState>(enCF_SetTextureStageState);
	param->Stage	=	Stage;
	param->Type		=	Type;
	param->Value	=	Value;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetSamplerState(IDirect3DDevice9* pThis, DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetSamplerState(IDirect3DDevice9* pThis, DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value){
	CmdSetSamplerState*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetSamplerState>(enCF_SetSamplerState);
	param->Sampler	=	Sampler;
	param->Type		=	Type;
	param->Value	=	Value;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_ValidateDevice(IDirect3DDevice9* pThis, DWORD* pNumPasses){
	return ST_ValidateDevice(pThis,pNumPasses);
};
HRESULT STDMETHODCALLTYPE MT_SetPaletteEntries(IDirect3DDevice9* pThis, UINT PaletteNumber,CONST PALETTEENTRY* pEntries){

	CmdSetPaletteEntries*	param	=	NULL;
	if(PaletteNumber>0&&pEntries!=NULL){
		U32		uiBufferSize	=	sizeof(PALETTEENTRY)*PaletteNumber;
		void*	pBuffer			=	NULL;
		param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetPaletteEntries>(enCF_SetPaletteEntries,uiBufferSize,pBuffer);
		memcpy(pBuffer,pEntries,uiBufferSize);
	}else{
		param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetPaletteEntries>(enCF_SetPaletteEntries);
	}
	param->PaletteNumber	=	PaletteNumber;
	param->pEntries			=	pEntries;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetPaletteEntries(IDirect3DDevice9* pThis, UINT PaletteNumber,PALETTEENTRY* pEntries){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetCurrentTexturePalette(IDirect3DDevice9* pThis, UINT PaletteNumber){
	CmdSetCurrentTexturePalette*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetCurrentTexturePalette>(enCF_SetCurrentTexturePalette);
	*param	=	PaletteNumber;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetCurrentTexturePalette(IDirect3DDevice9* pThis, UINT *PaletteNumber){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetScissorRect(IDirect3DDevice9* pThis, CONST RECT* pRect){
	CmdSetScissorRect*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetScissorRect>(enCF_SetScissorRect);
	*param	=	*pRect;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetScissorRect(IDirect3DDevice9* pThis, RECT* pRect){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetSoftwareVertexProcessing(IDirect3DDevice9* pThis, BOOL bSoftware){
	CmdSetSoftwareVertexProcessing*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetSoftwareVertexProcessing>(enCF_SetSoftwareVertexProcessing);
	*param	=	bSoftware;
	return S_OK;
};
BOOL	STDMETHODCALLTYPE MT_GetSoftwareVertexProcessing(IDirect3DDevice9* pThis){return FALSE;};
HRESULT STDMETHODCALLTYPE MT_SetNPatchMode(IDirect3DDevice9* pThis, float nSegments){
	CmdSetNPatchMode*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetNPatchMode>(enCF_SetNPatchMode);
	*param	=	nSegments;
	return S_OK;
};
float	STDMETHODCALLTYPE MT_GetNPatchMode(IDirect3DDevice9* pThis){return 1.0f;};
HRESULT STDMETHODCALLTYPE MT_DrawPrimitive(IDirect3DDevice9* pThis, D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount){
	CmdDrawPrimitive*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdDrawPrimitive>(enCF_DrawPrimitive);
	param->PrimitiveType	=	PrimitiveType;
	param->StartVertex		=	StartVertex;
	param->PrimitiveCount	=	PrimitiveCount;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_DrawIndexedPrimitive(IDirect3DDevice9* pThis, D3DPRIMITIVETYPE PrimitiveType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount){
	CmdDrawIndexedPrimitive*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdDrawIndexedPrimitive>(enCF_DrawIndexedPrimitive);
	param->PrimitiveType	=	PrimitiveType;
	param->BaseVertexIndex	=	BaseVertexIndex;
	param->MinVertexIndex	=	MinVertexIndex;
	param->NumVertices		=	NumVertices;
	param->startIndex		=	startIndex;
	param->primCount		=	primCount;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_DrawPrimitiveUP(IDirect3DDevice9* pThis, D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_DrawIndexedPrimitiveUP(IDirect3DDevice9* pThis, D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_ProcessVertices(IDirect3DDevice9* pThis, UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_CreateVertexDeclaration(IDirect3DDevice9* pThis, CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl){

	HRESULT	hr	=	ST_CreateVertexDeclaration(pThis,pVertexElements,ppDecl);
	if(SUCCEEDED(hr)){

	}
	return hr;
};
HRESULT STDMETHODCALLTYPE MT_SetVertexDeclaration(IDirect3DDevice9* pThis, IDirect3DVertexDeclaration9* pDecl){
	CmdSetVertexDeclaration*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetVertexDeclaration>(enCF_SetVertexDeclaration);
	if(pDecl==NULL)
		*param	=	NULL;
	else
		*param	=	pDecl;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetVertexDeclaration(IDirect3DDevice9* pThis, IDirect3DVertexDeclaration9** ppDecl){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetFVF(IDirect3DDevice9* pThis, DWORD FVF){
	CmdSetFVF*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetFVF>(enCF_SetFVF);
	*param	=	FVF;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetFVF(IDirect3DDevice9* pThis, DWORD* pFVF){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_CreateVertexShader(IDirect3DDevice9* pThis, CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader){

	HRESULT	hr	=	ST_CreateVertexShader(pThis,pFunction,ppShader);
	if(SUCCEEDED(hr)){

	}
	return hr;
};
HRESULT STDMETHODCALLTYPE MT_SetVertexShader(IDirect3DDevice9* pThis, IDirect3DVertexShader9* pShader){
	CmdSetVertexShader*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetVertexShader>(enCF_SetVertexShader);
	if(pShader==NULL)
		*param	=	NULL;
	else
		*param	=	pShader;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetVertexShader(IDirect3DDevice9* pThis, IDirect3DVertexShader9** ppShader){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetVertexShaderConstantF(IDirect3DDevice9* pThis, UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount){
	U32		uiBufferSize	=	sizeof(float)*4*Vector4fCount;
	void*	pBuffer			=	NULL;
	CmdSetVertexShaderConstantF*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetVertexShaderConstantF>(enCF_SetVertexShaderConstantF,uiBufferSize,pBuffer);
	memcpy(pBuffer,pConstantData,uiBufferSize);
	param->StartRegister	=	StartRegister;
	param->Vector4fCount	=	Vector4fCount;

	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetVertexShaderConstantF(IDirect3DDevice9* pThis, UINT StartRegister,float* pConstantData,UINT Vector4fCount){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetVertexShaderConstantI(IDirect3DDevice9* pThis, UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount){
	U32		uiBufferSize	=	sizeof(int)*4*Vector4iCount;
	void*	pBuffer			=	NULL;
	CmdSetVertexShaderConstantI*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetVertexShaderConstantI>(enCF_SetVertexShaderConstantI,uiBufferSize,pBuffer);
	memcpy(pBuffer,pConstantData,uiBufferSize);
	param->StartRegister	=	StartRegister;
	param->Vector4iCount	=	Vector4iCount;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetVertexShaderConstantI(IDirect3DDevice9* pThis, UINT StartRegister,int* pConstantData,UINT Vector4iCount){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetVertexShaderConstantB(IDirect3DDevice9* pThis, UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount){
	U32		uiBufferSize	=	sizeof(BOOL)*BoolCount;
	void*	pBuffer			=	NULL;
	CmdSetVertexShaderConstantB*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetVertexShaderConstantB>(enCF_SetVertexShaderConstantB,uiBufferSize,pBuffer);
	memcpy(pBuffer,pConstantData,uiBufferSize);
	param->StartRegister	=	StartRegister;
	param->BoolCount	=	BoolCount;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetVertexShaderConstantB(IDirect3DDevice9* pThis, UINT StartRegister,BOOL* pConstantData,UINT BoolCount){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetStreamSource(IDirect3DDevice9* pThis, UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride){
	CmdSetStreamSource*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetStreamSource>(enCF_SetStreamSource);
	param->StreamNumber		=	StreamNumber;
	if(pStreamData==NULL)
		param->pStreamData	=	NULL;
	else
		param->pStreamData	=	pStreamData;
	param->OffsetInBytes	=	OffsetInBytes;
	param->Stride	=	Stride;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetStreamSource(IDirect3DDevice9* pThis, UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* pOffsetInBytes,UINT* pStride){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetStreamSourceFreq(IDirect3DDevice9* pThis, UINT StreamNumber,UINT Setting){
	CmdSetStreamSourceFreq*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetStreamSourceFreq>(enCF_SetStreamSourceFreq);
	param->StreamNumber		=	StreamNumber;
	param->Setting	=	Setting;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetStreamSourceFreq(IDirect3DDevice9* pThis, UINT StreamNumber,UINT* pSetting){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetIndices(IDirect3DDevice9* pThis, IDirect3DIndexBuffer9* pIndexData){
	CmdSetIndices*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetIndices>(enCF_SetIndices);
	if(pIndexData==NULL)
		*param	=	NULL;
	else
		*param	=	pIndexData;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetIndices(IDirect3DDevice9* pThis, IDirect3DIndexBuffer9** ppIndexData){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_CreatePixelShader(IDirect3DDevice9* pThis, CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader){

	HRESULT	hr	=	ST_CreatePixelShader(pThis,pFunction,ppShader);
	if(SUCCEEDED(hr)){

	}
	return hr;
};
HRESULT STDMETHODCALLTYPE MT_SetPixelShader(IDirect3DDevice9* pThis, IDirect3DPixelShader9* pShader){
	CmdSetPixelShader*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetPixelShader>(enCF_SetPixelShader);
	if(pShader==NULL)
		*param	=	NULL;
	else
		*param	=	pShader;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetPixelShader(IDirect3DDevice9* pThis, IDirect3DPixelShader9** ppShader){
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_SetPixelShaderConstantF(IDirect3DDevice9* pThis, UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount){
	U32		uiBufferSize	=	sizeof(float)*4*Vector4fCount;
	void*	pBuffer			=	NULL;
	CmdSetPixelShaderConstantF*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetPixelShaderConstantF>(enCF_SetPixelShaderConstantF,uiBufferSize,pBuffer);
	memcpy(pBuffer,pConstantData,uiBufferSize);
	param->StartRegister	=	StartRegister;
	param->Vector4fCount	=	Vector4fCount;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetPixelShaderConstantF(IDirect3DDevice9* pThis, UINT StartRegister,float* pConstantData,UINT Vector4fCount){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetPixelShaderConstantI(IDirect3DDevice9* pThis, UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount){
	U32		uiBufferSize	=	sizeof(int)*4*Vector4iCount;
	void*	pBuffer			=	NULL;
	CmdSetPixelShaderConstantI*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetPixelShaderConstantI>(enCF_SetPixelShaderConstantI,uiBufferSize,pBuffer);
	memcpy(pBuffer,pConstantData,uiBufferSize);
	param->StartRegister	=	StartRegister;
	param->Vector4iCount	=	Vector4iCount;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetPixelShaderConstantI(IDirect3DDevice9* pThis, UINT StartRegister,int* pConstantData,UINT Vector4iCount){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_SetPixelShaderConstantB(IDirect3DDevice9* pThis, UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount){
	U32		uiBufferSize	=	sizeof(BOOL)*BoolCount;
	void*	pBuffer			=	NULL;
	CmdSetPixelShaderConstantB*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSetPixelShaderConstantB>(enCF_SetPixelShaderConstantB,uiBufferSize,pBuffer);
	memcpy(pBuffer,pConstantData,uiBufferSize);
	param->StartRegister	=	StartRegister;
	param->BoolCount	=	BoolCount;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_GetPixelShaderConstantB(IDirect3DDevice9* pThis, UINT StartRegister,BOOL* pConstantData,UINT BoolCount){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_DrawRectPatch(IDirect3DDevice9* pThis, UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_DrawTriPatch(IDirect3DDevice9* pThis, UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo){return S_OK;};
HRESULT STDMETHODCALLTYPE MT_DeletePatch(IDirect3DDevice9* pThis, UINT Handle){
	return ST_DeletePatch(pThis,Handle);
};
HRESULT STDMETHODCALLTYPE MT_CreateQuery(IDirect3DDevice9* pThis, D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery){

	HRESULT	hr	=	ST_CreateQuery(pThis,Type,ppQuery);
	if(SUCCEEDED(hr)){

	}
	return hr;
};

HRESULT STDMETHODCALLTYPE MT_SwapChain_Present(IDirect3DSwapChain9*	pThis,CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags){
	CmdSwapChain_Present*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSwapChain_Present>(enCF_SwapChain_Present);
	param->pSwapChain		=	pThis;
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
U32	uiReadLock	=	0;

HRESULT STDMETHODCALLTYPE MT_Surface_LockRect(IDirect3DSurface9*	pThis,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags){
	if(D3DLOCK_READONLY&Flags){
		uiReadLock++;
		pThis->lpVtbl->SetPriority(pThis,0xFFFFFFFF);
		return	ST_Surface_LockRect(pThis,pLockedRect,pRect,Flags);
	};
	D3DSURFACE_DESC	desc;
	pThis->lpVtbl->GetDesc(pThis,&desc);
	
	U32	uiFormatSize	=	BitsPerPixel(desc.Format);
	U32	uiBufferSize	=	desc.Width*desc.Height;
	if(pRect!=NULL){
		uiBufferSize	=	(pRect->right	-	pRect->left)	*	(pRect->bottom	-	pRect->top);
	}
	uiBufferSize*=uiFormatSize;
	uiBufferSize/=8;
	void*	pBuffer		=	NULL;
	
	CmdSurface_LockRect*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSurface_LockRect>(enCF_Surface_LockRect,uiBufferSize,pBuffer);
	param->pSurface	=	pThis;
	param->pRect	=	pRect;
	param->Flags	=	Flags;
	param->dwLockSize	=	uiBufferSize;
	if(pRect!=NULL)
		param->rData	=	*pRect;

	pLockedRect->pBits	=	pBuffer;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Surface_UnlockRect(IDirect3DSurface9*	pThis){
	if(uiReadLock!=0){
		if(pThis->lpVtbl->GetPriority(pThis)	==	0xFFFFFFFF){
			uiReadLock--;
			pThis->lpVtbl->SetPriority(pThis,1);
			return	ST_Surface_UnlockRect(pThis);
		}
	}
	CmdSurface_UnlockRect*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdSurface_UnlockRect>(enCF_Surface_UnlockRect);
	*param	=	pThis;
	return S_OK;
};

HRESULT	STDMETHODCALLTYPE MT_CubeSurface_LockRect(IDirect3DSurface9*	pThis,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags){
	return	MT_Surface_LockRect(pThis,pLockedRect,pRect,Flags);
};
HRESULT	STDMETHODCALLTYPE MT_CubeSurface_UnlockRect(IDirect3DSurface9*	pThis){
	return	MT_Surface_UnlockRect(pThis);
};
HRESULT STDMETHODCALLTYPE MT_Volume_LockBox(IDirect3DVolume9*	pThis,D3DLOCKED_BOX * pLockedVolume,CONST D3DBOX* pBox,DWORD Flags){
	D3DVOLUME_DESC	desc;
	pThis->lpVtbl->GetDesc(pThis,&desc);
	
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
	
	CmdVolume_LockBox*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdVolume_LockBox>(enCF_Volume_LockBox,uiBufferSize,pBuffer);
	param->pVolume	=	pThis;
	param->pBox		=	pBox;
	param->Flags	=	Flags;
	param->dwLockSize	=	uiBufferSize;
	if(pBox!=NULL)
		param->boxData	=	*pBox;

	pLockedVolume->pBits	=	pBuffer;

	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Volume_UnlockBox(IDirect3DVolume9*	pThis){
	CmdVolume_UnlockBox*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdVolume_UnlockBox>(enCF_Volume_UnlockBox);
	*param	=	pThis;
	return S_OK;
};
U32	uiVBReadLock=0;
HRESULT STDMETHODCALLTYPE MT_VertexBuffer_Lock(IDirect3DVertexBuffer9*	pThis,UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags){
	return	ST_VertexBuffer_Lock(pThis,OffsetToLock,SizeToLock,ppbData,Flags);

	if(D3DLOCK_READONLY&Flags){
		uiVBReadLock++;
		pThis->lpVtbl->SetPriority(pThis,0xFFFFFFFF);
		return	ST_VertexBuffer_Lock(pThis,OffsetToLock,SizeToLock,ppbData,Flags);
	};
	UINT	uiBufferSize	=	SizeToLock;
	if(uiBufferSize==0)
	{
		D3DVERTEXBUFFER_DESC	vbDesc;
		pThis->lpVtbl->GetDesc(pThis,&vbDesc);
		uiBufferSize	=	vbDesc.Size;
	}
	void*	pBuffer	=	NULL;
	CmdVertexBuffer_Lock*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdVertexBuffer_Lock>(enCF_VertexBuffer_Lock,uiBufferSize,pBuffer);
	param->pVB			=	pThis;
	param->OffsetToLock	=	OffsetToLock;
	param->SizeToLock	=	uiBufferSize;
	param->Flags		=	Flags;


	*ppbData			=	pBuffer;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_VertexBuffer_Unlock(IDirect3DVertexBuffer9*	pThis){
	return	ST_VertexBuffer_Unlock(pThis);;
	if(uiVBReadLock!=0){
		if(pThis->lpVtbl->GetPriority(pThis)	==	0xFFFFFFFF){
			uiVBReadLock--;
			pThis->lpVtbl->SetPriority(pThis,1);
			return	ST_VertexBuffer_Unlock(pThis);
		}
	}
	CmdVertexBuffer_Unlock*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdVertexBuffer_Unlock>(enCF_VertexBuffer_Unlock);
	*param	=	pThis;
	return S_OK;
};
U32 uiIBReadLock=0;
HRESULT STDMETHODCALLTYPE MT_IndexBuffer_Lock(IDirect3DIndexBuffer9*	pThis,UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags){
	return	ST_IndexBuffer_Lock(pThis,OffsetToLock,SizeToLock,ppbData,Flags);;

	if(D3DLOCK_READONLY&Flags){
		uiIBReadLock++;
		pThis->lpVtbl->SetPriority(pThis,0xFFFFFFFF);
		return	ST_IndexBuffer_Lock(pThis,OffsetToLock,SizeToLock,ppbData,Flags);
	};
	UINT	uiBufferSize	=	SizeToLock;
	if(uiBufferSize==0)
	{
		D3DINDEXBUFFER_DESC	ibDesc;
		pThis->lpVtbl->GetDesc(pThis,&ibDesc);
		uiBufferSize	=	ibDesc.Size;
	}

	void*	pBuffer	=	NULL;
	CmdIndexBuffer_Lock*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdIndexBuffer_Lock>(enCF_IndexBuffer_Lock,uiBufferSize,pBuffer);
	param->pIB			=	pThis;
	param->OffsetToLock	=	OffsetToLock;
	param->SizeToLock	=	uiBufferSize;
	param->Flags		=	Flags;


	*ppbData			=	pBuffer;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_IndexBuffer_Unlock(IDirect3DIndexBuffer9*	pThis){
	return	ST_IndexBuffer_Unlock(pThis);

	if(uiIBReadLock!=0){
		if(pThis->lpVtbl->GetPriority(pThis)	==	0xFFFFFFFF){
			uiIBReadLock--;
			pThis->lpVtbl->SetPriority(pThis,1);
			return	ST_IndexBuffer_Unlock(pThis);
		}
	}
	CmdIndexBuffer_Unlock*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdIndexBuffer_Unlock>(enCF_IndexBuffer_Unlock);
	*param	=	pThis;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_BaseTexture_SetAutoGenFilterType(IDirect3DBaseTexture9*	pThis,D3DTEXTUREFILTERTYPE FilterType){
	CmdBaseTexture_SetAutoGenFilterType*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdBaseTexture_SetAutoGenFilterType>(enCF_BaseTexture_SetAutoGenFilterType);
	param->pTex			=	pThis;
	param->FilterType	=	FilterType;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_BaseTexture_GenerateMipSubLevels(IDirect3DBaseTexture9*	pThis){
	CmdBaseTexture_GenerateMipSubLevels*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdBaseTexture_GenerateMipSubLevels>(enCF_BaseTexture_GenerateMipSubLevels);
	*param	=	pThis;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Texture_LockRect(IDirect3DTexture9*	pThis,UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags){
	D3DSURFACE_DESC	desc;
	pThis->lpVtbl->GetLevelDesc(pThis,Level,&desc);
	
	U32	uiFormatSize	=	BitsPerPixel(desc.Format);
	U32	uiBufferSize	=	desc.Width*desc.Height;
	if(pRect!=NULL){
		uiBufferSize	=	(pRect->right	-	pRect->left)	*	(pRect->bottom	-	pRect->top);
	}
	uiBufferSize*=uiFormatSize;
	uiBufferSize/=8;
	void*	pBuffer		=	NULL;
	
	CmdTexture_LockRect*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdTexture_LockRect>(enCF_Texture_LockRect,uiBufferSize,pBuffer);
	param->pTex		=	pThis;
	param->Level	=	Level;
	param->pRect	=	pRect;
	param->Flags	=	Flags;
	param->dwLockSize	=	uiBufferSize;
	if(pRect!=NULL)
		param->rData	=	*pRect;

	pLockedRect->pBits	=	pBuffer;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Texture_UnLockRect(IDirect3DTexture9*	pThis,UINT Level){
	CmdTexture_UnlockRect*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdTexture_UnlockRect>(enCF_Texture_UnlockRect);
	param->pTex			=	pThis;
	param->Level		=	Level;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Texture_AddDirtyRect(IDirect3DTexture9*	pThis,CONST RECT* pDirtyRect){
	CmdTexture_AddDirtyRect*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdTexture_AddDirtyRect>(enCF_Texture_AddDirtyRect);
	param->pTex				=	pThis;
	param->pDirtyRect		=	*pDirtyRect;

	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_CubeTexture_LockRect(IDirect3DCubeTexture9*	pThis,D3DCUBEMAP_FACES FaceType,UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags){
	D3DSURFACE_DESC	desc;
	pThis->lpVtbl->GetLevelDesc(pThis,Level,&desc);
	
	U32	uiFormatSize	=	BitsPerPixel(desc.Format);
	U32	uiBufferSize	=	desc.Width*desc.Height;
	if(pRect!=NULL){
		uiBufferSize	=	(pRect->right	-	pRect->left)	*	(pRect->bottom	-	pRect->top);
	}
	uiBufferSize*=uiFormatSize;
	uiBufferSize/=8;
	void*	pBuffer		=	NULL;
	
	CmdCubeTexture_LockRect*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdCubeTexture_LockRect>(enCF_CubeTexture_LockRect,uiBufferSize,pBuffer);
	param->pCubeTex		=	pThis;
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
HRESULT STDMETHODCALLTYPE MT_CubeTexture_UnlockRect(IDirect3DCubeTexture9*	pThis,D3DCUBEMAP_FACES FaceType,UINT Level){
	CmdCubeTexture_UnlockRect*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdCubeTexture_UnlockRect>(enCF_CubeTexture_UnlockRect);
	param->pCubeTex		=	pThis;
	param->FaceType		=	FaceType;
	param->Level		=	Level;
	
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_CubeTexture_AddDirtyRect(IDirect3DCubeTexture9*	pThis,D3DCUBEMAP_FACES FaceType,CONST RECT* pDirtyRect){
	CmdCubeTexture_AddDirtyRect*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdCubeTexture_AddDirtyRect>(enCF_CubeTexture_AddDirtyRect);
	param->pCubeTex		=	pThis;
	param->FaceType		=	FaceType;
	param->pDirtyRect	=	*pDirtyRect;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_VolumeTexture_LockBox(IDirect3DVolumeTexture9*	pThis,UINT Level,D3DLOCKED_BOX* pLockedVolume,CONST D3DBOX* pBox,DWORD Flags){
	D3DVOLUME_DESC	desc;
	pThis->lpVtbl->GetLevelDesc(pThis,Level,&desc);
	
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
	
	CmdVolumeTexture_LockBox*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdVolumeTexture_LockBox>(enCF_VolumeTexture_LockBox,uiBufferSize,pBuffer);
	param->pVolumeTex	=	pThis;
	param->Level	=	Level;
	param->pBox		=	pBox;
	param->Flags	=	Flags;
	param->dwLockSize	=	uiBufferSize;
	if(pBox!=NULL)
		param->boxData	=	*pBox;

	pLockedVolume->pBits	=	pBuffer;

	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_VolumeTexture_UnlockBox(IDirect3DVolumeTexture9*	pThis,UINT Level){
	CmdVolumeTexture_UnlockBox*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdVolumeTexture_UnlockBox>(enCF_VolumeTexture_UnlockBox);
	param->pVolumeTex	=	pThis;
	param->Level		=	Level;
	
	return S_OK;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_VolumeTexture_AddDirtyBox(IDirect3DVolumeTexture9*	pThis,CONST D3DBOX* pDirtyBox){
	CmdVolumeTexture_AddDirtyBox*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdVolumeTexture_AddDirtyBox>(enCF_VolumeTexture_AddDirtyBox);
	param->pVolumeTex	=	pThis;
	param->pDirtyBox	=	*pDirtyBox;

	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_StateBlock_Apply(IDirect3DStateBlock9* pThis){
	CmdStateBlock_Apply*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdStateBlock_Apply>(enCF_StateBlock_Apply);
	*param	=	pThis;
	return S_OK;
};
HRESULT STDMETHODCALLTYPE MT_StateBlock_Capture(IDirect3DStateBlock9* pThis){
	CmdStateBlock_Capture*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdStateBlock_Capture>(enCF_StateBlock_Capture);
	*param	=	pThis;
	return S_OK;
};

int		WINAPI MT_PIX_D3DPERF_BeginEvent(D3DCOLOR col,LPCWSTR wszName){
	static wchar_t	str[]	=	L"Unknown";
	if(wszName==NULL)
		wszName	=	str;
	U32	uiBufferSize	=	(wcslen(wszName)+1)*2;
	void*	pBuffer		=	NULL;
	CmdPIX_D3DPERF_BeginEvent*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdPIX_D3DPERF_BeginEvent>(enCF_PIX_D3DPERF_BeginEvent,uiBufferSize,pBuffer);
	param->col			=	col;
	param->dwNameSize	=	uiBufferSize;
	memcpy(pBuffer,wszName,uiBufferSize);

	return	0;
}
int		WINAPI MT_PIX_D3DPERF_EndEvent(){
	MT_RenderThread::GetSingleton().GetDBuffer().Request(enCF_PIX_D3DPERF_EndEvent);
	return	0;
}
void	WINAPI MT_PIX_D3DPERF_SetMarker(D3DCOLOR col,LPCWSTR wszName){
	static wchar_t	str[]	=	L"UnknownMarker";
	if(wszName==NULL)
		wszName	=	str;
	U32	uiBufferSize	=	(wcslen(wszName)+1)*2;
	void*	pBuffer		=	NULL;
	CmdPIX_D3DPERF_SetMarker*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdPIX_D3DPERF_SetMarker>(enCF_PIX_D3DPERF_SetMarker,uiBufferSize,pBuffer);
	param->col			=	col;
	param->dwNameSize	=	uiBufferSize;

	memcpy(pBuffer,wszName,uiBufferSize);
}

HRESULT STDMETHODCALLTYPE MT_Effect_SetValue(ID3DXEffect* pThis,D3DXHANDLE hParameter, LPCVOID pData, UINT Bytes){
	void*	pBuffer		=	NULL;
	CmdEffect_SetValue*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_SetValue>(enCF_Effect_SetValue,Bytes,pBuffer);
	param->pID3DXEffect	=	pThis;
	param->Bytes		=	Bytes;
	memcpy(pBuffer,pData,Bytes);
	return	S_OK;
}
HRESULT STDMETHODCALLTYPE MT_Effect_SetBool(ID3DXEffect* pThis,D3DXHANDLE hParameter, BOOL b){
	CmdEffect_SetBool*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_SetBool>(enCF_Effect_SetBool);
	param->pID3DXEffect	=	pThis;
	param->hParameter	=	hParameter;
	param->b			=	b;
	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_SetBoolArray(ID3DXEffect* pThis,D3DXHANDLE hParameter, CONST BOOL* pb, UINT Count){
	U32	uiBufferSize	=	sizeof(BOOL)*Count;
	void*	pBuffer		=	NULL;
	CmdEffect_SetBoolArray*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_SetBoolArray>(enCF_Effect_SetBoolArray,uiBufferSize,pBuffer);
	param->pID3DXEffect	=	pThis;
	param->hParameter	=	hParameter;
	param->Count		=	Count;
	memcpy(pBuffer,pb,uiBufferSize);
	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_SetInt(ID3DXEffect* pThis,D3DXHANDLE hParameter, INT n){
	CmdEffect_SetInt*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_SetInt>(enCF_Effect_SetInt);
	param->pID3DXEffect	=	pThis;
	param->hParameter	=	hParameter;
	param->n			=	n;
	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_SetIntArray(ID3DXEffect* pThis,D3DXHANDLE hParameter, CONST INT* pn, UINT Count)
{
	U32	uiBufferSize	=	sizeof(INT)*Count;
	void*	pBuffer		=	NULL;
	CmdEffect_SetIntArray*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_SetIntArray>(enCF_Effect_SetIntArray,uiBufferSize,pBuffer);
	param->pID3DXEffect	=	pThis;
	param->hParameter	=	hParameter;
	param->Count		=	Count;
	memcpy(pBuffer,pn,uiBufferSize);
	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_SetFloat(ID3DXEffect* pThis,D3DXHANDLE hParameter, FLOAT f){
	CmdEffect_SetFloat*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_SetFloat>(enCF_Effect_SetFloat);
	param->pID3DXEffect	=	pThis;
	param->hParameter	=	hParameter;
	param->f			=	f;
	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_SetFloatArray(ID3DXEffect* pThis,THIS_ D3DXHANDLE hParameter, CONST FLOAT* pf, UINT Count){
	U32	uiBufferSize	=	sizeof(INT)*Count;
	void*	pBuffer		=	NULL;
	CmdEffect_SetFloatArray*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_SetFloatArray>(enCF_Effect_SetFloatArray,uiBufferSize,pBuffer);
	param->pID3DXEffect	=	pThis;
	param->hParameter	=	hParameter;
	param->Count		=	Count;
	memcpy(pBuffer,pf,uiBufferSize);
	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_SetVector(ID3DXEffect* pThis,D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector){
	CmdEffect_SetVector*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_SetVector>(enCF_Effect_SetVector);
	param->pID3DXEffect	=	pThis;
	param->hParameter	=	hParameter;
	param->pVector		=	*pVector;
	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_SetVectorArray(ID3DXEffect* pThis,D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector, UINT Count){
	U32	uiBufferSize	=	sizeof(D3DXVECTOR4)*Count;
	void*	pBuffer		=	NULL;
	CmdEffect_SetVectorArray*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_SetVectorArray>(enCF_Effect_SetVectorArray,uiBufferSize,pBuffer);
	param->pID3DXEffect	=	pThis;
	param->hParameter	=	hParameter;
	param->Count		=	Count;
	memcpy(pBuffer,pVector,uiBufferSize);
	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_SetMatrix(ID3DXEffect* pThis,D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix){
	CmdEffect_SetMatrix*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_SetMatrix>(enCF_Effect_SetMatrix);
	param->pID3DXEffect	=	pThis;
	param->hParameter	=	hParameter;
	param->pMatrix		=	*pMatrix;
	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_SetMatrixArray(ID3DXEffect* pThis,D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count){
	U32	uiBufferSize	=	sizeof(D3DXMATRIX)*Count;
	void*	pBuffer		=	NULL;
	CmdEffect_SetMatrixArray*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_SetMatrixArray>(enCF_Effect_SetMatrixArray,uiBufferSize,pBuffer);
	param->pID3DXEffect	=	pThis;
	param->hParameter	=	hParameter;
	param->Count		=	Count;
	memcpy(pBuffer,pMatrix,uiBufferSize);
	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_SetMatrixPointerArray(ID3DXEffect* pThis,D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count){
	//U32	uiBufferSize	=	sizeof(D3DXMATRIX)*Count;
	//void*	pBuffer		=	NULL;
	//CmdEffect_SetMatrixArray*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_SetMatrixArray>(enCF_Effect_SetMatrixArray,uiBufferSize,pBuffer);
	//param->pID3DXEffect	=	pThis;
	//param->hParameter	=	hParameter;
	//param->Count		=	Count;
	//memcpy(pBuffer,pMatrix,uiBufferSize);
	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_SetMatrixTranspose(ID3DXEffect* pThis,D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix){
	CmdEffect_SetMatrixTranspose*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_SetMatrixTranspose>(enCF_Effect_SetMatrixTranspose);
	param->pID3DXEffect	=	pThis;
	param->hParameter	=	hParameter;
	param->pMatrix		=	*pMatrix;
	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_SetMatrixTransposeArray(ID3DXEffect* pThis,D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count){
	U32	uiBufferSize	=	sizeof(D3DXMATRIX)*Count;
	void*	pBuffer		=	NULL;
	CmdEffect_SetMatrixTransposeArray*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_SetMatrixTransposeArray>(enCF_Effect_SetMatrixTransposeArray,uiBufferSize,pBuffer);
	param->pID3DXEffect	=	pThis;
	param->hParameter	=	hParameter;
	param->Count		=	Count;
	memcpy(pBuffer,pMatrix,uiBufferSize);
	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_SetMatrixTransposePointerArray(ID3DXEffect* pThis,D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count){
	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_SetString(ID3DXEffect* pThis,THIS_ D3DXHANDLE hParameter, LPCSTR pString){
	U32	uiBufferSize	=	strlen(pString)+1;
	void*	pBuffer		=	NULL;
	CmdEffect_SetString*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_SetString>(enCF_Effect_SetString,uiBufferSize,pBuffer);
	param->pID3DXEffect	=	pThis;
	param->hParameter	=	hParameter;
	param->uiBufferSize	=	uiBufferSize;
	memcpy(pBuffer,pString,uiBufferSize);
	return	S_OK;
}
HRESULT STDMETHODCALLTYPE MT_Effect_SetTexture(ID3DXEffect* pThis,D3DXHANDLE hParameter, LPDIRECT3DBASETEXTURE9 pTexture){
	CmdEffect_SetTexture*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_SetTexture>(enCF_Effect_SetTexture);
	param->pID3DXEffect	=	pThis;
	param->hParameter	=	hParameter;
	param->pTexture		=	pTexture;
	return	S_OK;
};

HRESULT STDMETHODCALLTYPE MT_Effect_SetTechnique(ID3DXEffect* pThis,D3DXHANDLE hTechnique){
	CmdEffect_SetTechnique*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_SetTechnique>(enCF_Effect_SetTechnique);
	param->pID3DXEffect	=	pThis;
	param->hTechnique	=	hTechnique;

	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_Begin(ID3DXEffect* pThis,UINT *pPasses, DWORD Flags){
	CmdEffect_Begin*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_Begin>(enCF_Effect_Begin);
	param->pID3DXEffect			=	pThis;
	param->Flags				=	Flags;
	//Not Allow Mutli Pass!So Return 1;
	*pPasses	=	1;

	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_BeginPass(ID3DXEffect* pThis,UINT Pass){
	CmdEffect_BeginPass*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_BeginPass>(enCF_Effect_BeginPass);
	param->pID3DXEffect			=	pThis;
	param->Pass				=	Pass;

	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_CommitChanges(ID3DXEffect* pThis){
	CmdEffect_CommitChanges*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_CommitChanges>(enCF_Effect_CommitChanges);
	(*param)	=	pThis;
	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_EndPass(ID3DXEffect* pThis){
	CmdEffect_EndPass*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_EndPass>(enCF_Effect_EndPass);
	(*param)	=	pThis;
	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_End(ID3DXEffect* pThis){
	CmdEffect_End*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_End>(enCF_Effect_End);
	(*param)	=	pThis;
	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_SetStateManager(ID3DXEffect* pThis,LPD3DXEFFECTSTATEMANAGER pManager){
	CmdEffect_SetStateManager*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_SetStateManager>(enCF_Effect_SetStateManager);
	param->pID3DXEffect				=	pThis;
	param->pManager					=	pManager;
	return	S_OK;
};
HRESULT STDMETHODCALLTYPE MT_Effect_SetRawValue(ID3DXEffect* pThis,D3DXHANDLE hParameter, LPCVOID pData, UINT ByteOffset, UINT Bytes){

	void*	pBuffer		=	NULL;
	CmdEffect_SetRawValue*	param	=	MT_RenderThread::GetSingleton().GetDBuffer().Request<CmdEffect_SetRawValue>(enCF_Effect_SetRawValue,Bytes,pBuffer);
	param->pID3DXEffect	=	pThis;
	param->hParameter	=	hParameter;
	param->ByteOffset	=	ByteOffset;
	param->Bytes		=	Bytes;
	memcpy(pBuffer,pData,Bytes);
	return	S_OK;
};

