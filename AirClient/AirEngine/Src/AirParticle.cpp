#include "AirParticle.h"
#include "AirParticleTemplate.h"
#include "AirParticleRenderer.h"
namespace	Air{
	namespace	Engine{
		AString Particle::ProductTypeName="Particle";
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
			SetMaterial(m_pTemplate->GetMaterial());
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

		void Particle::OnRender( Render::Device* pDevice )
		{
			ParticleRenderer* pRenderer	=	m_pTemplate->GetRenderer();
			if(pRenderer!=NULL)
				pRenderer->OnParticleRender(pDevice,this);
		}

		ParticleSystem::ParticleSystem()
		{

		}

		Air::U1 ParticleSystem::Initialization()
		{

			return true;
		}

		Air::U1 ParticleSystem::Release()
		{

			return true;

		}

		void ParticleSystem::Update( const FrameTime& frameTime )
		{
			class UpdateParticle:public Common::TraversalCallback{
			public:
				UpdateParticle(const FrameTime& frameTime):t(frameTime){

				};
				virtual	void	OnTraversal(IProduct* pProduct){
					Particle* p = (Particle*)pProduct;
					p->Update(t);
				}
				const FrameTime& t;
			};

			IFactory* pFactory	=	GetFactory(Particle::ProductTypeName);
			if(pFactory!=NULL){
				UpdateParticle tempUpdate(frameTime);
				pFactory->TraversalProduct(&tempUpdate);
			}
		}

	}
}