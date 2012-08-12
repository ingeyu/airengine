#ifndef RENDERSHADER_HEAD_FILE
#define RENDERSHADER_HEAD_FILE

#include "AirRenderHeader9.h"
#include "AirRenderFactory9.h"
namespace Air{
	
	namespace Client{
	
		namespace	Render{
			typedef	std::map<AString,DxVertexShader*>	VertexShaderMap;
			typedef	std::map<AString,DxPixelShader*>	PixelShaderMap;
			/**	\brief	顶点着色语言
			*
			*	顶点着色语言
			*
			***/
			class	Shader9	:
				public	IShader{
			public:
				Shader9(CAString&	strName,Info*	pInfo);
	
				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		Shader
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Create();
	
				/**	\brief	摧毁
				*   
				*	@remarks 	摧毁
				*	@see		Shader
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Destroy();
	
				/**	\brief	获取顶点着色指针
				*   
				*	@remarks 	获取顶点着色指针
				*	@see		Shader
				*	@return   	IDirect3DVertexShader9*
				*	@note
				*
				**/
				IDirect3DVertexShader9*	GetVS();
				/**	\brief	获取像素着色指针
				*   
				*	@remarks 	获取像素着色指针
				*	@see		Shader
				*	@return   	IDirect3DPixelShader9*
				*	@note
				*
				**/
				IDirect3DPixelShader9*	GetPS();

				virtual	void*			GetShader();
				/**	\brief	重载
				*   
				*	@remarks 	重载
				*	@see		IShader
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	Reload();
			protected:
				/**	\brief	获取顶点着色
				*   
				*	@remarks 	获取顶点着色
				*	@see		Shader
				*	@return   	DxVertexShader*
				*	@param		Resource::IStream*	pData
				*	@param		CAString & strName
				*	@param		AString strVersion
				*	@note
				*
				**/
				DxVertexShader*	CreateVS(Resource::IStream*	pData,CAString&	strName,CAString&	strVersion	=	"vs_3_0");
				/**	\brief	获取像素着色
				*   
				*	@remarks 	获取像素着色
				*	@see		Shader
				*	@return   	DxPixelShader*
				*	@param		Data*	pData
				*	@param		AString & strName
				*	@param		AString strVersion
				*	@note
				*
				**/
				DxPixelShader*	CreatePS(Resource::IStream*	pData,CAString&	strName,CAString&	strVersion	=	"ps_3_0");
	
				//union{
					IDirect3DVertexShader9*	m_pVertexShader;
					IDirect3DPixelShader9*	m_pPixelShader;
				Resource::IStream*			m_pStream;
			};
	
			/**	\brief	着色语言工厂
			*
			*	着色语言工厂
			*
			***/
			class	Shader9Factory	:
				public	Factory{
			public:
				Shader9Factory(){
					m_strTypeName	=	"Shader";
				}
	
				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		ShaderFactory
				*	@return   	IProduct*
				*	@param		AString& strName
				*	@param		IFactoryParamList * lstParam
				*	@note
				*
				**/
				virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam /* = NULL */);
			};
		}
	
	};
};
#endif // RENDERVERTEXSHADER_HEAD_FILE