#include "AirParticleAffector.h"
#include "AirParticle.h"

namespace	Air{
	namespace	Engine{

		AString ParticleAffector::ProductTypeName	="DefaultAffector";
		ParticleAffector::ParticleAffector( CAString& strName,Info* pInfo ):IProduct(strName)
		{

		}

		void ParticleAffector::Update( const FrameTime& frameTime,Particle* pParticle )
		{
			PElementList& lst = pParticle->GetElementList();
			for(PElementList::iterator i = lst.begin();i!=lst.end();i++){
				(*i)->vPos += (*i)->vVelocity*frameTime.fTimeDelta;
			}
		}

		Air::U1 ParticleAffector::Create()
		{
			return true;
		}

		Air::U1 ParticleAffector::Destroy()
		{
			return true;
		}

		void* ParticleAffector::ScriptParser( StringVector& vecWord,U32& i )
		{
			while(true){
				AString& strTemp2	=	vecWord[i++];
				if(strTemp2=="}"){
					break;
				}
			}
			return NULL;
		}

	}
}