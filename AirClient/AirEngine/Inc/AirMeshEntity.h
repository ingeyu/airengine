#ifndef AirMeshEntity_h__
#define AirMeshEntity_h__
#include "AirStaticMesh.h"

namespace	Air{
	namespace	Engine{
		class	MeshEntity	:	
			public	IProduct,
			public	Renderable,
			public	MovableObject{
		public:
			struct Info{
				AString	strMeshName;
				AString	strMaterial;
			};
		public:
			MeshEntity(CAString& strName,Info* pInfo);

			virtual	U1	Create();
			virtual	U1	Destroy();

			virtual	void		ProcessRenderObject(U32	uiPhaseFlag);
			virtual	Matrix*		GetWorldMatrix();
			StaticMesh*			GetMesh()const{
				return m_pMesh;
			};

			U1	RayCast(const	Ray&	ray,float*	pOutDistance	=	NULL);
		protected:
			StaticMesh*	m_pMesh;
			Info		m_Info;
			Renderable*	m_pBoxRenderable;
			Material*	m_pBoundingBoxMaterial;
		};
	}
}
#endif // AirMeshEntity_h__