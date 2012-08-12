#include "AirRenderTexture.h"

namespace	Air{
	namespace	Client{
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