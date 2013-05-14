#include "AirParticleTemplate.h"
#include "AirParticleEmitter.h"
#include "AirParticleAffector.h"
#include "AirParticleRenderer.h"
#include "AirParticle.h"
#include "AirResourceSystem.h"
#include "AirEngineMaterial.h"
#include "AirEngineSystem.h"

namespace	Air{
	namespace	Engine{

		AString	ParticleTemplate::ProductTypeName	=	"ParticleTemplate";
		ParticleTemplate::ParticleTemplate( CAString& strName):IProduct(strName)
		{
			m_pAffector		=	NULL;
			m_pEmitter		=	NULL;
			m_pRenderer	=	NULL;
			m_pMaterial		=	NULL;
			m_fLife		=	-1.0f;
		}

		Air::U1 ParticleTemplate::Create()
		{

			ResourceSystem::GetSingleton()->Find(m_strProductName+".pt",m_Data);
			if(m_Data.IsNull()){
				return CreateFromFile(m_strProductName+".pta");
			}
				
			Info*	pInfo	=	(Info*)m_Data.GetBuff();
			pInfo->ReLocation();

			m_fLife	=	pInfo->fLife;

			m_pEmitter	=	ParticleSystem::GetSingleton()->CreateProduct<ParticleEmitter>(m_strProductName+"_Emitter",pInfo->strEmitter,pInfo->pEmitterInfo);
			if(m_pEmitter==NULL)
				return false;
			m_pAffector	=	ParticleSystem::GetSingleton()->CreateProduct<ParticleAffector>(m_strProductName+"_Affector",pInfo->strAffector,pInfo->pAffectorInfo);
			if(m_pAffector==NULL)
				return false;
			m_pRenderer	=	ParticleSystem::GetSingleton()->CreateProduct<ParticleRenderer>(m_strProductName+"_Renderable",pInfo->strRender,pInfo->pRenderInfo);
			if(m_pRenderer==NULL)
				return false;
			m_pMaterial		=	EngineSystem::GetSingleton()->CreateProduct<Material>(pInfo->strMaterial);
			
			return true;
		}

		Air::U1 ParticleTemplate::Destroy()
		{
			m_Data.Clear();
			SAFE_RELEASE_REF(m_pEmitter);
			SAFE_RELEASE_REF(m_pAffector);
			SAFE_RELEASE_REF(m_pRenderer);
			SAFE_RELEASE_REF(m_pMaterial);
			return true;
		}

		void ParticleTemplate::Update( const FrameTime& frameTime,Particle* pParticle )
		{
			if(pParticle==NULL)
				return;
			m_pEmitter->Update(frameTime,pParticle);
			m_pAffector->Update(frameTime,pParticle);
		}

		Air::U1 ParticleTemplate::CreateFromFile( CAString& strName )
		{
			return true;
		}

	}
}