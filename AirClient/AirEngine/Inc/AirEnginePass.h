/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/05/08
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  EnginePass.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef ENGINEPASS_HEAD_FILE
#define ENGINEPASS_HEAD_FILE

#include "AirEngineShaderProgram.h"
#include "AirEngineMaterialCommon.h"

namespace	Air{
	namespace Engine{
		struct PassInfo;
		/**	\brief	通道
		*
		*	通道
		*
		***/
		class	ENGINE_EXPORT	Pass	:	
			public	Common::IObject{
		public:
			Pass(PassInfo*	pInfo);
			virtual	~Pass();

			/**	\brief	创建PASS
			*   
			*	@remarks 	摧毁PASS
			*	@see		Pass
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	Create();
			/**	\brief	摧毁PASS
			*   
			*	@remarks 	摧毁PASS
			*	@see		Pass
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	Destroy();

			
			/**	\brief	创建Shader
			*   
			*	@remarks 	创建Shader 纹理信息和参数信息 由ShaderProgram管理
			*	@see		Pass
			*	@return   	ShaderProgram*
			*	@param		ShaderParamInfo * pShaderInfo
			*	@param		Render::enumShaderType type
			*	@note
			*
			**/
			virtual	ShaderProgram*	CreateShaderProgram(ShaderParamInfo*	pShaderInfo,enumShaderType	type);
			/**	\brief	摧毁Shader
			*   
			*	@remarks 	摧毁Shader
			*	@see		Pass
			*	@return   	Air::U1
			*	@param		ShaderProgram * pShader
			*	@note
			*
			**/
			virtual	U1				DestroyShaderProgram(ShaderProgram*	pShader);
			/**	\brief	摧毁Shader
			*   
			*	@remarks 	摧毁Shader
			*	@see		Pass
			*	@return   	Air::U1
			*	@param		enumShaderType type
			*	@note
			*
			**/
			virtual	U1				DestroyShaderProgram(enumShaderType	type);

			virtual	void			UpdateTextureArray(TextureArray&	vecTexture);
			void					Begin();
			void					End();

			inline	PassHash		GetHash(){
				return	m_Hash;
			};
		protected:
			PassInfo*					m_pInfo;				///<	pass信息
			ShaderProgram*				m_pShaderArray[6];		///<	着色语言
			PassHash					m_Hash;

			Render::IRasterizerState*	m_pRasterizerState;		///<	光栅化状态
			Render::IBlendState*		m_pBlendState;			///<	混合状态
			Render::IDepthStencilState*	m_pDepthStencilState;	///<	深度状态
		};


		typedef	std::vector<Pass*>		PassVector;
	};//end of	namespace	Client
};//end of namespace Air
#endif // ENGINEPASS_HEAD_FILE