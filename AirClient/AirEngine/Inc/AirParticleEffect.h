#ifndef AirParticleEffect_h__
#define AirParticleEffect_h__
#include "AirParticle.h"

namespace	Air{
	namespace	Engine{
		class	ParticleEffect	:	public	Common::IProduct
		{
		public:
			struct Info{
				U32		uiBufferSize;
				U32		uiParticleCount;
				AChar*	uiParticleName[8];

			};
			ParticleEffect(CAString& strName)
		};
	}
}
#endif // AirParticleEffect_h__
