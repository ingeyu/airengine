#include "MTRenderThread.h"


MT_RenderThread::MT_RenderThread(IDirect3DDevice9*	pDevice){
	m_pDevice	=	pDevice;
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
		hr	=	m_pDevice->TestCooperativeLevel();
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
				hr	=	m_pDevice->SetCursorProperties(param->XHotSpot,param->YHotSpot,param->pCursorBitmap);
										  }break;
			case enCF_SetCursorPosition:{
				READ_COMMAND_STRUCT(CmdSetCursorPosition);
				m_pDevice->SetCursorPosition(param->X,param->Y,param->Flags);
										}break;
			case enCF_ShowCursor:{
				READ_COMMAND_STRUCT(BOOL);
				hr	=	(HRESULT)m_pDevice->ShowCursor(*param);
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
				hr	=	m_pDevice->Present(pSourceRect,pDestRect,param->hDestWindowOverride,pData);
							  }break;
			case enCF_SetDialogBoxMode:{
				READ_COMMAND_STRUCT(BOOL);
				hr	=	m_pDevice->SetDialogBoxMode(*param);
									   }break;
			case enCF_SetGammaRamp:{
				READ_COMMAND_STRUCT(CmdSetGammaRamp);
				m_pDevice->SetGammaRamp(param->iSwapChain,param->Flags,&param->pRamp);	   
								   }break;
			case enCF_UpdateSurface:{
				READ_COMMAND_STRUCT(CmdUpdateSurface);
				RECT*		pSourceRect	=	(RECT*)param->pSourceRect;
				POINT*		pDestPoint	=	(POINT*)param->pDestPoint;
				if(pSourceRect!=NULL)
					pSourceRect	=	&param->src;
				if(pDestPoint!=NULL)
					pDestPoint	=	&param->dst;

				hr	=	m_pDevice->UpdateSurface(param->pSourceSurface,pSourceRect,param->pDestinationSurface,pDestPoint);	
									}break;
			case enCF_UpdateTexture:{
				READ_COMMAND_STRUCT(CmdUpdateTexture);
				hr	=	m_pDevice->UpdateTexture(param->pSourceTexture,param->pDestinationTexture);	 
									}break;
			case enCF_StretchRect:{
				READ_COMMAND_STRUCT(CmdStretchRect);
				RECT*		pSourceRect	=	(RECT*)param->pSourceRect;
				RECT*		pDestRect	=	(RECT*)param->pDestRect;
				if(pSourceRect!=NULL)
					pSourceRect	=	&param->src;
				if(pDestRect!=NULL)
					pDestRect	=	&param->dst;

				hr	=	m_pDevice->StretchRect(param->pSourceSurface,pSourceRect,param->pDestSurface,pDestRect,param->Filter);						  
								  }break;
			case enCF_ColorFill:{
				READ_COMMAND_STRUCT(CmdColorFill);
				RECT*		pRect	=	(RECT*)param->pRect;
				if(pRect!=NULL)
					pRect	=	&param->src;
				hr	=	m_pDevice->ColorFill(param->pSurface,pRect,param->color);						
								}break;
			case enCF_SetRenderTarget:{
				READ_COMMAND_STRUCT(CmdSetRenderTarget);
				hr	=	m_pDevice->SetRenderTarget(param->RenderTargetIndex,param->pRenderTarget);								  
									  }break;
			case enCF_SetDepthStencilSurface:{
				READ_COMMAND_STRUCT(CmdSetDepthStencilSurface);
				hr	=	m_pDevice->SetDepthStencilSurface(param->pNewZStencil);						 
											 }break;
			case enCF_BeginScene:{
				hr	=	m_pDevice->BeginScene();
								 }break;
			case enCF_EndScene:{
				hr	=	m_pDevice->EndScene();
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
				hr	=	m_pDevice->Clear(Count,pRects,param->Flags,param->Color,param->Z,param->Stencil);	
							}break;
			case enCF_SetTransform:{
				READ_COMMAND_STRUCT(CmdSetTransform);
				hr	=	m_pDevice->SetTransform(param->State,&param->pMatrix);
								   }break;
			case enCF_MultiplyTransform:{}break;
			case enCF_SetViewport:{
				READ_COMMAND_STRUCT(CmdSetViewport);
				hr	=	m_pDevice->SetViewport(param);
								  }break;
			case enCF_SetMaterial:{
				READ_COMMAND_STRUCT(CmdSetMaterial);
				hr	=	m_pDevice->SetMaterial(param);
								  }break;
			case enCF_SetLight:{
				READ_COMMAND_STRUCT(CmdSetLight);
				hr	=	m_pDevice->SetLight(param->Index,&param->Light);
							   }break;
			case enCF_LightEnable:{
				READ_COMMAND_STRUCT(CmdLightEnable);
				hr	=	m_pDevice->LightEnable(param->Index,param->Enable);
								  }break;
			case enCF_SetClipPlane:{
				READ_COMMAND_STRUCT(CmdSetClipPlane);
				hr	=	m_pDevice->SetClipPlane(param->Index,param->pPlane);
								   }break;
			case enCF_SetRenderState:{
				READ_COMMAND_STRUCT(CmdSetRenderState);
				hr	=	m_pDevice->SetRenderState(param->State,param->Value);
									 }break;
			case enCF_BeginStateBlock:{
				hr	=	m_pDevice->BeginStateBlock();	  
									  }break;
			case enCF_EndStateBlock:{
				READ_COMMAND_STRUCT(CmdEndStateBlock);
				hr	=	m_pDevice->EndStateBlock(*param);
									}break;
			case enCF_SetClipStatus:{
				READ_COMMAND_STRUCT(CmdSetClipStatus);
				hr	=	m_pDevice->SetClipStatus(param);
									}break;
			case enCF_SetTexture:{
				READ_COMMAND_STRUCT(CmdSetTexture);
				hr	=	m_pDevice->SetTexture(param->Stage,param->pTexture);
								 }break;
			case enCF_SetTextureStageState:{
				READ_COMMAND_STRUCT(CmdSetTextureStageState);
				hr	=	m_pDevice->SetTextureStageState(param->Stage,param->Type,param->Value);
										   }break;
			case enCF_SetSamplerState:{
				READ_COMMAND_STRUCT(CmdSetSamplerState);
				hr	=	m_pDevice->SetSamplerState(param->Sampler,param->Type,param->Value);
									  }break;
			case enCF_SetPaletteEntries:{
				READ_COMMAND_STRUCT(CmdSetPaletteEntries);
				hr	=	m_pDevice->SetPaletteEntries(param->PaletteNumber,param->pEntries);
										}break;
			case enCF_SetCurrentTexturePalette:{
				READ_COMMAND_STRUCT(CmdSetCurrentTexturePalette);
				hr	=	m_pDevice->SetCurrentTexturePalette(*param);
											   }break;
			case enCF_SetScissorRect:{
				READ_COMMAND_STRUCT(CmdSetScissorRect);
				hr	=	m_pDevice->SetScissorRect(param);
									 }break;
			case enCF_SetSoftwareVertexProcessing:{
				READ_COMMAND_STRUCT(CmdSetSoftwareVertexProcessing);
				hr	=	m_pDevice->SetSoftwareVertexProcessing(*param);
												  }break;
			case enCF_SetNPatchMode:{
				READ_COMMAND_STRUCT(CmdSetNPatchMode);
				hr	=	m_pDevice->SetNPatchMode(*param);
									}break;
			case enCF_DrawPrimitive:{
				READ_COMMAND_STRUCT(CmdDrawPrimitive);
				hr	=	m_pDevice->DrawPrimitive(param->PrimitiveType,param->StartVertex,param->PrimitiveCount);
									}break;
			case enCF_DrawIndexedPrimitive:{
				READ_COMMAND_STRUCT(CmdDrawIndexedPrimitive);
				hr	=	m_pDevice->DrawIndexedPrimitive(param->PrimitiveType,param->BaseVertexIndex,param->MinVertexIndex,param->NumVertices,param->startIndex,param->primCount);
										   }break;
			case enCF_DrawPrimitiveUP:{
									  
									  }break;
			case enCF_DrawIndexedPrimitiveUP:{
											 
											 }break;
			case enCF_ProcessVertices:{
				READ_COMMAND_STRUCT(CmdProcessVertices);
				hr	=	m_pDevice->ProcessVertices(param->SrcStartIndex,param->DestIndex,param->VertexCount,param->pDestBuffer,param->pVertexDecl,param->Flags);
									  }break;
			case enCF_SetVertexDeclaration:{
				READ_COMMAND_STRUCT(CmdSetVertexDeclaration);
				hr	=	m_pDevice->SetVertexDeclaration(*param);
										   }break;
			case enCF_SetFVF:{
				READ_COMMAND_STRUCT(CmdSetFVF);
				hr	=	m_pDevice->SetFVF(*param);
							 }break;
			case enCF_SetVertexShader:{
				READ_COMMAND_STRUCT(CmdSetVertexShader);
				hr	=	m_pDevice->SetVertexShader(*param);
									  }break;
			case enCF_SetVertexShaderConstantF:{
				READ_COMMAND_STRUCT(CmdSetVertexShaderConstantF);
				U32	uiBufferSize		=	param->Vector4fCount*sizeof(float)*4;
				float*	pConstantData	=	(float*)pBuffer;
				pBuffer+=uiBufferSize;
				hr	=	m_pDevice->SetVertexShaderConstantF(param->StartRegister,pConstantData,param->Vector4fCount);
											   }break;
			case enCF_SetVertexShaderConstantI:{
				READ_COMMAND_STRUCT(CmdSetVertexShaderConstantI);
				U32	uiBufferSize		=	param->Vector4iCount*sizeof(int)*4;
				int*	pConstantData	=	(int*)pBuffer;
				pBuffer+=uiBufferSize;
				hr	=	m_pDevice->SetVertexShaderConstantI(param->StartRegister,pConstantData,param->Vector4iCount);
											   }break;
			case enCF_SetVertexShaderConstantB:{
				READ_COMMAND_STRUCT(CmdSetVertexShaderConstantB);
				U32	uiBufferSize		=	param->BoolCount*sizeof(BOOL);
				BOOL*	pConstantData	=	(BOOL*)pBuffer;
				pBuffer+=uiBufferSize;
				hr	=	m_pDevice->SetVertexShaderConstantB(param->StartRegister,pConstantData,param->BoolCount);
											   }break;
			case enCF_SetStreamSource:{
				READ_COMMAND_STRUCT(CmdSetStreamSource);
				hr	=	m_pDevice->SetStreamSource(param->StreamNumber,param->pStreamData,param->OffsetInBytes,param->Stride);
									  }break;
			case enCF_SetStreamSourceFreq:{
				READ_COMMAND_STRUCT(CmdSetStreamSourceFreq);
				hr	=	m_pDevice->SetStreamSourceFreq(param->StreamNumber,param->Setting);
										  }break;
			case enCF_SetIndices:{
				READ_COMMAND_STRUCT(CmdSetIndices);
				hr	=	m_pDevice->SetIndices(*param);
								 }break;
			case enCF_SetPixelShader:{
				READ_COMMAND_STRUCT(CmdSetPixelShader);
				hr	=	m_pDevice->SetPixelShader(*param);
									 }break;
			case enCF_SetPixelShaderConstantF:{
				READ_COMMAND_STRUCT(CmdSetPixelShaderConstantF);
				U32	uiBufferSize		=	param->Vector4fCount*sizeof(float)*4;
				float*	pConstantData	=	(float*)pBuffer;
				pBuffer+=uiBufferSize;
				hr	=	m_pDevice->SetPixelShaderConstantF(param->StartRegister,pConstantData,param->Vector4fCount);
											  }break;
			case enCF_SetPixelShaderConstantI:{
				READ_COMMAND_STRUCT(CmdSetPixelShaderConstantI);
				U32	uiBufferSize		=	param->Vector4iCount*sizeof(int)*4;
				int*	pConstantData	=	(int*)pBuffer;
				pBuffer+=uiBufferSize;
				hr	=	m_pDevice->SetPixelShaderConstantI(param->StartRegister,pConstantData,param->Vector4iCount);
											  }break;
			case enCF_SetPixelShaderConstantB:{
				READ_COMMAND_STRUCT(CmdSetPixelShaderConstantB);
				U32	uiBufferSize		=	param->BoolCount*sizeof(BOOL);
				BOOL*	pConstantData	=	(BOOL*)pBuffer;
				pBuffer+=uiBufferSize;
				hr	=	m_pDevice->SetPixelShaderConstantB(param->StartRegister,pConstantData,param->BoolCount);
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
				hr	=	param->pSwapChain->Present(pSourceRect,pDestRect,param->hDestWindowOverride,pDirtyRegion,param->dwFlags);
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
			case enCF_Surface_LockRect:{
				READ_COMMAND_STRUCT(CmdSurface_LockRect);
				RECT*	pRect	=	(RECT*)param->pRect;
				if(pRect!=NULL){
					pRect	=	&param->rData;
				}
				D3DLOCKED_RECT	rLock;
				hr	=	param->pSurface->LockRect(&rLock,pRect,param->Flags);
				if(SUCCEEDED(hr)){
					memcpy(rLock.pBits,pBuffer,param->dwLockSize);
				}
				pBuffer+=param->dwLockSize;
									   }break;
			case enCF_Surface_UnlockRect:{
				READ_COMMAND_STRUCT(CmdSurface_UnlockRect);
				hr	=	(*param)->UnlockRect();
										 }break;
			case enCF_Volume_LockBox:{
				READ_COMMAND_STRUCT(CmdVolume_LockBox);
				D3DBOX*	pBox	=	(D3DBOX*)param->pBox;
				if(pBox!=NULL){
					pBox	=	&param->boxData;
				}
				D3DLOCKED_BOX	bLock;
				hr	=	param->pVolume->LockBox(&bLock,pBox,param->Flags);
				if(SUCCEEDED(hr)){
					memcpy(bLock.pBits,pBuffer,param->dwLockSize);
				}
				pBuffer+=param->dwLockSize;
									 }break;
			case enCF_Volume_UnlockBox:{
				READ_COMMAND_STRUCT(CmdVolume_UnlockBox);
				hr	=	(*param)->UnlockBox();
									   }break;
			case enCF_VertexBuffer_Lock:{
				READ_COMMAND_STRUCT(CmdVertexBuffer_Lock);
				void*	pData	=	NULL;
				hr	=	param->pVB->Lock(param->OffsetToLock,param->SizeToLock,(void**)&pData,param->Flags);
				if(SUCCEEDED(hr)){
					memcpy(pData,pBuffer,param->SizeToLock);
				}
				pBuffer+=param->SizeToLock;
										}break;
			case enCF_VertexBuffer_Unlock:{
				READ_COMMAND_STRUCT(CmdVertexBuffer_Unlock);
				hr	=	(*param)->Unlock();
										}break;
			case enCF_IndexBuffer_Lock:{
				READ_COMMAND_STRUCT(CmdIndexBuffer_Lock);
				void*	pData	=	NULL;
				hr	=	param->pIB->Lock(param->OffsetToLock,param->SizeToLock,(void**)&pData,param->Flags);
				if(SUCCEEDED(hr)){
					memcpy(pData,pBuffer,param->SizeToLock);
				}
				pBuffer+=param->SizeToLock;
									   }break;
			case enCF_IndexBuffer_Unlock:{
				READ_COMMAND_STRUCT(CmdIndexBuffer_Unlock);
				hr	=	(*param)->Unlock();
									   }break;
			case enCF_BaseTexture_SetAutoGenFilterType:{
				READ_COMMAND_STRUCT(CmdBaseTexture_SetAutoGenFilterType);
				hr	=	param->pTex->SetAutoGenFilterType(param->FilterType);
													   }break;
			case enCF_BaseTexture_GenerateMipSubLevels:{
				READ_COMMAND_STRUCT(CmdBaseTexture_GenerateMipSubLevels);
				(*param)->GenerateMipSubLevels();
													   }break;
			case enCF_Texture_LockRect:{
				READ_COMMAND_STRUCT(CmdTexture_LockRect);
				RECT*	pRect	=	(RECT*)param->pRect;
				if(pRect!=NULL){
					pRect	=	&param->rData;
				}
				D3DLOCKED_RECT	rLock;
				hr	=	param->pTex->LockRect(param->Level,&rLock,pRect,param->Flags);
				if(SUCCEEDED(hr)){
					memcpy(rLock.pBits,pBuffer,param->dwLockSize);
				}
				pBuffer+=param->dwLockSize;
									   }break;
			case enCF_Texture_UnlockRect:{
				READ_COMMAND_STRUCT(CmdTexture_UnlockRect);
				hr	=	param->pTex->UnlockRect(param->Level);
										 }break;
			case enCF_Texture_AddDirtyRect:{
				READ_COMMAND_STRUCT(CmdTexture_AddDirtyRect);
				hr	=	param->pTex->AddDirtyRect(&param->pDirtyRect);
										   }break;
			case enCF_CubeTexture_LockRect:{
				READ_COMMAND_STRUCT(CmdCubeTexture_LockRect);
				RECT*	pRect	=	(RECT*)param->pRect;
				if(pRect!=NULL){
					pRect	=	&param->rData;
				}
				D3DLOCKED_RECT	rLock;
				hr	=	param->pCubeTex->LockRect(param->FaceType,param->Level,&rLock,pRect,param->Flags);
				if(SUCCEEDED(hr)){
					memcpy(rLock.pBits,pBuffer,param->dwLockSize);
				}
				pBuffer+=param->dwLockSize;
										   }break;
			case enCF_CubeTexture_UnlockRect:{
				READ_COMMAND_STRUCT(CmdCubeTexture_UnlockRect);
				hr	=	param->pCubeTex->UnlockRect(param->FaceType,param->Level);
											 }break;
			case enCF_CubeTexture_AddDirtyRect:{
				READ_COMMAND_STRUCT(CmdCubeTexture_AddDirtyRect);
				hr	=	param->pCubeTex->AddDirtyRect(param->FaceType,&param->pDirtyRect);
											   }break;
			case enCF_VolumeTexture_LockBox:{
				READ_COMMAND_STRUCT(CmdVolumeTexture_LockBox);
				D3DBOX*	pBox	=	(D3DBOX*)param->pBox;
				if(pBox!=NULL){
					pBox	=	&param->boxData;
				}
				D3DLOCKED_BOX	rLock;
				hr	=	param->pVolumeTex->LockBox(param->Level,&rLock,pBox,param->Flags);
				if(SUCCEEDED(hr)){
					memcpy(rLock.pBits,pBuffer,param->dwLockSize);
				}
				pBuffer+=param->dwLockSize;
											}break;
			case enCF_VolumeTexture_UnlockBox:{
				READ_COMMAND_STRUCT(CmdVolumeTexture_UnlockBox);
				hr	=	param->pVolumeTex->UnlockBox(param->Level);
											  }break;
			case enCF_VolumeTexture_AddDirtyBox:{
				READ_COMMAND_STRUCT(CmdVolumeTexture_AddDirtyBox);
				hr	=	param->pVolumeTex->AddDirtyBox(&param->pDirtyBox);
												}break;
			case enCF_StateBlock_Apply:{
				READ_COMMAND_STRUCT(CmdStateBlock_Apply);
				hr	=	(*param)->Apply();
									   }break;
			case enCF_StateBlock_Capture:{
				READ_COMMAND_STRUCT(CmdStateBlock_Capture);
				hr	=	(*param)->Capture();
										 }break;
			case enCF_PIX_D3DPERF_BeginEvent:{
				READ_COMMAND_STRUCT(CmdPIX_D3DPERF_BeginEvent);
				wchar_t*	pStr	=	(wchar_t*)pBuffer;
				pBuffer+=param->dwNameSize;
				hr	=	D3DPERF_BeginEvent(param->col,pStr);
											 }break;
			case enCF_PIX_D3DPERF_EndEvent:{
				hr	=	D3DPERF_EndEvent();
										   }break;
			case enCF_PIX_D3DPERF_SetMarker:{
				READ_COMMAND_STRUCT(CmdPIX_D3DPERF_SetMarker);
				wchar_t*	pStr	=	(wchar_t*)pBuffer;
				pBuffer+=param->dwNameSize;
				D3DPERF_SetMarker(param->col,pStr);
											}break;
			case enCF_Effect_SetValue:{//(THIS_ D3DXHANDLE hParameter, LPCVOID pData, UINT Bytes);
				READ_COMMAND_STRUCT(CmdEffect_SetValue);
				hr	=	param->pID3DXEffect->SetValue(param->hParameter,pBuffer,param->Bytes);
				pBuffer+=param->Bytes;
				}break;
			case enCF_Effect_SetBool:{//(THIS_ D3DXHANDLE hParameter, BOOL b);
				READ_COMMAND_STRUCT(CmdEffect_SetBool);
				hr	=	param->pID3DXEffect->SetBool(param->hParameter,param->b);
				}break;
			case enCF_Effect_SetBoolArray:{//(THIS_ D3DXHANDLE hParameter, CONST BOOL* pb, UINT Count);
				READ_COMMAND_STRUCT(CmdEffect_SetBoolArray);
				hr	=	param->pID3DXEffect->SetBoolArray(param->hParameter,(CONST BOOL*)pBuffer,param->Count);
				pBuffer+=param->Count*sizeof(BOOL);
				}break;
			case enCF_Effect_SetInt:{//(THIS_ D3DXHANDLE hParameter, INT n);
				READ_COMMAND_STRUCT(CmdEffect_SetInt);
				hr	=	param->pID3DXEffect->SetInt(param->hParameter,param->n);
				}break;
			case enCF_Effect_SetIntArray:{//(THIS_ D3DXHANDLE hParameter, CONST INT* pn, UINT Count);
				READ_COMMAND_STRUCT(CmdEffect_SetIntArray);
				hr	=	param->pID3DXEffect->SetIntArray(param->hParameter,(CONST INT*)pBuffer,param->Count);
				pBuffer+=param->Count*sizeof(INT);
				}break;
			case enCF_Effect_SetFloat:{//(THIS_ D3DXHANDLE hParameter, FLOAT f);
				READ_COMMAND_STRUCT(CmdEffect_SetFloat);
				hr	=	param->pID3DXEffect->SetFloat(param->hParameter,param->f);
				}break;
			case enCF_Effect_SetFloatArray:{//(THIS_ D3DXHANDLE hParameter, CONST FLOAT* pf, UINT Count);
				READ_COMMAND_STRUCT(CmdEffect_SetFloatArray);
				hr	=	param->pID3DXEffect->SetFloatArray(param->hParameter,(CONST FLOAT*)pBuffer,param->Count);
				pBuffer+=param->Count*sizeof(float);
				}break;
			case enCF_Effect_SetVector:{//(THIS_ D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector);
				READ_COMMAND_STRUCT(CmdEffect_SetVector);
				hr	=	param->pID3DXEffect->SetVector(param->hParameter,&param->pVector);
				}break;
			case enCF_Effect_SetVectorArray:{//(THIS_ D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector, UINT Count);
				READ_COMMAND_STRUCT(CmdEffect_SetVectorArray);
				hr	=	param->pID3DXEffect->SetVectorArray(param->hParameter,(CONST D3DXVECTOR4*)pBuffer,param->Count);
				pBuffer+=param->Count*sizeof(D3DXVECTOR4);
				}break;
			case enCF_Effect_SetMatrix:{//(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix);
				READ_COMMAND_STRUCT(CmdEffect_SetMatrix);
				hr	=	param->pID3DXEffect->SetMatrix(param->hParameter,&param->pMatrix);

				}break;
			case enCF_Effect_SetMatrixArray:{//(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count);
				READ_COMMAND_STRUCT(CmdEffect_SetMatrixArray);
				hr	=	param->pID3DXEffect->SetMatrixArray(param->hParameter,(CONST D3DXMATRIX*)pBuffer,param->Count);
				pBuffer+=param->Count*sizeof(D3DXMATRIX);
				}break;
			case enCF_Effect_SetMatrixPointerArray:{//(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count);

				}break;
			case enCF_Effect_SetMatrixTranspose:{//(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix);
				READ_COMMAND_STRUCT(CmdEffect_SetMatrixTranspose);
				hr	=	param->pID3DXEffect->SetMatrixTranspose(param->hParameter,&param->pMatrix);
				}break;
			case enCF_Effect_SetMatrixTransposeArray:{//(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count);
				READ_COMMAND_STRUCT(CmdEffect_SetMatrixTransposeArray);
				hr	=	param->pID3DXEffect->SetMatrixTransposeArray(param->hParameter,(CONST D3DXMATRIX*)pBuffer,param->Count);
				pBuffer+=param->Count*sizeof(D3DXMATRIX);
				}break;
			case enCF_Effect_SetMatrixTransposePointerArray:{//(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count);

				}break;
			case enCF_Effect_SetString:{//(THIS_ D3DXHANDLE hParameter, LPCSTR pString);
				READ_COMMAND_STRUCT(CmdEffect_SetString);
				hr	=	param->pID3DXEffect->SetString(param->hParameter,(LPCSTR)pBuffer);
				pBuffer+=param->uiBufferSize;
				}break;
			case enCF_Effect_SetTexture:{//(THIS_ D3DXHANDLE hParameter, LPDIRECT3DBASETEXTURE9 pTexture);
				READ_COMMAND_STRUCT(CmdEffect_SetTexture);
				hr	=	param->pID3DXEffect->SetTexture(param->hParameter,param->pTexture);
				}break;
			case enCF_Effect_SetTechnique:{//(THIS_ D3DXHANDLE hTechnique);
				READ_COMMAND_STRUCT(CmdEffect_SetTechnique);
				hr	=	param->pID3DXEffect->SetTechnique(param->hTechnique);
				}break;
			case enCF_Effect_Begin:{//(THIS_ UINT *pPasses, DWORD Flags) ;
				UINT uiPassCount	=	0;
				READ_COMMAND_STRUCT(CmdEffect_Begin);
				hr	=	param->pID3DXEffect->Begin(&uiPassCount,param->Flags);

				}break;
			case enCF_Effect_BeginPass:{//(THIS_ UINT Pass) ;
				READ_COMMAND_STRUCT(CmdEffect_BeginPass);
				hr	=	param->pID3DXEffect->BeginPass(param->Pass);

				}break;
			case enCF_Effect_CommitChanges:{//(THIS) ;
				READ_COMMAND_STRUCT(CmdEffect_CommitChanges);
				hr	=	(*param)->CommitChanges();

				}break;
			case enCF_Effect_EndPass:{//(THIS) ;
				READ_COMMAND_STRUCT(CmdEffect_EndPass);
				hr	=	(*param)->EndPass();
				}break;
			case enCF_Effect_End:{//(THIS) ;
				READ_COMMAND_STRUCT(CmdEffect_End);
				hr	=	(*param)->End();
				}break;
			case enCF_Effect_SetStateManager:{//(THIS_ LPD3DXEFFECTSTATEMANAGER pManager);
				READ_COMMAND_STRUCT(CmdEffect_SetStateManager);
				hr	=	param->pID3DXEffect->SetStateManager(param->pManager);

				}break;
			case enCF_Effect_SetRawValue:{//(THIS_ D3DXHANDLE hParameter, LPCVOID pData, UINT ByteOffset, UINT Bytes);
				READ_COMMAND_STRUCT(CmdEffect_SetRawValue);
				hr	=	param->pID3DXEffect->SetRawValue(param->hParameter,pBuffer,param->ByteOffset,param->Bytes);
				pBuffer+=param->Bytes;
				}break;
		}
	}
};

bool	MT_RenderThread::RepetitionRun(){
	//如果 主线程调用StopThread  则需要不再执行内部逻辑 也不进入等待
	if(!m_bExit){
		//等待主线程
		m_evtRenderWaitMain.Wait();
		//渲染
		RenderFrame();
		//发送渲染完毕信号
		m_evtMainWaitRender.Reset();
	}
	return	true;
};

void	MT_RenderThread::WaitRenderComplated(){
	//等待渲染完毕
	m_evtMainWaitRender.Wait();
}