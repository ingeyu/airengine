//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InterfalHell	Xinhe
 \date      2010/04/02
 \version   ver 0.4.0.0
 \filepath  f:\tj.src\Client0400\Render
 \filename  RenderHeader.h
 \note     
       
 \attention:
			DirectXÍ·ÎÄ¼þ
 \remarks    created by InterfalHell version 0.4.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/

#ifndef RENDERHEADER_HEAD_FILE
#define RENDERHEADER_HEAD_FILE



#include "AirEngineHeader.h"




#include "d3d11.h"
#include "d3dx11.h"
#include "DxErr.h"
#include "DXGI.h"
#include "DXGIFormat.h"
#include "DXGIType.h"

#include "d3d9.h"
//#include "dxerr9.h"

#include "AirGlobalSetting.h"
#include "AirEngineSystem.h"
#include "AirRenderCommon.h"
#include "AirRenderSystem.h"
#include "AirInterfaceResourceSystem.h"






#ifndef	RENDER_LOG_INFO
#define RENDER_LOG_INFO	LOG_INFO(Render)
#endif

//#ifndef		DX10APPLICATION


#define		DxD				IDirect3D9
#define		DxDevice		ID3D11Device
#define		DxContext		ID3D11DeviceContext
#define		DxTexture		ID3D11Texture2D
#define		DxBaseTexture	ID3D11Texture2D
#define		DxVolumeTexture	ID3D11Texture3D
#define		DxCubeTexture	ID3D11Texture2D
#define		DxEffect		ID3DXEffect
#define		DxFont			ID3DXFont
#define		DxVertexBuff	ID3D11Buffer
#define		DxIndexBuff		ID3D11Buffer
#define		DxVertexDeclare	ID3D11InputLayout
#define		DxSurface		ID3D11ShaderResourceView
#define		DxSurfaceDesc	
#define		DxMesh			ID3DXMesh
#define		DxVector3		D3DXVECTOR3
#define		DxVector2		D3DXVECTOR2
#define		DxVector4		D3DXVECTOR4
#define		DxMatrix		D3DXMATRIX
#define		DxQuat			D3DXQUATERNION
#define		DxLight			D3DLIGHT9
#define		DxResult		HRESULT
#define		DxElement		
#define		DxBuffer		ID3D11Buffer
#define		DxFormat		DXGI_FORMAT
#define		DxPool			D3DPOOL
#define		DxFontDesc		D3DXFONT_DESCA
#define		DxPlane			D3DXPLANE
#define		DxViewport		D3DVIEWPORT9
#define		DxCaps			D3DCAPS9
#define		DxHandle		D3DXHANDLE
#define		DxPrimitiveType	D3D11_PRIMITIVE_TOPOLOGY
#define		DxVertexShader	ID3D11VertexShader
#define		DxPixelShader	ID3D11PixelShader
#define		DxSwapChain		IDXGISwapChain
#define		DxFactory		IDXGIFactory
#define		DxAdapter		IDXGIAdapter

#define		DxFactory1		IDXGIFactory1
#define		DxAdapter1		IDXGIAdapter1

#define		DxSRV			ID3D11ShaderResourceView
#define		DxRTV			ID3D11RenderTargetView
#define		DxUAV			ID3D11UnorderedAccessView
#define		DxDSV			ID3D11DepthStencilView




#define IDC_JOINGAME			20
#define IDC_CREATEGAME			21
#define IDC_SURE				22
#define IDC_PLAYERID			23
#define IDC_ROOMLIST			24
// #define IDC_QUITGAME			25
// #define IDC_CINTINUE			26
#define IDC_BELIEVE				27
#define IDC_UNBELIEVE			28
#define IDC_PLAYER				29
#define IDC_ROLE				30
#define IDC_PLAYERNAME			31
//#define IDC_UNSURE				32
#define IDC_DIESTAIC			36
#define IDC_QUITSTAIC			33
#define IDC_QUITSURE			34
#define IDC_QUITUNSURE			35
#define IDC_OUTLINESTAIC		37
#define IDC_OUTLINESURE			38
#define IDC_QUITGAME			39
#define IDC_EDITOR				40
#define IDC_CREATEGAMEFACE		41
#define IDC_GAME				42
#define IDC_CENTER				43


template<typename T>
void	TRelease(void*&	pProduct){
	if(pProduct!=NULL){
		T*	p	=	(T*)pProduct;
		p->Release();
		pProduct	=	NULL;
	}
}
//uaternion

// #else
// 
// 
// 
// #endif
namespace Air{
	
	namespace Engine{
	
		namespace	Render{


	
		}
	
	};
};

#ifndef RENDER_DEBUG_INFO
#define RENDER_DEBUG_INFO(hr)	\
	AChar StringBuff[MAX_NAME];\
	sprintf_s(StringBuff,MAX_NAME,"Info[%s] File[%s] Function[%s] Line[%d]\n",DXGetErrorDescriptionA(hr),__FILE__,__FUNCTION__,__LINE__);\
	RenderLogError(__FUNCTION__,StringBuff);\
	OutputDebugStringA(StringBuff);
	
#endif

#endif // RENDERHEADER_HEAD_FILE