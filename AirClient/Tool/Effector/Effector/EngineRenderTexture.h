#ifndef EngineRenderTexture_h__
#define EngineRenderTexture_h__

#include "EngineTexture.h"

class	RenderTexture	:public	ETexture{
public:
	RenderTexture(const TCHAR*	strName,TreeObj*	pParent);
	virtual	bool	Create();
	virtual	bool	Destroy();

	Air::Client::Texture::Info	info;
};
#endif // EngineRenderTexture_h__