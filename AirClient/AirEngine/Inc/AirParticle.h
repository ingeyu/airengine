#ifndef AirParticle_h__
#define AirParticle_h__

#include "AirEngineMovableObject.h"
#include "AirParticleElement.h"

namespace	Air{
	namespace	Engine{
		
		class ParticleEmitter;
		class ParticleRenderable;
		class ParticleAffector;
		class ParticleRecycle;

		class ENGINE_EXPORT	Particle	:	
			public	IProduct,
			public	MovableObject{
		public:
			struct Info{
				float	fLife;
				float	fElementLife;
				float	fMaxElementCount;
				Float3	vVelocityDir;
				float	fVelocityAngle;
			};
			Particle(CAString& str);

			virtual	U1	Create();
			virtual	U1	Destroy();
			virtual	void				Update(const FrameTime& frameTime);
			
			inline	U32					GetElementCount()const	{return m_lstElement.size();};
			inline	PElementList&		GetElementList()		{return m_lstElement;};
			//Call By Emitter
			virtual	void		OnElementBorn(ParticleElement* pElementArray,U32 uiCount);
		protected:
			float							m_fBornTime;
			PElementList					m_lstElement;

		};

		class ParticleSystem	:	
			public	IFactoryManager,
			public Singleton<ParticleSystem>
		{
		public:
			ParticleSystem();

			virtual	U1	Initialization();
			virtual	U1	Release();
		};
	}
}
#endif // AirParticle_h__