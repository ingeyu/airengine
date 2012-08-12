#ifndef EngineModel_h__
#define EngineModel_h__

#include "EngineCommon.h"

class	Model	:	public	TreeObj{
public:
	Model(const TCHAR*	strName,TreeObj* pParent);

	virtual	bool	Create();
	virtual	bool	Destroy();

	virtual	void	OnPropertyChanged(CMFCPropertyGridProperty* pProperty);
	virtual	void	OnShowProperty(CMFCPropertyGridProperty* pGroup);

	void	Draw();

	Air::Float3				Position;
	Air::Float4				Rotation;
	Air::Float3				Scale;
	Air::Client::Buffer*	m_pObjBuffer;
};
class	ModelRef	:	public	TreeObj{
public:
	ModelRef(const TCHAR*	strName,TreeObj* pParent);
};
#endif // EngineModel_h__