#ifndef EngineRenderState_h__
#define EngineRenderState_h__

#include "EngineCommon.h"

class	RenderState	:	public	TreeObj{
public:
	RenderState(const TCHAR*	strName,TreeObj*	pParent,enumTreeObjType	t);

	virtual	bool	Create();
	virtual	bool	Destroy();

	virtual	void			OnShowProperty(CMFCPropertyGridProperty*	pGroup);
	virtual	void			OnPropertyChanged(CMFCPropertyGridProperty*	pProperty);

	Air::Client::PassStateInfo	info;
	Air::Client::RenderState*	m_pState;
};




#endif // EngineRenderState_h__