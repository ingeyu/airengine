#ifndef AirRenderShader_h__
#define AirRenderShader_h__

#include "AirRenderCommon.h"

namespace	Air{
	namespace	Client{

			class	Shader	:	public	IProduct{
			public:
				Shader(CAString&	strName):IProduct(strName){};
				virtual	void*			GetShader()										=	NULL;
				virtual	void			GetBinaryCode(void*&	pOut,U32&	uiSize)		=	NULL;
				virtual	enumShaderType	GetType()										=	NULL;
				virtual	void			Reload(){
					Destroy();
					Create();
				};
			};

	}
}
#endif // AirRenderShader_h__