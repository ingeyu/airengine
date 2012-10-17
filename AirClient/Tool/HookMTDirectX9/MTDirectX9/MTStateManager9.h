#ifndef MTSTATEMANAGER_HEAD_FILE
#define MTSTATEMANAGER_HEAD_FILE

#include "MTHeader.h"


			struct	VB{
				IDirect3DVertexBuffer9*	pVB;
				U32						uiOffset;
				U32						uiSize;
				U32						Freq;
			};

			struct int4{
				int4(){
					x	=	y	=	z	=	w;
				};
				int x,y,z,w;
			};

			class	StateManager{
			public:
				StateManager();

				void	OnLostDevice();
				void	OnResetState(IDirect3DDevice9* pDevice);
/*

				HRESULT SetDepthStencilSurface(
					IDirect3DSurface9 *pNewZStencil
					);

				HRESULT SetIndices(
					IDirect3DIndexBuffer9 *pIndexData
					);
				HRESULT SetPixelShader(
					IDirect3DPixelShader9 *pShader
					);
				HRESULT SetPixelShaderConstantF(
					UINT StartRegister,
					const float *pConstantData,
					UINT Vector4fCount
					);
				HRESULT SetRenderState(
					D3DRENDERSTATETYPE State,
					DWORD Value
					);
				HRESULT SetRenderTarget(
					DWORD RenderTargetIndex,
					IDirect3DSurface9 *pRenderTarget
					);

				HRESULT SetSamplerState(
					DWORD Sampler,
					D3DSAMPLERSTATETYPE Type,
					DWORD Value
					);
				HRESULT SetVSSamplerState(
					DWORD Sampler,
					D3DSAMPLERSTATETYPE Type,
					DWORD Value
					);

				HRESULT SetStreamSource(
					UINT StreamNumber,
					IDirect3DVertexBuffer9 *pStreamData,
					UINT OffsetInBytes,
					UINT Stride
					);

				HRESULT SetStreamSourceFreq(
					UINT StreamNumber,
					UINT FrequencyParameter
					);
				HRESULT SetTexture(
					DWORD Sampler,
					IDirect3DBaseTexture9 *pTexture
					);
				HRESULT SetVSTexture(
					DWORD Sampler,
					IDirect3DBaseTexture9 *pTexture
					);
				HRESULT SetVertexDeclaration(
					IDirect3DVertexDeclaration9 *pDecl
					);
				HRESULT SetVertexShader(
					IDirect3DVertexShader9 *pShader
					);
				HRESULT SetVertexShaderConstantF(
					UINT StartRegister,
					const float *pConstantData,
					UINT Vector4fCount
					);

				HRESULT SetViewport(
					const D3DVIEWPORT9 *pViewport
					);
				IDirect3DDevice9*		GetDevice();
				void					SetDevice(IDirect3DDevice9*	pDevice);
*/


				DWORD							m_RenderState[210];
				IDirect3DSurface9*				m_pRT[4];
				IDirect3DSurface9*				m_pDepthStencil;
				IDirect3DVertexDeclaration9*	m_pVD;
				VB								m_VB[16];
				IDirect3DIndexBuffer9*			m_pIB;
				IDirect3DVertexShader9*			m_pVS;
				IDirect3DPixelShader9*			m_pPS;
				DWORD							m_PSSamplerState[16][14];
				DWORD							m_VSSamplerState[4][14];
				IDirect3DBaseTexture9*			m_pPSTexture[16];
				IDirect3DBaseTexture9*			m_pVSTexture[4];
				D3DXVECTOR4						m_VSParam[256];
				D3DXVECTOR4						m_PSParam[224];
				D3DVIEWPORT9					m_Viewport;
				IDirect3DDevice9*				m_pDevice;
				D3DMATRIX						m_Transform[512];
				D3DMATERIAL9					m_Material;
				D3DLIGHT9						m_Light[8];
				BOOL							m_LightEnable[8];
				D3DXVECTOR4						m_ClipPlane[6];
				DWORD							m_TextureState[16][33];
				RECT							m_ScissorRect;
				DWORD							m_FVF;
				int4							m_VSParamI[16];
				int4							m_PSParamI[16];
				BOOL							m_VSParamB[16];
				BOOL							m_PSParamB[16];
				float							m_fNPatchMode;
			};

#endif // RENDERSTATEMANAGER_HEAD_FILE