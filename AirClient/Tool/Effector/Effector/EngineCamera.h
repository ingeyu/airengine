#ifndef EngineCamera_h__
#define EngineCamera_h__

#include "EngineCommon.h"

class	ECamera	:	public	TreeObj{
public:
	ECamera(const TCHAR*	strName,TreeObj*	pParent);
	virtual	~ECamera();
	virtual	bool	Create();
	virtual	bool	Destroy();

	Air::Client::Camera*	m_pCamera;

};
#endif // EngineCamera_h__