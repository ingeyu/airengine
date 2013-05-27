#include	"AirGameSkill.h"
#include	"AirGameSystem.h"
#include	"AirGameActor.h"
#include "AirParticle.h"
#include "AirEngineSceneNode.h"
namespace	Air{
	namespace	Game{

		AString	SkillTemplate::ProductTypeName="SkillTemplate";
		SkillTemplate::SkillTemplate( CAString& strName,Info* pInfo ):Common::IProduct(strName)
		{
			m_pInfo	=	pInfo;
		}

		Air::U1 SkillTemplate::Create()
		{
			if(m_pInfo==NULL)
			{
				return false;
			}
			return true;
		}

		Air::U1 SkillTemplate::Destroy()
		{

			return true;
		}

		void SkillTemplate::Update( const FrameTime& frameTime,Skill* pSkill )
		{

		}

		AString	Skill::ProductTypeName="Skill";
		Skill::Skill( CAString& strName,Info* pInfo ):Common::IProduct(strName)
		{
			m_fCurrentCoolDown	=	-1.0f;
			m_pTemplate		=	NULL;
			m_State			=	enSS_Ready;
			if(pInfo!=NULL){
				m_Info	=	*pInfo;
			}
			m_fAnimationLength	=	0.5f;
			m_pParticle			=	NULL;
		}

		Air::U1 Skill::Create()
		{
			if(m_Info.strTemplate.empty())
				return false;
			m_pTemplate			=	GameSystem::GetSingleton()->CreateProduct<SkillTemplate>(m_Info.strTemplate);

			SkillTemplate::Info&	stInfo	=	m_pTemplate->GetInfo();
			m_fAnimationLength	=	m_Info.pActor->GetModel()->GetAnimationLength(stInfo.strAnimationName);

			Engine::Particle::Info info;
			info.strTemplate	=	stInfo.strEffectName;
			m_pParticle			=	Engine::ParticleSystem::GetSingleton()->CreateProduct<Engine::Particle>(m_strProductName+"_Particle",&info);
			Engine::ParticleCB cb;
			cb.pObject	=		this;

			cb.pCB		=		(Engine::ElementHitCallback)Convert(&Skill::HitCallback);

			
			m_pParticle->SetCallback(cb);
			switch(stInfo.bindType){
				case enSBT_Bone:{
					m_Info.pActor->GetModel()->attachObject(stInfo.sbt_strBindBoneName,m_pParticle);
								}break;
				case enSBT_Node:{
					m_Info.pActor->GetNode()->attachObject(m_pParticle);
								}break;
				case enSBT_NewNode:{
					m_Info.pActor->GetNode()->attachObject(m_pParticle);
								   }break;
			}
			return true;
		}

		Air::U1 Skill::Destroy()
		{
			SkillTemplate::Info&	stInfo	=	m_pTemplate->GetInfo();
			switch(stInfo.bindType){
			case enSBT_Bone:{
				m_Info.pActor->GetModel()->detachObject(m_pParticle);
							}break;
			case enSBT_Node:{
				m_Info.pActor->GetNode()->detachObject(m_pParticle);
							}break;
			case enSBT_NewNode:{
				m_Info.pActor->GetNode()->detachObject(m_pParticle);
							   }break;
			}
			SAFE_RELEASE_REF(m_pTemplate);
			SAFE_RELEASE_REF(m_pParticle);
			return true;
		}

		void Skill::Update( const FrameTime& frameTime,Actor* pActor )
		{
			if(m_fCurrentCoolDown	<	0){
				m_pParticle->EnableEmitter(false);
				m_State	=	enSS_Ready;
				return;
			}
			switch(m_State){
				case enSS_Casting:{
					m_fCurrentCastTime	-=	frameTime.fTimeDelta;
					if(m_fCurrentCastTime	<	0){
						m_pParticle->EnableEmitter(false);
						m_State	=	enSS_CoolDown;
					}
								  }break;
				case enSS_CoolDown:{
					m_fCurrentCoolDown	-=	frameTime.fTimeDelta;
					if(m_fCurrentCoolDown	<	0){
						m_State	=	enSS_Ready;
					}

								   }break;
			}

			m_pTemplate->Update(frameTime,this);
		}

		void Skill::Cast( Actor* pActor )
		{
			if(m_fCurrentCoolDown	>	0){
				return;
			}else{
				if(m_pTemplate->GetCastType()	==	enSCT_Immediately){
					m_fCurrentCoolDown	=	m_pTemplate->GetCoolDownTime();
					m_fCurrentCastTime	=	-1;
					m_State				=	enSS_CoolDown;
					pActor->GetModel()->PlayAction(m_pTemplate->GetInfo().strAnimationName,0.05);
				}
				else	if(	m_pTemplate->GetCastType()	==	enSCT_HoldOn	||	m_pTemplate->GetCastType()	==	enSCT_TimeDelay)
				{
					if(m_State==enSS_Ready){
						m_fCurrentCastTime	=	m_pTemplate->GetCastTime();
						m_State				=	enSS_Casting;
						pActor->GetModel()->PlayAction(m_pTemplate->GetInfo().strAnimationName,0.05);
						
					}
				}
				if(m_pTemplate->GetCastType()	==	enSCT_HoldOn){
					m_pParticle->EnableEmitter(true);
				}
			}
		}

		void Skill::StopCast( Actor* pActor )
		{
			m_fCurrentCoolDown	=	m_pTemplate->GetCoolDownTime();
			if(m_fCurrentCoolDown	<	0){
				m_State		=	enSS_Ready;
			}else{
				if(m_State	==	enSS_Casting){
					m_State		=	enSS_CoolDown;
				}
			}
			m_pParticle->EnableEmitter(false);
		}

		void	__stdcall Skill::HitCallback( const Engine::ParticleElement& element, U32 hitMask, PhysicsObject* pObject )
		{

		}

	}
}