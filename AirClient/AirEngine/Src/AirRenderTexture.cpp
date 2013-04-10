#include "AirRenderTexture.h"

namespace	Air{
	namespace	Engine{
		namespace	Render{

			AString		Texture::ProductTypeName="Texture";
			Texture::Texture( CAString& strName,Info* pInfo ):IProduct(strName)
			{
				if(pInfo!=NULL)
					m_Info	=	*pInfo;
			}

			Texture::~Texture()
			{

			}

		}
	}
}