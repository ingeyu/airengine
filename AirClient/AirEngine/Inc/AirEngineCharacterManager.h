#ifndef ENGINECHARACTERMANAGER_HEAD_FILE
#define ENGINECHARACTERMANAGER_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineCharacterAnimationModel.h"

namespace Air{
	
	namespace Client{
		class	SceneNode;
		namespace	Character{
			
	
			class	ENGINE_EXPORT	Manager{
			public:
				Manager();
				~Manager();
				U1	LoadSLK(CAString&	strName);
	
				void	SetSceneNode(SceneNode*	pNode);
				SceneNode*	GetSceneNode();
				Animation::Model*	Create(CAString&	strName,CAString&	strType);
				void	Destroy();
	
				void	Updata(Real	fTimeDelta);
				void	Render();
	
				void	Action(CAString&	strName,Real fBlend	=	0.3f);
				void	State(CAString&	strName);
				AString	NextAction();
				AString	NextState();
	
	
				Real	GetAnimationSpeed();
				void	SetAnimationSpeed(Real	fSpeed	=	1.0f);
				void	SetAnimationSpeedOffset(Real	fSpeedOffset	=	-0.01f);
	
				void	SetMaterial(CAString&	strType,CAString&	strMaterial);
	
				void	Remove(CAString&	strType);
				void	Add();
	
				Animation::Model*	GetModel(){
					return	m_pModel;
				};
			protected:
				void	LoadAnimation(CAString&	strAnimationName);
				void	LoadEquipment(CAString&	strEquipmentName);
			private:
				Animation::Model*	m_pModel;
				struct	CharacterInfo{
					UInt	uiID;
					AString	strName;
					AString	strAnimationFileName;
					AString	strEquipmentFileName;
					AString	strPath;
					AString	strSkeletonName;
				};
				struct AnimationInfo{
					AString	strName;
					AString	strFileName;
					U1		bLoop;
				};
				struct EquipmentInfo{
					AString	strPart;
					AString	strFileName;
					AString	strMaterialName;
				};
				typedef	std::map<AString,CharacterInfo>	CharacterInfoMap;
				typedef	CharacterInfoMap::iterator		CharacterInfoMapItr;
				typedef	CharacterInfoMap::value_type	CharacterInfoMapPair;
	
				typedef	std::vector<AnimationInfo>		AnimationInfoVector;
				typedef	AnimationInfoVector::iterator	AnimationInfoVectorItr;
	
	
	
				CharacterInfoMap		m_mapCharacterInfo;
				AnimationInfoVector		m_lstAnimation;
				AnimationInfoVector		m_lstStateAnimation;
				UInt					m_uiCurrentId;
	
				SceneNode*				m_pNode;
	
				AString					m_strState;
			};
		}
	
	};
};
#endif // ENGINECHARACTERMANAGER_HEAD_FILE