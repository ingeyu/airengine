#ifndef AirGameSection_h__
#define AirGameSection_h__

#include "AirEngineHeader.h"
#include "AirGameControl.h"

namespace	Air{
	namespace	Engine{
		class Screen;
		class Scene;
	}
	namespace	Game{

		class	ENGINE_EXPORT	Section	:	
			public	Common::IProduct,
			public	IActionState
		{
		public:
			static	AString	ProductTypeName;
			Section(CAString&	strName);

			virtual	U1			Create();
			virtual	U1			Destroy();
			virtual	void		Update(const FrameTime& fFrameTime);
			virtual	void		RenderOneFrame(const FrameTime& fFrameTime);

			Engine::Pipeline*	GetPipeline();
			Engine::Scene*		GetScene();
			Control*			GetControl();
			Engine::SceneNode*	GetActorNode();

			virtual	void		LoadScene(CAString& strName);
			virtual	void		SaveScene(CAString& strName);
			virtual	Control*	OnCreateControl();		

			virtual	void	OnActorState(enumActorState	state,enumMoveState mstate){};
			virtual	void	OnAction(enumAction	action){};
			virtual	void	OnGameState(enumGameState	state){};

			
		protected:

			Engine::Pipeline*	m_pPipeline;
			Engine::Scene*		m_pScene;
			Control*			m_pControl;
		};
	}
}
#endif // AirGameSection_h__