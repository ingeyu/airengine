#ifndef MTHEADER_HEAD_FILE
#define MTHEADER_HEAD_FILE

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <string>

typedef	std::string		AString;
typedef	const AString	CAString;
typedef	unsigned char	U8;
typedef	unsigned int	U32;


class MT_IUnknown
{
public:
	MT_IUnknown(){
		uiRef	=	0;
	};
	virtual	~MT_IUnknown()=0;
    virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject) = 0;

	virtual ULONG STDMETHODCALLTYPE AddRef( void){
		InterlockedIncrement(&uiRef);
		return	uiRef;
	};

	virtual ULONG STDMETHODCALLTYPE Release( void){
		InterlockedDecrement(&uiRef);
		if(uiRef==0){
			delete this;
		}
		return	uiRef;
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
typedef	MT_IDirect3DDevice9*		MT_LPDIRECT3DDEVICE9;
typedef	MT_IDirect3DSurface9*		MT_LPDIRECT3DSURFACE9;
typedef	MT_IDirect3DTexture9*		MT_LPDIRECT3DTEXTURE9;
typedef	MT_IDirect3DCubeTexture9*	MT_LPDIRECT3DCUBETEXTURE9;
typedef	MT_IDirect3DVolumeTexture9*	MT_LPDIRECT3DVOLUMETEXTURE9;

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
};

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
#endif