#ifndef EnginePhase_h__
#define EnginePhase_h__

#include "EnginePass.h"

class	Phase	:	public	TreeObj{
public:
	Phase(const TCHAR*	strName,TreeObj*	pParent);
	bool	Create();
	bool	Destroy();

	void	Draw();
};

typedef	std::vector<Phase*>	PhaseVector;
#endif // EnginePhase_h__
