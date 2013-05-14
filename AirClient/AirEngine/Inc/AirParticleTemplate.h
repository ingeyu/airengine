#ifndef AirParticleTemplate_h__
#define AirParticleTemplate_h__

#include "AirEngineHeader.h"

namespace	Air{
	namespace	Engine{
		class	Particle;
		class	ParticleAffector;
		class	ParticleEmitter;
		class	ParticleRenderer;
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
				AChar*	strMaterial;
				void*	pEmitterInfo;
				void*	pAffectorInfo;
				void*	pRenderInfo;
				float	fLife;
			};
			ParticleTemplate(CAString&	strName);
			virtual	U1	Create();
			virtual	U1	Destroy();

			virtual	void	Update(const FrameTime& frameTime,Particle*	pParticle);
		public:
			virtual	U1					CreateFromFile(CAString& strName);
			inline	float				GetLife(){return m_fLife;};
			inline	ParticleEmitter*	GetEmitter(){return m_pEmitter;};
			inline	ParticleAffector*	GetAffector(){return m_pAffector;};
			inline	ParticleRenderer*	GetRenderer(){return m_pRenderer;};
			inline	Material*			GetMaterial(){return m_pMaterial;};
		protected:
			ParticleEmitter*				m_pEmitter;
			ParticleAffector*				m_pAffector;
			ParticleRenderer*				m_pRenderer;
			Material*						m_pMaterial;
			Data							m_Data;
			float							m_fLife;
		};
	}
}
#endif // AirParticleTemplate_h__