#include "AirRenderShader11.h"
#include "AirRenderDevice11.h"
#include "D3Dcompiler.h"

namespace Air{
	
	namespace	Client{
		extern	Render::Device11*	pDevice;
		namespace	Render{
			
	
			typedef	std::map<AString,enumShaderType>	ShaderTypeMap;
			typedef	std::map<AString,enumSystemVersion>	ShaderVersionMap;

			enumShaderType	ParseShaderType(CAString&	strType){
				static	U1	bInit	=	false;
				static	ShaderTypeMap	mapType;
				if(!bInit){
					mapType["vs"]	=	enVS;
					mapType["gs"]	=	enGS;
					mapType["ps"]	=	enPS;
					mapType["cs"]	=	enCS;
					mapType["hs"]	=	enHS;
					mapType["ds"]	=	enDS;
					bInit	=	true;
				}
				return	mapType[strType];
			}
			enumSystemVersion	ParseShaderVersion(CAString&	strVersion){
				static	U1	bInit	=	false;
				static	ShaderVersionMap	mapVersion;
				if(!bInit){
					mapVersion["9"]		=	enRSV_9;
					mapVersion["10"]	=	enRSV_10;
					mapVersion["10_1"]	=	enRSV_10_1;
					mapVersion["11"]	=	enRSV_11;
					bInit	=	true;
				}
				return	mapVersion[strVersion];
			}
			Shader11::Shader11( CAString& strName ):Shader(strName)
			{
				m_pDxShader			=	NULL;
				m_pStream			=	NULL;
				m_ShaderType		=	enVS;
				m_ShaderVersion		=	enRSV_11;
				m_pBinaryCode		=	NULL;

			}

			Air::U1 Shader11::Create()
			{
				AString	strPath,strFileName,strExt;
				Common::Converter::SplitFilePath(m_strProductName,&strPath,&strFileName,&strExt);
				//AString	strExt	=	strstr(m_strProductName.c_str(),".")+1;
				AString	strType;
				strType.resize(2);
				memcpy(&strType[0],&strExt[0],2);
				Common::Converter::ToLowerCase(strType);
				m_ShaderType		=	ParseShaderType(strType);
				AString	strVersion	=	&strExt[2];
				m_ShaderVersion		=	ParseShaderVersion(strVersion);
				enumSystemVersion	hwVersion	=	pDevice->GetHWVersion();
				if(m_ShaderVersion	>	hwVersion){
					m_ShaderVersion	=	hwVersion;
				}

				static	AString	strShaderType[]	=	{
					"",
					"_1_0",
					"_3_0",
					"_4_0",
					"_4_1",
					"_5_0",
					"",
					""
				};
				AString	strProfile	=	strType	+	strShaderType[m_ShaderVersion];

				U8*	pData	=	NULL;
				U32	uiSize	=	0;
				if(Common::File::Load(m_strProductName,pData,uiSize)){
					ID3DBlob*	pError	=	NULL;
					D3DCompile(pData,uiSize,m_strProductName.c_str(),NULL,NULL,"main",strProfile.c_str(),0,0,&m_pBinaryCode,&pError);
					DxDevice*	pDxDevice	=	(DxDevice*)pDevice->GetDevice();
					switch(m_ShaderType){
						case enVS:{
							DxVertexShader*	pShader	=	NULL;
							pDxDevice->CreateVertexShader(m_pBinaryCode->GetBufferPointer(),m_pBinaryCode->GetBufferSize(),NULL,&pShader);
							m_pDxShader		=	pShader;
							break;}
						case enGS:{
							ID3D11GeometryShader*	pShader	=	NULL;
							pDxDevice->CreateGeometryShader(m_pBinaryCode->GetBufferPointer(),m_pBinaryCode->GetBufferSize(),NULL,&pShader);
							m_pDxShader		=	pShader;
							break;}
						case enPS:{
							ID3D11PixelShader*	pShader	=	NULL;
							pDxDevice->CreatePixelShader(m_pBinaryCode->GetBufferPointer(),m_pBinaryCode->GetBufferSize(),NULL,&pShader);
							m_pDxShader		=	pShader;
							break;}
						case enCS:{
							ID3D11ComputeShader*	pShader	=	NULL;
							pDxDevice->CreateComputeShader(m_pBinaryCode->GetBufferPointer(),m_pBinaryCode->GetBufferSize(),NULL,&pShader);
							m_pDxShader		=	pShader;
							break;}
						case enHS:{
							ID3D11HullShader*	pShader	=	NULL;
							pDxDevice->CreateHullShader(m_pBinaryCode->GetBufferPointer(),m_pBinaryCode->GetBufferSize(),NULL,&pShader);
							m_pDxShader		=	pShader;
							break;}
						case enDS:{
							ID3D11DomainShader*	pShader	=	NULL;
							pDxDevice->CreateDomainShader(m_pBinaryCode->GetBufferPointer(),m_pBinaryCode->GetBufferSize(),NULL,&pShader);
							m_pDxShader		=	pShader;
							break;}
					}

					delete[] pData;
				}

				return	true;
			}

			Air::U1 Shader11::Destroy()
			{
				switch(m_ShaderType){
				case enVS:{
					((DxVertexShader*)m_pDxShader)->Release();
					break;}
				case enGS:{
					((ID3D11GeometryShader*)m_pDxShader)->Release();
					break;}
				case enPS:{
					((ID3D11PixelShader*)m_pDxShader)->Release();
					break;}
				case enCS:{
					((ID3D11ComputeShader*)m_pDxShader)->Release();
					break;}
				case enHS:{
					((ID3D11HullShader*)m_pDxShader)->Release();
					break;}
				case enDS:{
					((ID3D11DomainShader*)m_pDxShader)->Release();
					break;}
				}
			
				m_pDxShader	=	NULL;
				SAFE_RELEASE(m_pBinaryCode);

				return	true;
			}

			void* Shader11::GetShader()
			{
				switch(m_ShaderType){
				case enVS:{
					return	((DxVertexShader*)m_pDxShader);
					break;}
				case enGS:{
					return	((ID3D11GeometryShader*)m_pDxShader);
					break;}
				case enPS:{
					return	((ID3D11PixelShader*)m_pDxShader);
					break;}
				case enCS:{
					return	((ID3D11ComputeShader*)m_pDxShader);
					break;}
				case enHS:{
					return	((ID3D11HullShader*)m_pDxShader);
					break;}
				case enDS:{
					return	((ID3D11DomainShader*)m_pDxShader);
					break;}
				}
				return	NULL;
			}

			void Shader11::GetBinaryCode( void*& pOut,U32& uiSize )
			{
				if(m_pBinaryCode==NULL)
					return;

				pOut	=	m_pBinaryCode->GetBufferPointer();
				uiSize	=	m_pBinaryCode->GetBufferSize();
			}

			enumShaderType Shader11::GetType()
			{
				return	m_ShaderType;
			}

		}
	}
};