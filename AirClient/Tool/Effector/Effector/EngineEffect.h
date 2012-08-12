#ifndef EngineEffect_h__
#define EngineEffect_h__

#include "EnginePhase.h"

class EffectorFile;
class	Effect	:	public	TreeObj{
public:
	Effect(const TCHAR*	strName,TreeObj* pFile);
	virtual	~Effect();

	bool	Create();
	bool	Destroy();

	bool	AddPhase(const TCHAR*	strName);

	void	Draw();

	PhaseVector	m_vecPhase;
};

typedef	std::vector<Effect*>	EffectVector;
#endif // EngineEffect_h__
