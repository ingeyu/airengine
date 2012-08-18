#ifndef MTHEADER_HEAD_FILE
#define MTHEADER_HEAD_FILE


#define CINTERFACE

#include <windows.h>
//#ifdef	__cplusplus
//	#undef __cplusplus
//	#define __cplusplus_DEFINED
//#endif
#include <d3d9.h>
#include <d3dx9.h>
//#ifdef __cplusplus_DEFINED
//#define __cplusplus
//#endif

#include <vector>
#include <string>
#include "detours.h"

typedef	std::string		AString;
typedef	const AString	CAString;
typedef	unsigned char	U8;
typedef	unsigned int	U32;


template<typename T>
class Singleton{
public:
	Singleton(){
		m_pSingleton	=	(T*)this;
	};
	virtual ~Singleton(){
		m_pSingleton	=	NULL;
	};

	static T& GetSingleton(){
		if(m_pSingleton==NULL){
			m_pSingleton	=	new T();
		}
		return	*m_pSingleton;
	};
	static void	ReleaseSingleton(){
		if(m_pSingleton!=NULL){
			delete m_pSingleton;
			m_pSingleton=NULL;
		}
	};
	static T* m_pSingleton;
};
template<typename T>
T* Singleton<T>::m_pSingleton	=	NULL;

class MT_IUnknown
{
public:
	MT_IUnknown(){
		uiRef	=	0;
	};
	virtual	~MT_IUnknown(){};
    virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject) = 0;

	virtual ULONG STDMETHODCALLTYPE AddRef( void){
		return	InterlockedIncrement(&uiRef);
	};

	virtual ULONG STDMETHODCALLTYPE Release( void){
		LONG	ret	=	InterlockedDecrement(&uiRef);
		if(ret<=0){
			delete this;
		}
		return	ret;
	};

    template<class Q>
    HRESULT
    STDMETHODCALLTYPE
    QueryInterface(Q** pp)
    {
        return QueryInterface(__uuidof(Q), (void **)pp);
    }
protected:
	LONG	uiRef;
};

class	Event{
public:
	Event(CAString&	strName	=	""){
		m_hEvent	=	CreateEventA(NULL,FALSE,FALSE,strName.c_str());
	};
	~Event(){
		CloseHandle(m_hEvent);
	}

	/**	\brief	设置事件
	*   
	*	@remarks 	设置事件
	*	@see		Event
	*	@return   	void
	*	@note
	*
	**/
	void	Reset(){
		SetEvent(m_hEvent);
	}
	/**	\brief	等待事件
	*   
	*	@remarks 	等待事件
	*	@see		Event
	*	@return   	void
	*	@param		U32		uiTime
	*	@note
	*
	**/
	void	Wait(U32	uiTime	=	INFINITE){
		WaitForSingleObject(m_hEvent,uiTime);
	}
	HANDLE	m_hEvent;
};


class MT_IDirect3D9;
class MT_IDirect3D9Ex ;
class MT_IDirect3DDevice9;
class MT_IDirect3DDevice9Ex ;
class MT_IDirect3DSwapChain9;
class MT_IDirect3DSwapChain9Ex ;
class MT_IDirect3DSurface9;
class MT_IDirect3DVertexBuffer9;
class MT_IDirect3DIndexBuffer9;
class MT_IDirect3DPixelShader9;
class MT_IDirect3DQuery9;
class MT_IDirect3DVertexDeclaration9 ;
class MT_IDirect3DVertexShader9 ;
class MT_IDirect3DVolume9 ;
class MT_IDirect3DVolumeTexture9 ;
class MT_IDirect3DCubeTexture9 ;
class MT_IDirect3DDevice9Video ;
class MT_IDirect3DCryptoSession9 ;
class MT_IDirect3DBaseTexture9 ;
class MT_IDirect3DTexture9 ;
class MT_IDirect3DAuthenticatedChannel9 ;
class MT_IDirect3D9ExOverlayExtension ;
class MT_IDirect3DResource9;
class MT_IDirect3DStateBlock9;

//D3DX
class MT_ID3DXEffect;


//typedef
typedef MT_IDirect3D9*							MT_LPDIRECT3D9;
typedef MT_IDirect3D9Ex *						MT_LPDIRECT3D9EX ;
typedef MT_IDirect3DDevice9*					MT_LPDIRECT3DDEVICE9;
typedef MT_IDirect3DDevice9Ex *					MT_LPDIRECT3DDEVICE9EX ;
typedef MT_IDirect3DSwapChain9*					MT_LPDIRECT3DSWAPCHAIN9;
typedef MT_IDirect3DSwapChain9Ex *				MT_LPDIRECT3DSWAPCHAIN9EX ;
typedef MT_IDirect3DSurface9*					MT_LPDIRECT3DSURFACE9;
typedef MT_IDirect3DVertexBuffer9*				MT_LPDIRECT3DVERTEXBUFFER9;
typedef MT_IDirect3DIndexBuffer9*				MT_LPDIRECT3DINDEXBUFFER9;
typedef MT_IDirect3DPixelShader9*				MT_LPDIRECT3DPIXELSHADER9;
typedef MT_IDirect3DQuery9*						MT_LPDIRECT3DQUERY9;
typedef MT_IDirect3DVertexDeclaration9 *		MT_LPDIRECT3DVERTEXDECLARATION9 ;
typedef MT_IDirect3DVertexShader9 *				MT_LPDIRECT3DVERTEXSHADER9 ;
typedef MT_IDirect3DVolume9 *					MT_LPDIRECT3DVOLUME9 ;
typedef MT_IDirect3DVolumeTexture9 *			MT_LPDIRECT3DVOLUMETEXTURE9 ;
typedef MT_IDirect3DCubeTexture9 *				MT_LPDIRECT3DCUBETEXTURE9 ;
typedef MT_IDirect3DDevice9Video *				MT_LPDIRECT3DDEVICE9VIDEO ;
typedef MT_IDirect3DCryptoSession9 *			MT_LPDIRECT3DCRYPTOSESSION9 ;
typedef MT_IDirect3DBaseTexture9 *				MT_LPDIRECT3DBASETEXTURE9 ;
typedef MT_IDirect3DTexture9 *					MT_LPDIRECT3DTEXTURE9 ;
typedef MT_IDirect3DAuthenticatedChannel9 *		MT_LPDIRECT3DAUTHENTICATEDCHANNEL9 ;
typedef MT_IDirect3D9ExOverlayExtension *		MT_LPDIRECT3D9EXOVERLAYEXTENSION ;
typedef MT_IDirect3DResource9*					MT_LPDIRECT3DRESOURCE9;
typedef MT_IDirect3DStateBlock9*				MT_LPDIRECT3DSTATEBLOCK9;


typedef	MT_ID3DXEffect*				MT_LPD3DXEFFECT;


typedef	std::vector<MT_IDirect3DVolume9*>	VolumeVector;


enum	enumCommandFunc{
enCF_UNKNOWN,
enCF_SetCursorProperties,
enCF_SetCursorPosition,
enCF_ShowCursor,
enCF_Present,
enCF_SetDialogBoxMode,
enCF_SetGammaRamp,
enCF_UpdateSurface,
enCF_UpdateTexture,
enCF_StretchRect,
enCF_ColorFill,
enCF_SetRenderTarget,
enCF_SetDepthStencilSurface,
enCF_BeginScene,
enCF_EndScene,
enCF_Clear,
enCF_SetTransform,
enCF_MultiplyTransform,
enCF_SetViewport,
enCF_SetMaterial,
enCF_SetLight,
enCF_LightEnable,
enCF_SetClipPlane,
enCF_SetRenderState,
enCF_BeginStateBlock,
enCF_EndStateBlock,
enCF_SetClipStatus,
enCF_SetTexture,
enCF_SetTextureStageState,
enCF_SetSamplerState,
enCF_SetPaletteEntries,
enCF_SetCurrentTexturePalette,
enCF_SetScissorRect,
enCF_SetSoftwareVertexProcessing,
enCF_SetNPatchMode,
enCF_DrawPrimitive,
enCF_DrawIndexedPrimitive,
enCF_DrawPrimitiveUP,
enCF_DrawIndexedPrimitiveUP,
enCF_ProcessVertices,
enCF_SetVertexDeclaration,
enCF_SetFVF,
enCF_SetVertexShader,
enCF_SetVertexShaderConstantF,
enCF_SetVertexShaderConstantI,
enCF_SetVertexShaderConstantB,
enCF_SetStreamSource,
enCF_SetStreamSourceFreq,
enCF_SetIndices,
enCF_SetPixelShader,
enCF_SetPixelShaderConstantF,
enCF_SetPixelShaderConstantI,
enCF_SetPixelShaderConstantB,
enCF_DrawRectPatch,
enCF_DrawTriPatch,
enCF_DeletePatch,
enCF_SwapChain_Present,
enCF_Surface_LockRect,
enCF_Surface_UnlockRect,
enCF_Volume_LockBox,
enCF_Volume_UnlockBox,
enCF_VertexBuffer_Lock,
enCF_VertexBuffer_Unlock,
enCF_IndexBuffer_Lock,
enCF_IndexBuffer_Unlock,
enCF_BaseTexture_SetAutoGenFilterType,
enCF_BaseTexture_GenerateMipSubLevels,
enCF_Texture_LockRect,
enCF_Texture_UnlockRect,
enCF_Texture_AddDirtyRect,
enCF_CubeTexture_LockRect,
enCF_CubeTexture_UnlockRect,
enCF_CubeTexture_AddDirtyRect,
enCF_VolumeTexture_LockBox,
enCF_VolumeTexture_UnlockBox,
enCF_VolumeTexture_AddDirtyBox,
enCF_StateBlock_Apply,
enCF_StateBlock_Capture,
enCF_PIX_D3DPERF_BeginEvent,
enCF_PIX_D3DPERF_EndEvent,
enCF_PIX_D3DPERF_SetMarker,

enCF_Effect_SetValue,//(THIS_ D3DXHANDLE hParameter, LPCVOID pData, UINT Bytes);
enCF_Effect_SetBool,//(THIS_ D3DXHANDLE hParameter, BOOL b);
enCF_Effect_SetBoolArray,//(THIS_ D3DXHANDLE hParameter, CONST BOOL* pb, UINT Count);
enCF_Effect_SetInt,//(THIS_ D3DXHANDLE hParameter, INT n);
enCF_Effect_SetIntArray,//(THIS_ D3DXHANDLE hParameter, CONST INT* pn, UINT Count);
enCF_Effect_SetFloat,//(THIS_ D3DXHANDLE hParameter, FLOAT f);
enCF_Effect_SetFloatArray,//(THIS_ D3DXHANDLE hParameter, CONST FLOAT* pf, UINT Count);
enCF_Effect_SetVector,//(THIS_ D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector);
enCF_Effect_SetVectorArray,//(THIS_ D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector, UINT Count);
enCF_Effect_SetMatrix,//(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix);
enCF_Effect_SetMatrixArray,//(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count);
enCF_Effect_SetMatrixPointerArray,//(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count);
enCF_Effect_SetMatrixTranspose,//(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix);
enCF_Effect_SetMatrixTransposeArray,//(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count);
enCF_Effect_SetMatrixTransposePointerArray,//(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count);
enCF_Effect_SetString,//(THIS_ D3DXHANDLE hParameter, LPCSTR pString);
enCF_Effect_SetTexture,//(THIS_ D3DXHANDLE hParameter, LPDIRECT3DBASETEXTURE9 pTexture);
enCF_Effect_SetTechnique,//(THIS_ D3DXHANDLE hTechnique);
enCF_Effect_Begin,//(THIS_ UINT *pPasses, DWORD Flags) ;
enCF_Effect_BeginPass,//(THIS_ UINT Pass) ;
enCF_Effect_CommitChanges,//(THIS) ;
enCF_Effect_EndPass,//(THIS) ;
enCF_Effect_End,//(THIS) ;
enCF_Effect_SetStateManager,//(THIS_ LPD3DXEFFECTSTATEMANAGER pManager);
enCF_Effect_SetRawValue,//(THIS_ D3DXHANDLE hParameter, LPCVOID pData, UINT ByteOffset, UINT Bytes);
};


/*** IDirect3DDevice9 methods ***/
typedef HRESULT(STDMETHODCALLTYPE *T_TestCooperativeLevel)(IDirect3DDevice9* pThis);
typedef HRESULT(STDMETHODCALLTYPE *T_EvictManagedResources)(IDirect3DDevice9* pThis);

typedef HRESULT(STDMETHODCALLTYPE *T_SetCursorProperties)(IDirect3DDevice9* pThis, UINT XHotSpot,UINT YHotSpot,IDirect3DSurface9* pCursorBitmap);
typedef void(	STDMETHODCALLTYPE *T_SetCursorPosition)(IDirect3DDevice9* pThis, int X,int Y,DWORD Flags);
typedef BOOL(	STDMETHODCALLTYPE *T_ShowCursor)(IDirect3DDevice9* pThis, BOOL bShow);
typedef HRESULT(STDMETHODCALLTYPE *T_CreateAdditionalSwapChain)(IDirect3DDevice9* pThis, D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain9** pSwapChain);
typedef HRESULT(STDMETHODCALLTYPE *T_GetSwapChain)(IDirect3DDevice9* pThis, UINT iSwapChain,IDirect3DSwapChain9** pSwapChain);
typedef UINT(	STDMETHODCALLTYPE *T_GetNumberOfSwapChains)(IDirect3DDevice9* pThis);
typedef HRESULT(STDMETHODCALLTYPE *T_Reset)(IDirect3DDevice9* pThis, D3DPRESENT_PARAMETERS* pPresentationParameters);
typedef HRESULT(STDMETHODCALLTYPE *T_Present)(IDirect3DDevice9* pThis, CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion);
typedef HRESULT(STDMETHODCALLTYPE *T_GetBackBuffer)(IDirect3DDevice9* pThis, UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer);
typedef HRESULT(STDMETHODCALLTYPE *T_GetRasterStatus)(IDirect3DDevice9* pThis, UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus);
typedef HRESULT(STDMETHODCALLTYPE *T_SetDialogBoxMode)(IDirect3DDevice9* pThis, BOOL bEnableDialogs);
typedef void(	STDMETHODCALLTYPE *T_SetGammaRamp)(IDirect3DDevice9* pThis, UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp);
typedef void(	STDMETHODCALLTYPE *T_GetGammaRamp)(IDirect3DDevice9* pThis, UINT iSwapChain,D3DGAMMARAMP* pRamp);
typedef HRESULT(STDMETHODCALLTYPE *T_CreateTexture)(IDirect3DDevice9* pThis, UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle);
typedef HRESULT(STDMETHODCALLTYPE *T_CreateVolumeTexture)(IDirect3DDevice9* pThis, UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle);
typedef HRESULT(STDMETHODCALLTYPE *T_CreateCubeTexture)(IDirect3DDevice9* pThis, UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle);
typedef HRESULT(STDMETHODCALLTYPE *T_CreateVertexBuffer)(IDirect3DDevice9* pThis, UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle);
typedef HRESULT(STDMETHODCALLTYPE *T_CreateIndexBuffer)(IDirect3DDevice9* pThis, UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle);
typedef HRESULT(STDMETHODCALLTYPE *T_CreateRenderTarget)(IDirect3DDevice9* pThis, UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle);
typedef HRESULT(STDMETHODCALLTYPE *T_CreateDepthStencilSurface)(IDirect3DDevice9* pThis, UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle);
typedef HRESULT(STDMETHODCALLTYPE *T_UpdateSurface)(IDirect3DDevice9* pThis, IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint);
typedef HRESULT(STDMETHODCALLTYPE *T_UpdateTexture)(IDirect3DDevice9* pThis, IDirect3DBaseTexture9* pSourceTexture,IDirect3DBaseTexture9* pDestinationTexture);
typedef HRESULT(STDMETHODCALLTYPE *T_GetRenderTargetData)(IDirect3DDevice9* pThis, IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface);
typedef HRESULT(STDMETHODCALLTYPE *T_GetFrontBufferData)(IDirect3DDevice9* pThis, UINT iSwapChain,IDirect3DSurface9* pDestSurface);
typedef HRESULT(STDMETHODCALLTYPE *T_StretchRect)(IDirect3DDevice9* pThis, IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter);
typedef HRESULT(STDMETHODCALLTYPE *T_ColorFill)(IDirect3DDevice9* pThis, IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color);
typedef HRESULT(STDMETHODCALLTYPE *T_CreateOffscreenPlainSurface)(IDirect3DDevice9* pThis, UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle);
typedef HRESULT(STDMETHODCALLTYPE *T_SetRenderTarget)(IDirect3DDevice9* pThis, DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget);
typedef HRESULT(STDMETHODCALLTYPE *T_GetRenderTarget)(IDirect3DDevice9* pThis, DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget);
typedef HRESULT(STDMETHODCALLTYPE *T_SetDepthStencilSurface)(IDirect3DDevice9* pThis, IDirect3DSurface9* pNewZStencil);
typedef HRESULT(STDMETHODCALLTYPE *T_GetDepthStencilSurface)(IDirect3DDevice9* pThis, IDirect3DSurface9** ppZStencilSurface);
typedef HRESULT(STDMETHODCALLTYPE *T_BeginScene)(IDirect3DDevice9* pThis);
typedef HRESULT(STDMETHODCALLTYPE *T_EndScene)(IDirect3DDevice9* pThis);
typedef HRESULT(STDMETHODCALLTYPE *T_Clear)(IDirect3DDevice9* pThis, DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil);
typedef HRESULT(STDMETHODCALLTYPE *T_SetTransform)(IDirect3DDevice9* pThis, D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix);
typedef HRESULT(STDMETHODCALLTYPE *T_GetTransform)(IDirect3DDevice9* pThis, D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix);
typedef HRESULT(STDMETHODCALLTYPE *T_MultiplyTransform)(IDirect3DDevice9* pThis, D3DTRANSFORMSTATETYPE,CONST D3DMATRIX*);
typedef HRESULT(STDMETHODCALLTYPE *T_SetViewport)(IDirect3DDevice9* pThis, CONST D3DVIEWPORT9* pViewport);
typedef HRESULT(STDMETHODCALLTYPE *T_GetViewport)(IDirect3DDevice9* pThis, D3DVIEWPORT9* pViewport);
typedef HRESULT(STDMETHODCALLTYPE *T_SetMaterial)(IDirect3DDevice9* pThis, CONST D3DMATERIAL9* pMaterial);
typedef HRESULT(STDMETHODCALLTYPE *T_GetMaterial)(IDirect3DDevice9* pThis, D3DMATERIAL9* pMaterial);
typedef HRESULT(STDMETHODCALLTYPE *T_SetLight)(IDirect3DDevice9* pThis, DWORD Index,CONST D3DLIGHT9*);
typedef HRESULT(STDMETHODCALLTYPE *T_GetLight)(IDirect3DDevice9* pThis, DWORD Index,D3DLIGHT9*);
typedef HRESULT(STDMETHODCALLTYPE *T_LightEnable)(IDirect3DDevice9* pThis, DWORD Index,BOOL Enable);
typedef HRESULT(STDMETHODCALLTYPE *T_GetLightEnable)(IDirect3DDevice9* pThis, DWORD Index,BOOL* pEnable);
typedef HRESULT(STDMETHODCALLTYPE *T_SetClipPlane)(IDirect3DDevice9* pThis, DWORD Index,CONST float* pPlane);
typedef HRESULT(STDMETHODCALLTYPE *T_GetClipPlane)(IDirect3DDevice9* pThis, DWORD Index,float* pPlane);
typedef HRESULT(STDMETHODCALLTYPE *T_SetRenderState)(IDirect3DDevice9* pThis, D3DRENDERSTATETYPE State,DWORD Value);
typedef HRESULT(STDMETHODCALLTYPE *T_GetRenderState)(IDirect3DDevice9* pThis, D3DRENDERSTATETYPE State,DWORD* pValue);
typedef HRESULT(STDMETHODCALLTYPE *T_CreateStateBlock)(IDirect3DDevice9* pThis, D3DSTATEBLOCKTYPE Type,IDirect3DStateBlock9** ppSB);
typedef HRESULT(STDMETHODCALLTYPE *T_BeginStateBlock)(IDirect3DDevice9* pThis);
typedef HRESULT(STDMETHODCALLTYPE *T_EndStateBlock)(IDirect3DDevice9* pThis, IDirect3DStateBlock9** ppSB);
typedef HRESULT(STDMETHODCALLTYPE *T_SetClipStatus)(IDirect3DDevice9* pThis, CONST D3DCLIPSTATUS9* pClipStatus);
typedef HRESULT(STDMETHODCALLTYPE *T_GetClipStatus)(IDirect3DDevice9* pThis, D3DCLIPSTATUS9* pClipStatus);
typedef HRESULT(STDMETHODCALLTYPE *T_GetTexture)(IDirect3DDevice9* pThis, DWORD Stage,IDirect3DBaseTexture9** ppTexture);
typedef HRESULT(STDMETHODCALLTYPE *T_SetTexture)(IDirect3DDevice9* pThis, DWORD Stage,IDirect3DBaseTexture9* pTexture);
typedef HRESULT(STDMETHODCALLTYPE *T_GetTextureStageState)(IDirect3DDevice9* pThis, DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue);
typedef HRESULT(STDMETHODCALLTYPE *T_SetTextureStageState)(IDirect3DDevice9* pThis, DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value);
typedef HRESULT(STDMETHODCALLTYPE *T_GetSamplerState)(IDirect3DDevice9* pThis, DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue);
typedef HRESULT(STDMETHODCALLTYPE *T_SetSamplerState)(IDirect3DDevice9* pThis, DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value);
typedef HRESULT(STDMETHODCALLTYPE *T_ValidateDevice)(IDirect3DDevice9* pThis, DWORD* pNumPasses);
typedef HRESULT(STDMETHODCALLTYPE *T_SetPaletteEntries)(IDirect3DDevice9* pThis, UINT PaletteNumber,CONST PALETTEENTRY* pEntries);
typedef HRESULT(STDMETHODCALLTYPE *T_GetPaletteEntries)(IDirect3DDevice9* pThis, UINT PaletteNumber,PALETTEENTRY* pEntries);
typedef HRESULT(STDMETHODCALLTYPE *T_SetCurrentTexturePalette)(IDirect3DDevice9* pThis, UINT PaletteNumber);
typedef HRESULT(STDMETHODCALLTYPE *T_GetCurrentTexturePalette)(IDirect3DDevice9* pThis, UINT *PaletteNumber);
typedef HRESULT(STDMETHODCALLTYPE *T_SetScissorRect)(IDirect3DDevice9* pThis, CONST RECT* pRect);
typedef HRESULT(STDMETHODCALLTYPE *T_GetScissorRect)(IDirect3DDevice9* pThis, RECT* pRect);
typedef HRESULT(STDMETHODCALLTYPE *T_SetSoftwareVertexProcessing)(IDirect3DDevice9* pThis, BOOL bSoftware);
typedef BOOL(	STDMETHODCALLTYPE *T_GetSoftwareVertexProcessing)(IDirect3DDevice9* pThis);
typedef HRESULT(STDMETHODCALLTYPE *T_SetNPatchMode)(IDirect3DDevice9* pThis, float nSegments);
typedef float(	STDMETHODCALLTYPE *T_GetNPatchMode)(IDirect3DDevice9* pThis);
typedef HRESULT(STDMETHODCALLTYPE *T_DrawPrimitive)(IDirect3DDevice9* pThis, D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount);
typedef HRESULT(STDMETHODCALLTYPE *T_DrawIndexedPrimitive)(IDirect3DDevice9* pThis, D3DPRIMITIVETYPE PrimitiveType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount);
typedef HRESULT(STDMETHODCALLTYPE *T_DrawPrimitiveUP)(IDirect3DDevice9* pThis, D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride);
typedef HRESULT(STDMETHODCALLTYPE *T_DrawIndexedPrimitiveUP)(IDirect3DDevice9* pThis, D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride);
typedef HRESULT(STDMETHODCALLTYPE *T_ProcessVertices)(IDirect3DDevice9* pThis, UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags);
typedef HRESULT(STDMETHODCALLTYPE *T_CreateVertexDeclaration)(IDirect3DDevice9* pThis, CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl);
typedef HRESULT(STDMETHODCALLTYPE *T_SetVertexDeclaration)(IDirect3DDevice9* pThis, IDirect3DVertexDeclaration9* pDecl);
typedef HRESULT(STDMETHODCALLTYPE *T_GetVertexDeclaration)(IDirect3DDevice9* pThis, IDirect3DVertexDeclaration9** ppDecl);
typedef HRESULT(STDMETHODCALLTYPE *T_SetFVF)(IDirect3DDevice9* pThis, DWORD FVF);
typedef HRESULT(STDMETHODCALLTYPE *T_GetFVF)(IDirect3DDevice9* pThis, DWORD* pFVF);
typedef HRESULT(STDMETHODCALLTYPE *T_CreateVertexShader)(IDirect3DDevice9* pThis, CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader);
typedef HRESULT(STDMETHODCALLTYPE *T_SetVertexShader)(IDirect3DDevice9* pThis, IDirect3DVertexShader9* pShader);
typedef HRESULT(STDMETHODCALLTYPE *T_GetVertexShader)(IDirect3DDevice9* pThis, IDirect3DVertexShader9** ppShader);
typedef HRESULT(STDMETHODCALLTYPE *T_SetVertexShaderConstantF)(IDirect3DDevice9* pThis, UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount);
typedef HRESULT(STDMETHODCALLTYPE *T_GetVertexShaderConstantF)(IDirect3DDevice9* pThis, UINT StartRegister,float* pConstantData,UINT Vector4fCount);
typedef HRESULT(STDMETHODCALLTYPE *T_SetVertexShaderConstantI)(IDirect3DDevice9* pThis, UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount);
typedef HRESULT(STDMETHODCALLTYPE *T_GetVertexShaderConstantI)(IDirect3DDevice9* pThis, UINT StartRegister,int* pConstantData,UINT Vector4iCount);
typedef HRESULT(STDMETHODCALLTYPE *T_SetVertexShaderConstantB)(IDirect3DDevice9* pThis, UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount);
typedef HRESULT(STDMETHODCALLTYPE *T_GetVertexShaderConstantB)(IDirect3DDevice9* pThis, UINT StartRegister,BOOL* pConstantData,UINT BoolCount);
typedef HRESULT(STDMETHODCALLTYPE *T_SetStreamSource)(IDirect3DDevice9* pThis, UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride);
typedef HRESULT(STDMETHODCALLTYPE *T_GetStreamSource)(IDirect3DDevice9* pThis, UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* pOffsetInBytes,UINT* pStride);
typedef HRESULT(STDMETHODCALLTYPE *T_SetStreamSourceFreq)(IDirect3DDevice9* pThis, UINT StreamNumber,UINT Setting);
typedef HRESULT(STDMETHODCALLTYPE *T_GetStreamSourceFreq)(IDirect3DDevice9* pThis, UINT StreamNumber,UINT* pSetting);
typedef HRESULT(STDMETHODCALLTYPE *T_SetIndices)(IDirect3DDevice9* pThis, IDirect3DIndexBuffer9* pIndexData);
typedef HRESULT(STDMETHODCALLTYPE *T_GetIndices)(IDirect3DDevice9* pThis, IDirect3DIndexBuffer9** ppIndexData);
typedef HRESULT(STDMETHODCALLTYPE *T_CreatePixelShader)(IDirect3DDevice9* pThis, CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader);
typedef HRESULT(STDMETHODCALLTYPE *T_SetPixelShader)(IDirect3DDevice9* pThis, IDirect3DPixelShader9* pShader);
typedef HRESULT(STDMETHODCALLTYPE *T_GetPixelShader)(IDirect3DDevice9* pThis, IDirect3DPixelShader9** ppShader);
typedef HRESULT(STDMETHODCALLTYPE *T_SetPixelShaderConstantF)(IDirect3DDevice9* pThis, UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount);
typedef HRESULT(STDMETHODCALLTYPE *T_GetPixelShaderConstantF)(IDirect3DDevice9* pThis, UINT StartRegister,float* pConstantData,UINT Vector4fCount);
typedef HRESULT(STDMETHODCALLTYPE *T_SetPixelShaderConstantI)(IDirect3DDevice9* pThis, UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount);
typedef HRESULT(STDMETHODCALLTYPE *T_GetPixelShaderConstantI)(IDirect3DDevice9* pThis, UINT StartRegister,int* pConstantData,UINT Vector4iCount);
typedef HRESULT(STDMETHODCALLTYPE *T_SetPixelShaderConstantB)(IDirect3DDevice9* pThis, UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount);
typedef HRESULT(STDMETHODCALLTYPE *T_GetPixelShaderConstantB)(IDirect3DDevice9* pThis, UINT StartRegister,BOOL* pConstantData,UINT BoolCount);
typedef HRESULT(STDMETHODCALLTYPE *T_DrawRectPatch)(IDirect3DDevice9* pThis, UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo);
typedef HRESULT(STDMETHODCALLTYPE *T_DrawTriPatch)(IDirect3DDevice9* pThis, UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo);
typedef HRESULT(STDMETHODCALLTYPE *T_DeletePatch)(IDirect3DDevice9* pThis, UINT Handle);
typedef HRESULT(STDMETHODCALLTYPE *T_CreateQuery)(IDirect3DDevice9* pThis, D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery);


typedef	HRESULT	(STDMETHODCALLTYPE *T_SwapChain_Present)(IDirect3DSwapChain9*	pThis,CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Surface_LockRect)(IDirect3DSurface9*	pThis,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Surface_UnlockRect)(IDirect3DSurface9*	pThis);
typedef	HRESULT (STDMETHODCALLTYPE *T_Volume_LockBox)(IDirect3DVolume9*	pThis,D3DLOCKED_BOX * pLockedVolume,CONST D3DBOX* pBox,DWORD Flags);
typedef	HRESULT (STDMETHODCALLTYPE *T_Volume_UnlockBox)(IDirect3DVolume9*	pThis);
typedef	HRESULT	(STDMETHODCALLTYPE *T_VertexBuffer_Lock)(IDirect3DVertexBuffer9*	pThis,UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags);
typedef	HRESULT	(STDMETHODCALLTYPE *T_VertexBuffer_Unlock)(IDirect3DVertexBuffer9*	pThis);
typedef	HRESULT	(STDMETHODCALLTYPE *T_IndexBuffer_Lock)(IDirect3DIndexBuffer9*	pThis,UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags);
typedef	HRESULT	(STDMETHODCALLTYPE *T_IndexBuffer_Unlock)(IDirect3DIndexBuffer9*	pThis);
typedef	HRESULT	(STDMETHODCALLTYPE *T_BaseTexture_SetAutoGenFilterType)(IDirect3DBaseTexture9*	pThis,D3DTEXTUREFILTERTYPE FilterType);
typedef	HRESULT	(STDMETHODCALLTYPE *T_BaseTexture_GenerateMipSubLevels)(IDirect3DBaseTexture9*	pThis);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Texture_LockRect)(IDirect3DTexture9*	pThis,UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Texture_UnLockRect)(IDirect3DTexture9*	pThis,UINT Level);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Texture_AddDirtyRect)(IDirect3DTexture9*	pThis,CONST RECT* pDirtyRect);
typedef	HRESULT	(STDMETHODCALLTYPE *T_CubeTexture_LockRect)(IDirect3DCubeTexture9*	pThis,D3DCUBEMAP_FACES FaceType,UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags);
typedef	HRESULT	(STDMETHODCALLTYPE *T_CubeTexture_UnlockRect)(IDirect3DCubeTexture9*	pThis,D3DCUBEMAP_FACES FaceType,UINT Level);
typedef	HRESULT	(STDMETHODCALLTYPE *T_CubeTexture_AddDirtyRect)(IDirect3DCubeTexture9*	pThis,D3DCUBEMAP_FACES FaceType,CONST RECT* pDirtyRect);
typedef	HRESULT	(STDMETHODCALLTYPE *T_VolumeTexture_LockBox)(IDirect3DVolumeTexture9*	pThis,UINT Level,D3DLOCKED_BOX* pLockedVolume,CONST D3DBOX* pBox,DWORD Flags);
typedef	HRESULT	(STDMETHODCALLTYPE *T_VolumeTexture_UnlockBox)(IDirect3DVolumeTexture9*	pThis,UINT Level);
typedef	HRESULT	(STDMETHODCALLTYPE *T_VolumeTexture_AddDirtyBox)(IDirect3DVolumeTexture9*	pThis,CONST D3DBOX* pDirtyBox);
typedef	HRESULT	(STDMETHODCALLTYPE *T_StateBlock_Apply)(IDirect3DStateBlock9* pThis);
typedef	HRESULT	(STDMETHODCALLTYPE *T_StateBlock_Capture)(IDirect3DStateBlock9* pThis);


typedef int		(	WINAPI *T_D3DPERF_BeginEvent)	(	D3DCOLOR col, LPCWSTR wszName	);
typedef int		(	WINAPI *T_D3DPERF_EndEvent)		(	void							);
typedef void	(	WINAPI *T_D3DPERF_SetMarker)	(	D3DCOLOR col, LPCWSTR wszName	);

typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_SetValue)(ID3DXEffect* pThis, D3DXHANDLE hParameter, LPCVOID pData, UINT Bytes);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_SetBool)(ID3DXEffect* pThis, D3DXHANDLE hParameter, BOOL b);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_SetBoolArray)(ID3DXEffect* pThis, D3DXHANDLE hParameter, CONST BOOL* pb, UINT Count);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_SetInt)(ID3DXEffect* pThis, D3DXHANDLE hParameter, INT n);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_SetIntArray)(ID3DXEffect* pThis, D3DXHANDLE hParameter, CONST INT* pn, UINT Count);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_SetFloat)(ID3DXEffect* pThis, D3DXHANDLE hParameter, FLOAT f);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_SetFloatArray)(ID3DXEffect* pThis, D3DXHANDLE hParameter, CONST FLOAT* pf, UINT Count);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_SetVector)(ID3DXEffect* pThis, D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_SetVectorArray)(ID3DXEffect* pThis, D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector, UINT Count);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_SetMatrix)(ID3DXEffect* pThis, D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_SetMatrixArray)(ID3DXEffect* pThis, D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_SetMatrixPointerArray)(ID3DXEffect* pThis, D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_SetMatrixTranspose)(ID3DXEffect* pThis, D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_SetMatrixTransposeArray)(ID3DXEffect* pThis, D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_SetMatrixTransposePointerArray)(ID3DXEffect* pThis, D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_SetString)(ID3DXEffect* pThis, D3DXHANDLE hParameter, LPCSTR pString);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_SetTexture)(ID3DXEffect* pThis, D3DXHANDLE hParameter, LPDIRECT3DBASETEXTURE9 pTexture);

typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_SetTechnique)(ID3DXEffect* pThis, D3DXHANDLE hTechnique);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_Begin)(ID3DXEffect* pThis, UINT *pPasses, DWORD Flags) ;
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_BeginPass)(ID3DXEffect* pThis, UINT Pass) ;
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_CommitChanges)(ID3DXEffect* pThis) ;
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_EndPass)(ID3DXEffect* pThis) ;
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_End)(ID3DXEffect* pThis) ;
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_SetStateManager)(ID3DXEffect* pThis, LPD3DXEFFECTSTATEMANAGER pManager);
typedef	HRESULT	(STDMETHODCALLTYPE *T_Effect_SetRawValue)(ID3DXEffect* pThis, D3DXHANDLE hParameter, LPCVOID pData, UINT ByteOffset, UINT Bytes);

struct CmdSetCursorProperties{
	UINT				XHotSpot;
	UINT				YHotSpot;
	IDirect3DSurface9*	pCursorBitmap;
};
struct CmdSetCursorPosition{
	int					X;
	int					Y;
	DWORD				Flags;
};
struct CmdPresent{
	CONST	RECT*		pSourceRect;
	CONST	RECT*		pDestRect;
	HWND				hDestWindowOverride;
	CONST	RGNDATA*	pDirtyRegion;
	RECT				src;
	RECT				dst;
	RGNDATA				dirty;
};
typedef	BOOL	CmdSetDialogBoxMode;
struct CmdSetGammaRamp{
	UINT iSwapChain;
	DWORD Flags;
	D3DGAMMARAMP pRamp;
};
struct CmdUpdateSurface{
	IDirect3DSurface9*	pSourceSurface;
	CONST	RECT*		pSourceRect;
	IDirect3DSurface9*	pDestinationSurface;
	CONST	POINT*		pDestPoint;
	RECT				src;
	POINT				dst;
};
struct CmdUpdateTexture{
	IDirect3DBaseTexture9* pSourceTexture;
	IDirect3DBaseTexture9* pDestinationTexture;
};
struct CmdStretchRect{
	IDirect3DSurface9* pSourceSurface;
	CONST	RECT* pSourceRect;
	IDirect3DSurface9* pDestSurface;
	CONST	RECT* pDestRect;
	D3DTEXTUREFILTERTYPE Filter;
	RECT	src;
	RECT	dst;
};
struct CmdColorFill{
	IDirect3DSurface9*	pSurface;
	CONST	RECT* 		pRect;
	D3DCOLOR			color;
	RECT				src;
};
struct CmdSetRenderTarget{
	DWORD				RenderTargetIndex;
	IDirect3DSurface9*	pRenderTarget;
};
struct CmdSetDepthStencilSurface{
	IDirect3DSurface9* pNewZStencil;
};
struct CmdClear{
	DWORD				Count;
	CONST	D3DRECT*	pRects;
	DWORD				Flags;
	D3DCOLOR			Color;
	float				Z;
	DWORD				Stencil;
};
struct CmdSetTransform{
	D3DTRANSFORMSTATETYPE	State;
	D3DMATRIX				pMatrix;
};
struct CmdMultiplyTransform{
	D3DTRANSFORMSTATETYPE	type;
	D3DMATRIX*				pMatrix;
};
typedef	D3DVIEWPORT9	CmdSetViewport;
typedef	D3DMATERIAL9	CmdSetMaterial;
struct CmdSetLight{
	DWORD		Index;
	D3DLIGHT9	Light;
};
struct CmdLightEnable{
	DWORD Index;
	BOOL Enable;
};
struct CmdSetClipPlane{
	DWORD Index;
	float pPlane[4];
};
struct CmdSetRenderState{
	D3DRENDERSTATETYPE State;
	DWORD Value;
};
typedef	IDirect3DStateBlock9**	CmdEndStateBlock;
typedef	D3DCLIPSTATUS9			CmdSetClipStatus;
struct CmdSetTexture{
	DWORD Stage;
	IDirect3DBaseTexture9* pTexture;
};
struct CmdSetTextureStageState{
	DWORD Stage;
	D3DTEXTURESTAGESTATETYPE Type;
	DWORD Value;
};
struct CmdSetSamplerState{
	DWORD Sampler;
	D3DSAMPLERSTATETYPE Type;
	DWORD Value;
};
struct CmdSetPaletteEntries{
	UINT					PaletteNumber;
	CONST	PALETTEENTRY*	pEntries;
};
typedef	UINT	CmdSetCurrentTexturePalette;
typedef	RECT	CmdSetScissorRect;
typedef	BOOL	CmdSetSoftwareVertexProcessing;
typedef	float	CmdSetNPatchMode;
struct	CmdDrawPrimitive{
	D3DPRIMITIVETYPE PrimitiveType;
	UINT StartVertex;
	UINT PrimitiveCount;
};
struct CmdDrawIndexedPrimitive{
	D3DPRIMITIVETYPE	PrimitiveType;
	INT BaseVertexIndex;
	UINT MinVertexIndex;
	UINT NumVertices;
	UINT startIndex;
	UINT primCount;
};
struct CmdDrawPrimitiveUP{
	D3DPRIMITIVETYPE PrimitiveType;
	UINT PrimitiveCount;
	//CONST void* pVertexStreamZeroData;
	UINT VertexStreamZeroStride;
};
struct CmdDrawIndexedPrimitiveUP{
	D3DPRIMITIVETYPE PrimitiveType;
	UINT MinVertexIndex;
	UINT NumVertices;
	UINT PrimitiveCount;
	//CONST void* pIndexData;
	D3DFORMAT IndexDataFormat;
	//CONST void* pVertexStreamZeroData;
	UINT VertexStreamZeroStride;
};
struct CmdProcessVertices{
	UINT SrcStartIndex;
	UINT DestIndex;
	UINT VertexCount;
	IDirect3DVertexBuffer9* pDestBuffer;
	IDirect3DVertexDeclaration9* pVertexDecl;
	DWORD Flags;
};
typedef	IDirect3DVertexDeclaration9* CmdSetVertexDeclaration;
typedef	DWORD	CmdSetFVF;
typedef	IDirect3DVertexShader9*	CmdSetVertexShader;
struct CmdSetVertexShaderConstantF{
	UINT StartRegister;
	//CONST float* pConstantData;
	UINT Vector4fCount;
};
struct CmdSetVertexShaderConstantI{
	UINT StartRegister;
	//CONST int* pConstantData;
	UINT Vector4iCount;
};
struct CmdSetVertexShaderConstantB{
	UINT StartRegister;
	//CONST BOOL* pConstantData;
	UINT  BoolCount;
};
struct CmdSetStreamSource{
	UINT StreamNumber;
	IDirect3DVertexBuffer9* pStreamData;
	UINT OffsetInBytes;
	UINT Stride;
};
struct CmdSetStreamSourceFreq{
	UINT StreamNumber;
	UINT Setting;
};
typedef	IDirect3DIndexBuffer9*	CmdSetIndices;
typedef	IDirect3DPixelShader9*	CmdSetPixelShader;

typedef	CmdSetVertexShaderConstantF	CmdSetPixelShaderConstantF;
typedef	CmdSetVertexShaderConstantI	CmdSetPixelShaderConstantI;
typedef	CmdSetVertexShaderConstantB	CmdSetPixelShaderConstantB;
struct CmdDrawRectPatch{
	UINT Handle;
	//CONST float* pNumSegs;
	D3DRECTPATCH_INFO pRectPatchInfo;
};
struct CmdDrawTriPatch{
	UINT Handle;
	//CONST float* pNumSegs;
	D3DTRIPATCH_INFO pTriPatchInfo;
};
typedef	UINT CmdDeletePatch;
struct CmdSwapChain_Present{
	IDirect3DSwapChain9*	pSwapChain;
	CONST RECT* pSourceRect;
	CONST RECT* pDestRect;
	HWND hDestWindowOverride;
	CONST RGNDATA* pDirtyRegion;
	DWORD dwFlags;
	RECT	src;
	RECT	dst;
	RGNDATA	dirty;
};
struct CmdSurface_LockRect{
	IDirect3DSurface9*	pSurface;
	CONST RECT*	pRect;
	DWORD	Flags;
	RECT	rData;
	DWORD	dwLockSize;	///<	Save Lock Size
};
typedef	IDirect3DSurface9*	CmdSurface_UnlockRect;
struct CmdVolume_LockBox{
	IDirect3DVolume9*	pVolume;
	//D3DLOCKED_BOX * pLockedVolume;
	CONST D3DBOX* pBox;
	DWORD	Flags;
	D3DBOX	boxData;
	DWORD	dwLockSize;	///<	Save Lock Size
};
typedef	IDirect3DVolume9*	CmdVolume_UnlockBox;
struct CmdVertexBuffer_Lock{
	IDirect3DVertexBuffer9*	pVB;
	UINT OffsetToLock;
	UINT SizeToLock;
	//void** ppbData;
	DWORD Flags;
};
typedef	IDirect3DVertexBuffer9*	CmdVertexBuffer_Unlock;
struct CmdIndexBuffer_Lock{
	IDirect3DIndexBuffer9*	pIB;
	UINT OffsetToLock;
	UINT SizeToLock;
	//void** ppbData;
	DWORD Flags;
};
typedef	IDirect3DIndexBuffer9*	CmdIndexBuffer_Unlock;
struct CmdBaseTexture_SetAutoGenFilterType{
	IDirect3DBaseTexture9*	pTex;
	D3DTEXTUREFILTERTYPE FilterType;
};
typedef	IDirect3DBaseTexture9* CmdBaseTexture_GenerateMipSubLevels;
struct CmdTexture_LockRect{
	IDirect3DTexture9*	pTex;
	UINT Level;
	//D3DLOCKED_RECT* pLockedRect;
	CONST RECT*	pRect;
	DWORD	Flags;
	RECT	rData;
	DWORD	dwLockSize;		///<Save Lock	Size
};
struct CmdTexture_UnlockRect{
	IDirect3DTexture9*	pTex;
	UINT Level;
};
struct CmdTexture_AddDirtyRect{
	IDirect3DTexture9*	pTex;
	RECT pDirtyRect;
};
struct CmdCubeTexture_LockRect{
	IDirect3DCubeTexture9*	pCubeTex;
	D3DCUBEMAP_FACES FaceType;
	UINT Level;
	//D3DLOCKED_RECT* pLockedRect;
	CONST RECT*	pRect;
	DWORD	Flags;
	RECT	rData;
	DWORD	dwLockSize;		///<Save Lock	Size
};
struct CmdCubeTexture_UnlockRect{
	IDirect3DCubeTexture9*	pCubeTex;
	D3DCUBEMAP_FACES FaceType;
	UINT Level;
};
struct CmdCubeTexture_AddDirtyRect{
	IDirect3DCubeTexture9*	pCubeTex;
	D3DCUBEMAP_FACES		FaceType;
	RECT					pDirtyRect;
};
struct CmdVolumeTexture_LockBox{
	IDirect3DVolumeTexture9*	pVolumeTex;
	UINT Level;
	//D3DLOCKED_BOX* pLockedVolume;
	CONST D3DBOX* pBox;
	DWORD	Flags;
	D3DBOX	boxData;
	DWORD	dwLockSize;		///<Save Lock	Size
};
struct CmdVolumeTexture_UnlockBox{
	IDirect3DVolumeTexture9*	pVolumeTex;
	UINT Level;
};
struct CmdVolumeTexture_AddDirtyBox{
	IDirect3DVolumeTexture9*	pVolumeTex;
	D3DBOX						pDirtyBox;
};
typedef	IDirect3DStateBlock9* CmdStateBlock_Apply;
typedef	IDirect3DStateBlock9* CmdStateBlock_Capture;

struct CmdPIX_D3DPERF_BeginEvent{
	D3DCOLOR col;
	//LPCWSTR wszName
	DWORD		dwNameSize;	///<	Save Size
};

struct CmdPIX_D3DPERF_SetMarker{
	D3DCOLOR col;
	//LPCWSTR wszName
	DWORD		dwNameSize;	///<	Save Size
};

struct CmdEffect_SetValue{
	ID3DXEffect* pID3DXEffect; 
	D3DXHANDLE hParameter; 
	//LPCVOID pData; 
	UINT Bytes;
};
struct CmdEffect_SetBool{
	ID3DXEffect* pID3DXEffect; 
	D3DXHANDLE hParameter; 
	BOOL b;
};
struct CmdEffect_SetBoolArray{
	ID3DXEffect* pID3DXEffect; 
	D3DXHANDLE hParameter; 
	//CONST BOOL* pb; 
	UINT Count;
};
struct CmdEffect_SetInt{
	ID3DXEffect* pID3DXEffect; 
	D3DXHANDLE hParameter; 
	INT n;
};
struct CmdEffect_SetIntArray{
	ID3DXEffect* pID3DXEffect;
	D3DXHANDLE hParameter; 
	//CONST INT* pn; 
	UINT Count;
};
struct CmdEffect_SetFloat{
	ID3DXEffect* pID3DXEffect; 
	D3DXHANDLE hParameter; 
	FLOAT f;
};
struct CmdEffect_SetFloatArray{
	ID3DXEffect* pID3DXEffect; 
	D3DXHANDLE hParameter; 
	//CONST FLOAT* pf; 
	UINT Count;
};
struct CmdEffect_SetVector{
	ID3DXEffect* pID3DXEffect; 
	D3DXHANDLE hParameter; 
	D3DXVECTOR4 pVector;
};
struct CmdEffect_SetVectorArray{
	ID3DXEffect* pID3DXEffect; 
	D3DXHANDLE hParameter; 
	//CONST D3DXVECTOR4* pVector; 
	UINT Count;
};
struct CmdEffect_SetMatrix{
	ID3DXEffect* pID3DXEffect; 
	D3DXHANDLE hParameter; 
	D3DXMATRIX pMatrix;
};
struct CmdEffect_SetMatrixArray{
	ID3DXEffect* pID3DXEffect; 
	D3DXHANDLE hParameter; 
	//CONST D3DXMATRIX* pMatrix; 
	UINT Count;
};
struct CmdEffect_SetMatrixPointerArray{
	ID3DXEffect* pID3DXEffect; 
	D3DXHANDLE hParameter; 
	CONST D3DXMATRIX** ppMatrix; 
	UINT Count;
};
struct CmdEffect_SetMatrixTranspose{
	ID3DXEffect* pID3DXEffect; 
	D3DXHANDLE hParameter; 
	D3DXMATRIX pMatrix;
};
struct CmdEffect_SetMatrixTransposeArray{
	ID3DXEffect* pID3DXEffect; 
	D3DXHANDLE hParameter; 
	//CONST D3DXMATRIX* pMatrix; 
	UINT Count;
};
struct CmdEffect_SetMatrixTransposePointerArray{
	ID3DXEffect* pID3DXEffect; 
	D3DXHANDLE hParameter; 
	CONST D3DXMATRIX** ppMatrix; 
	UINT Count;
};
struct CmdEffect_SetString{
	ID3DXEffect* pID3DXEffect; 
	D3DXHANDLE hParameter; 
	//LPCSTR pString;
	UINT	uiBufferSize;
};
struct CmdEffect_SetTexture{
	ID3DXEffect* pID3DXEffect; 
	D3DXHANDLE hParameter; 
	LPDIRECT3DBASETEXTURE9 pTexture;
};
struct CmdEffect_SetTechnique{
	ID3DXEffect* pID3DXEffect; 
	D3DXHANDLE hTechnique;
};
struct CmdEffect_Begin{
	ID3DXEffect* pID3DXEffect; 
	//UINT *pPasses; 
	DWORD Flags;
};
struct CmdEffect_BeginPass{
	ID3DXEffect* pID3DXEffect; 
	UINT Pass;
};
typedef	ID3DXEffect*	CmdEffect_CommitChanges;
typedef ID3DXEffect*	CmdEffect_EndPass;
typedef ID3DXEffect*	CmdEffect_End;
struct CmdEffect_SetStateManager{
	ID3DXEffect* pID3DXEffect; 
	LPD3DXEFFECTSTATEMANAGER pManager;
};
struct CmdEffect_SetRawValue{
	ID3DXEffect* pID3DXEffect; 
	D3DXHANDLE hParameter; 
	//LPCVOID pData; 
	UINT ByteOffset; 
	UINT Bytes;
};
#endif