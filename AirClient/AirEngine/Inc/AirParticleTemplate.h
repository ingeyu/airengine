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
				void	Relative2Abs(){
					strEmitter		=	(AChar*)(((U8*)this)+(U32)strEmitter);
					strAffector		=	(AChar*)(((U8*)this)+(U32)strAffector);
					strRender		=	(AChar*)(((U8*)this)+(U32)strRender);
					strMaterial		=	(AChar*)(((U8*)this)+(U32)strMaterial);
					pEmitterInfo	=	(AChar*)(((U8*)this)+(U32)pEmitterInfo);
					pAffectorInfo	=	(AChar*)(((U8*)this)+(U32)pAffectorInfo);
					pRenderInfo		=	(AChar*)(((U8*)this)+(U32)pRenderInfo);
				};
				void	Abs2Relative(){
					strEmitter		=	(AChar*)((U32)strEmitter	-((U32)this));
					strAffector		=	(AChar*)((U32)strAffector	-((U32)this));
					strRender		=	(AChar*)((U32)strRender		-((U32)this));
					strMaterial		=	(AChar*)((U32)strMaterial	-((U32)this));
					pEmitterInfo	=	(AChar*)((U32)pEmitterInfo	-((U32)this));
					pAffectorInfo	=	(AChar*)((U32)pAffectorInfo	-((U32)this));
					pRenderInfo		=	(AChar*)((U32)pRenderInfo	-((U32)this));
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
			
			inline	float				GetLife(){return m_pInfo->fLife;};
			inline	ParticleEmitter*	GetEmitter(){return m_pEmitter;};
			inline	ParticleAffector*	GetAffector(){return m_pAffector;};
			inline	ParticleRenderer*	GetRenderer(){return m_pRenderer;};
			inline	Material*			GetMaterial(){return m_pMaterial;};
		protected:
			ParticleEmitter*				m_pEmitter;
			ParticleAffector*				m_pAffector;
			ParticleRenderer*				m_pRenderer;
			Material*						m_pMaterial;
			Info*							m_pInfo;
		};
	}
}
#endif // AirParticleTemplate_h__