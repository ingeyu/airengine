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
			virtual	void		RenderOneFrame(const FrameTime& fFrameTime);

			Engine::Pipeline*	GetPipeline();
			Engine::Scene*		GetScene();

			virtual	void		LoadScene(CAString& strName);
			virtual	void		SaveScene(CAString& strName);
		protected:

			Engine::Pipeline*	m_pPipeline;
			Engine::Scene*		m_pScene;
		};
	}
}
#endif // AirGameSection_h__