#ifndef AirSceneLoader_h__
#define AirSceneLoader_h__

#include "AirEngineHeader.h"
#include "AirEngineSceneNode.h"


namespace	Air{
	namespace	Engine{

		class MeshEntity;
		typedef STD_LIST<MeshEntity*>	MeshEntityList;
		class	ENGINE_EXPORT	SceneLoader	:	public	MemoryObject{
		public:


			SceneLoader();

			void		SetNode(SceneNode*	pParent);
			SceneNode*	GetNode(){
				return m_pNode;
			};

			U1	Load(CAString&	strSceneName);
			U1	Unload();
			MeshEntityList&	GetAllEntity(){
				return m_lstEntity;
			}

			MeshEntity*			AddEntity(CAString& strName,U1 bCreateNode	=	false );
			void				RemoveEntity(MeshEntity* pEnt);
		protected:
			SceneNode*			m_pNode;
			MeshEntityList	m_lstEntity;
		};
	}
}
#endif // AirSceneLoader_h__