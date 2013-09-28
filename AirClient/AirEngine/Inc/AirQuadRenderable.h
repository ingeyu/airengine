#ifndef AirQuadRenderable_h__
#define AirQuadRenderable_h__

#include "AirEngineRenderable.h"

namespace	Air{
	namespace	Engine{
		class	ENGINE_EXPORT	QuadRenderable	:	public Renderable{
		public:
			QuadRenderable();

			virtual	~QuadRenderable();
		};

		class	ENGINE_EXPORT	CSRenderable	:	public	Renderable{
		public:
			CSRenderable();
			virtual	void	OnRender(Render::Device* pDevice);
			
			U32	m_Dispatch[3];
		};
	}
}
#endif // AirQuadRenderable_h__