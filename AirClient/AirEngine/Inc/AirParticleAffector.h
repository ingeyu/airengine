#ifndef AirParticleAffector_h__
#define AirParticleAffector_h__

#include "AirParticleEmitter.h"

namespace	Air{
	namespace	Engine{
		class	Particle;
		enum	enumForceFieldType{
			enFFT_PointForce,
			enFFT_DirectionForce,
			enFFT_DirectionVelocity,
			enFFT_RotateForce,
			enFFT_RotateVelocity,
		};
		class	ENGINE_EXPORT	ForceField	:	MemoryObject{
		public:
			enumForceFieldType	type;
			Float3				vForce_Velocity;
			Float3				vPosition;
			Float3				vAxis;
		};
		class	ENGINE_EXPORT	ParticleAffector	:	public	IProduct{
		public:
			struct Info{
				U32			uiCount;
				ForceField	forceField[4];
				U32			bEnableCollision;
			};
			static	AString	ProductTypeName;
			static	void*	ScriptParser(StringVector& vecWord,U32& i);
			ParticleAffector(CAString& strName,Info* pInfo);
			virtual	U1	Create();
			virtual	U1	Destroy();
			virtual	void	Update(const FrameTime& frameTime,Particle* pParticle);
		protected:
			void			UpdateForceField(ForceField* pForceField,Particle* pParticle);
		protected:
			void			UpdateVelocityPosition(const FrameTime& frameTime,ParticleElement* pElement,ForceField* pForceField);
			Info*			m_pInfo;
		};
	}
}
#endif // AirParticleAffector_h__