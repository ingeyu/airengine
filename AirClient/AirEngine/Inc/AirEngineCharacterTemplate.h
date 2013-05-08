#ifndef ENGINECHARACTERMANAGER_HEAD_FILE
#define ENGINECHARACTERMANAGER_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineCharacterAnimationModel.h"

namespace Air{
	
	namespace Engine{
		class	SceneNode;
		namespace	Character{
			class	ENGINE_EXPORT	ModelTemplate	:	public	IProduct{
			public:
				static AString ProductTypeName;
				struct Info{
					AString strModelPath;
					AString	strSkeletonName;
				};
				ModelTemplate(CAString& strName,Info* pInfo);

				virtual	U1	Create();
				virtual	U1	Destroy();


				STD_VECTOR<AString>	m_vecAction;
				STD_VECTOR<AString>	m_vecState;
				STD_VECTOR<AString>	m_vecEquipment;
				STD_VECTOR<AString>	m_vecMaterial;
				Info				m_Info;
			};

			U1				InitModelTemplate(CAString& strModelTemplateFileName);
			
		}
	
	};
};
#endif // ENGINECHARACTERMANAGER_HEAD_FILE