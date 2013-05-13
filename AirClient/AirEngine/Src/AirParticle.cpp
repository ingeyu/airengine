#include "AirParticle.h"
#include "AirParticleTemplate.h"
namespace	Air{
	namespace	Engine{


		Particle::Particle( CAString& str,Info* pInfo ):IProduct(str)
		{
			m_pTemplate	=	NULL;
			if(pInfo!=NULL)
				m_strTemplate	=	pInfo->strTemplate;
			m_fBornTime	=	0;
		}

		Air::U1 Particle::Create()
		{
			m_fBornTime	=	GetTimer().m_FrameTime.fTotalTime;
			m_pTemplate	=	ParticleSystem::GetSingleton()->CreateProduct<ParticleTemplate>(m_strTemplate);
			if(m_pTemplate==NULL)
				return false;
			return true;
		}

		Air::U1 Particle::Destroy()
		{
			SAFE_RELEASE_REF(m_pTemplate);
			return true;
		}

		void Particle::Update( const FrameTime& frameTime )
		{
			if(m_pTemplate->GetLife() + m_fBornTime	<	frameTime.fTotalTime){
				return;
			}
			//当前帧不可见
			if(frameTime.uiFrameIndex	!=	m_uiVisiableFrame){
				return;
			}
			if(m_pTemplate!=NULL){
				m_pTemplate->Update(frameTime,this);
			}
		}

	}
}