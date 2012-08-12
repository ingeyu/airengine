#ifndef EnginePass_h__
#define EnginePass_h__

#include "EngineCommon.h"

class EPass	:public	TreeObj{
public:
	EPass(const TCHAR*	strName,TreeObj*	pParent);

	virtual	bool	Create();
	virtual	bool	Destroy();

	void	Draw();
};
#endif // EnginePass_h__
