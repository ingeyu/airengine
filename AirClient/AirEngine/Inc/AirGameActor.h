#ifndef AirGameActor_h__
#define AirGameActor_h__

#include "AirEngineHeader.h"
#include "AirEngineCharacterAnimationModel.h"
#include "AirGameSkill.h"
namespace	Air{
	
	namespace	Game{
		class	Section;
		enum	enumActorMoveState{
			enAMS_NoMove			=	0,
			enAMS_Left			=	1,
			enAMS_Right			=	2,
			enAMS_Run			=	4,
			enAMS_Back			=	8,
			enAMS_RunLeft		=	enAMS_Run	|enAMS_Left,
			enAMS_RunRight		=	enAMS_Run	|enAMS_Right,
			enAMS_BackLeft		=	enAMS_Back	|enAMS_Left,
			enAMS_BackRight		=	enAMS_Back	|enAMS_Right,
			enAMS_CustomRun		=	16,
			enAMS_CustomBack	=	32
		};
		class	ENGINE_EXPORT	Actor	:public	Common::IProduct{
		public:
			static AString	ProductTypeName;
			struct Info{
				AString		strModelName;
				Section*	pSection;
			};
			Actor(CAString& strName,Info* pInfo);
			virtual	U1		Create();
			virtual	U1		Destroy();
			virtual	void	Update(const FrameTime& frameTime);
			const	Float3&	GetPosition();
			void			SetPosition(const Float3& v);
			void			SetMoveState(enumActorMoveState	state);
			void			SetMoveDirection(const Float3& v);
			void			SetModelName(CAString& strModelName);

			void			SetSkill(U32 uiIndex,Skill* pSkill);
			void			CastSkill(U32	uiIndex);
			void			StopCastSkill(U32	uiIndex);
			U1				Move(float fTimeDelta);


			//inline function
		public:
			inline	float				GetMoveVelocity(){return m_fMoveVelocity;};
			inline	void				SetMoveVelocity(float f){m_fMoveVelocity	=	f;};
			inline	const	Float3&		GetMoveDirection(){return m_vMoveDir;};
			inline	const	Float3&		GetFaceDirection(){return m_vFaceDir;};			
			inline	void				SetFaceDirection(const Float3& v){m_vFaceDir=v;m_vFaceDir.Normalize();};
			inline	AnimationModel*		GetModel(){return m_pModel;};
			inline	Skill*				GetSkill(U32 uiIndex){return m_vecSkill[uiIndex];};
			inline	void				SetTarget(Actor* pActor){m_pTarget	=	pActor;};
			inline	Actor*				GetTarget(){return m_pTarget;};
			inline	Engine::SceneNode*	GetNode(){return	m_pNode;};
		protected:
			void	UpdateActionState(enumActorMoveState state);
		protected:
			float					m_fMoveVelocity;
			Float3					m_vMoveDir;
			Float3					m_vFaceDir;
			
			Engine::SceneNode*		m_pNode;
			AnimationModel*			m_pModel;
			Info					m_Info;
			U32						m_uiLowBodyBoneIndex;
			Actor*					m_pTarget;
			SkillVector				m_vecSkill;
			Physics::Object*		m_pHitShape;
			Physics::Object*		m_pMoveShape;
			enumActorMoveState		m_MoveState;
		};
	}
}
#endif // AirGameActor_h__