//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InterfalHell	Xinhe
 \date      2010/04/02
 \version   ver 0.4.0.0
 \filepath  f:\tj.src\Client0400\Render
 \filename  RenderHeader.h
 \note     
       
 \attention:
			DirectX头文件
 \remarks    created by InterfalHell version 0.4.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/

#ifndef RENDERHEADER_HEAD_FILE
#define RENDERHEADER_HEAD_FILE



#include "AirEngineHeader.h"


#ifdef	_DEBUG
//打开调试信息
#define D3D_DEBUG_INFO
#endif

#include "d3d9.h"
#include "d3dx9.h"
#include "DxErr.h"
//#include "dxerr9.h"

#include "AirGlobalSetting.h"
#include "AirEngineSystem.h"
#include "AirInterfaceRenderCommon.h"
#include "AirInterfaceRenderSystem.h"
#include "AirInterfaceResourceSystem.h"






#ifndef	RENDER_LOG_INFO
#define RENDER_LOG_INFO	LOG_INFO(Render)
#endif

//#ifndef		DX10APPLICATION


#define		DxD				IDirect3D9
#define		DxDevice		IDirect3DDevice9
#define		DxTexture		IDirect3DTexture9
#define		DxBaseTexture	IDirect3DBaseTexture9
#define		DxVolumeTexture	IDirect3DVolumeTexture9
#define		DxCubeTexture	IDirect3DCubeTexture9
#define		DxEffect		ID3DXEffect
#define		DxFont			ID3DXFont
#define		DxVertexBuff	IDirect3DVertexBuffer9
#define		DxIndexBuff		IDirect3DIndexBuffer9
#define		DxVertexDeclare	IDirect3DVertexDeclaration9
#define		DxSurface		IDirect3DSurface9
#define		DxSurfaceDesc	D3DSURFACE_DESC
#define		DxMesh			ID3DXMesh
#define		DxVector3		D3DXVECTOR3
#define		DxVector2		D3DXVECTOR2
#define		DxVector4		D3DXVECTOR4
#define		DxMatrix		D3DXMATRIX
#define		DxQuat			D3DXQUATERNION
#define		DxLight			D3DLIGHT9
#define		DxResult		HRESULT
#define		DxElement		D3DVERTEXELEMENT9
#define		DxBuffer		ID3DXBuffer
#define		DxFormat		D3DFORMAT
#define		DxPool			D3DPOOL
#define		DxFontDesc		D3DXFONT_DESCA
#define		DxPlane			D3DXPLANE
#define		DxViewport		D3DVIEWPORT9
#define		DxCaps			D3DCAPS9
#define		DxHandle		D3DXHANDLE
#define		DxPrimitiveType	D3DPRIMITIVETYPE
#define		DxVertexShader	IDirect3DVertexShader9
#define		DxPixelShader	IDirect3DPixelShader9




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

//uaternion

// #else
// 
// 
// 
// #endif
namespace Air{
	
	namespace Client{
	
		namespace	Render{
			/**	\brief	引擎错误日志函数
			*   
			*	@remarks 	引擎错误日志函数
			*	@see		
			*	@return   	void
			*	@param		AChar * strName
			*	@param		AChar * strInfo
			*	@note
			*
			**/
			inline	void	RenderLogError(const AChar*	strName,const AChar*	strInfo){
				AChar	str[MAX_NAME];
				sprintf_s(str,MAX_NAME,"(%s)(%s)",strName,strInfo);
				Common::Logger("Render","Error",str);
			};
			/**	\brief	引擎警告日志
			*   
			*	@remarks 	引擎警告日志
			*	@see		
			*	@return   	void
			*	@param		AChar * strName
			*	@param		AChar * strInfo
			*	@note
			*
			**/
			inline	void	RenderLogWarnning(const AChar*	strName,const AChar*	strInfo,SInt hr = 0){
				AChar	str[MAX_NAME];
				sprintf_s(str,MAX_NAME,"Name(%s),Info(%s),Result(%s)",strName,strInfo,DXGetErrorDescriptionA(hr));
				Common::Logger("Render","Warnning",str);
			};
	
			/**	\brief	渲染调试日志
			*   
			*	@remarks 	渲染调试日志
			*	@see		
			*	@return   	void
			*	@param		AChar * strName
			*	@param		AChar * strInfo
			*	@note
			*
			**/
			inline	void	RenderLogDebug(const AChar*	strName,const AChar*	strInfo){
				AChar	str[MAX_NAME];
				//sprintf(StringBuff,"[Render][Error] At File[%s] Function[%s] Line[%d]\n",__FILE__,__FUNCTION__,__LINE__);
				sprintf_s(str,MAX_NAME,"(%s)(%s)",strName,strInfo);
				Common::Logger("Render","Debug",str);
			};
	
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