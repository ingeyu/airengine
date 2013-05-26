#ifndef AirGameDefaultSection_h__
#define AirGameDefaultSection_h__

#include "AirGameHeader.h"

namespace	Air{
	namespace	Game{
		class	GAME_EXPORT	DefaultSection	:public	Section{
		public:
			static AString	ProductTypeName;
			DefaultSection(CAString& strName);

			virtual	U1	Create();
			virtual	U1	Destroy();
			virtual	void	OnActorState(enumActorState	state,enumMoveState mstate);
			virtual	void	OnAction(enumAction	action);
			virtual	void	OnGameState(enumGameState	state);
			virtual	void		Update(const FrameTime& fFrameTime);
			virtual	Control*	OnCreateControl();

			void	__stdcall	OnESC(const Key& k);
			void	__stdcall	OnFireStart(const Key& k);
			void	__stdcall	OnFireEnd(const Key& k);
			void	__stdcall	OnBigFireStart(const Key& k);
			void	__stdcall	OnBigFireEnd(const Key& k);

			void	__stdcall		HitCallback(
				const Engine::ParticleElement&	element,
				U32								hitMask,
				PhysicsObject*					pObject
				);

			AnimationModel*		m_pModel;
			Engine::Particle*	m_pParticle;
			Engine::Particle*	m_pBigParticle;
			float				m_fShootTime;
			Float3				m_vMoveDir;
			Float3				m_vFaceDir;
		};
		class	GAME_EXPORT	EditorSection	:public	Section{
		public:
			static AString	ProductTypeName;
			EditorSection(CAString& strName);

			virtual	U1	Create();
			virtual	U1	Destroy();

			virtual	Control*	OnCreateControl();		
		};
	}
}
#endif // AirGameDefaultSection_h__
