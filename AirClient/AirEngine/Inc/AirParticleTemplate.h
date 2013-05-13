#ifndef AirParticleTemplate_h__
#define AirParticleTemplate_h__

#include "AirEngineHeader.h"

namespace	Air{
	namespace	Engine{
		class	Particle;
		class	ParticleAffector;
		class	ParticleEmitter;
		class	ParticleRenderable;
		class	ENGINE_EXPORT	ParticleTemplate	:	public	IProduct
		{
		public:
			static	AString	ProductTypeName;
			struct Info 
			{
				void ReLocation(){
					strEmitter		=	(AChar*)(((U8*)this)+(U32)strEmitter);
					strAffector		=	(AChar*)(((U8*)this)+(U32)strAffector);
					strRender		=	(AChar*)(((U8*)this)+(U32)strRender);
					pEmitterInfo	=	(AChar*)(((U8*)this)+(U32)pEmitterInfo);
					pAffectorInfo	=	(AChar*)(((U8*)this)+(U32)pAffectorInfo);
					pRenderInfo		=	(AChar*)(((U8*)this)+(U32)pRenderInfo);
				};
				AChar*	strEmitter;
				AChar*	strAffector;
				AChar*	strRender;
				void*	pEmitterInfo;
				void*	pAffectorInfo;
				void*	pRenderInfo;
				float	fLife;
				float	fElementLife;
			};
			ParticleTemplate(CAString&	strName);
			virtual	U1	Create();
			virtual	U1	Destroy();

			virtual	void	Update(const FrameTime& frameTime,Particle*	pParticle);
		public:
			inline	float				GetLife(){return m_fLife;};
			inline	ParticleEmitter*	GetEmitter(){return m_pEmitter;};
			inline	ParticleAffector*	GetAffector(){return m_pAffector;};
			inline	ParticleRenderable*	GetRenderable(){return m_pRenderable;};
		protected:
			ParticleEmitter*				m_pEmitter;
			ParticleAffector*				m_pAffector;
			ParticleRenderable*				m_pRenderable;
			Data							m_Data;
			float							m_fLife;
		};
	}
}
#endif // AirParticleTemplate_h__