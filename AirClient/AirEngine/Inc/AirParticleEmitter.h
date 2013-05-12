#ifndef AirParticleEmitter_h__
#define AirParticleEmitter_h__

#include "AirEngineHeader.h"

namespace	Air{
	namespace	Engine{
		class	Particle;

		class	ParticleEmitter	:	public	IProduct{
		public:
			struct Info{
				float		fFreq;
			};
			ParticleEmitter(CAString& strName,Info* pInfo);
			virtual	U1		Create();
			virtual	U1		Destroy();
			virtual	void	Update(const FrameTime& frameTime,Particle* pParticle);
		protected:
			float			m_fFreq;
			float			m_fUpdateTime;
		};

		class	BoxEmitter	:	public ParticleEmitter
		{
		public:
			struct Info	:	ParticleEmitter::Info{
				Float3	vCenter;
				Float3	vHalfSize;
			};
			BoxEmitter(CAString& strName,BoxEmitter::Info* pInfo);
			virtual	void	Update(const FrameTime& frameTime,Particle* pParticle);
		protected:
			Float3	m_vCenter;
			Float3	m_vHalfSize;
		};

		class SphereEmitter	:	public ParticleEmitter{
		public:
			struct Info	:	ParticleEmitter::Info{
				Float3	vCenter;
				float	fRadius;
			};
			SphereEmitter(CAString& strName,SphereEmitter::Info* pInfo);
			virtual	void	Update(const FrameTime& frameTime,Particle* pParticle);
		protected:
			Float3	m_vCenter;
			float	m_fRadius;
		};

	}
}
#endif // AirParticleEmitter_h__