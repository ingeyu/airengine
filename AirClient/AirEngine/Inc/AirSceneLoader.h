#ifndef AirSceneLoader_h__
#define AirSceneLoader_h__

#include "AirEngineHeader.h"
#include "AirEngineSceneNode.h"


namespace	Air{
	namespace	Engine{

		class MeshEntity;

		class	ENGINE_EXPORT	SceneLoader{
		public:


			SceneLoader();

			void		SetNode(SceneNode*	pParent);
			

			U1	Load(CAString&	strSceneName);
			U1	Unload();
			
			SceneNode*					m_pParentNode;
			std::vector<MeshEntity*>	m_vecEntity;
		};
	}
}
#endif // AirSceneLoader_h__