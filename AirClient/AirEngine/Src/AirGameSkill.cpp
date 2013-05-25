#include	"AirGameSkill.h"
#include	"AirGameSystem.h"
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
		}

		Air::U1 Skill::Create()
		{
			if(m_Info.strTemplate.empty())
				return false;
			m_pTemplate	=	GameSystem::GetSingleton()->CreateProduct<SkillTemplate>(m_Info.strTemplate);
			return true;
		}

		Air::U1 Skill::Destroy()
		{
			return true;
		}

		void Skill::Update( const FrameTime& frameTime,Actor* pActor )
		{
			if(m_fCurrentCoolDown	<	0){
				m_State	=	enSS_Ready;
				return;
			}
			switch(m_State){
				case enSS_Casting:{
					m_fCurrentCastTime	-=	frameTime.fTimeDelta;
					if(m_fCurrentCastTime	<	0){
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
				}else	if(	m_pTemplate->GetCastType()	==	enSCT_HoldOn	||
							m_pTemplate->GetCastType()	==	enSCT_TimeDelay){
					m_fCurrentCastTime	=	m_pTemplate->GetCastTime();
					m_State				=	enSS_Casting;
				}
			}
		}

		void Skill::StopCast( Actor* pActor )
		{
			m_fCurrentCoolDown	=	m_pTemplate->GetCoolDownTime();
			if(m_fCurrentCoolDown	<	0){
				m_State		=	enSS_Ready;
			}else{
				m_State		=	enSS_CoolDown;
			}
		}

	}
}