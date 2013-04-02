#include "AirRenderTexture.h"

namespace	Air{
	namespace	Engine{
		namespace	Render{


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