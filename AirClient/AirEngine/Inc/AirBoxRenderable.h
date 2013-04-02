#ifndef AirBoxRenderable_h__
#define AirBoxRenderable_h__

#include "AirEngineRenderable.h"

namespace	Air{
	namespace	Engine{
		class	ENGINE_EXPORT	BoxMesh	:	public	RefSingleton<BoxMesh>{
		public:
			BoxMesh();
			virtual	~BoxMesh();
			DrawBuff	m_DrawBuff;
		};

		class	ENGINE_EXPORT	BoxRenderable	:	public Renderable{
		public:
			BoxRenderable();
			virtual	~BoxRenderable();
			virtual	Matrix*	GetWorldMatrix(){return	&m_WorldMatrix;};
			Matrix	m_WorldMatrix;
		};
	}
}

#endif // AirBoxRenderable_h__