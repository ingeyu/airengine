#include "AirParticleEmitter.h"
#include "AirParticle.h"
namespace	Air{
	namespace	Engine{


		ParticleEmitter::ParticleEmitter( CAString& strName,Info* pInfo):IProduct(strName)
		{
			if(pInfo!=NULL){

				m_fFreq			=	pInfo->fFreq;
			}else{

				m_fFreq			=	-1.0f;
			}
			m_fUpdateTime		=	0.0f;
		}

		Air::U1 ParticleEmitter::Create()
		{
			if(	m_fFreq	<	0.000001f)
				return false;
			return	true;
						
		}

		Air::U1 ParticleEmitter::Destroy()
		{
			return	true;
		}

		void ParticleEmitter::Update( const FrameTime& frameTime ,Particle* pParticle)
		{

			m_fUpdateTime	+=	frameTime.fTimeDelta;

			while(m_fUpdateTime>m_fFreq){
				pParticle->OnElementBorn(new ParticleElement());
				m_fUpdateTime-=m_fFreq;
			}

			
		}


		BoxEmitter::BoxEmitter( CAString& strName,BoxEmitter::Info* pInfo ):ParticleEmitter(strName,pInfo)
		{
			if(pInfo!=NULL){
				m_vCenter	=	pInfo->vCenter;
				m_vHalfSize	=	pInfo->vHalfSize;
			}
		}

		void BoxEmitter::Update( const FrameTime& frameTime ,Particle* pParticle)
		{
			m_fUpdateTime	+=	frameTime.fTimeDelta;
			Float3 vPos(0,0,0);
			Float3 vVelocity;
			while(m_fUpdateTime>m_fFreq){
				vPos	=	Float3(
					Common::Number::RandomF(),
					Common::Number::RandomF(),
					Common::Number::RandomF())/65535.0f;
				vPos=vPos*2-1;
				ParticleElement* p=new ParticleElement;
				p->vPos	=	&(m_vCenter+m_vHalfSize*vPos);
				pParticle->OnElementBorn(p);
				m_fUpdateTime-=m_fFreq;
			}
		}


		SphereEmitter::SphereEmitter( CAString& strName,SphereEmitter::Info* pInfo ):ParticleEmitter(strName,pInfo)
		{
			if(pInfo!=NULL){
				m_vCenter	=	pInfo->vCenter;
				m_fRadius	=	pInfo->fRadius;
			}
		}

		void SphereEmitter::Update( const FrameTime& frameTime,Particle* pParticle )
		{
			m_fUpdateTime	+=	frameTime.fTimeDelta;
			Float3 vPos(0,0,0);
			Float3 vVelocity;
			while(m_fUpdateTime>m_fFreq){
				vPos	=	Float3(rand(),rand(),rand())/65535.0f;
				vPos=vPos*2-1;
				vPos.Normalize();
				ParticleElement* p=new ParticleElement;
				p->vPos	=	&(m_vCenter+vPos*m_fRadius*rand()/65535.0f);
				pParticle->OnElementBorn(p);
				m_fUpdateTime-=m_fFreq;
			}
		}


	}
}