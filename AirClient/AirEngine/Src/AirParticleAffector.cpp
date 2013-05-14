#include "AirParticleAffector.h"
#include "AirParticle.h"

namespace	Air{
	namespace	Engine{


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

	}
}