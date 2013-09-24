#ifndef AirRenderShader_h__
#define AirRenderShader_h__

#include "AirRenderCommon.h"

namespace	Air{
	namespace	Engine{

			class	ENGINE_EXPORT	Shader	:	public	IProduct{
			public:
				static AString ProductTypeName;
				Shader(CAString&	strName):IProduct(strName){};
				virtual	U1				IsFileUpdate(){return false;};
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