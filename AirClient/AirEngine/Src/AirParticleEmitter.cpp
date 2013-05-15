#include "AirParticleEmitter.h"
#include "AirParticle.h"
namespace	Air{
	namespace	Engine{

		AString	ParticleEmitter::ProductTypeName	=	"DefaultEmitter";
		ParticleEmitter::ParticleEmitter( CAString& strName,Info* pInfo):IProduct(strName)
		{
			m_pInfo	=	pInfo;
			m_fUpdateTime		=	0.0f;
		}

		Air::U1 ParticleEmitter::Create()
		{
			if(m_pInfo==NULL){
				return false;
			}
			
			if(	m_pInfo->fFreq	<	0.000001f)
				return false;
			return	true;
						
		}

		Air::U1 ParticleEmitter::Destroy()
		{
			return	true;
		}

		void ParticleEmitter::Update( const FrameTime& frameTime ,Particle* pParticle)
		{

			
			//this is order list; borntime (earlier->later)
			PElementList& lst	=	pParticle->GetElementList();
			PElementList::iterator i = lst.begin();
			for(;i!=lst.end();){
				if((*i)->m_fBornTime	+	m_pInfo->fElementLife	<	frameTime.fTotalTime){
					delete (*i);
					i = lst.erase(i);
				}else{
					break;
				}
			}
			m_fUpdateTime	+=	frameTime.fTimeDelta;
			ElementBorn(frameTime,lst);

			
		}

		void ParticleEmitter::ElementBorn( const FrameTime& frameTime,PElementList& lst )
		{
			while(m_fUpdateTime>m_pInfo->fFreq){
				ParticleElement* p = NewElement(frameTime.fTotalTime);
				RandomPosition(p->vPos);
				RandomVelocity(p->vVelocity);
				RandomSize(p->m_fSize);
				lst.push_back(p);
				m_fUpdateTime-=m_pInfo->fFreq;
			}
		}

		void ParticleEmitter::RandomVelocity( Float3& vVelocity )
		{
			float fLength = m_pInfo->vVelocityDir.Length();
			Float3 v(
				Common::Number::RandomF(),
				Common::Number::RandomF(),
				Common::Number::RandomF());
			v=v.Normalize()*Common::Number::RandomF()*sin(m_pInfo->fVelocityAngle)+m_pInfo->vVelocityDir;//.Normalize();
			v.Normalize();
			vVelocity=v;
		}

		void ParticleEmitter::RandomPosition( Float3& vPos )
		{
			//VPos Default Float3(0,0,0)
		}

		void ParticleEmitter::RandomSize( float& fSize )
		{
			//fSize Default 1.0f
		}

		ParticleElement* ParticleEmitter::NewElement( double dTotalTime )
		{
			return new ParticleElement(dTotalTime);
		}

		AString	BoxEmitter::ProductTypeName="BoxEmitter";
		BoxEmitter::BoxEmitter( CAString& strName,BoxEmitter::Info* pInfo ):ParticleEmitter(strName,pInfo)
		{
			if(pInfo!=NULL){
				m_vCenter	=	pInfo->vCenter;
				m_vHalfSize	=	pInfo->vHalfSize;
			}
		}

		void	BoxEmitter::ElementBorn(const FrameTime& frameTime,PElementList& lst)
		{
			
			Float3 vPos(0,0,0);
			Float3 vVelocity;
			while(m_fUpdateTime>m_pInfo->fFreq){
				vPos	=	Float3(
					Common::Number::RandomF(),
					Common::Number::RandomF(),
					Common::Number::RandomF())/65535.0f;
				vPos=vPos*2-1;
				ParticleElement* p=new ParticleElement;
				p->vPos	=	&(m_vCenter+m_vHalfSize*vPos);
				lst.push_back(p);
				m_fUpdateTime-=m_pInfo->fFreq;
			}
		}

		AString	SphereEmitter::ProductTypeName="SphereEmitter";
		SphereEmitter::SphereEmitter( CAString& strName,SphereEmitter::Info* pInfo ):ParticleEmitter(strName,pInfo)
		{
			if(pInfo!=NULL){
				m_vCenter	=	pInfo->vCenter;
				m_fRadius	=	pInfo->fRadius;
			}
		}

		void	SphereEmitter::ElementBorn(const FrameTime& frameTime,PElementList& lst)
		{

			Float3 vPos(0,0,0);
			Float3 vVelocity;
			while(m_fUpdateTime>m_pInfo->fFreq){
				vPos	=	Float3(rand(),rand(),rand())/65535.0f;
				vPos=vPos*2-1;
				vPos.Normalize();
				ParticleElement* p=new ParticleElement;
				p->vPos	=	&(m_vCenter+vPos*m_fRadius*rand()/65535.0f);
				lst.push_back(p);
				m_fUpdateTime-=m_pInfo->fFreq;
			}
		}


	}
}