#ifndef INTERFACERENDERMATERIALTEMPLATE_HEAD_FILE
#define INTERFACERENDERMATERIALTEMPLATE_HEAD_FILE

#include "AirInterfaceRenderCommon.h"

namespace Air{
	
	namespace Client{
	
		namespace	Render{
			class		ITexture;
			class		IShader;
			typedef		std::vector<ITexture*>	TextureVector;
	
	
			/**	\brief	新的材质系统
			*
			*	新的材质系统
			*
			***/
			class	IMaterialTemplate{
			public:
				/**	\brief	技术
				*
				*	技术
				*
				***/
				class	ITechnique{
				public:
					/**	\brief	通道
					*
					*	通道
					*
					***/
					class	IPass{
					public:
						IPass(){
							m_pInfo		=	NULL;
						};
						
						PassInfo*	m_pInfo;
					};
					
					ITechnique(){
						m_pInfo		=	NULL;
						m_pShader	=	NULL;
					};
	
					virtual	void	Render()	=	NULL;
	
					IShader*		m_pShader;
					TechniqueInfo*	m_pInfo;
				};
	
				IMaterialTemplate(){
					m_pInfo	=	NULL;
				};
	
				MaterialTemplateInfo*	m_pInfo;	///<	材质信息
			};
		}
	};
};
#endif // INTERFACERENDERMATERIAL2_HEAD_FILE