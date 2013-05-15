#include "AirParticleTemplate.h"
#include "AirParticleEmitter.h"
#include "AirParticleAffector.h"
#include "AirParticleRenderer.h"
#include "AirParticle.h"
#include "AirResourceSystem.h"
#include "AirEngineMaterial.h"
#include "AirEngineSystem.h"
#include "AirCommonParse.h"

namespace	Air{
	namespace	Engine{

		AString	ParticleTemplate::ProductTypeName	=	"ParticleTemplate";
		ParticleTemplate::ParticleTemplate( CAString& strName):IProduct(strName)
		{
			m_pAffector		=	NULL;
			m_pEmitter		=	NULL;
			m_pRenderer	=	NULL;
			m_pMaterial		=	NULL;
			m_pInfo		=	NULL;
		}

		Air::U1 ParticleTemplate::Create()
		{

			m_pInfo	=	(Info*)ParticleSystem::GetSingleton()->GetTemplateInfo(m_strProductName);
			if(m_pInfo==NULL){
				return false;
			}

			m_pEmitter	=	ParticleSystem::GetSingleton()->CreateProduct<ParticleEmitter>(m_strProductName+"_Emitter",m_pInfo->strEmitter,m_pInfo->pEmitterInfo);
			if(m_pEmitter==NULL)
				return false;
			m_pAffector	=	ParticleSystem::GetSingleton()->CreateProduct<ParticleAffector>(m_strProductName+"_Affector",m_pInfo->strAffector,m_pInfo->pAffectorInfo);
			if(m_pAffector==NULL)
				return false;
			m_pRenderer	=	ParticleSystem::GetSingleton()->CreateProduct<ParticleRenderer>(m_strProductName+"_Renderable",m_pInfo->strRender,m_pInfo->pRenderInfo);
			if(m_pRenderer==NULL)
				return false;
			m_pMaterial		=	EngineSystem::GetSingleton()->CreateProduct<Material>(m_pInfo->strMaterial);
			
			return true;
		}

		Air::U1 ParticleTemplate::Destroy()
		{
			
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

		void* ParticleTemplate::ScriptParser( StringVector& vecWord,U32& i )
		{
			ParticleTemplate::Info* pInfo	=	(ParticleTemplate::Info*)ParticleSystem::GetSingleton()->PTAlloc(sizeof(ParticleTemplate::Info));
			while(true){
				AString& strPT = vecWord[i++];
				if(strPT=="}"){
					break;
				}else if(strPT=="Life"){
					pInfo->fLife	=	Common::Parse::ParseFloat(vecWord,i);
					continue;
				}else if(strPT=="Material"){
					AString& strTemp	=	vecWord[i++];
					pInfo->strMaterial	=	(AChar*)ParticleSystem::GetSingleton()->PTAlloc(strTemp.c_str(),strTemp.size()+1);

				}else if(strPT=="Emitter"){
					AString& strTemp	=	vecWord[i++];
					pInfo->strEmitter	=	(AChar*)ParticleSystem::GetSingleton()->PTAlloc(strTemp.c_str(),strTemp.size()+1);
					ParticleScriptParser pParser = ParticleSystem::GetSingleton()->GetScriptParser(strTemp);
					if(pParser!=NULL){
						pInfo->pEmitterInfo		=	(*pParser)(vecWord,i);
					}

				}else if(strPT=="Affector"){
					AString& strTemp	=	vecWord[i++];
					pInfo->strAffector		=	(AChar*)ParticleSystem::GetSingleton()->PTAlloc(strTemp.c_str(),strTemp.size()+1);
					ParticleScriptParser pParser = ParticleSystem::GetSingleton()->GetScriptParser(strTemp);
					if(pParser!=NULL){
						pInfo->pAffectorInfo		=	(*pParser)(vecWord,i);
					}
				}else if(strPT=="Renderer"){
					AString& strTemp	=	vecWord[i++];
					pInfo->strRender	=	(AChar*)ParticleSystem::GetSingleton()->PTAlloc(strTemp.c_str(),strTemp.size()+1);
					ParticleScriptParser pParser = ParticleSystem::GetSingleton()->GetScriptParser(strTemp);
					if(pParser!=NULL){
						pInfo->pRenderInfo		=	(*pParser)(vecWord,i);
					}

				}

			}
			return pInfo;
		}



	}
}