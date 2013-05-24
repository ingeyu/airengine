#ifndef AirParticleAffector_h__
#define AirParticleAffector_h__

#include "AirParticleEmitter.h"

namespace	Air{
	namespace	Engine{
		class	Particle;
		class	ForceField	:	MemoryObject{
		public:

		};
		class	ENGINE_EXPORT	ParticleAffector	:	public	IProduct{
		public:
			struct Info{
				U32			uiCount;
				ForceField* pForceField;
				U32			bEnableCollision;
			};
			static	AString	ProductTypeName;
			static	void*	ScriptParser(StringVector& vecWord,U32& i);
			ParticleAffector(CAString& strName,Info* pInfo);
			virtual	U1	Create();
			virtual	U1	Destroy();
			virtual	void	Update(const FrameTime& frameTime,Particle* pParticle);
			Info*			m_pInfo;
		};
	}
}
#endif // AirParticleAffector_h__