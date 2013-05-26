#ifndef AirGameActor_h__
#define AirGameActor_h__

#include "AirEngineHeader.h"
#include "AirEngineCharacterAnimationModel.h"
#include "AirGameSkill.h"
namespace	Air{
	
	namespace	Game{
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
		};
		class	ENGINE_EXPORT	Actor	:public	Common::IProduct{
		public:
			static AString	ProductTypeName;
			struct Info{
				AString	strModelName;	
			};
			Actor(CAString& strName,Info* pInfo);
			virtual	U1		Create();
			virtual	U1		Destroy();
			virtual	void	Update(const FrameTime& frameTime);
			const	Float3&	GetPosition();
			void			SetPosition(const Float3& v);
			void			SetMoveState(enumActorMoveState	state);
			void			SetModelName(CAString& strModelName);

			void			SetSkill(U32 uiIndex,Skill* pSkill);
			void			CastSkill(U32	uiIndex);
			void			StopCastSkill(U32	uiIndex);
			//inline function
		public:
			inline	float				GetMoveVelocity(){return m_fMoveVelocity;};
			inline	void				SetMoveVelocity(float f){m_fMoveVelocity	=	f;};
			inline	const	Float3&		GetMoveDirection(){return m_vMoveDir;};
			inline	const	Float3&		GetFaceDirection(){return m_vFaceDir;};
			inline	float				GetGravityVelocity(){return m_fGravityVelocity;};
			inline	void				SetMoveDirection(const Float3& v){m_vMoveDir=v;m_vMoveDir.Normalize();};
			inline	void				SetFaceDirection(const Float3& v){m_vFaceDir=v;m_vFaceDir.Normalize();};
			inline	void				SetGravityVelocity(float f){m_fGravityVelocity=f;};
			inline	AnimationModel*		GetModel(){return m_pModel;};
			inline	Skill*				GetSkill(U32 uiIndex){return m_vecSkill[uiIndex];};
			inline	void				SetTarget(Actor* pActor){m_pTarget	=	pActor;};
			inline	Actor*				GetTarget(){return m_pTarget;};
			inline	Engine::SceneNode*	GetNode(){return	m_pNode;};
		protected:
			float					m_fMoveVelocity;
			Float3					m_vMoveDir;
			Float3					m_vFaceDir;
			float					m_fGravityVelocity;
			Engine::SceneNode*		m_pNode;
			AnimationModel*			m_pModel;
			Info					m_Info;
			U32						m_uiLowBodyBoneIndex;
			Actor*					m_pTarget;
			SkillVector				m_vecSkill;
		};
	}
}
#endif // AirGameActor_h__