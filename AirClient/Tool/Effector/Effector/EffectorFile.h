#ifndef EffectorFile_h__
#define EffectorFile_h__

#include "EngineEffect.h"

class EffectorFile	:	public	TreeObj
{
public:
	EffectorFile(CTreeCtrl*	pTree);
	virtual	~EffectorFile();

	bool	New();
	bool	Open(const TCHAR*	strName);
	bool	Save();
	bool	SaveAs(const TCHAR*	strName);

	void	Close();

	void	AddEffect(const TCHAR*	strName);
	void	AddCamera(const TCHAR*	strName);
	void	AddMesh(const TCHAR*	strName);

	void	DrawActiveEffect();

protected:
	bool	ParseFile(unsigned char*& pData);
	bool	ParseEffect(Effect* p,unsigned char* pData);
private:
	bool			m_bLoaded;
};
#endif // EffectorFile_h__
