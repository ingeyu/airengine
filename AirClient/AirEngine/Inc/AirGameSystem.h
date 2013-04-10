#ifndef AirGameSystem_h__
#define AirGameSystem_h__

#include "AirEngineHeader.h"

namespace	Air{
	namespace	Engine{
		class	Screen;
	};
	namespace	Game{
		class	Section;
		class	ENGINE_EXPORT	System	:	
			public	Common::IFactoryManager,
			public	Singleton<System>
		{
		public:
			System();


			virtual	U1	Initialization();
			virtual	U1	Release();


			Section*		GetCurrentSection();
			void			SetCurrentSection(Section* pSection);

			void		Update(const FrameTime&	fFrameTime);
			void		RenderOneFrame(const FrameTime&	fFrameTime);
		public:
			Section*	m_pSection;
		};
	}
	typedef	Game::System	GameSystem;
}
#endif // AirGameSystem_h__
