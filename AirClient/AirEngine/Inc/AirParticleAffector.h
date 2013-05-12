#ifndef AirParticleAffector_h__
#define AirParticleAffector_h__

#include "AirParticleEmitter.h"

namespace	Air{
	namespace	Engine{
		class	Particle;
		class	ForceField	:	MemoryObject{
		public:

		};
		class	ParticleAffector	:	public	IProduct{
		public:
			struct Info{
				Particle*	pParticle;
				Float3		vForce;
			};
			ParticleAffector(CAString& strName,Info* pInfo);
			virtual	void	Update(const FrameTime& frameTime,Particle* pParticle);
		};
	}
}
#endif // AirParticleAffector_h__