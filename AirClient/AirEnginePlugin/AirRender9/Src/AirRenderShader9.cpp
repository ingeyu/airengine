#include "AirRenderShader9.h"
#include "AirRenderGlobal9.h"
namespace Air{
	
	namespace	Client{
		namespace	Render{
			//extern	Effect::HlslInclude	hlslInclude;
	
	
			Shader9::Shader9( CAString& strName,Info* pInfo ):
				IShader(strName,pInfo){
				m_pVertexShader	=	NULL;
				m_pPixelShader	=	NULL;
				m_pStream		=	NULL;
			}
	
	
			U1 Shader9::Destroy(){
				SAFE_RELEASE(m_pVertexShader);
				SAFE_RELEASE(m_pPixelShader);
				return	true;
			}
	
			DxVertexShader* Shader9::CreateVS(Resource::IStream*	pData, CAString& strName,CAString& strVersion /*= "vs_3_0"*/ ){
	
				LPD3DXBUFFER	pShader	=	NULL;
				LPD3DXBUFFER	pError	=	NULL;
				HRESULT			hr		=	S_OK;
				//编译
				hr	=	D3DXCompileShader(	(AChar*)pData->GetData(),
											pData->GetSize(),
											NULL,
											NULL,//&hlslInclude,
											strName.c_str(),
											strVersion.c_str(),
											D3DXSHADER_DEBUG,
											&pShader,
											&pError,
											NULL);
				if(FAILED(hr)){
					RENDER_DEBUG_INFO(hr);
					RenderLogError("D3DXCompileShader",(AChar*)pError->GetBufferPointer());
					SAFE_RELEASE(pShader);
					SAFE_RELEASE(pError);
					return	NULL;
				}
				DxVertexShader*	pVertexShader	=	NULL;
				//创建
				hr	=	GetGlobal().m_pDevice->CreateVertexShader(	(DWORD*)pShader->GetBufferPointer(),
																	&pVertexShader);
				SAFE_RELEASE(pShader);
				if(FAILED(hr)){
					RENDER_DEBUG_INFO(hr);
					RenderLogError("CreateVertexShader","创建失败");
					return	NULL;
				}
				return	pVertexShader;
			}
	
			DxPixelShader* Shader9::CreatePS(Resource::IStream*	pData, CAString& strName,CAString& strVersion /*= "ps_3_0"*/ ){
				//查找是否已经创建
				LPD3DXBUFFER	pShader	=	NULL;
				LPD3DXBUFFER	pError	=	NULL;
				HRESULT			hr		=	S_OK;
				//编译
				hr	=	D3DXCompileShader(	(AChar*)pData->GetData(),
											pData->GetSize(),
											NULL,
											NULL,//&hlslInclude,
											strName.c_str(),
											strVersion.c_str(),
											D3DXSHADER_DEBUG,
											&pShader,
											&pError,
											NULL);
				if(FAILED(hr)){
					RENDER_DEBUG_INFO(hr);
					RenderLogError("D3DXCompileShader",(AChar*)pError->GetBufferPointer());
					SAFE_RELEASE(pShader);
					SAFE_RELEASE(pError);
					return	NULL;
				}
				DxPixelShader*	pPixelShader	=	NULL;
				//创建
				hr	=	GetGlobal().m_pDevice->CreatePixelShader(	(DWORD*)pShader->GetBufferPointer(),
																	&pPixelShader);
				SAFE_RELEASE(pShader);
				if(FAILED(hr)){
					RENDER_DEBUG_INFO(hr);
					RenderLogError("CreatePixelShader","创建失败");
					return	NULL;
				}
				//存入列表
				return	pPixelShader;
			}
	
			U1 Shader9::Create(){
				AString	str	=	m_strProductName	+	"9";

				U32	uiSize	=	GetGlobalSetting().m_pResourceSystem->Find(str);
				if(uiSize==0)
					return	false;
				m_pStream	=	GetGlobalSetting().m_pResourceSystem->CreateProduct<Resource::IStream*>(str,"Stream");
				
				

				
				return	true;
			}
	
			IDirect3DVertexShader9* Shader9::GetVS(){
				if(	m_pStream->GetState()	==	Resource::enSS_Loaded	&&
					m_pVertexShader			==	NULL	){
					AString	strFunctionName	=	"main";
					m_pVertexShader	=	CreateVS(m_pStream,strFunctionName);
				}
				return	m_pVertexShader;
			}
	
			IDirect3DPixelShader9* Shader9::GetPS(){

				if(m_pStream->GetState()	==	Resource::enSS_Loaded	&&
					m_pPixelShader			==	NULL	){
					AString	strFunctionName	=	"main";
					m_pPixelShader	=	CreatePS(m_pStream,strFunctionName);
				}
				return	m_pPixelShader;
			}

			void* Shader9::GetShader(){
				if(m_Info.type	==	enVS){
					return	GetVS();
				}else{
					return	GetPS();
				}
			}

			void Shader9::Reload(){
				Destroy();

				if(m_pStream!=NULL)
					m_pStream->ForceReLoad();
			}
			IProduct* Shader9Factory::NewProduct( CAString& strName,IFactoryParamList* lstParam /* = NULL */ ){
				return	new	Shader9(strName,(Shader9::Info*)lstParam);
			}
		}
	}
};