#ifndef EngineShader_h__
#define EngineShader_h__

#include "EngineCommon.h"

class EShader	:	public	TreeObj{
public:
	EShader(const TCHAR*	strName,TreeObj*	pParent,enumTreeObjType	t);
	virtual	bool	Create();
	virtual	bool	Destroy();
	virtual	void	OnPropertyChanged(CMFCPropertyGridProperty* pProperty);
	virtual	void	OnShowProperty(CMFCPropertyGridProperty* pGroup);
	virtual	bool	ReLoad();
	Air::Client::Shader*	m_pShader;
};
#endif // EngineShader_h__