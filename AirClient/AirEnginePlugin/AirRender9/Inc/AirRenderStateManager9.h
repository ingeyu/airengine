#ifndef RENDERSTATEMANAGER_HEAD_FILE
#define RENDERSTATEMANAGER_HEAD_FILE

#include "AirRenderHeader9.h"

namespace	Air{
	namespace Client{

		namespace	Render{
			struct	VB{
				DxVertexBuff*	pVB;
				U32				uiOffset;
				U32				uiSize;
				U32				Freq;
			};

			class	StateManager{
			public:
				StateManager();

				virtual	void	OnResetState();


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
				DxDevice*		GetDevice();
				void			SetDevice(IDirect3DDevice9*	pDevice);



				DWORD				m_RenderState[210];
				DxSurface*			m_pRT[4];
				DxSurface*			m_pDepthStencil;
				DxVertexDeclare*	m_pVD;
				VB					m_VB[16];
				DxIndexBuff*		m_pIB;
				DxVertexShader*		m_pVS;
				DxPixelShader*		m_pPS;
				DWORD				m_PSSamplerState[16][14];
				DWORD				m_VSSamplerState[4][14];
				DxBaseTexture*		m_pPSTexture[16];
				DxBaseTexture*		m_pVSTexture[4];

				Float4				m_VSParam[256];
				Float4				m_PSParam[224];

				D3DVIEWPORT9		m_Viewport;

				DxDevice*			m_pDevice;
			};
		}

	};
};
#endif // RENDERSTATEMANAGER_HEAD_FILE