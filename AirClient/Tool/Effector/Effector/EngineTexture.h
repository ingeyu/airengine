#ifndef EngineTexture_h__
#define EngineTexture_h__

#include "EngineCommon.h"

namespace	Air{
	namespace	Client{
		namespace	Render{
			class Texture;
		}
	}
}

typedef	Air::Client::Render::Texture	AirTexture;

class	ETexture	:	public	TreeObj{
public:
	ETexture(const TCHAR*	strName,TreeObj*	pObj);

	virtual	bool	Create();

	virtual	bool	Destroy();
	virtual	bool	ReLoad();
	virtual	void			OnShowProperty(CMFCPropertyGridProperty*	pGroup);
	virtual	void			OnPropertyChanged(CMFCPropertyGridProperty*	pProperty);



	AirTexture*	m_pTexture;
};
class	ETextureRef	:	public	TreeObj{
public:
	ETextureRef(const TCHAR*	strName,TreeObj*	pObj);
};
#endif // EngineTexture_h__