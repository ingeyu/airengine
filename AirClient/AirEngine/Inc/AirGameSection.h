#ifndef AirGameSection_h__
#define AirGameSection_h__

#include "AirEngineHeader.h"

namespace	Air{
	namespace	Engine{
		class Screen;
		class Scene;
	}
	namespace	Game{
		class	ENGINE_EXPORT	Section	:	
			public	Common::IProduct
		{
		public:
			static	AString	ProductTypeName;
			Section(CAString&	strName);

			virtual	U1			Create();
			virtual	U1			Destroy();
			virtual	void		Update(const FrameTime& fFrameTime);

			Engine::Screen*		GetScreen();
			Engine::Scene*		GetScene();
		protected:

			Engine::Screen*		m_pScreen;
			Engine::Scene*		m_pScene;
		};
	}
}
#endif // AirGameSection_h__