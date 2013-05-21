#ifndef AirGameDefaultSection_h__
#define AirGameDefaultSection_h__

#include "AirGameHeader.h"

namespace	Air{
	namespace	Game{
		class	GAME_EXPORT	DefaultSection	:public	Section{
		public:
			DefaultSection(CAString& strName);

			virtual	U1	Create();
			virtual	U1	Destroy();
			virtual	void	OnActorState(enumActorState	state,enumMoveState mstate);
			virtual	void	OnAction(enumAction	action);
			virtual	void	OnGameState(enumGameState	state);

			void	__stdcall	OnESC(const Key& k);
			AnimationModel*	m_pModel;
		};
	}
}
#endif // AirGameDefaultSection_h__
