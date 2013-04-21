#ifndef AirSceneLoader_h__
#define AirSceneLoader_h__

#include "AirEngineHeader.h"
#include "AirEngineSceneNode.h"


namespace	Air{
	namespace	Engine{

		class MeshEntity;
		typedef STD_VECTOR<MeshEntity*>	MeshEntityVector;
		class	ENGINE_EXPORT	SceneLoader	:	public	MemoryObject{
		public:


			SceneLoader();

			void		SetNode(SceneNode*	pParent);
			SceneNode*	GetNode(){
				return m_pNode;
			};

			U1	Load(CAString&	strSceneName);
			U1	Unload();
			MeshEntityVector&	GetAllEntity(){
				return m_vecEntity;
			}
		protected:
			SceneNode*			m_pNode;
			MeshEntityVector	m_vecEntity;
		};
	}
}
#endif // AirSceneLoader_h__