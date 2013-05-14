#ifndef AirParticleRenderable_h__
#define AirParticleRenderable_h__

#include "AirEngineRenderable.h"

namespace	Air{
	namespace	Engine{
		class	Particle;
		class	ParticleRenderer	:	
			public	IProduct
		{
		public:
			struct Info{
				AString strTemp;
			};
			ParticleRenderer(CAString& strName,Info* pInfo);
			virtual	U1	Create();
			virtual	U1	Destroy();
			virtual	void	OnParticleRender(Render::Device* pDevice,Particle* pParticle);
		protected:
			Render::Draw::Buff	m_DrawBuffer;
			Render::Buffer*		m_pInstanceBuffer;
		};
	}
}

#endif // AirParticleRenderable_h__