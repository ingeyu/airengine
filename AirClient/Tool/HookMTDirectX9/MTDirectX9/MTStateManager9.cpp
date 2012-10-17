
#include "MTStateManager9.h"

D3DCOLORVALUE	Make_D3DCOLORVALUE(float r,float g,float b,float a = 0.0f){
	D3DCOLORVALUE	c;
	c.r	=	r;
	c.g	=	g;
	c.b	=	b;
	c.a	=	a;
	return	c;
};

D3DVECTOR	Make_D3DVECTOR(float x,float y,float z){

	D3DVECTOR	v;
	v.x	=	x;
	v.y	=	y;
	v.z	=	z;
	return	v;
};

extern T_DeviceRelease						ST_DeviceRelease						;
extern T_TestCooperativeLevel				ST_TestCooperativeLevel					;
extern T_EvictManagedResources				ST_EvictManagedResources				;
extern T_SetCursorProperties				ST_SetCursorProperties					;
extern T_SetCursorPosition					ST_SetCursorPosition					;
extern T_ShowCursor							ST_ShowCursor							;
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
extern T_CreateVertexBuffer					ST_CreateVertexBuffer					;
extern T_CreateIndexBuffer					ST_CreateIndexBuffer					;
extern T_CreateRenderTarget					ST_CreateRenderTarget					;
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



			StateManager::StateManager(){
				m_pDevice	=	NULL;
			}
			void StateManager::OnLostDevice(){
				
				for(U32	i=0;i<4;i++){
					T_Release(m_pRT[i]);	
				}
				T_Release(m_pDepthStencil);
				for(int i=0;i<4;i++)
					T_Release(m_pVSTexture[i]);
				for(int i=0;i<16;i++)
					T_Release(m_pPSTexture[i]);
				T_Release(m_pVS);
				T_Release(m_pPS);
				T_Release(m_pVD);
				T_Release(m_pIB);
				for(int i=0;i<16;i++)
					T_Release(m_VB[i].pVB);
			};
			void StateManager::OnResetState(IDirect3DDevice9* pDevice){
				m_fNPatchMode	=	0.0f;

				m_Viewport.X	=	0;
				m_Viewport.Y	=	0;
				m_Viewport.Width	=	1;
				m_Viewport.Height	=	1;
				m_Viewport.MinZ		=	0.0f;
				m_Viewport.MaxZ		=	1.0f;

				//SEE Materials (Direct3D 9)
				m_Material.Diffuse	=	Make_D3DCOLORVALUE(1,1,1);
				m_Material.Specular	=	Make_D3DCOLORVALUE(0,0,0);
				m_Material.Ambient	=	Make_D3DCOLORVALUE(0,0,0);
				m_Material.Emissive	=	Make_D3DCOLORVALUE(0,0,0);
				m_Material.Power	=	0.0f;//Make_D3DCOLORVALUE(1,1,1);


				for(U32	i=0;i<4;i++){
					m_pRT[i]	=	NULL;
				}

				m_pDepthStencil	=	NULL;

				for(U32	i=0;i<16;i++){
					m_VB[i].pVB			=	NULL;
					m_VB[i].uiOffset	=	0;
					m_VB[i].uiSize		=	0;
					m_VB[i].Freq		=	1;
				}

				m_pIB			=	NULL;
				m_pVD			=	NULL;

				for(U32	i=0;i<16;i++){
					m_PSSamplerState[i][D3DSAMP_ADDRESSU		]	=	D3DTADDRESS_WRAP;
					m_PSSamplerState[i][D3DSAMP_ADDRESSV		]	=	D3DTADDRESS_WRAP;
					m_PSSamplerState[i][D3DSAMP_ADDRESSW		]	=	D3DTADDRESS_WRAP;
					m_PSSamplerState[i][D3DSAMP_BORDERCOLOR     ]	=	0x00000000;
					m_PSSamplerState[i][D3DSAMP_MAGFILTER       ]	=	D3DTEXF_POINT;
					m_PSSamplerState[i][D3DSAMP_MINFILTER       ]	=	D3DTEXF_POINT;
					m_PSSamplerState[i][D3DSAMP_MIPFILTER       ]	=	D3DTEXF_NONE;
					m_PSSamplerState[i][D3DSAMP_MIPMAPLODBIAS   ]	=	0;
					m_PSSamplerState[i][D3DSAMP_MAXMIPLEVEL     ]	=	0;
					m_PSSamplerState[i][D3DSAMP_MAXANISOTROPY   ]	=	1;
					m_PSSamplerState[i][D3DSAMP_SRGBTEXTURE     ]	=	0;
					m_PSSamplerState[i][D3DSAMP_ELEMENTINDEX    ]	=	0;
					m_PSSamplerState[i][D3DSAMP_DMAPOFFSET      ]	=	0;

					m_pPSTexture[i]	=	NULL;
				}
				for(U32	i=0;i<4;i++){
					m_VSSamplerState[i][D3DSAMP_ADDRESSU		]	=	D3DTADDRESS_WRAP;
					m_VSSamplerState[i][D3DSAMP_ADDRESSV		]	=	D3DTADDRESS_WRAP;
					m_VSSamplerState[i][D3DSAMP_ADDRESSW		]	=	D3DTADDRESS_WRAP;
					m_VSSamplerState[i][D3DSAMP_BORDERCOLOR		]	=	0x00000000;
					m_VSSamplerState[i][D3DSAMP_MAGFILTER		]	=	D3DTEXF_POINT;
					m_VSSamplerState[i][D3DSAMP_MINFILTER		]	=	D3DTEXF_POINT;
					m_VSSamplerState[i][D3DSAMP_MIPFILTER      	]	=	D3DTEXF_NONE;
					m_VSSamplerState[i][D3DSAMP_MIPMAPLODBIAS  	]	=	0;
					m_VSSamplerState[i][D3DSAMP_MAXMIPLEVEL    	]	=	0;
					m_VSSamplerState[i][D3DSAMP_MAXANISOTROPY  	]	=	1;
					m_VSSamplerState[i][D3DSAMP_SRGBTEXTURE    	]	=	0;
					m_VSSamplerState[i][D3DSAMP_ELEMENTINDEX   	]	=	0;
					m_VSSamplerState[i][D3DSAMP_DMAPOFFSET     	]	=	0;

					m_pVSTexture[i]	=	NULL;
				}

				m_RenderState[D3DRS_ZENABLE]=			D3DZB_TRUE;
				m_RenderState[D3DRS_SPECULARENABLE]=	FALSE ;
				m_RenderState[D3DRS_FILLMODE]=			D3DFILL_SOLID ;
				m_RenderState[D3DRS_SHADEMODE]=			D3DSHADE_GOURAUD ;
				m_RenderState[D3DRS_ZWRITEENABLE]=		TRUE ;
				m_RenderState[D3DRS_ALPHATESTENABLE]=	FALSE ;
				m_RenderState[D3DRS_LASTPIXEL]=			TRUE ;
				m_RenderState[D3DRS_SRCBLEND]=			D3DBLEND_ONE ;
				m_RenderState[D3DRS_DESTBLEND]=			D3DBLEND_ZERO ;
				m_RenderState[D3DRS_ZFUNC]=				D3DCMP_LESSEQUAL ;
				m_RenderState[D3DRS_ALPHAREF]=			0 ;
				m_RenderState[D3DRS_ALPHAFUNC]=			D3DCMP_ALWAYS ;
				m_RenderState[D3DRS_DITHERENABLE]=		FALSE ;
				m_RenderState[D3DRS_FOGSTART]=			0 ;
				m_RenderState[D3DRS_FOGEND]=			1 ;
				m_RenderState[D3DRS_FOGDENSITY]=		1 ;
				m_RenderState[D3DRS_ALPHABLENDENABLE]=	FALSE ;
				m_RenderState[D3DRS_DEPTHBIAS]=			0 ;
				m_RenderState[D3DRS_STENCILENABLE]=		FALSE ;
				m_RenderState[D3DRS_STENCILFAIL]=		D3DSTENCILOP_KEEP ;
				m_RenderState[D3DRS_STENCILZFAIL]=		D3DSTENCILOP_KEEP ;
				m_RenderState[D3DRS_STENCILPASS]=		D3DSTENCILOP_KEEP ;
				m_RenderState[D3DRS_STENCILFUNC]=		D3DCMP_ALWAYS ;
				m_RenderState[D3DRS_STENCILREF]=		0 ;
				m_RenderState[D3DRS_STENCILMASK]=		0xffffffff ;
				m_RenderState[D3DRS_STENCILWRITEMASK]=	0xffffffff ;
				m_RenderState[D3DRS_TEXTUREFACTOR]=		0xffffffff ;
				m_RenderState[D3DRS_WRAP0]=				0 ;
				m_RenderState[D3DRS_WRAP1]=				0 ;
				m_RenderState[D3DRS_WRAP2]=				0 ;
				m_RenderState[D3DRS_WRAP3]=				0 ;
				m_RenderState[D3DRS_WRAP4]=				0 ;
				m_RenderState[D3DRS_WRAP5]=				0 ;
				m_RenderState[D3DRS_WRAP6]=				0 ;
				m_RenderState[D3DRS_WRAP7]=				0 ;
				m_RenderState[D3DRS_WRAP8]=				0 ;
				m_RenderState[D3DRS_WRAP9]=				0 ;
				m_RenderState[D3DRS_WRAP10]=			0 ;
				m_RenderState[D3DRS_WRAP11]=			0 ;
				m_RenderState[D3DRS_WRAP12]=			0 ;
				m_RenderState[D3DRS_WRAP13]=			0 ;
				m_RenderState[D3DRS_WRAP14]=			0 ;
				m_RenderState[D3DRS_WRAP15]=			0 ;
				m_RenderState[D3DRS_LOCALVIEWER]=		TRUE ;
				m_RenderState[D3DRS_EMISSIVEMATERIALSOURCE]=	D3DMCS_MATERIAL ;
				m_RenderState[D3DRS_AMBIENTMATERIALSOURCE]=		D3DMCS_MATERIAL ;
				m_RenderState[D3DRS_DIFFUSEMATERIALSOURCE]=		D3DMCS_COLOR1 ;
				m_RenderState[D3DRS_SPECULARMATERIALSOURCE]=	D3DMCS_COLOR2 ;
				m_RenderState[D3DRS_COLORWRITEENABLE]=	 		0x0000000f ;
				m_RenderState[D3DRS_BLENDOP]=					D3DBLENDOP_ADD ;
				m_RenderState[D3DRS_SCISSORTESTENABLE]=			FALSE ;
				m_RenderState[D3DRS_SLOPESCALEDEPTHBIAS]=		0 ;
				m_RenderState[D3DRS_ANTIALIASEDLINEENABLE]=		FALSE ;
				m_RenderState[D3DRS_TWOSIDEDSTENCILMODE]=		FALSE ;
				m_RenderState[D3DRS_CCW_STENCILFAIL]=			D3DSTENCILOP_KEEP ;
				m_RenderState[D3DRS_CCW_STENCILZFAIL]=			D3DSTENCILOP_KEEP ;
				m_RenderState[D3DRS_CCW_STENCILPASS]=			D3DSTENCILOP_KEEP ;
				m_RenderState[D3DRS_CCW_STENCILFUNC]=			D3DCMP_ALWAYS ;
				m_RenderState[D3DRS_COLORWRITEENABLE1]=			0x0000000f ;
				m_RenderState[D3DRS_COLORWRITEENABLE2]=			0x0000000f ;
				m_RenderState[D3DRS_COLORWRITEENABLE3]=			0x0000000f ;
				m_RenderState[D3DRS_BLENDFACTOR]=				0xffffffff ;
				m_RenderState[D3DRS_SRGBWRITEENABLE]=			0 ;
				m_RenderState[D3DRS_SEPARATEALPHABLENDENABLE]=	FALSE ;
				m_RenderState[D3DRS_SRCBLENDALPHA]=				D3DBLEND_ONE ;
				m_RenderState[D3DRS_DESTBLENDALPHA]=			D3DBLEND_ZERO ;
				m_RenderState[D3DRS_BLENDOPALPHA]=				D3DBLENDOP_ADD ;

				memset(m_VSParam,0,sizeof(D3DXVECTOR4)*256);
				memset(m_PSParam,0,sizeof(D3DXVECTOR4)*224);

				m_pVS	=	NULL;
				m_pPS	=	NULL;

				
				m_FVF	=	0;
				m_ScissorRect.left		=	0;
				m_ScissorRect.top		=	0;;
				m_ScissorRect.right		=	1;
				m_ScissorRect.bottom	=	1;

				//SEE Specular Lighting (Direct3D 9)
				for(int i=0;i<8;i++){
					m_LightEnable[i]	=	FALSE;
					m_Light[i].Ambient	=	Make_D3DCOLORVALUE(0,0,0);
					m_Light[i].Attenuation0	=	0;//Make_D3DCOLORVALUE(0,0,0);
					m_Light[i].Attenuation1	=	0;//Make_D3DCOLORVALUE(0,0,0);
					m_Light[i].Attenuation2	=	0;//Make_D3DCOLORVALUE(0,0,0);
					m_Light[i].Diffuse		=	Make_D3DCOLORVALUE(1,1,1);
					m_Light[i].Specular		=	Make_D3DCOLORVALUE(0,0,0);
					m_Light[i].Position		=	Make_D3DVECTOR(0,0,0);
					m_Light[i].Direction		=	Make_D3DVECTOR(0,0,0);
				}
				for(int i=0;i<6;i++){
					m_ClipPlane[i]	=	D3DXVECTOR4(0,0,0,0);
				}
				for(int i=0;i<512;i++){
					memset(&m_Transform[i],0,sizeof(D3DMATRIX));
					m_Transform[i]._11	=	1;
					m_Transform[i]._22	=	1;
					m_Transform[i]._33	=	1;
					m_Transform[i]._44	=	1;
				}
				for(int i=0;i<16;i++){
					m_VSParamB[i]	=	FALSE;
					m_PSParamB[i]	=	FALSE;

					m_VSParamI[i]	=	int4();
					m_PSParamI[i]	=	int4();
				}
				for(int i=0;i<16;i++){
					m_TextureState[i][D3DTSS_COLOROP                ]	=	D3DTOP_DISABLE;
					m_TextureState[i][D3DTSS_COLORARG1				]	=	D3DTA_TEXTURE;
					m_TextureState[i][D3DTSS_COLORARG2				]	=	D3DTA_CURRENT;
					m_TextureState[i][D3DTSS_ALPHAOP				]	=	D3DTOP_DISABLE;
					m_TextureState[i][D3DTSS_ALPHAARG1				]	=	D3DTA_TEXTURE;
					m_TextureState[i][D3DTSS_ALPHAARG2				]	=	D3DTA_CURRENT;
					m_TextureState[i][D3DTSS_BUMPENVMAT00			]	=	0;
					m_TextureState[i][D3DTSS_BUMPENVMAT01			]	=	0;
					m_TextureState[i][D3DTSS_BUMPENVMAT10			]	=	0;
					m_TextureState[i][D3DTSS_BUMPENVMAT11			]	=	0;
					m_TextureState[i][D3DTSS_TEXCOORDINDEX			]	=	i;
					m_TextureState[i][D3DTSS_BUMPENVLSCALE			]	=	0;
					m_TextureState[i][D3DTSS_BUMPENVLOFFSET			]	=	0;
					m_TextureState[i][D3DTSS_TEXTURETRANSFORMFLAGS	]	=	D3DTTFF_DISABLE;
					m_TextureState[i][D3DTSS_COLORARG0				]	=	D3DTA_CURRENT;
					m_TextureState[i][D3DTSS_ALPHAARG0				]	=	D3DTA_CURRENT;
					m_TextureState[i][D3DTSS_RESULTARG				]	=	D3DTA_CURRENT ;
					m_TextureState[i][D3DTSS_CONSTANT				]	=	D3DCOLOR_ARGB(0x00,0x00,0x00,0x00);

				}

				for(int i=0;i<4;i++){
					ST_GetRenderTarget(pDevice,i,&m_pRT[i]);
				}
				ST_GetDepthStencilSurface(pDevice,&m_pDepthStencil);

				ST_GetScissorRect(pDevice,&m_ScissorRect);

				ST_GetViewport(pDevice,&m_Viewport);
			}
/*
			HRESULT StateManager::SetIndices( IDirect3DIndexBuffer9 *pIndexData ){
				if(pIndexData!=m_pIB){
					m_pIB	=	pIndexData;
					return	m_pDevice->SetIndices(pIndexData);
				}
				return	S_OK;
			}

			HRESULT StateManager::SetDepthStencilSurface( IDirect3DSurface9 *pNewZStencil ){
				if(m_pDepthStencil!=pNewZStencil){
					m_pDepthStencil	=	pNewZStencil;
					return	m_pDevice->SetDepthStencilSurface(pNewZStencil);
				}
				return	S_OK;
			}

			HRESULT StateManager::SetPixelShader( IDirect3DPixelShader9 *pShader ){
				if(m_pPS!=pShader){
					m_pPS	=	pShader;
					return	m_pDevice->SetPixelShader(pShader);
				}
				return	S_OK;
			}

			HRESULT StateManager::SetPixelShaderConstantF( UINT StartRegister, const float *pConstantData, UINT Vector4fCount ){
				//if(Common::Memcmp4())
				return	m_pDevice->SetPixelShaderConstantF(StartRegister,pConstantData,Vector4fCount);
				return	S_OK;
			}

			HRESULT StateManager::SetRenderState( D3DRENDERSTATETYPE State, DWORD Value ){
				if(m_RenderState[State]!=Value){
					m_RenderState[State]	=	Value;
					return	m_pDevice->SetRenderState(State,Value);
				}
				return	S_OK;
			}

			HRESULT StateManager::SetRenderTarget( DWORD RenderTargetIndex, IDirect3DSurface9 *pRenderTarget ){
				if(m_pRT[RenderTargetIndex]!=pRenderTarget){
					m_pRT[RenderTargetIndex]=pRenderTarget;
					return	m_pDevice->SetRenderTarget(RenderTargetIndex,pRenderTarget);
				}
				return	S_OK;
			}

			HRESULT StateManager::SetSamplerState( DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value ){
				DWORD&	dwValue	=	m_PSSamplerState[Sampler][Type];
				if(dwValue!=Value){
					dwValue	=	Value;
					return	m_pDevice->SetSamplerState(Sampler,Type,Value);
				}
				return	S_OK;
			}

			HRESULT StateManager::SetStreamSource( UINT StreamNumber, IDirect3DVertexBuffer9 *pStreamData, UINT OffsetInBytes, UINT Stride ){
				VB&	vb	=	m_VB[StreamNumber];

				if(	vb.pVB		!=	pStreamData	||
					vb.uiOffset	!=	OffsetInBytes	||
					vb.uiSize	!=	Stride)
				{
					vb.pVB		=	pStreamData;
					vb.uiOffset	=	OffsetInBytes;
					vb.uiSize	=	Stride;
					return	m_pDevice->SetStreamSource(StreamNumber,pStreamData,OffsetInBytes,Stride);
				}

				return	S_OK;
			}

			HRESULT StateManager::SetStreamSourceFreq( UINT StreamNumber, UINT FrequencyParameter ){
				if(m_VB[StreamNumber].Freq	!=	FrequencyParameter){
					m_VB[StreamNumber].Freq	=	FrequencyParameter;
					return	m_pDevice->SetStreamSourceFreq(StreamNumber,FrequencyParameter);
				}
				return	S_OK;
			}

			HRESULT StateManager::SetTexture( DWORD Sampler, IDirect3DBaseTexture9 *pTexture ){
				if(m_pPSTexture[Sampler]!=pTexture){
					m_pPSTexture[Sampler]	=	pTexture;
					return	m_pDevice->SetTexture(Sampler,pTexture);
				}
				return	S_OK;
			}

			HRESULT StateManager::SetVertexDeclaration( IDirect3DVertexDeclaration9 *pDecl ){
				if(m_pVD!=pDecl){
					m_pVD=pDecl;
					return	m_pDevice->SetVertexDeclaration(pDecl);
				}
				return	S_OK;
			}

			HRESULT StateManager::SetVertexShader( IDirect3DVertexShader9 *pShader ){
				if(m_pVS!=pShader){
					m_pVS	=	pShader;
					return	m_pDevice->SetVertexShader(pShader);
				}
				return	S_OK;
			}

			HRESULT StateManager::SetVertexShaderConstantF( UINT StartRegister, const float *pConstantData, UINT Vector4fCount ){
				return	m_pDevice->SetVertexShaderConstantF(StartRegister,pConstantData,Vector4fCount);
				return	S_OK;
			}

			HRESULT StateManager::SetViewport( const D3DVIEWPORT9 *pViewport ){
				if(!Common::CompareCopy4(&m_Viewport,pViewport,sizeof(D3DVIEWPORT9))){
					return	m_pDevice->SetViewport(pViewport);
				}
				return	S_OK;
			}

			HRESULT StateManager::SetVSTexture( DWORD Sampler, IDirect3DBaseTexture9 *pTexture ){
				if(m_pVSTexture[Sampler]!=pTexture){
					m_pVSTexture[Sampler]	=	pTexture;
					return	m_pDevice->SetTexture(256+Sampler,pTexture);
				}
				return	S_OK;
			}

			HRESULT StateManager::SetVSSamplerState( DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value ){
				DWORD&	dwValue	=	m_VSSamplerState[Sampler][Type];
				if(dwValue!=Value){
					dwValue	=	Value;
					return	m_pDevice->SetSamplerState(256+Sampler,Type,Value);
				}
				return	S_OK;
			}

			IDirect3DDevice9* StateManager::GetDevice(){
				return	m_pDevice;
			}
			void StateManager::SetDevice( IDirect3DDevice9* pDevice ){
				m_pDevice	=	pDevice;
			}
*/