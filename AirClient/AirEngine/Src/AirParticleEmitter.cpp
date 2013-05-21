#include "AirParticleEmitter.h"
#include "AirParticle.h"
#include "AirCommonParse.h"
namespace	Air{
	namespace	Engine{

		AString	ParticleEmitter::ProductTypeName	=	"DefaultEmitter";
		ParticleEmitter::ParticleEmitter( CAString& strName,Info* pInfo):IProduct(strName)
		{
			m_pInfo				=	pInfo;
			m_fUpdateTime		=	0.0f;
			m_bEnable			=	true;
		}

		Air::U1 ParticleEmitter::Create()
		{
			if(m_pInfo==NULL){
				return false;
			}

			m_bEnable	=	m_pInfo->bEnable;
			
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
				if((*i)->fBornTime	+	m_pInfo->fElementLife	<	frameTime.fTotalTime){
					delete (*i);
					i = lst.erase(i);
				}else{
					break;
				}
			}
			if(m_bEnable){
				m_fUpdateTime	+=	frameTime.fTimeDelta;
				ElementBorn(frameTime,lst,pParticle);
			}
		}

		void ParticleEmitter::ElementBorn( const FrameTime& frameTime,PElementList& lst ,Particle* pParticle)
		{
			while(m_fUpdateTime>m_pInfo->fFreq){
				ParticleElement* p = NewElement(frameTime.fTotalTime);
				RandomPosition(p->vPos);
				p->vPos	=	(*pParticle->GetWorldMatrix())*p->vPos;
				RandomVelocity(p->vVelocity);
				Float3 vZeroPoint	=	(*pParticle->GetWorldMatrix())*Float3(0,0,0);
				p->vVelocity	=	(*pParticle->GetWorldMatrix())*p->vVelocity	-	vZeroPoint;
				RandomSize(p->fSize);
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
			v=v*2-1;
			v=v.Normalize()*Common::Number::RandomF()*m_pInfo->fVelocityAngle+m_pInfo->vVelocityDir;//.Normalize();
			//v.Normalize();
			vVelocity=v;
		}

		void ParticleEmitter::RandomPosition( Float3& vPos )
		{
			//VPos Default Float3(0,0,0)
		}

		void ParticleEmitter::RandomSize( float& fSize )
		{
			//fSize Default 1.0f
			fSize	=	m_pInfo->fElementSize;
		}

		ParticleElement* ParticleEmitter::NewElement( double dTotalTime )
		{
			return new ParticleElement(dTotalTime);
		}

		void* ParticleEmitter::ScriptParser( StringVector& vecWord,U32& i )
		{

			ParticleEmitter::Info* pEInfo = (ParticleEmitter::Info*)ParticleSystem::GetSingleton()->PTAlloc(sizeof(ParticleEmitter::Info));

			while(true){
				AString& strTemp2	=	vecWord[i++];
				if(strTemp2=="}"){
					break;
				}else if(strTemp2	==	"Freq"){
					pEInfo->fFreq	=	Common::Parse::ParseFloat(vecWord,i);
				}else if(strTemp2	==	"ElementLife"){
					pEInfo->fElementLife	=	Common::Parse::ParseFloat(vecWord,i);
				}
				else if(strTemp2	==	"ElementSize"){
					pEInfo->fElementSize	=	Common::Parse::ParseFloat(vecWord,i);
				}
				else if(strTemp2	==	"VelocityDir"){
					pEInfo->vVelocityDir.x	=	Common::Parse::ParseFloat(vecWord,i);
					pEInfo->vVelocityDir.y	=	Common::Parse::ParseFloat(vecWord,i);
					pEInfo->vVelocityDir.z	=	Common::Parse::ParseFloat(vecWord,i);
				}else if(strTemp2	==	"VelocityAngle"){
					pEInfo->fVelocityAngle	=	Common::Parse::ParseFloat(vecWord,i);
				}else if(strTemp2	==	"Enable"){
					pEInfo->bEnable			=	Common::Converter::ToU1(vecWord[i++]);
				}
			}
			return pEInfo;
		}


		AString	BoxEmitter::ProductTypeName="BoxEmitter";
		BoxEmitter::BoxEmitter( CAString& strName,BoxEmitter::Info* pInfo ):ParticleEmitter(strName,pInfo)
		{
		}
		void* BoxEmitter::ScriptParser( StringVector& vecWord,U32& i )
		{
			BoxEmitter::Info* pEInfo = (BoxEmitter::Info*)ParticleSystem::GetSingleton()->PTAlloc(sizeof(BoxEmitter::Info));

			while(true){
				AString& strTemp2	=	vecWord[i++];
				if(strTemp2=="}"){
					break;
				}else if(strTemp2=="{"){
					continue;
				}else if(strTemp2	==	"Freq"){
					pEInfo->fFreq	=	Common::Parse::ParseFloat(vecWord,i);
				}else if(strTemp2	==	"ElementLife"){
					pEInfo->fElementLife	=	Common::Parse::ParseFloat(vecWord,i);
				}else if(strTemp2	==	"ElementSize"){
					pEInfo->fElementSize	=	Common::Parse::ParseFloat(vecWord,i);
				}else if(strTemp2	==	"VelocityDir"){
					pEInfo->vVelocityDir.x	=	Common::Parse::ParseFloat(vecWord,i);
					pEInfo->vVelocityDir.y	=	Common::Parse::ParseFloat(vecWord,i);
					pEInfo->vVelocityDir.z	=	Common::Parse::ParseFloat(vecWord,i);
				}else if(strTemp2	==	"VelocityAngle"){
					pEInfo->fVelocityAngle	=	Common::Parse::ParseFloat(vecWord,i);
				}else if(strTemp2	==	"Center"){
					pEInfo->vCenter.x	=	Common::Parse::ParseFloat(vecWord,i);
					pEInfo->vCenter.y	=	Common::Parse::ParseFloat(vecWord,i);
					pEInfo->vCenter.z	=	Common::Parse::ParseFloat(vecWord,i);
				}else if(strTemp2	==	"HalfSize"){
					pEInfo->vHalfSize.x	=	Common::Parse::ParseFloat(vecWord,i);
					pEInfo->vHalfSize.y	=	Common::Parse::ParseFloat(vecWord,i);
					pEInfo->vHalfSize.z	=	Common::Parse::ParseFloat(vecWord,i);
				}
			}
			return pEInfo;
		}

		void BoxEmitter::RandomPosition( Float3& vPos )
		{
			Float3 v	=	Float3(
				Common::Number::RandomF(),
				Common::Number::RandomF(),
				Common::Number::RandomF());
			v=v*2-1;
			BoxEmitter::Info*	pInfo	=	(BoxEmitter::Info*)m_pInfo;
			vPos	=	pInfo->vCenter	+	pInfo->vHalfSize*v;
		}

		AString	SphereEmitter::ProductTypeName="SphereEmitter";
		SphereEmitter::SphereEmitter( CAString& strName,SphereEmitter::Info* pInfo ):ParticleEmitter(strName,pInfo)
		{
		}


		void SphereEmitter::RandomPosition( Float3& vPos )
		{
			Float3 v	=	Float3(
				Common::Number::RandomF(),
				Common::Number::RandomF(),
				Common::Number::RandomF());
			v=v*2-1;
			SphereEmitter::Info*	pInfo	=	(SphereEmitter::Info*)m_pInfo;
			vPos	=	pInfo->vCenter+v.Normalize()*pInfo->fRadius*Common::Number::RandomF();
		}

		void* SphereEmitter::ScriptParser( StringVector& vecWord,U32& i )
		{

			SphereEmitter::Info* pEInfo = (SphereEmitter::Info*)ParticleSystem::GetSingleton()->PTAlloc(sizeof(SphereEmitter::Info));

			while(true){
				AString& strTemp2	=	vecWord[i++];
				if(strTemp2=="}"){
					break;
				}else if(strTemp2=="{"){
					continue;
				}else if(strTemp2	==	"Freq"){
					pEInfo->fFreq	=	Common::Parse::ParseFloat(vecWord,i);
				}else if(strTemp2	==	"ElementLife"){
					pEInfo->fElementLife	=	Common::Parse::ParseFloat(vecWord,i);
				}else if(strTemp2	==	"ElementSize"){
					pEInfo->fElementSize	=	Common::Parse::ParseFloat(vecWord,i);
				}else if(strTemp2	==	"VelocityDir"){
					pEInfo->vVelocityDir.x	=	Common::Parse::ParseFloat(vecWord,i);
					pEInfo->vVelocityDir.y	=	Common::Parse::ParseFloat(vecWord,i);
					pEInfo->vVelocityDir.z	=	Common::Parse::ParseFloat(vecWord,i);
				}else if(strTemp2	==	"VelocityAngle"){
					pEInfo->fVelocityAngle	=	Common::Parse::ParseFloat(vecWord,i);
				}else if(strTemp2	==	"Center"){
					pEInfo->vCenter.x	=	Common::Parse::ParseFloat(vecWord,i);
					pEInfo->vCenter.y	=	Common::Parse::ParseFloat(vecWord,i);
					pEInfo->vCenter.z	=	Common::Parse::ParseFloat(vecWord,i);
				}else if(strTemp2	==	"Radius"){
					pEInfo->fRadius	=	Common::Parse::ParseFloat(vecWord,i);
				}
			}
			return pEInfo;
		}


	}
}