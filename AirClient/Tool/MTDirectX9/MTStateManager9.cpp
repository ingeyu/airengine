#include "stdafx.h"
#include "MTStateManager9.h"

namespace	Air{
	namespace	Client{
		namespace	Render{


			StateManager::StateManager(){
				OnResetState();
				m_pDevice	=	NULL;
			}

			void StateManager::OnResetState(){

				memset(&m_Viewport,0,sizeof(D3DVIEWPORT9));

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

				m_RenderState[D3DRS_ZENABLE]=			D3DZB_FALSE;
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
				m_RenderState[D3DRS_COLORWRITEENABLE]=			0x0000000f ;
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

				memset(m_VSParam,0,sizeof(Float4)*256);
				memset(m_PSParam,0,sizeof(Float4)*224);

				m_pVS	=	NULL;
				m_pPS	=	NULL;

			}

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

			DxDevice* StateManager::GetDevice(){
				return	m_pDevice;
			}
			void StateManager::SetDevice( IDirect3DDevice9* pDevice ){
				m_pDevice	=	pDevice;
			}
		}
	}
}