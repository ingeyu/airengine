#ifndef AirParticle_h__
#define AirParticle_h__

#include "AirEngineMovableObject.h"
#include "AirParticleElement.h"

namespace	Air{
	namespace	Engine{
		
		class ParticleTemplate;

		class ENGINE_EXPORT	Particle	:	
			public	IProduct,
			public	MovableObject{
		public:
			struct Info{
				AString strTemplate;
			};
			Particle(CAString& str,Info* pInfo);

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
			ParticleTemplate*				m_pTemplate;
			AString							m_strTemplate;
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