#ifndef EngineMesh_h__
#define EngineMesh_h__

#include "EngineCommon.h"
namespace	Air{
	namespace	Client{
		class	StaticMesh;
	}
}

class Mesh:public	TreeObj{
public:
	Mesh(const TCHAR*	strName,TreeObj*	pParent);
public:
	virtual	bool	Create();
	virtual	bool	Destroy();
	virtual	void	OnPropertyChanged(CMFCPropertyGridProperty* pProperty);
	virtual	void	OnShowProperty(CMFCPropertyGridProperty* pGroup);
	virtual	bool	ReLoad();
	void			Draw(const Air::Client::Matrix& matWorld);

	Air::Client::StaticMesh*	m_pMeshFile;
};





#endif // EngineMesh_h__