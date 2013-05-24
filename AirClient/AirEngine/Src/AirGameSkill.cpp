#include	"AirGameSkill.h"
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

		}

		Air::U1 Skill::Create()
		{
			return true;
		}

		Air::U1 Skill::Destroy()
		{
			return true;
		}

		void Skill::Update( const FrameTime& frameTime,Actor* pActor )
		{

		}

	}
}