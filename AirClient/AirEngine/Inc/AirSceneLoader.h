#ifndef AirSceneLoader_h__
#define AirSceneLoader_h__

#include "AirEngineHeader.h"
#include "AirEngineSceneNode.h"


namespace	Air{
	struct	Transform{
		Float3	pos;
		Float4	rot;
		Float3	scale;
	};
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
			U1	Load2(CAString&	strSceneName);
			U1	Save(CAString&	strSceneName);
			U1	Unload();
			MeshEntityList&	GetAllEntity(){
				return m_lstEntity;
			}

			MeshEntity*			AddEntity(CAString& strName,Transform* ptrans=NULL );
			void				RemoveEntity(MeshEntity* pEnt);
			void				AddObject(CAString& strName,CAString& strType,Transform& trans,void* pInfo);
		protected:
			SceneNode*			m_pNode;
			MeshEntityList	m_lstEntity;
		};
	}
}
#endif // AirSceneLoader_h__