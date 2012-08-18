#include "MTRenderThread.h"
#include "MTDevice9.h"


T_TestCooperativeLevel				ST_TestCooperativeLevel					=NULL;
T_EvictManagedResources				ST_EvictManagedResources				=NULL;
T_SetCursorProperties				ST_SetCursorProperties					=NULL;
T_SetCursorPosition					ST_SetCursorPosition					=NULL;
T_ShowCursor						ST_ShowCursor							=NULL;
T_CreateAdditionalSwapChain			ST_CreateAdditionalSwapChain			=NULL;
T_GetSwapChain						ST_GetSwapChain							=NULL;
T_GetNumberOfSwapChains				ST_GetNumberOfSwapChains				=NULL;
T_Reset								ST_Reset								=NULL;
T_Present							ST_Present								=NULL;
T_GetBackBuffer						ST_GetBackBuffer						=NULL;
T_GetRasterStatus					ST_GetRasterStatus						=NULL;
T_SetDialogBoxMode					ST_SetDialogBoxMode						=NULL;
T_SetGammaRamp						ST_SetGammaRamp							=NULL;
T_GetGammaRamp						ST_GetGammaRamp							=NULL;
T_CreateTexture						ST_CreateTexture						=NULL;
T_CreateVolumeTexture				ST_CreateVolumeTexture					=NULL;
T_CreateCubeTexture					ST_CreateCubeTexture					=NULL;
T_CreateVertexBuffer				ST_CreateVertexBuffer					=NULL;
T_CreateIndexBuffer					ST_CreateIndexBuffer					=NULL;
T_CreateRenderTarget				ST_CreateRenderTarget					=NULL;
T_CreateDepthStencilSurface			ST_CreateDepthStencilSurface			=NULL;
T_UpdateSurface						ST_UpdateSurface						=NULL;
T_UpdateTexture						ST_UpdateTexture						=NULL;
T_GetRenderTargetData				ST_GetRenderTargetData					=NULL;
T_GetFrontBufferData				ST_GetFrontBufferData					=NULL;
T_StretchRect						ST_StretchRect							=NULL;
T_ColorFill							ST_ColorFill							=NULL;
T_CreateOffscreenPlainSurface		ST_CreateOffscreenPlainSurface			=NULL;
T_SetRenderTarget					ST_SetRenderTarget						=NULL;
T_GetRenderTarget					ST_GetRenderTarget						=NULL;
T_SetDepthStencilSurface			ST_SetDepthStencilSurface				=NULL;
T_GetDepthStencilSurface			ST_GetDepthStencilSurface				=NULL;
T_BeginScene						ST_BeginScene							=NULL;
T_EndScene							ST_EndScene								=NULL;
T_Clear								ST_Clear								=NULL;
T_SetTransform						ST_SetTransform							=NULL;
T_GetTransform						ST_GetTransform							=NULL;
T_MultiplyTransform					ST_MultiplyTransform					=NULL;
T_SetViewport						ST_SetViewport							=NULL;
T_GetViewport						ST_GetViewport							=NULL;
T_SetMaterial						ST_SetMaterial							=NULL;
T_GetMaterial						ST_GetMaterial							=NULL;
T_SetLight							ST_SetLight								=NULL;
T_GetLight							ST_GetLight								=NULL;
T_LightEnable						ST_LightEnable							=NULL;
T_GetLightEnable					ST_GetLightEnable						=NULL;
T_SetClipPlane						ST_SetClipPlane							=NULL;
T_GetClipPlane						ST_GetClipPlane							=NULL;
T_SetRenderState					ST_SetRenderState						=NULL;
T_GetRenderState					ST_GetRenderState						=NULL;
T_CreateStateBlock					ST_CreateStateBlock						=NULL;
T_BeginStateBlock					ST_BeginStateBlock						=NULL;
T_EndStateBlock						ST_EndStateBlock						=NULL;
T_SetClipStatus						ST_SetClipStatus						=NULL;
T_GetClipStatus						ST_GetClipStatus						=NULL;
T_GetTexture						ST_GetTexture							=NULL;
T_SetTexture						ST_SetTexture							=NULL;
T_GetTextureStageState				ST_GetTextureStageState					=NULL;
T_SetTextureStageState				ST_SetTextureStageState					=NULL;
T_GetSamplerState					ST_GetSamplerState						=NULL;
T_SetSamplerState					ST_SetSamplerState						=NULL;
T_ValidateDevice					ST_ValidateDevice						=NULL;
T_SetPaletteEntries					ST_SetPaletteEntries					=NULL;
T_GetPaletteEntries					ST_GetPaletteEntries					=NULL;
T_SetCurrentTexturePalette			ST_SetCurrentTexturePalette				=NULL;
T_GetCurrentTexturePalette			ST_GetCurrentTexturePalette				=NULL;
T_SetScissorRect					ST_SetScissorRect						=NULL;
T_GetScissorRect					ST_GetScissorRect						=NULL;
T_SetSoftwareVertexProcessing		ST_SetSoftwareVertexProcessing			=NULL;
T_GetSoftwareVertexProcessing		ST_GetSoftwareVertexProcessing			=NULL;
T_SetNPatchMode						ST_SetNPatchMode						=NULL;
T_GetNPatchMode						ST_GetNPatchMode						=NULL;
T_DrawPrimitive						ST_DrawPrimitive						=NULL;
T_DrawIndexedPrimitive				ST_DrawIndexedPrimitive					=NULL;
T_DrawPrimitiveUP					ST_DrawPrimitiveUP						=NULL;
T_DrawIndexedPrimitiveUP			ST_DrawIndexedPrimitiveUP				=NULL;
T_ProcessVertices					ST_ProcessVertices						=NULL;
T_CreateVertexDeclaration			ST_CreateVertexDeclaration				=NULL;
T_SetVertexDeclaration				ST_SetVertexDeclaration					=NULL;
T_GetVertexDeclaration				ST_GetVertexDeclaration					=NULL;
T_SetFVF							ST_SetFVF								=NULL;
T_GetFVF							ST_GetFVF								=NULL;
T_CreateVertexShader				ST_CreateVertexShader					=NULL;
T_SetVertexShader					ST_SetVertexShader						=NULL;
T_GetVertexShader					ST_GetVertexShader						=NULL;
T_SetVertexShaderConstantF			ST_SetVertexShaderConstantF				=NULL;
T_GetVertexShaderConstantF			ST_GetVertexShaderConstantF				=NULL;
T_SetVertexShaderConstantI			ST_SetVertexShaderConstantI				=NULL;
T_GetVertexShaderConstantI			ST_GetVertexShaderConstantI				=NULL;
T_SetVertexShaderConstantB			ST_SetVertexShaderConstantB				=NULL;
T_GetVertexShaderConstantB			ST_GetVertexShaderConstantB				=NULL;
T_SetStreamSource					ST_SetStreamSource						=NULL;
T_GetStreamSource					ST_GetStreamSource						=NULL;
T_SetStreamSourceFreq				ST_SetStreamSourceFreq					=NULL;
T_GetStreamSourceFreq				ST_GetStreamSourceFreq					=NULL;
T_SetIndices						ST_SetIndices							=NULL;
T_GetIndices						ST_GetIndices							=NULL;
T_CreatePixelShader					ST_CreatePixelShader					=NULL;
T_SetPixelShader					ST_SetPixelShader						=NULL;
T_GetPixelShader					ST_GetPixelShader						=NULL;
T_SetPixelShaderConstantF			ST_SetPixelShaderConstantF				=NULL;
T_GetPixelShaderConstantF			ST_GetPixelShaderConstantF				=NULL;
T_SetPixelShaderConstantI			ST_SetPixelShaderConstantI				=NULL;
T_GetPixelShaderConstantI			ST_GetPixelShaderConstantI				=NULL;
T_SetPixelShaderConstantB			ST_SetPixelShaderConstantB				=NULL;
T_GetPixelShaderConstantB			ST_GetPixelShaderConstantB				=NULL;
T_DrawRectPatch						ST_DrawRectPatch						=NULL;
T_DrawTriPatch						ST_DrawTriPatch							=NULL;
T_DeletePatch						ST_DeletePatch							=NULL;
T_CreateQuery						ST_CreateQuery							=NULL;


T_SwapChain_Present							ST_SwapChain_Present					 =NULL;
T_Surface_LockRect							ST_Surface_LockRect						 =NULL;
T_Surface_UnlockRect						ST_Surface_UnlockRect					 =NULL;

T_Surface_LockRect							ST_CubeSurface_LockRect					=	NULL;
T_Surface_UnlockRect						ST_CubeSurface_UnlockRect				=	NULL;

T_Volume_LockBox							ST_Volume_LockBox						 =NULL;
T_Volume_UnlockBox							ST_Volume_UnlockBox						 =NULL;
T_VertexBuffer_Lock							ST_VertexBuffer_Lock					 =NULL;
T_VertexBuffer_Unlock						ST_VertexBuffer_Unlock					 =NULL;
T_IndexBuffer_Lock							ST_IndexBuffer_Lock						 =NULL;
T_IndexBuffer_Unlock						ST_IndexBuffer_Unlock					 =NULL;
T_BaseTexture_SetAutoGenFilterType			ST_BaseTexture_SetAutoGenFilterType		 =NULL;
T_BaseTexture_GenerateMipSubLevels			ST_BaseTexture_GenerateMipSubLevels		 =NULL;
T_Texture_LockRect							ST_Texture_LockRect						 =NULL;
T_Texture_UnLockRect						ST_Texture_UnLockRect					 =NULL;
T_Texture_AddDirtyRect						ST_Texture_AddDirtyRect					 =NULL;
T_CubeTexture_LockRect						ST_CubeTexture_LockRect					 =NULL;
T_CubeTexture_UnlockRect					ST_CubeTexture_UnlockRect				 =NULL;
T_CubeTexture_AddDirtyRect					ST_CubeTexture_AddDirtyRect				 =NULL;
T_VolumeTexture_LockBox						ST_VolumeTexture_LockBox				 =NULL;
T_VolumeTexture_UnlockBox					ST_VolumeTexture_UnlockBox				 =NULL;
T_VolumeTexture_AddDirtyBox					ST_VolumeTexture_AddDirtyBox			 =NULL;
T_StateBlock_Apply							ST_StateBlock_Apply						 =NULL;
T_StateBlock_Capture						ST_StateBlock_Capture					 =NULL;
T_D3DPERF_BeginEvent						ST_D3DPERF_BeginEvent					 =NULL;
T_D3DPERF_EndEvent							ST_D3DPERF_EndEvent						 =NULL;
T_D3DPERF_SetMarker							ST_D3DPERF_SetMarker					 =NULL;
//T_Effect_SetValue							ST_Effect_SetValue						 =NULL;
//T_Effect_SetBool							ST_Effect_SetBool						 =NULL;
//T_Effect_SetBoolArray						ST_Effect_SetBoolArray					 =NULL;
//T_Effect_SetInt								ST_Effect_SetInt						 =NULL;
//T_Effect_SetIntArray						ST_Effect_SetIntArray					 =NULL;
//T_Effect_SetFloat							ST_Effect_SetFloat						 =NULL;
//T_Effect_SetFloatArray						ST_Effect_SetFloatArray					 =NULL;
//T_Effect_SetVector							ST_Effect_SetVector						 =NULL;
//T_Effect_SetVectorArray						ST_Effect_SetVectorArray				 =NULL;
//T_Effect_SetMatrix							ST_Effect_SetMatrix						 =NULL;
//T_Effect_SetMatrixArray						ST_Effect_SetMatrixArray				 =NULL;
//T_Effect_SetMatrixPointerArray				ST_Effect_SetMatrixPointerArray			 =NULL;
//T_Effect_SetMatrixTranspose					ST_Effect_SetMatrixTranspose			 =NULL;
//T_Effect_SetMatrixTransposeArray			ST_Effect_SetMatrixTransposeArray		 =NULL;
//T_Effect_SetMatrixTransposePointerArray		ST_Effect_SetMatrixTransposePointerArray =NULL;
//T_Effect_SetString							ST_Effect_SetString						 =NULL;
//T_Effect_SetTexture							ST_Effect_SetTexture					 =NULL;
//T_Effect_SetTechnique						ST_Effect_SetTechnique					 =NULL;
//T_Effect_Begin								ST_Effect_Begin							 =NULL;
//T_Effect_BeginPass							ST_Effect_BeginPass						 =NULL;
//T_Effect_CommitChanges						ST_Effect_CommitChanges					 =NULL;
//T_Effect_EndPass							ST_Effect_EndPass						 =NULL;
//T_Effect_End								ST_Effect_End							 =NULL;
//T_Effect_SetStateManager					ST_Effect_SetStateManager				 =NULL;
//T_Effect_SetRawValue						ST_Effect_SetRawValue					 =NULL;


U1	bHook_IDirect3DDevice9_Finished				=	false;
U1	bHook_IDirect3DSurface9_Finished			=	false;
U1	bHook_IDirect3DCubeSurface9_Finished		=	false;
U1	bHook_IDirect3DVolume9_Finished				=	false;
U1	bHook_IDirect3DSwapChain9_Finished			=	false;
U1	bHook_IDirect3DTexture9_Finished			=	false;
U1	bHook_IDirect3DCubeTexture9_Finished		=	false;
U1	bHook_IDirect3DVolumeTexture9_Finished		=	false;
U1	bHook_IDirect3DVertexBuffer9_Finished		=	false;
U1	bHook_IDirect3DIndexBuffer9_Finished		=	false;
U1	bHook_IDirect3DStateBlock9_Finished			=	false;

void	Hook_IDirect3DSurface9(IDirect3DDevice9* pDevice){
	if(bHook_IDirect3DSurface9_Finished)
		return;
	if(pDevice==NULL)
		return;

	IDirect3DSurface9* pSurface	=	NULL;
	IDirect3DTexture9* pTex	=	NULL;
	pDevice->lpVtbl->CreateTexture(pDevice,1,1,1,0,D3DFMT_A8R8G8B8,D3DPOOL_MANAGED,&pTex,NULL);
	pTex->lpVtbl->GetSurfaceLevel(pTex,0,&pSurface);


	ST_Surface_LockRect		=	pSurface->lpVtbl->LockRect;
	ST_Surface_UnlockRect	=	pSurface->lpVtbl->UnlockRect;


	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)	ST_Surface_LockRect				,MT_Surface_LockRect			);
	DetourAttach(&(PVOID&)	ST_Surface_UnlockRect			,MT_Surface_UnlockRect			);
	DetourTransactionCommit();

	pSurface->lpVtbl->Release(pSurface);
	pTex->lpVtbl->Release(pTex);

	bHook_IDirect3DSurface9_Finished	=	true;
}

void	Hook_IDirect3DCubeSurface9(IDirect3DDevice9* pDevice){
	if(bHook_IDirect3DCubeSurface9_Finished)
		return;
	if(pDevice==NULL)
		return;

	IDirect3DSurface9* pSurface	=	NULL;
	IDirect3DCubeTexture9* pTex	=	NULL;
	pDevice->lpVtbl->CreateCubeTexture(pDevice,1,1,0,D3DFMT_A8R8G8B8,D3DPOOL_MANAGED,&pTex,NULL);
	pTex->lpVtbl->GetCubeMapSurface(pTex,D3DCUBEMAP_FACE_NEGATIVE_X,0,&pSurface);

	ST_CubeSurface_LockRect		=	pSurface->lpVtbl->LockRect;
	ST_CubeSurface_UnlockRect	=	pSurface->lpVtbl->UnlockRect;


	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)	ST_CubeSurface_LockRect				,MT_Surface_LockRect			);
	DetourAttach(&(PVOID&)	ST_CubeSurface_UnlockRect			,MT_Surface_UnlockRect			);
	DetourTransactionCommit();

	pSurface->lpVtbl->Release(pSurface);
	pTex->lpVtbl->Release(pTex);

	bHook_IDirect3DCubeSurface9_Finished	=	true;
}

void	Hook_IDirect3DVolume9(IDirect3DDevice9* pDevice){
	if(bHook_IDirect3DVolume9_Finished)
		return;
	if(pDevice==NULL)
		return;

	IDirect3DVolume9* pVolume	=	NULL;
	IDirect3DVolumeTexture9* pTex	=	NULL;
	pDevice->lpVtbl->CreateVolumeTexture(pDevice,1,1,1,1,0,D3DFMT_A8R8G8B8,D3DPOOL_MANAGED,&pTex,NULL);
	pTex->lpVtbl->GetVolumeLevel(pTex,0,&pVolume);

	ST_Volume_LockBox		=	pVolume->lpVtbl->LockBox;
	ST_Volume_UnlockBox		=	pVolume->lpVtbl->UnlockBox;


	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)	ST_Volume_LockBox			,MT_Volume_LockBox			);
	DetourAttach(&(PVOID&)	ST_Volume_UnlockBox			,MT_Volume_UnlockBox			);
	DetourTransactionCommit();

	pVolume->lpVtbl->Release(pVolume);
	pTex->lpVtbl->Release(pTex);

	bHook_IDirect3DVolume9_Finished	=	true;

};

void	Hook_IDirect3DVertexBuffer9(IDirect3DDevice9* pDevice){
	if(bHook_IDirect3DVertexBuffer9_Finished)
		return;
	if(pDevice==NULL)
		return;

	IDirect3DVertexBuffer9* pVB=NULL;
	pDevice->lpVtbl->CreateVertexBuffer(pDevice,32,0,0,D3DPOOL_MANAGED,&pVB,0);
	ST_VertexBuffer_Lock		=	pVB->lpVtbl->Lock;
	ST_VertexBuffer_Unlock		=	pVB->lpVtbl->Unlock;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)	ST_VertexBuffer_Lock			,MT_VertexBuffer_Lock			);
	DetourAttach(&(PVOID&)	ST_VertexBuffer_Unlock			,MT_VertexBuffer_Unlock			);
	DetourTransactionCommit();

	pVB->lpVtbl->Release(pVB);

	bHook_IDirect3DVertexBuffer9_Finished	=	true;
}
void	Hook_IDirect3DIndexBuffer9(IDirect3DDevice9* pDevice){
	if(bHook_IDirect3DIndexBuffer9_Finished)
		return;
	if(pDevice==NULL)
		return;

	IDirect3DIndexBuffer9* pIB=NULL;
	pDevice->lpVtbl->CreateIndexBuffer(pDevice,32,0,D3DFMT_INDEX16,D3DPOOL_MANAGED,&pIB,0);
	ST_IndexBuffer_Lock			=	pIB->lpVtbl->Lock;
	ST_IndexBuffer_Unlock		=	pIB->lpVtbl->Unlock;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)	ST_IndexBuffer_Lock			,MT_IndexBuffer_Lock			);
	DetourAttach(&(PVOID&)	ST_IndexBuffer_Unlock			,MT_IndexBuffer_Unlock			);
	DetourTransactionCommit();

	pIB->lpVtbl->Release(pIB);

	bHook_IDirect3DIndexBuffer9_Finished	=	true;
}

void	Hook_IDirect3DStateBlock9(IDirect3DDevice9* pDevice){
	if(bHook_IDirect3DIndexBuffer9_Finished)
		return;
	if(pDevice==NULL)
		return;

	IDirect3DStateBlock9* p=NULL;
	pDevice->lpVtbl->CreateStateBlock(pDevice,D3DSBT_ALL,&p);
	ST_StateBlock_Apply			=	p->lpVtbl->Apply;
	ST_StateBlock_Capture		=	p->lpVtbl->Capture;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)	ST_StateBlock_Apply				,MT_StateBlock_Apply			);
	DetourAttach(&(PVOID&)	ST_StateBlock_Capture			,MT_StateBlock_Capture			);
	DetourTransactionCommit();

	p->lpVtbl->Release(p);

	bHook_IDirect3DIndexBuffer9_Finished	=	true;

}


void	Hook_IDirect3DSwapChain9(IDirect3DDevice9* pDevice){
	if(bHook_IDirect3DSwapChain9_Finished)
		return;
	if(pDevice==NULL)
		return;

	IDirect3DSwapChain9*	pSwap=NULL;
	ST_GetSwapChain(pDevice,0,&pSwap);

	ST_SwapChain_Present	=	pSwap->lpVtbl->Present;
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)	ST_SwapChain_Present				 ,MT_SwapChain_Present			);
	DetourTransactionCommit();

	pSwap->lpVtbl->Release(pSwap);


	bHook_IDirect3DSwapChain9_Finished	=	true;
}



//void	Hook_IDirect3DTexture9(IDirect3DTexture9* p){
//	if(bHook_IDirect3DTexture9_Finished)
//		return;
//	if(p==NULL)
//		return;
//
//	ST_SwapChain_Present	=	pSwap->lpVtbl->Present;
//	DetourTransactionBegin();
//	DetourUpdateThread(GetCurrentThread());
//	DetourAttach(&(PVOID&)	ST_SwapChain_Present				 ,MT_SwapChain_Present			);
//	DetourTransactionCommit();
//
//	bHook_IDirect3DTexture9_Finished	=	true;
//}

void	Hook_IDirect3DDevice9(IDirect3DDevice9*	pThis){
		if(bHook_IDirect3DDevice9_Finished)
			return;

		ST_TestCooperativeLevel					=	pThis->lpVtbl->TestCooperativeLevel			;
		ST_EvictManagedResources				=	pThis->lpVtbl->EvictManagedResources		;
		ST_SetCursorProperties					=	pThis->lpVtbl->SetCursorProperties			;
		ST_SetCursorPosition					=	pThis->lpVtbl->SetCursorPosition			;
		ST_ShowCursor							=	pThis->lpVtbl->ShowCursor					;
		ST_CreateAdditionalSwapChain			=	pThis->lpVtbl->CreateAdditionalSwapChain	;
		ST_GetSwapChain							=	pThis->lpVtbl->GetSwapChain					;
		ST_GetNumberOfSwapChains				=	pThis->lpVtbl->GetNumberOfSwapChains		;
		ST_Reset								=	pThis->lpVtbl->Reset						;
		ST_Present								=	pThis->lpVtbl->Present						;
		ST_GetBackBuffer						=	pThis->lpVtbl->GetBackBuffer				;
		ST_GetRasterStatus						=	pThis->lpVtbl->GetRasterStatus				;
		ST_SetDialogBoxMode						=	pThis->lpVtbl->SetDialogBoxMode				;
		ST_SetGammaRamp							=	pThis->lpVtbl->SetGammaRamp					;
		ST_GetGammaRamp							=	pThis->lpVtbl->GetGammaRamp					;
		ST_CreateTexture						=	pThis->lpVtbl->CreateTexture				;
		ST_CreateVolumeTexture					=	pThis->lpVtbl->CreateVolumeTexture			;
		ST_CreateCubeTexture					=	pThis->lpVtbl->CreateCubeTexture			;
		ST_CreateVertexBuffer					=	pThis->lpVtbl->CreateVertexBuffer			;
		ST_CreateIndexBuffer					=	pThis->lpVtbl->CreateIndexBuffer			;
		ST_CreateRenderTarget					=	pThis->lpVtbl->CreateRenderTarget			;
		ST_CreateDepthStencilSurface			=	pThis->lpVtbl->CreateDepthStencilSurface	;
		ST_UpdateSurface						=	pThis->lpVtbl->UpdateSurface				;
		ST_UpdateTexture						=	pThis->lpVtbl->UpdateTexture				;
		ST_GetRenderTargetData					=	pThis->lpVtbl->GetRenderTargetData			;
		ST_GetFrontBufferData					=	pThis->lpVtbl->GetFrontBufferData			;
		ST_StretchRect							=	pThis->lpVtbl->StretchRect					;
		ST_ColorFill							=	pThis->lpVtbl->ColorFill					;
		ST_CreateOffscreenPlainSurface			=	pThis->lpVtbl->CreateOffscreenPlainSurface	;
		ST_SetRenderTarget						=	pThis->lpVtbl->SetRenderTarget				;
		ST_GetRenderTarget						=	pThis->lpVtbl->GetRenderTarget				;
		ST_SetDepthStencilSurface				=	pThis->lpVtbl->SetDepthStencilSurface		;
		ST_GetDepthStencilSurface				=	pThis->lpVtbl->GetDepthStencilSurface		;
		ST_BeginScene							=	pThis->lpVtbl->BeginScene					;
		ST_EndScene								=	pThis->lpVtbl->EndScene						;
		ST_Clear								=	pThis->lpVtbl->Clear						;
		ST_SetTransform							=	pThis->lpVtbl->SetTransform					;
		ST_GetTransform							=	pThis->lpVtbl->GetTransform					;
		ST_MultiplyTransform					=	pThis->lpVtbl->MultiplyTransform			;
		ST_SetViewport							=	pThis->lpVtbl->SetViewport					;
		ST_GetViewport							=	pThis->lpVtbl->GetViewport					;
		ST_SetMaterial							=	pThis->lpVtbl->SetMaterial					;
		ST_GetMaterial							=	pThis->lpVtbl->GetMaterial					;
		ST_SetLight								=	pThis->lpVtbl->SetLight						;
		ST_GetLight								=	pThis->lpVtbl->GetLight						;
		ST_LightEnable							=	pThis->lpVtbl->LightEnable					;
		ST_GetLightEnable						=	pThis->lpVtbl->GetLightEnable				;
		ST_SetClipPlane							=	pThis->lpVtbl->SetClipPlane					;
		ST_GetClipPlane							=	pThis->lpVtbl->GetClipPlane					;
		ST_SetRenderState						=	pThis->lpVtbl->SetRenderState				;
		ST_GetRenderState						=	pThis->lpVtbl->GetRenderState				;
		ST_CreateStateBlock						=	pThis->lpVtbl->CreateStateBlock				;
		ST_BeginStateBlock						=	pThis->lpVtbl->BeginStateBlock				;
		ST_EndStateBlock						=	pThis->lpVtbl->EndStateBlock				;
		ST_SetClipStatus						=	pThis->lpVtbl->SetClipStatus				;
		ST_GetClipStatus						=	pThis->lpVtbl->GetClipStatus				;
		ST_GetTexture							=	pThis->lpVtbl->GetTexture					;
		ST_SetTexture							=	pThis->lpVtbl->SetTexture					;
		ST_GetTextureStageState					=	pThis->lpVtbl->GetTextureStageState			;
		ST_SetTextureStageState					=	pThis->lpVtbl->SetTextureStageState			;
		ST_GetSamplerState						=	pThis->lpVtbl->GetSamplerState				;
		ST_SetSamplerState						=	pThis->lpVtbl->SetSamplerState				;
		ST_ValidateDevice						=	pThis->lpVtbl->ValidateDevice				;
		ST_SetPaletteEntries					=	pThis->lpVtbl->SetPaletteEntries			;
		ST_GetPaletteEntries					=	pThis->lpVtbl->GetPaletteEntries			;
		ST_SetCurrentTexturePalette				=	pThis->lpVtbl->SetCurrentTexturePalette		;
		ST_GetCurrentTexturePalette				=	pThis->lpVtbl->GetCurrentTexturePalette		;
		ST_SetScissorRect						=	pThis->lpVtbl->SetScissorRect				;
		ST_GetScissorRect						=	pThis->lpVtbl->GetScissorRect				;
		ST_SetSoftwareVertexProcessing			=	pThis->lpVtbl->SetSoftwareVertexProcessing	;
		ST_GetSoftwareVertexProcessing			=	pThis->lpVtbl->GetSoftwareVertexProcessing	;
		ST_SetNPatchMode						=	pThis->lpVtbl->SetNPatchMode				;
		ST_GetNPatchMode						=	pThis->lpVtbl->GetNPatchMode				;
		ST_DrawPrimitive						=	pThis->lpVtbl->DrawPrimitive				;
		ST_DrawIndexedPrimitive					=	pThis->lpVtbl->DrawIndexedPrimitive			;
		ST_DrawPrimitiveUP						=	pThis->lpVtbl->DrawPrimitiveUP				;
		ST_DrawIndexedPrimitiveUP				=	pThis->lpVtbl->DrawIndexedPrimitiveUP		;
		ST_ProcessVertices						=	pThis->lpVtbl->ProcessVertices				;
		ST_CreateVertexDeclaration				=	pThis->lpVtbl->CreateVertexDeclaration		;
		ST_SetVertexDeclaration					=	pThis->lpVtbl->SetVertexDeclaration			;
		ST_GetVertexDeclaration					=	pThis->lpVtbl->GetVertexDeclaration			;
		ST_SetFVF								=	pThis->lpVtbl->SetFVF						;
		ST_GetFVF								=	pThis->lpVtbl->GetFVF						;
		ST_CreateVertexShader					=	pThis->lpVtbl->CreateVertexShader			;
		ST_SetVertexShader						=	pThis->lpVtbl->SetVertexShader				;
		ST_GetVertexShader						=	pThis->lpVtbl->GetVertexShader				;
		ST_SetVertexShaderConstantF				=	pThis->lpVtbl->SetVertexShaderConstantF		;
		ST_GetVertexShaderConstantF				=	pThis->lpVtbl->GetVertexShaderConstantF		;
		ST_SetVertexShaderConstantI				=	pThis->lpVtbl->SetVertexShaderConstantI		;
		ST_GetVertexShaderConstantI				=	pThis->lpVtbl->GetVertexShaderConstantI		;
		ST_SetVertexShaderConstantB				=	pThis->lpVtbl->SetVertexShaderConstantB		;
		ST_GetVertexShaderConstantB				=	pThis->lpVtbl->GetVertexShaderConstantB		;
		ST_SetStreamSource						=	pThis->lpVtbl->SetStreamSource				;
		ST_GetStreamSource						=	pThis->lpVtbl->GetStreamSource				;
		ST_SetStreamSourceFreq					=	pThis->lpVtbl->SetStreamSourceFreq			;
		ST_GetStreamSourceFreq					=	pThis->lpVtbl->GetStreamSourceFreq			;
		ST_SetIndices							=	pThis->lpVtbl->SetIndices					;
		ST_GetIndices							=	pThis->lpVtbl->GetIndices					;
		ST_CreatePixelShader					=	pThis->lpVtbl->CreatePixelShader			;
		ST_SetPixelShader						=	pThis->lpVtbl->SetPixelShader				;
		ST_GetPixelShader						=	pThis->lpVtbl->GetPixelShader				;
		ST_SetPixelShaderConstantF				=	pThis->lpVtbl->SetPixelShaderConstantF		;
		ST_GetPixelShaderConstantF				=	pThis->lpVtbl->GetPixelShaderConstantF		;
		ST_SetPixelShaderConstantI				=	pThis->lpVtbl->SetPixelShaderConstantI		;
		ST_GetPixelShaderConstantI				=	pThis->lpVtbl->GetPixelShaderConstantI		;
		ST_SetPixelShaderConstantB				=	pThis->lpVtbl->SetPixelShaderConstantB		;
		ST_GetPixelShaderConstantB				=	pThis->lpVtbl->GetPixelShaderConstantB		;
		ST_DrawRectPatch						=	pThis->lpVtbl->DrawRectPatch				;
		ST_DrawTriPatch							=	pThis->lpVtbl->DrawTriPatch					;
		ST_DeletePatch							=	pThis->lpVtbl->DeletePatch					;
		ST_CreateQuery							=	pThis->lpVtbl->CreateQuery					;

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());

			DetourAttach(&(PVOID&)	ST_TestCooperativeLevel				 ,MT_TestCooperativeLevel			);
			DetourAttach(&(PVOID&)	ST_EvictManagedResources			 ,MT_EvictManagedResources			);
			DetourAttach(&(PVOID&)	ST_SetCursorProperties				 ,MT_SetCursorProperties			);
			DetourAttach(&(PVOID&)	ST_SetCursorPosition				 ,MT_SetCursorPosition				);
			DetourAttach(&(PVOID&)	ST_ShowCursor						 ,MT_ShowCursor						);
			DetourAttach(&(PVOID&)	ST_CreateAdditionalSwapChain		 ,MT_CreateAdditionalSwapChain		);
			//DetourAttach(&(PVOID&)	ST_GetSwapChain						 ,MT_GetSwapChain					);
			//DetourAttach(&(PVOID&)	ST_GetNumberOfSwapChains			 ,MT_GetNumberOfSwapChains			);
			DetourAttach(&(PVOID&)	ST_Reset							 ,MT_Reset							);
			DetourAttach(&(PVOID&)	ST_Present							 ,MT_Present						);
			//DetourAttach(&(PVOID&)	ST_GetBackBuffer					 ,MT_GetBackBuffer					);
			DetourAttach(&(PVOID&)	ST_GetRasterStatus					 ,MT_GetRasterStatus				);
			DetourAttach(&(PVOID&)	ST_SetDialogBoxMode					 ,MT_SetDialogBoxMode				);
			DetourAttach(&(PVOID&)	ST_SetGammaRamp						 ,MT_SetGammaRamp					);
			DetourAttach(&(PVOID&)	ST_GetGammaRamp						 ,MT_GetGammaRamp					);
			DetourAttach(&(PVOID&)	ST_CreateTexture					 ,MT_CreateTexture					);
			DetourAttach(&(PVOID&)	ST_CreateVolumeTexture				 ,MT_CreateVolumeTexture			);
			DetourAttach(&(PVOID&)	ST_CreateCubeTexture				 ,MT_CreateCubeTexture				);
			DetourAttach(&(PVOID&)	ST_CreateVertexBuffer				 ,MT_CreateVertexBuffer				);
			DetourAttach(&(PVOID&)	ST_CreateIndexBuffer				 ,MT_CreateIndexBuffer				);
			DetourAttach(&(PVOID&)	ST_CreateRenderTarget				 ,MT_CreateRenderTarget				);
			DetourAttach(&(PVOID&)	ST_CreateDepthStencilSurface		 ,MT_CreateDepthStencilSurface		);
			DetourAttach(&(PVOID&)	ST_UpdateSurface					 ,MT_UpdateSurface					);
			DetourAttach(&(PVOID&)	ST_UpdateTexture					 ,MT_UpdateTexture					);
			//DetourAttach(&(PVOID&)	ST_GetRenderTargetData				 ,MT_GetRenderTargetData			);
			//DetourAttach(&(PVOID&)	ST_GetFrontBufferData				 ,MT_GetFrontBufferData				);
			DetourAttach(&(PVOID&)	ST_StretchRect						 ,MT_StretchRect					);
			DetourAttach(&(PVOID&)	ST_ColorFill						 ,MT_ColorFill						);
			DetourAttach(&(PVOID&)	ST_CreateOffscreenPlainSurface		 ,MT_CreateOffscreenPlainSurface	);
			DetourAttach(&(PVOID&)	ST_SetRenderTarget					 ,MT_SetRenderTarget				);
			//DetourAttach(&(PVOID&)	ST_GetRenderTarget					 ,MT_GetRenderTarget				);
			DetourAttach(&(PVOID&)	ST_SetDepthStencilSurface			 ,MT_SetDepthStencilSurface			);
			//DetourAttach(&(PVOID&)	ST_GetDepthStencilSurface			 ,MT_GetDepthStencilSurface			);
			DetourAttach(&(PVOID&)	ST_BeginScene						 ,MT_BeginScene						);
			DetourAttach(&(PVOID&)	ST_EndScene							 ,MT_EndScene						);
			DetourAttach(&(PVOID&)	ST_Clear							 ,MT_Clear							);
			DetourAttach(&(PVOID&)	ST_SetTransform						 ,MT_SetTransform					);
			//DetourAttach(&(PVOID&)	ST_GetTransform						 ,MT_GetTransform					);
			DetourAttach(&(PVOID&)	ST_MultiplyTransform				 ,MT_MultiplyTransform				);
			DetourAttach(&(PVOID&)	ST_SetViewport						 ,MT_SetViewport					);
			//DetourAttach(&(PVOID&)	ST_GetViewport						 ,MT_GetViewport					);
			DetourAttach(&(PVOID&)	ST_SetMaterial						 ,MT_SetMaterial					);
			//DetourAttach(&(PVOID&)	ST_GetMaterial						 ,MT_GetMaterial					);
			DetourAttach(&(PVOID&)	ST_SetLight							 ,MT_SetLight						);
			//DetourAttach(&(PVOID&)	ST_GetLight							 ,MT_GetLight						);
			DetourAttach(&(PVOID&)	ST_LightEnable						 ,MT_LightEnable					);
			//DetourAttach(&(PVOID&)	ST_GetLightEnable					 ,MT_GetLightEnable					);
			DetourAttach(&(PVOID&)	ST_SetClipPlane						 ,MT_SetClipPlane					);
			//DetourAttach(&(PVOID&)	ST_GetClipPlane						 ,MT_GetClipPlane					);
			DetourAttach(&(PVOID&)	ST_SetRenderState					 ,MT_SetRenderState					);
			//DetourAttach(&(PVOID&)	ST_GetRenderState					 ,MT_GetRenderState					);
			DetourAttach(&(PVOID&)	ST_CreateStateBlock					 ,MT_CreateStateBlock				);
			DetourAttach(&(PVOID&)	ST_BeginStateBlock					 ,MT_BeginStateBlock				);
			DetourAttach(&(PVOID&)	ST_EndStateBlock					 ,MT_EndStateBlock					);
			DetourAttach(&(PVOID&)	ST_SetClipStatus					 ,MT_SetClipStatus					);
			DetourAttach(&(PVOID&)	ST_GetClipStatus					 ,MT_GetClipStatus					);
			DetourAttach(&(PVOID&)	ST_GetTexture						 ,MT_GetTexture						);
			DetourAttach(&(PVOID&)	ST_SetTexture						 ,MT_SetTexture						);
			DetourAttach(&(PVOID&)	ST_GetTextureStageState				 ,MT_GetTextureStageState			);
			DetourAttach(&(PVOID&)	ST_SetTextureStageState				 ,MT_SetTextureStageState			);
			DetourAttach(&(PVOID&)	ST_GetSamplerState					 ,MT_GetSamplerState				);
			DetourAttach(&(PVOID&)	ST_SetSamplerState					 ,MT_SetSamplerState				);
			DetourAttach(&(PVOID&)	ST_ValidateDevice					 ,MT_ValidateDevice					);
			DetourAttach(&(PVOID&)	ST_SetPaletteEntries				 ,MT_SetPaletteEntries				);
			DetourAttach(&(PVOID&)	ST_GetPaletteEntries				 ,MT_GetPaletteEntries				);
			DetourAttach(&(PVOID&)	ST_SetCurrentTexturePalette			 ,MT_SetCurrentTexturePalette		);
			DetourAttach(&(PVOID&)	ST_GetCurrentTexturePalette			 ,MT_GetCurrentTexturePalette		);
			DetourAttach(&(PVOID&)	ST_SetScissorRect					 ,MT_SetScissorRect					);
			DetourAttach(&(PVOID&)	ST_GetScissorRect					 ,MT_GetScissorRect					);
			DetourAttach(&(PVOID&)	ST_SetSoftwareVertexProcessing		 ,MT_SetSoftwareVertexProcessing	);
			DetourAttach(&(PVOID&)	ST_GetSoftwareVertexProcessing		 ,MT_GetSoftwareVertexProcessing	);
			DetourAttach(&(PVOID&)	ST_SetNPatchMode					 ,MT_SetNPatchMode					);
			DetourAttach(&(PVOID&)	ST_GetNPatchMode					 ,MT_GetNPatchMode					);
			DetourAttach(&(PVOID&)	ST_DrawPrimitive					 ,MT_DrawPrimitive					);
			DetourAttach(&(PVOID&)	ST_DrawIndexedPrimitive				 ,MT_DrawIndexedPrimitive			);
			DetourAttach(&(PVOID&)	ST_DrawPrimitiveUP					 ,MT_DrawPrimitiveUP				);
			DetourAttach(&(PVOID&)	ST_DrawIndexedPrimitiveUP			 ,MT_DrawIndexedPrimitiveUP			);
			DetourAttach(&(PVOID&)	ST_ProcessVertices					 ,MT_ProcessVertices				);
			DetourAttach(&(PVOID&)	ST_CreateVertexDeclaration			 ,MT_CreateVertexDeclaration		);
			DetourAttach(&(PVOID&)	ST_SetVertexDeclaration				 ,MT_SetVertexDeclaration			);
			DetourAttach(&(PVOID&)	ST_GetVertexDeclaration				 ,MT_GetVertexDeclaration			);
			DetourAttach(&(PVOID&)	ST_SetFVF							 ,MT_SetFVF							);
			DetourAttach(&(PVOID&)	ST_GetFVF							 ,MT_GetFVF							);
			DetourAttach(&(PVOID&)	ST_CreateVertexShader				 ,MT_CreateVertexShader				);
			DetourAttach(&(PVOID&)	ST_SetVertexShader					 ,MT_SetVertexShader				);
			DetourAttach(&(PVOID&)	ST_GetVertexShader					 ,MT_GetVertexShader				);
			DetourAttach(&(PVOID&)	ST_SetVertexShaderConstantF			 ,MT_SetVertexShaderConstantF		);
			DetourAttach(&(PVOID&)	ST_GetVertexShaderConstantF			 ,MT_GetVertexShaderConstantF		);
			DetourAttach(&(PVOID&)	ST_SetVertexShaderConstantI			 ,MT_SetVertexShaderConstantI		);
			DetourAttach(&(PVOID&)	ST_GetVertexShaderConstantI			 ,MT_GetVertexShaderConstantI		);
			DetourAttach(&(PVOID&)	ST_SetVertexShaderConstantB			 ,MT_SetVertexShaderConstantB		);
			DetourAttach(&(PVOID&)	ST_GetVertexShaderConstantB			 ,MT_GetVertexShaderConstantB		);
			DetourAttach(&(PVOID&)	ST_SetStreamSource					 ,MT_SetStreamSource				);
			DetourAttach(&(PVOID&)	ST_GetStreamSource					 ,MT_GetStreamSource				);
			DetourAttach(&(PVOID&)	ST_SetStreamSourceFreq				 ,MT_SetStreamSourceFreq			);
			DetourAttach(&(PVOID&)	ST_GetStreamSourceFreq				 ,MT_GetStreamSourceFreq			);
			DetourAttach(&(PVOID&)	ST_SetIndices						 ,MT_SetIndices						);
			DetourAttach(&(PVOID&)	ST_GetIndices						 ,MT_GetIndices						);
			DetourAttach(&(PVOID&)	ST_CreatePixelShader				 ,MT_CreatePixelShader				);
			DetourAttach(&(PVOID&)	ST_SetPixelShader					 ,MT_SetPixelShader					);
			DetourAttach(&(PVOID&)	ST_GetPixelShader					 ,MT_GetPixelShader					);
			DetourAttach(&(PVOID&)	ST_SetPixelShaderConstantF			 ,MT_SetPixelShaderConstantF		);
			DetourAttach(&(PVOID&)	ST_GetPixelShaderConstantF			 ,MT_GetPixelShaderConstantF		);
			DetourAttach(&(PVOID&)	ST_SetPixelShaderConstantI			 ,MT_SetPixelShaderConstantI		);
			DetourAttach(&(PVOID&)	ST_GetPixelShaderConstantI			 ,MT_GetPixelShaderConstantI		);
			DetourAttach(&(PVOID&)	ST_SetPixelShaderConstantB			 ,MT_SetPixelShaderConstantB		);
			DetourAttach(&(PVOID&)	ST_GetPixelShaderConstantB			 ,MT_GetPixelShaderConstantB		);
			DetourAttach(&(PVOID&)	ST_DrawRectPatch					 ,MT_DrawRectPatch					);
			DetourAttach(&(PVOID&)	ST_DrawTriPatch						 ,MT_DrawTriPatch					);
			DetourAttach(&(PVOID&)	ST_DeletePatch						 ,MT_DeletePatch					);
			DetourAttach(&(PVOID&)	ST_CreateQuery						 ,MT_CreateQuery					);

		DetourTransactionCommit();

		//HOOK SURFACE
		//Hook_IDirect3DSurface9(pThis);
		//HOOK CUBESURFACE
		//Hook_IDirect3DCubeSurface9(pThis);
		//HOOK VOLUME
		Hook_IDirect3DVolume9(pThis);
		//HOOK VERTEXBUFFER
		Hook_IDirect3DVertexBuffer9(pThis);
		//HOOK INDEXBUFFER
		Hook_IDirect3DIndexBuffer9(pThis);
		//HOOK STATEBLOCK
		Hook_IDirect3DStateBlock9(pThis);
		//HOOK SWAPCHAIN
		Hook_IDirect3DSwapChain9(pThis);


		MT_RenderThread::GetSingleton().SetDevice(pThis);

		bHook_IDirect3DDevice9_Finished	=	true;
}
void	UnHook_IDirect3DDevice9(){
	if(!bHook_IDirect3DDevice9_Finished)
		return;
#if 0
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	DetourDetach(&(PVOID&)	ST_TestCooperativeLevel				 ,MT_TestCooperativeLevel			);
	DetourDetach(&(PVOID&)	ST_EvictManagedResources			 ,MT_EvictManagedResources			);
	DetourDetach(&(PVOID&)	ST_SetCursorProperties				 ,MT_SetCursorProperties			);
	DetourDetach(&(PVOID&)	ST_SetCursorPosition				 ,MT_SetCursorPosition				);
	DetourDetach(&(PVOID&)	ST_ShowCursor						 ,MT_ShowCursor						);
	DetourDetach(&(PVOID&)	ST_CreateAdditionalSwapChain		 ,MT_CreateAdditionalSwapChain		);
	DetourDetach(&(PVOID&)	ST_GetSwapChain						 ,MT_GetSwapChain					);
	DetourDetach(&(PVOID&)	ST_GetNumberOfSwapChains			 ,MT_GetNumberOfSwapChains			);
	DetourDetach(&(PVOID&)	ST_Reset							 ,MT_Reset							);
	DetourDetach(&(PVOID&)	ST_Present							 ,MT_Present						);
	DetourDetach(&(PVOID&)	ST_GetBackBuffer					 ,MT_GetBackBuffer					);
	DetourDetach(&(PVOID&)	ST_GetRasterStatus					 ,MT_GetRasterStatus				);
	DetourDetach(&(PVOID&)	ST_SetDialogBoxMode					 ,MT_SetDialogBoxMode				);
	DetourDetach(&(PVOID&)	ST_SetGammaRamp						 ,MT_SetGammaRamp					);
	DetourDetach(&(PVOID&)	ST_GetGammaRamp						 ,MT_GetGammaRamp					);
	DetourDetach(&(PVOID&)	ST_CreateTexture					 ,MT_CreateTexture					);
	DetourDetach(&(PVOID&)	ST_CreateVolumeTexture				 ,MT_CreateVolumeTexture			);
	DetourDetach(&(PVOID&)	ST_CreateCubeTexture				 ,MT_CreateCubeTexture				);
	DetourDetach(&(PVOID&)	ST_CreateVertexBuffer				 ,MT_CreateVertexBuffer				);
	DetourDetach(&(PVOID&)	ST_CreateIndexBuffer				 ,MT_CreateIndexBuffer				);
	DetourDetach(&(PVOID&)	ST_CreateRenderTarget				 ,MT_CreateRenderTarget				);
	DetourDetach(&(PVOID&)	ST_CreateDepthStencilSurface		 ,MT_CreateDepthStencilSurface		);
	DetourDetach(&(PVOID&)	ST_UpdateSurface					 ,MT_UpdateSurface					);
	DetourDetach(&(PVOID&)	ST_UpdateTexture					 ,MT_UpdateTexture					);
	DetourDetach(&(PVOID&)	ST_GetRenderTargetData				 ,MT_GetRenderTargetData			);
	DetourDetach(&(PVOID&)	ST_GetFrontBufferData				 ,MT_GetFrontBufferData				);
	DetourDetach(&(PVOID&)	ST_StretchRect						 ,MT_StretchRect					);
	DetourDetach(&(PVOID&)	ST_ColorFill						 ,MT_ColorFill						);
	DetourDetach(&(PVOID&)	ST_CreateOffscreenPlainSurface		 ,MT_CreateOffscreenPlainSurface	);
	DetourDetach(&(PVOID&)	ST_SetRenderTarget					 ,MT_SetRenderTarget				);
	DetourDetach(&(PVOID&)	ST_GetRenderTarget					 ,MT_GetRenderTarget				);
	DetourDetach(&(PVOID&)	ST_SetDepthStencilSurface			 ,MT_SetDepthStencilSurface			);
	DetourDetach(&(PVOID&)	ST_GetDepthStencilSurface			 ,MT_GetDepthStencilSurface			);
	DetourDetach(&(PVOID&)	ST_BeginScene						 ,MT_BeginScene						);
	DetourDetach(&(PVOID&)	ST_EndScene							 ,MT_EndScene						);
	DetourDetach(&(PVOID&)	ST_Clear							 ,MT_Clear							);
	DetourDetach(&(PVOID&)	ST_SetTransform						 ,MT_SetTransform					);
	DetourDetach(&(PVOID&)	ST_GetTransform						 ,MT_GetTransform					);
	DetourDetach(&(PVOID&)	ST_MultiplyTransform				 ,MT_MultiplyTransform				);
	DetourDetach(&(PVOID&)	ST_SetViewport						 ,MT_SetViewport					);
	DetourDetach(&(PVOID&)	ST_GetViewport						 ,MT_GetViewport					);
	DetourDetach(&(PVOID&)	ST_SetMaterial						 ,MT_SetMaterial					);
	DetourDetach(&(PVOID&)	ST_GetMaterial						 ,MT_GetMaterial					);
	DetourDetach(&(PVOID&)	ST_SetLight							 ,MT_SetLight						);
	DetourDetach(&(PVOID&)	ST_GetLight							 ,MT_GetLight						);
	DetourDetach(&(PVOID&)	ST_LightEnable						 ,MT_LightEnable					);
	DetourDetach(&(PVOID&)	ST_GetLightEnable					 ,MT_GetLightEnable					);
	DetourDetach(&(PVOID&)	ST_SetClipPlane						 ,MT_SetClipPlane					);
	DetourDetach(&(PVOID&)	ST_GetClipPlane						 ,MT_GetClipPlane					);
	DetourDetach(&(PVOID&)	ST_SetRenderState					 ,MT_SetRenderState					);
	DetourDetach(&(PVOID&)	ST_GetRenderState					 ,MT_GetRenderState					);
	DetourDetach(&(PVOID&)	ST_CreateStateBlock					 ,MT_CreateStateBlock				);
	DetourDetach(&(PVOID&)	ST_BeginStateBlock					 ,MT_BeginStateBlock				);
	DetourDetach(&(PVOID&)	ST_EndStateBlock					 ,MT_EndStateBlock					);
	DetourDetach(&(PVOID&)	ST_SetClipStatus					 ,MT_SetClipStatus					);
	DetourDetach(&(PVOID&)	ST_GetClipStatus					 ,MT_GetClipStatus					);
	DetourDetach(&(PVOID&)	ST_GetTexture						 ,MT_GetTexture						);
	DetourDetach(&(PVOID&)	ST_SetTexture						 ,MT_SetTexture						);
	DetourDetach(&(PVOID&)	ST_GetTextureStageState				 ,MT_GetTextureStageState			);
	DetourDetach(&(PVOID&)	ST_SetTextureStageState				 ,MT_SetTextureStageState			);
	DetourDetach(&(PVOID&)	ST_GetSamplerState					 ,MT_GetSamplerState				);
	DetourDetach(&(PVOID&)	ST_SetSamplerState					 ,MT_SetSamplerState				);
	DetourDetach(&(PVOID&)	ST_ValidateDevice					 ,MT_ValidateDevice					);
	DetourDetach(&(PVOID&)	ST_SetPaletteEntries				 ,MT_SetPaletteEntries				);
	DetourDetach(&(PVOID&)	ST_GetPaletteEntries				 ,MT_GetPaletteEntries				);
	DetourDetach(&(PVOID&)	ST_SetCurrentTexturePalette			 ,MT_SetCurrentTexturePalette		);
	DetourDetach(&(PVOID&)	ST_GetCurrentTexturePalette			 ,MT_GetCurrentTexturePalette		);
	DetourDetach(&(PVOID&)	ST_SetScissorRect					 ,MT_SetScissorRect					);
	DetourDetach(&(PVOID&)	ST_GetScissorRect					 ,MT_GetScissorRect					);
	DetourDetach(&(PVOID&)	ST_SetSoftwareVertexProcessing		 ,MT_SetSoftwareVertexProcessing	);
	DetourDetach(&(PVOID&)	ST_GetSoftwareVertexProcessing		 ,MT_GetSoftwareVertexProcessing	);
	DetourDetach(&(PVOID&)	ST_SetNPatchMode					 ,MT_SetNPatchMode					);
	DetourDetach(&(PVOID&)	ST_GetNPatchMode					 ,MT_GetNPatchMode					);
	DetourDetach(&(PVOID&)	ST_DrawPrimitive					 ,MT_DrawPrimitive					);
	DetourDetach(&(PVOID&)	ST_DrawIndexedPrimitive				 ,MT_DrawIndexedPrimitive			);
	DetourDetach(&(PVOID&)	ST_DrawPrimitiveUP					 ,MT_DrawPrimitiveUP				);
	DetourDetach(&(PVOID&)	ST_DrawIndexedPrimitiveUP			 ,MT_DrawIndexedPrimitiveUP			);
	DetourDetach(&(PVOID&)	ST_ProcessVertices					 ,MT_ProcessVertices				);
	DetourDetach(&(PVOID&)	ST_CreateVertexDeclaration			 ,MT_CreateVertexDeclaration		);
	DetourDetach(&(PVOID&)	ST_SetVertexDeclaration				 ,MT_SetVertexDeclaration			);
	DetourDetach(&(PVOID&)	ST_GetVertexDeclaration				 ,MT_GetVertexDeclaration			);
	DetourDetach(&(PVOID&)	ST_SetFVF							 ,MT_SetFVF							);
	DetourDetach(&(PVOID&)	ST_GetFVF							 ,MT_GetFVF							);
	DetourDetach(&(PVOID&)	ST_CreateVertexShader				 ,MT_CreateVertexShader				);
	DetourDetach(&(PVOID&)	ST_SetVertexShader					 ,MT_SetVertexShader				);
	DetourDetach(&(PVOID&)	ST_GetVertexShader					 ,MT_GetVertexShader				);
	DetourDetach(&(PVOID&)	ST_SetVertexShaderConstantF			 ,MT_SetVertexShaderConstantF		);
	DetourDetach(&(PVOID&)	ST_GetVertexShaderConstantF			 ,MT_GetVertexShaderConstantF		);
	DetourDetach(&(PVOID&)	ST_SetVertexShaderConstantI			 ,MT_SetVertexShaderConstantI		);
	DetourDetach(&(PVOID&)	ST_GetVertexShaderConstantI			 ,MT_GetVertexShaderConstantI		);
	DetourDetach(&(PVOID&)	ST_SetVertexShaderConstantB			 ,MT_SetVertexShaderConstantB		);
	DetourDetach(&(PVOID&)	ST_GetVertexShaderConstantB			 ,MT_GetVertexShaderConstantB		);
	DetourDetach(&(PVOID&)	ST_SetStreamSource					 ,MT_SetStreamSource				);
	DetourDetach(&(PVOID&)	ST_GetStreamSource					 ,MT_GetStreamSource				);
	DetourDetach(&(PVOID&)	ST_SetStreamSourceFreq				 ,MT_SetStreamSourceFreq			);
	DetourDetach(&(PVOID&)	ST_GetStreamSourceFreq				 ,MT_GetStreamSourceFreq			);
	DetourDetach(&(PVOID&)	ST_SetIndices						 ,MT_SetIndices						);
	DetourDetach(&(PVOID&)	ST_GetIndices						 ,MT_GetIndices						);
	DetourDetach(&(PVOID&)	ST_CreatePixelShader				 ,MT_CreatePixelShader				);
	DetourDetach(&(PVOID&)	ST_SetPixelShader					 ,MT_SetPixelShader					);
	DetourDetach(&(PVOID&)	ST_GetPixelShader					 ,MT_GetPixelShader					);
	DetourDetach(&(PVOID&)	ST_SetPixelShaderConstantF			 ,MT_SetPixelShaderConstantF		);
	DetourDetach(&(PVOID&)	ST_GetPixelShaderConstantF			 ,MT_GetPixelShaderConstantF		);
	DetourDetach(&(PVOID&)	ST_SetPixelShaderConstantI			 ,MT_SetPixelShaderConstantI		);
	DetourDetach(&(PVOID&)	ST_GetPixelShaderConstantI			 ,MT_GetPixelShaderConstantI		);
	DetourDetach(&(PVOID&)	ST_SetPixelShaderConstantB			 ,MT_SetPixelShaderConstantB		);
	DetourDetach(&(PVOID&)	ST_GetPixelShaderConstantB			 ,MT_GetPixelShaderConstantB		);
	DetourDetach(&(PVOID&)	ST_DrawRectPatch					 ,MT_DrawRectPatch					);
	DetourDetach(&(PVOID&)	ST_DrawTriPatch						 ,MT_DrawTriPatch					);
	DetourDetach(&(PVOID&)	ST_DeletePatch						 ,MT_DeletePatch					);
	DetourDetach(&(PVOID&)	ST_CreateQuery						 ,MT_CreateQuery					);

	DetourTransactionCommit();
	bHook_IDirect3DDevice9_Finished	=	false;
#endif
	
}



MT_RenderThread::MT_RenderThread(IDirect3DDevice9*	pDevice){
	m_pDevice	=	pDevice;
	m_State		=	enRTS_Waiting;

	//Reset Main Thread Event
	m_evtMainWaitRender.Reset();
	//Start
	StartThread();
};
MT_RenderThread::~MT_RenderThread(){
	StopThreadWaitForExit();
};
void	MT_RenderThread::Swap(){
	//等待渲染完毕
	m_evtMainWaitRender.Wait();
	//交换
	m_DBuffer.Sync();
	//发送开始渲染信号
	m_evtRenderWaitMain.Reset();
};

#define	READ_COMMAND_STRUCT(CmdStruct)	CmdStruct*	param	=	(CmdStruct*)pBuffer;pBuffer+=sizeof(CmdStruct);

void	MT_RenderThread::RenderFrame(){
		HRESULT		hr	=	S_OK;

		//Before Render,We Check the Device Lost
		hr	=	IDirect3DDevice9_TestCooperativeLevel(m_pDevice);
		//If Device isn't OK! return it.
		if(hr!=D3D_OK)
			return;

		U8*	pBuffer	=	(U8*)m_DBuffer.Read(4);
		

		while(true){
		
		enumCommandFunc	func	=	(enumCommandFunc)(*pBuffer);
		pBuffer+=sizeof(enumCommandFunc);

		switch(func){
			case enCF_UNKNOWN:{
				return;
			}break;
			case enCF_SetCursorProperties:{
				READ_COMMAND_STRUCT(CmdSetCursorProperties);
				hr	=	ST_SetCursorProperties(m_pDevice,param->XHotSpot,param->YHotSpot,param->pCursorBitmap);
										  }break;
			case enCF_SetCursorPosition:{
				READ_COMMAND_STRUCT(CmdSetCursorPosition);
				ST_SetCursorPosition(m_pDevice,param->X,param->Y,param->Flags);
										}break;
			case enCF_ShowCursor:{
				READ_COMMAND_STRUCT(BOOL);
				hr	=	(HRESULT)ST_ShowCursor(m_pDevice,*param);
								 }break;
			case enCF_Present:{
				READ_COMMAND_STRUCT(CmdPresent);
				RECT*		pSourceRect	=	(RECT*)param->pSourceRect;
				RECT*		pDestRect	=	(RECT*)param->pDestRect;
				RGNDATA*	pData		=	(RGNDATA*)param->pDirtyRegion;
				if(pSourceRect!=NULL)
					pSourceRect			=	&param->src;
				if(pDestRect!=NULL)
					pDestRect			=	&param->dst;
				if(pData!=NULL)
					pData				=	&param->dirty;
				hr	=	ST_Present(m_pDevice,pSourceRect,pDestRect,param->hDestWindowOverride,pData);

				switch(hr){
					case D3D_OK:{
								
					}break;
					case D3DERR_DEVICELOST:{
										   
					}break;
					case D3DERR_DRIVERINTERNALERROR:{
													
					}break;
					case D3DERR_DEVICEREMOVED:{
											  
					}break;
				}
				//Render	Complated!
				return;
							  }break;
			case enCF_SetDialogBoxMode:{
				READ_COMMAND_STRUCT(BOOL);
				hr	=	ST_SetDialogBoxMode(m_pDevice,*param);
									   }break;
			case enCF_SetGammaRamp:{
				READ_COMMAND_STRUCT(CmdSetGammaRamp);
				ST_SetGammaRamp(m_pDevice,param->iSwapChain,param->Flags,&param->pRamp);	   
								   }break;
			case enCF_UpdateSurface:{
				READ_COMMAND_STRUCT(CmdUpdateSurface);
				RECT*		pSourceRect	=	(RECT*)param->pSourceRect;
				POINT*		pDestPoint	=	(POINT*)param->pDestPoint;
				if(pSourceRect!=NULL)
					pSourceRect	=	&param->src;
				if(pDestPoint!=NULL)
					pDestPoint	=	&param->dst;

				hr	=	ST_UpdateSurface(m_pDevice,param->pSourceSurface,pSourceRect,param->pDestinationSurface,pDestPoint);	
									}break;
			case enCF_UpdateTexture:{
				READ_COMMAND_STRUCT(CmdUpdateTexture);
				hr	=	ST_UpdateTexture(m_pDevice,param->pSourceTexture,param->pDestinationTexture);	 
									}break;
			case enCF_StretchRect:{
				READ_COMMAND_STRUCT(CmdStretchRect);
				RECT*		pSourceRect	=	(RECT*)param->pSourceRect;
				RECT*		pDestRect	=	(RECT*)param->pDestRect;
				if(pSourceRect!=NULL)
					pSourceRect	=	&param->src;
				if(pDestRect!=NULL)
					pDestRect	=	&param->dst;

				hr	=	ST_StretchRect(m_pDevice,param->pSourceSurface,pSourceRect,param->pDestSurface,pDestRect,param->Filter);						  
								  }break;
			case enCF_ColorFill:{
				READ_COMMAND_STRUCT(CmdColorFill);
				RECT*		pRect	=	(RECT*)param->pRect;
				if(pRect!=NULL)
					pRect	=	&param->src;
				hr	=	ST_ColorFill(m_pDevice,param->pSurface,pRect,param->color);						
								}break;
			case enCF_SetRenderTarget:{
				READ_COMMAND_STRUCT(CmdSetRenderTarget);
				hr	=	ST_SetRenderTarget(m_pDevice,param->RenderTargetIndex,param->pRenderTarget);								  
									  }break;
			case enCF_SetDepthStencilSurface:{
				READ_COMMAND_STRUCT(CmdSetDepthStencilSurface);
				hr	=	ST_SetDepthStencilSurface(m_pDevice,param->pNewZStencil);						 
											 }break;
			case enCF_BeginScene:{
				hr	=	ST_BeginScene(m_pDevice);
								 }break;
			case enCF_EndScene:{
				hr	=	ST_EndScene(m_pDevice);
							   }break;
			case enCF_Clear:{
				READ_COMMAND_STRUCT(CmdClear);
				D3DRECT*	pRects	=	(D3DRECT*)param->pRects;
				DWORD		Count	=	param->Count;
				if(Count>0&&pRects!=NULL){
					pRects	=	(D3DRECT*)pBuffer;
					pBuffer+=sizeof(D3DRECT)*Count;
				}else{
					Count	=	0;
					pRects	=	NULL;
				}
				hr	=	ST_Clear(m_pDevice,Count,pRects,param->Flags,param->Color,param->Z,param->Stencil);	
							}break;
			case enCF_SetTransform:{
				READ_COMMAND_STRUCT(CmdSetTransform);
				hr	=	ST_SetTransform(m_pDevice,param->State,&param->pMatrix);
								   }break;
			case enCF_MultiplyTransform:{}break;
			case enCF_SetViewport:{
				READ_COMMAND_STRUCT(CmdSetViewport);
				hr	=	ST_SetViewport(m_pDevice,param);
								  }break;
			case enCF_SetMaterial:{
				READ_COMMAND_STRUCT(CmdSetMaterial);
				hr	=	ST_SetMaterial(m_pDevice,param);
								  }break;
			case enCF_SetLight:{
				READ_COMMAND_STRUCT(CmdSetLight);
				hr	=	ST_SetLight(m_pDevice,param->Index,&param->Light);
							   }break;
			case enCF_LightEnable:{
				READ_COMMAND_STRUCT(CmdLightEnable);
				hr	=	ST_LightEnable(m_pDevice,param->Index,param->Enable);
								  }break;
			case enCF_SetClipPlane:{
				READ_COMMAND_STRUCT(CmdSetClipPlane);
				hr	=	ST_SetClipPlane(m_pDevice,param->Index,param->pPlane);
								   }break;
			case enCF_SetRenderState:{
				READ_COMMAND_STRUCT(CmdSetRenderState);
				hr	=	ST_SetRenderState(m_pDevice,param->State,param->Value);
									 }break;
			case enCF_BeginStateBlock:{
				hr	=	ST_BeginStateBlock(m_pDevice);	  
									  }break;
			case enCF_EndStateBlock:{
				READ_COMMAND_STRUCT(CmdEndStateBlock);
				hr	=	ST_EndStateBlock(m_pDevice,*param);
									}break;
			case enCF_SetClipStatus:{
				READ_COMMAND_STRUCT(CmdSetClipStatus);
				hr	=	ST_SetClipStatus(m_pDevice,param);
									}break;
			case enCF_SetTexture:{
				READ_COMMAND_STRUCT(CmdSetTexture);
				hr	=	ST_SetTexture(m_pDevice,param->Stage,param->pTexture);
								 }break;
			case enCF_SetTextureStageState:{
				READ_COMMAND_STRUCT(CmdSetTextureStageState);
				hr	=	ST_SetTextureStageState(m_pDevice,param->Stage,param->Type,param->Value);
										   }break;
			case enCF_SetSamplerState:{
				READ_COMMAND_STRUCT(CmdSetSamplerState);
				hr	=	ST_SetSamplerState(m_pDevice,param->Sampler,param->Type,param->Value);
									  }break;
			case enCF_SetPaletteEntries:{
				READ_COMMAND_STRUCT(CmdSetPaletteEntries);
				hr	=	ST_SetPaletteEntries(m_pDevice,param->PaletteNumber,param->pEntries);
										}break;
			case enCF_SetCurrentTexturePalette:{
				READ_COMMAND_STRUCT(CmdSetCurrentTexturePalette);
				hr	=	ST_SetCurrentTexturePalette(m_pDevice,*param);
											   }break;
			case enCF_SetScissorRect:{
				READ_COMMAND_STRUCT(CmdSetScissorRect);
				hr	=	ST_SetScissorRect(m_pDevice,param);
									 }break;
			case enCF_SetSoftwareVertexProcessing:{
				READ_COMMAND_STRUCT(CmdSetSoftwareVertexProcessing);
				hr	=	ST_SetSoftwareVertexProcessing(m_pDevice,*param);
												  }break;
			case enCF_SetNPatchMode:{
				READ_COMMAND_STRUCT(CmdSetNPatchMode);
				hr	=	ST_SetNPatchMode(m_pDevice,*param);
									}break;
			case enCF_DrawPrimitive:{
				READ_COMMAND_STRUCT(CmdDrawPrimitive);
				hr	=	ST_DrawPrimitive(m_pDevice,param->PrimitiveType,param->StartVertex,param->PrimitiveCount);
									}break;
			case enCF_DrawIndexedPrimitive:{
				READ_COMMAND_STRUCT(CmdDrawIndexedPrimitive);
				hr	=	ST_DrawIndexedPrimitive(m_pDevice,param->PrimitiveType,param->BaseVertexIndex,param->MinVertexIndex,param->NumVertices,param->startIndex,param->primCount);
										   }break;
			case enCF_DrawPrimitiveUP:{
									  
									  }break;
			case enCF_DrawIndexedPrimitiveUP:{
											 
											 }break;
			case enCF_ProcessVertices:{
				READ_COMMAND_STRUCT(CmdProcessVertices);
				hr	=	ST_ProcessVertices(m_pDevice,param->SrcStartIndex,param->DestIndex,param->VertexCount,param->pDestBuffer,param->pVertexDecl,param->Flags);
									  }break;
			case enCF_SetVertexDeclaration:{
				READ_COMMAND_STRUCT(CmdSetVertexDeclaration);
				hr	=	ST_SetVertexDeclaration(m_pDevice,*param);
										   }break;
			case enCF_SetFVF:{
				READ_COMMAND_STRUCT(CmdSetFVF);
				hr	=	ST_SetFVF(m_pDevice,*param);
							 }break;
			case enCF_SetVertexShader:{
				READ_COMMAND_STRUCT(CmdSetVertexShader);
				hr	=	ST_SetVertexShader(m_pDevice,*param);
									  }break;
			case enCF_SetVertexShaderConstantF:{
				READ_COMMAND_STRUCT(CmdSetVertexShaderConstantF);
				U32	uiBufferSize		=	param->Vector4fCount*sizeof(float)*4;
				float*	pConstantData	=	(float*)pBuffer;
				pBuffer+=uiBufferSize;
				hr	=	ST_SetVertexShaderConstantF(m_pDevice,param->StartRegister,pConstantData,param->Vector4fCount);
											   }break;
			case enCF_SetVertexShaderConstantI:{
				READ_COMMAND_STRUCT(CmdSetVertexShaderConstantI);
				U32	uiBufferSize		=	param->Vector4iCount*sizeof(int)*4;
				int*	pConstantData	=	(int*)pBuffer;
				pBuffer+=uiBufferSize;
				hr	=	ST_SetVertexShaderConstantI(m_pDevice,param->StartRegister,pConstantData,param->Vector4iCount);
											   }break;
			case enCF_SetVertexShaderConstantB:{
				READ_COMMAND_STRUCT(CmdSetVertexShaderConstantB);
				U32	uiBufferSize		=	param->BoolCount*sizeof(BOOL);
				BOOL*	pConstantData	=	(BOOL*)pBuffer;
				pBuffer+=uiBufferSize;
				hr	=	ST_SetVertexShaderConstantB(m_pDevice,param->StartRegister,pConstantData,param->BoolCount);
											   }break;
			case enCF_SetStreamSource:{
				READ_COMMAND_STRUCT(CmdSetStreamSource);
				hr	=	ST_SetStreamSource(m_pDevice,param->StreamNumber,param->pStreamData,param->OffsetInBytes,param->Stride);
									  }break;
			case enCF_SetStreamSourceFreq:{
				READ_COMMAND_STRUCT(CmdSetStreamSourceFreq);
				hr	=	ST_SetStreamSourceFreq(m_pDevice,param->StreamNumber,param->Setting);
										  }break;
			case enCF_SetIndices:{
				READ_COMMAND_STRUCT(CmdSetIndices);
				hr	=	ST_SetIndices(m_pDevice,*param);
								 }break;
			case enCF_SetPixelShader:{
				READ_COMMAND_STRUCT(CmdSetPixelShader);
				hr	=	ST_SetPixelShader(m_pDevice,*param);
									 }break;
			case enCF_SetPixelShaderConstantF:{
				READ_COMMAND_STRUCT(CmdSetPixelShaderConstantF);
				U32	uiBufferSize		=	param->Vector4fCount*sizeof(float)*4;
				float*	pConstantData	=	(float*)pBuffer;
				pBuffer+=uiBufferSize;
				hr	=	ST_SetPixelShaderConstantF(m_pDevice,param->StartRegister,pConstantData,param->Vector4fCount);
											  }break;
			case enCF_SetPixelShaderConstantI:{
				READ_COMMAND_STRUCT(CmdSetPixelShaderConstantI);
				U32	uiBufferSize		=	param->Vector4iCount*sizeof(int)*4;
				int*	pConstantData	=	(int*)pBuffer;
				pBuffer+=uiBufferSize;
				hr	=	ST_SetPixelShaderConstantI(m_pDevice,param->StartRegister,pConstantData,param->Vector4iCount);
											  }break;
			case enCF_SetPixelShaderConstantB:{
				READ_COMMAND_STRUCT(CmdSetPixelShaderConstantB);
				U32	uiBufferSize		=	param->BoolCount*sizeof(BOOL);
				BOOL*	pConstantData	=	(BOOL*)pBuffer;
				pBuffer+=uiBufferSize;
				hr	=	ST_SetPixelShaderConstantB(m_pDevice,param->StartRegister,pConstantData,param->BoolCount);
											  }break;
			case enCF_DrawRectPatch:{}break;
			case enCF_DrawTriPatch:{}break;
			case enCF_DeletePatch:{}break;
			case enCF_SwapChain_Present:{
				READ_COMMAND_STRUCT(CmdSwapChain_Present);
				RECT*		pSourceRect		=	(RECT*)param->pSourceRect;
				RECT*		pDestRect		=	(RECT*)param->pDestRect;
				RGNDATA*	pDirtyRegion	=	(RGNDATA*)param->pDirtyRegion;
				if(pSourceRect!=NULL){
					pSourceRect	=	&param->src;
				}
				if(pDestRect!=NULL){
					pDestRect	=	&param->dst;
				}
				if(pDirtyRegion!=NULL){
					pDirtyRegion	=	&param->dirty;
				}
				hr	=	ST_SwapChain_Present(param->pSwapChain,pSourceRect,pDestRect,param->hDestWindowOverride,pDirtyRegion,param->dwFlags);
										}break;
			case enCF_Surface_LockRect:{
				READ_COMMAND_STRUCT(CmdSurface_LockRect);
				RECT*	pRect	=	(RECT*)param->pRect;
				if(pRect!=NULL){
					pRect	=	&param->rData;
				}
				D3DLOCKED_RECT	rLock;
				hr	=	ST_Surface_LockRect(param->pSurface,&rLock,pRect,param->Flags);
				if(SUCCEEDED(hr)){
					memcpy(rLock.pBits,pBuffer,param->dwLockSize);
				}
				pBuffer+=param->dwLockSize;
									   }break;
			case enCF_Surface_UnlockRect:{
				READ_COMMAND_STRUCT(CmdSurface_UnlockRect);
				hr	=	ST_Surface_UnlockRect(*param);
										 }break;
			case enCF_Volume_LockBox:{
				READ_COMMAND_STRUCT(CmdVolume_LockBox);
				D3DBOX*	pBox	=	(D3DBOX*)param->pBox;
				if(pBox!=NULL){
					pBox	=	&param->boxData;
				}
				D3DLOCKED_BOX	bLock;
				hr	=	ST_Volume_LockBox(param->pVolume,&bLock,pBox,param->Flags);
				if(SUCCEEDED(hr)){
					memcpy(bLock.pBits,pBuffer,param->dwLockSize);
				}
				pBuffer+=param->dwLockSize;
									 }break;
			case enCF_Volume_UnlockBox:{
				READ_COMMAND_STRUCT(CmdVolume_UnlockBox);
				hr	=	ST_Volume_UnlockBox(*param);
									   }break;
			case enCF_VertexBuffer_Lock:{
				READ_COMMAND_STRUCT(CmdVertexBuffer_Lock);
				void*	pData	=	NULL;
				hr	=	ST_VertexBuffer_Lock(param->pVB,param->OffsetToLock,param->SizeToLock,(void**)&pData,param->Flags);
				if(SUCCEEDED(hr)){
					memcpy(pData,pBuffer,param->SizeToLock);
				}
				pBuffer+=param->SizeToLock;
										}break;
			case enCF_VertexBuffer_Unlock:{
				READ_COMMAND_STRUCT(CmdVertexBuffer_Unlock);
				hr	=	ST_VertexBuffer_Unlock(*param);
										}break;
			case enCF_IndexBuffer_Lock:{
				READ_COMMAND_STRUCT(CmdIndexBuffer_Lock);
				void*	pData	=	NULL;
				hr	=	ST_IndexBuffer_Lock(param->pIB,param->OffsetToLock,param->SizeToLock,(void**)&pData,param->Flags);
				if(SUCCEEDED(hr)){
					memcpy(pData,pBuffer,param->SizeToLock);
				}
				pBuffer+=param->SizeToLock;
									   }break;
			case enCF_IndexBuffer_Unlock:{
				READ_COMMAND_STRUCT(CmdIndexBuffer_Unlock);
				hr	=	ST_IndexBuffer_Unlock(*param);
									   }break;
			case enCF_BaseTexture_SetAutoGenFilterType:{
				READ_COMMAND_STRUCT(CmdBaseTexture_SetAutoGenFilterType);
				hr	=	ST_BaseTexture_SetAutoGenFilterType(param->pTex,param->FilterType);
													   }break;
			case enCF_BaseTexture_GenerateMipSubLevels:{
				READ_COMMAND_STRUCT(CmdBaseTexture_GenerateMipSubLevels);
				ST_BaseTexture_GenerateMipSubLevels(*param);;//->GenerateMipSubLevels();
													   }break;
			case enCF_Texture_LockRect:{
				READ_COMMAND_STRUCT(CmdTexture_LockRect);
				RECT*	pRect	=	(RECT*)param->pRect;
				if(pRect!=NULL){
					pRect	=	&param->rData;
				}
				//D3DLOCKED_RECT	rLock;
				//hr	=	ST_LockRect(param->pTex,param->Level,&rLock,pRect,param->Flags);
				//if(SUCCEEDED(hr)){
				//	memcpy(rLock.pBits,pBuffer,param->dwLockSize);
				//}
				pBuffer+=param->dwLockSize;
									   }break;
			case enCF_Texture_UnlockRect:{
				READ_COMMAND_STRUCT(CmdTexture_UnlockRect);
				//hr	=	IDirect3DTexture9_UnlockRect(param->pTex,param->Level);
										 }break;
			case enCF_Texture_AddDirtyRect:{
				READ_COMMAND_STRUCT(CmdTexture_AddDirtyRect);
				//hr	=	IDirect3DTexture9_AddDirtyRect(param->pTex,&param->pDirtyRect);
										   }break;
			case enCF_CubeTexture_LockRect:{
				READ_COMMAND_STRUCT(CmdCubeTexture_LockRect);
				RECT*	pRect	=	(RECT*)param->pRect;
				if(pRect!=NULL){
					pRect	=	&param->rData;
				}
				//D3DLOCKED_RECT	rLock;
				//hr	=	IDirect3DCubeTexture9_LockRect(param->pCubeTex,param->FaceType,param->Level,&rLock,pRect,param->Flags);
				//if(SUCCEEDED(hr)){
				//	memcpy(rLock.pBits,pBuffer,param->dwLockSize);
				//}
				pBuffer+=param->dwLockSize;
										   }break;
			case enCF_CubeTexture_UnlockRect:{
				READ_COMMAND_STRUCT(CmdCubeTexture_UnlockRect);
				//hr	=	IDirect3DCubeTexture9_UnlockRect(param->pCubeTex,param->FaceType,param->Level);
											 }break;
			case enCF_CubeTexture_AddDirtyRect:{
				READ_COMMAND_STRUCT(CmdCubeTexture_AddDirtyRect);
				//hr	=	IDirect3DCubeTexture9_AddDirtyRect(param->pCubeTex,param->FaceType,&param->pDirtyRect);
											   }break;
			case enCF_VolumeTexture_LockBox:{
				READ_COMMAND_STRUCT(CmdVolumeTexture_LockBox);
				D3DBOX*	pBox	=	(D3DBOX*)param->pBox;
				if(pBox!=NULL){
					pBox	=	&param->boxData;
				}
				//D3DLOCKED_BOX	rLock;
				//hr	=	IDirect3DVolumeTexture9_LockBox(param->pVolumeTex,param->Level,&rLock,pBox,param->Flags);
				//if(SUCCEEDED(hr)){
				//	memcpy(rLock.pBits,pBuffer,param->dwLockSize);
				//}
				pBuffer+=param->dwLockSize;
											}break;
			case enCF_VolumeTexture_UnlockBox:{
				READ_COMMAND_STRUCT(CmdVolumeTexture_UnlockBox);
				//hr	=	IDirect3DVolumeTexture9_UnlockBox(param->pVolumeTex,param->Level);
											  }break;
			case enCF_VolumeTexture_AddDirtyBox:{
				READ_COMMAND_STRUCT(CmdVolumeTexture_AddDirtyBox);
				//hr	=	IDirect3DVolumeTexture9_AddDirtyBox(param->pVolumeTex,&param->pDirtyBox);
												}break;
			case enCF_StateBlock_Apply:{
				READ_COMMAND_STRUCT(CmdStateBlock_Apply);
				hr	=	IDirect3DStateBlock9_Apply(*param);//->Apply();
									   }break;
			case enCF_StateBlock_Capture:{
				READ_COMMAND_STRUCT(CmdStateBlock_Capture);
				hr	=	IDirect3DStateBlock9_Capture(*param);//->Capture();
										 }break;
			case enCF_PIX_D3DPERF_BeginEvent:{
				READ_COMMAND_STRUCT(CmdPIX_D3DPERF_BeginEvent);
				wchar_t*	pStr	=	(wchar_t*)pBuffer;
				pBuffer+=param->dwNameSize;
				hr	=	S_OK;//D3DPERF_BeginEvent(param->col,pStr);
											 }break;
			case enCF_PIX_D3DPERF_EndEvent:{
				hr	=	S_OK;//hr	=	D3DPERF_EndEvent();
										   }break;
			case enCF_PIX_D3DPERF_SetMarker:{
				READ_COMMAND_STRUCT(CmdPIX_D3DPERF_SetMarker);
				wchar_t*	pStr	=	(wchar_t*)pBuffer;
				pBuffer+=param->dwNameSize;
				hr	=	S_OK;//D3DPERF_SetMarker(param->col,pStr);
											}break;
			case enCF_Effect_SetValue:{//(THIS_ D3DXHANDLE hParameter, LPCVOID pData, UINT Bytes);
				READ_COMMAND_STRUCT(CmdEffect_SetValue);
				hr	=	param->pID3DXEffect->lpVtbl->SetValue(param->pID3DXEffect,param->hParameter,pBuffer,param->Bytes);
				pBuffer+=param->Bytes;
				}break;
			case enCF_Effect_SetBool:{//(THIS_ D3DXHANDLE hParameter, BOOL b);
				READ_COMMAND_STRUCT(CmdEffect_SetBool);
				hr	=	param->pID3DXEffect->lpVtbl->SetBool(param->pID3DXEffect,param->hParameter,param->b);
				}break;
			case enCF_Effect_SetBoolArray:{//(THIS_ D3DXHANDLE hParameter, CONST BOOL* pb, UINT Count);
				READ_COMMAND_STRUCT(CmdEffect_SetBoolArray);
				hr	=	param->pID3DXEffect->lpVtbl->SetBoolArray(param->pID3DXEffect,param->hParameter,(CONST BOOL*)pBuffer,param->Count);
				pBuffer+=param->Count*sizeof(BOOL);
				}break;
			case enCF_Effect_SetInt:{//(THIS_ D3DXHANDLE hParameter, INT n);
				READ_COMMAND_STRUCT(CmdEffect_SetInt);
				hr	=	param->pID3DXEffect->lpVtbl->SetInt(param->pID3DXEffect,param->hParameter,param->n);
				}break;
			case enCF_Effect_SetIntArray:{//(THIS_ D3DXHANDLE hParameter, CONST INT* pn, UINT Count);
				READ_COMMAND_STRUCT(CmdEffect_SetIntArray);
				hr	=	param->pID3DXEffect->lpVtbl->SetIntArray(param->pID3DXEffect,param->hParameter,(CONST INT*)pBuffer,param->Count);
				pBuffer+=param->Count*sizeof(INT);
				}break;
			case enCF_Effect_SetFloat:{//(THIS_ D3DXHANDLE hParameter, FLOAT f);
				READ_COMMAND_STRUCT(CmdEffect_SetFloat);
				hr	=	param->pID3DXEffect->lpVtbl->SetFloat(param->pID3DXEffect,param->hParameter,param->f);
				}break;
			case enCF_Effect_SetFloatArray:{//(THIS_ D3DXHANDLE hParameter, CONST FLOAT* pf, UINT Count);
				READ_COMMAND_STRUCT(CmdEffect_SetFloatArray);
				hr	=	param->pID3DXEffect->lpVtbl->SetFloatArray(param->pID3DXEffect,param->hParameter,(CONST FLOAT*)pBuffer,param->Count);
				pBuffer+=param->Count*sizeof(float);
				}break;
			case enCF_Effect_SetVector:{//(THIS_ D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector);
				READ_COMMAND_STRUCT(CmdEffect_SetVector);
				hr	=	param->pID3DXEffect->lpVtbl->SetVector(param->pID3DXEffect,param->hParameter,&param->pVector);
				}break;
			case enCF_Effect_SetVectorArray:{//(THIS_ D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector, UINT Count);
				READ_COMMAND_STRUCT(CmdEffect_SetVectorArray);
				hr	=	param->pID3DXEffect->lpVtbl->SetVectorArray(param->pID3DXEffect,param->hParameter,(CONST D3DXVECTOR4*)pBuffer,param->Count);
				pBuffer+=param->Count*sizeof(D3DXVECTOR4);
				}break;
			case enCF_Effect_SetMatrix:{//(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix);
				READ_COMMAND_STRUCT(CmdEffect_SetMatrix);
				hr	=	param->pID3DXEffect->lpVtbl->SetMatrix(param->pID3DXEffect,param->hParameter,&param->pMatrix);

				}break;
			case enCF_Effect_SetMatrixArray:{//(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count);
				READ_COMMAND_STRUCT(CmdEffect_SetMatrixArray);
				hr	=	param->pID3DXEffect->lpVtbl->SetMatrixArray(param->pID3DXEffect,param->hParameter,(CONST D3DXMATRIX*)pBuffer,param->Count);
				pBuffer+=param->Count*sizeof(D3DXMATRIX);
				}break;
			case enCF_Effect_SetMatrixPointerArray:{//(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count);

				}break;
			case enCF_Effect_SetMatrixTranspose:{//(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix);
				READ_COMMAND_STRUCT(CmdEffect_SetMatrixTranspose);
				hr	=	param->pID3DXEffect->lpVtbl->SetMatrixTranspose(param->pID3DXEffect,param->hParameter,&param->pMatrix);
				}break;
			case enCF_Effect_SetMatrixTransposeArray:{//(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count);
				READ_COMMAND_STRUCT(CmdEffect_SetMatrixTransposeArray);
				hr	=	param->pID3DXEffect->lpVtbl->SetMatrixTransposeArray(param->pID3DXEffect,param->hParameter,(CONST D3DXMATRIX*)pBuffer,param->Count);
				pBuffer+=param->Count*sizeof(D3DXMATRIX);
				}break;
			case enCF_Effect_SetMatrixTransposePointerArray:{//(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count);

				}break;
			case enCF_Effect_SetString:{//(THIS_ D3DXHANDLE hParameter, LPCSTR pString);
				READ_COMMAND_STRUCT(CmdEffect_SetString);
				hr	=	param->pID3DXEffect->lpVtbl->SetString(param->pID3DXEffect,param->hParameter,(LPCSTR)pBuffer);
				pBuffer+=param->uiBufferSize;
				}break;
			case enCF_Effect_SetTexture:{//(THIS_ D3DXHANDLE hParameter, LPDIRECT3DBASETEXTURE9 pTexture);
				READ_COMMAND_STRUCT(CmdEffect_SetTexture);
				hr	=	param->pID3DXEffect->lpVtbl->SetTexture(param->pID3DXEffect,param->hParameter,param->pTexture);
				}break;
			case enCF_Effect_SetTechnique:{//(THIS_ D3DXHANDLE hTechnique);
				READ_COMMAND_STRUCT(CmdEffect_SetTechnique);
				hr	=	param->pID3DXEffect->lpVtbl->SetTechnique(param->pID3DXEffect,param->hTechnique);
				}break;
			case enCF_Effect_Begin:{//(THIS_ UINT *pPasses, DWORD Flags) ;
				UINT uiPassCount	=	0;
				READ_COMMAND_STRUCT(CmdEffect_Begin);
				hr	=	param->pID3DXEffect->lpVtbl->Begin(param->pID3DXEffect,&uiPassCount,param->Flags);

				}break;
			case enCF_Effect_BeginPass:{//(THIS_ UINT Pass) ;
				READ_COMMAND_STRUCT(CmdEffect_BeginPass);
				hr	=	param->pID3DXEffect->lpVtbl->BeginPass(param->pID3DXEffect,param->Pass);

				}break;
			case enCF_Effect_CommitChanges:{//(THIS) ;
				READ_COMMAND_STRUCT(CmdEffect_CommitChanges);
				hr	=	(*param)->lpVtbl->CommitChanges(*param);

				}break;
			case enCF_Effect_EndPass:{//(THIS) ;
				READ_COMMAND_STRUCT(CmdEffect_EndPass);
				hr	=	(*param)->lpVtbl->EndPass(*param);
				}break;
			case enCF_Effect_End:{//(THIS) ;
				READ_COMMAND_STRUCT(CmdEffect_End);
				hr	=	(*param)->lpVtbl->End(*param);
				}break;
			case enCF_Effect_SetStateManager:{//(THIS_ LPD3DXEFFECTSTATEMANAGER pManager);
				READ_COMMAND_STRUCT(CmdEffect_SetStateManager);
				hr	=	param->pID3DXEffect->lpVtbl->SetStateManager(param->pID3DXEffect,param->pManager);

				}break;
			case enCF_Effect_SetRawValue:{//(THIS_ D3DXHANDLE hParameter, LPCVOID pData, UINT ByteOffset, UINT Bytes);
				READ_COMMAND_STRUCT(CmdEffect_SetRawValue);
				hr	=	param->pID3DXEffect->lpVtbl->SetRawValue(param->pID3DXEffect,param->hParameter,pBuffer,param->ByteOffset,param->Bytes);
				pBuffer+=param->Bytes;
				}break;
		}
	}
};

bool	MT_RenderThread::RepetitionRun(){
	//如果 主线程调用StopThread  则需要不再执行内部逻辑 也不进入等待
	if(!m_bExit){
		m_State	=	enRTS_Waiting;
		//等待主线程
		m_evtRenderWaitMain.Wait();

		if(m_bExit)
			return	true;

		m_State	=	enRTS_Rendering;
		//渲染
		RenderFrame();

		m_State	=	enRTS_RenderComplated;
		//发送渲染完毕信号
		m_evtMainWaitRender.Reset();

		m_State	=	enRTS_EventResetComplated;
	}
	return	true;
};

void	MT_RenderThread::WaitRenderComplated(){
	//等待渲染完毕
	m_evtMainWaitRender.Wait();
}

bool MT_RenderThread::StopThread(){
	//直到渲染线程状态为 等待
	while(m_State!=enRTS_Waiting);

	__super::StopThread();

	m_evtRenderWaitMain.Reset();

	return	true;
}