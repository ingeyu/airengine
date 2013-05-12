#ifndef AirParticleRenderable_h__
#define AirParticleRenderable_h__

#include "AirEngineRenderable.h"

namespace	Air{
	namespace	Engine{
		class	ParticleRenderable	:	
			public	IProduct,
			public	Renderable
		{
		public:
			ParticleRenderable();

		};
	}
}

#endif // AirParticleRenderable_h__