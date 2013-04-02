#ifndef AirScreenSpaceTessellation_h__
#define AirScreenSpaceTessellation_h__

#include "AirRenderSystem.h"
#include "AirEngineRenderable.h"

namespace	Air{
	namespace	Engine{
		class	TessellationRenderable	:public	Renderable{
		public:
			TessellationRenderable();
			~TessellationRenderable();
		};
		class	ScreenSpaceTessellation{
		public:
			ScreenSpaceTessellation();
			~ScreenSpaceTessellation();

			U1	Init();
			U1	Release();
			U1		UpdateTarget(Camera* pMainCamera);

			RenderTarget*	m_pTessellationTarget;
			Material*		m_pTessellationMaterial;
			TessellationRenderable*	m_pTessRenderable;
		};
	}
}
#endif // AirScreenSpaceTessellation_h__
