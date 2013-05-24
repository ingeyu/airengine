#ifndef AirGameSkill_h__
#define AirGameSkill_h__

#include "AirEngineHeader.h"

namespace	Air{
	namespace	Game{
		enum enumSkillCastType{
			enSCT_Immediately,
			enSCT_TimeDelay,
			enSCT_TimeFreq,
		};
		enum enumSkillTargetType{
			enSTT_None,
			enSTT_Actor,
			enSTT_Enemy,
			enSTT_Friend,
			enSTT_Position,
			enSTT_Direction,
			enSTT_Cone,
		};
		enum enumSkillBindType{
			enSBT_None,
			enSBT_Bone,
			enSBT_Node,
			enSBT_NewNode
		};

		enum enumSkillDamageType{
			enSDT_Immediately	=	1,
			enSDT_TimeDelay		=	2,
			enSDT_TimeFreq		=	4,
			enSDT_ImmediatelyAndTimeDelay	=	enSDT_Immediately	|	enSDT_TimeDelay,
			enSDT_ImmediatelyAndTimeFreq	=	enSDT_Immediately	|	enSDT_TimeFreq,
			enSDT_TimeDelayAndTimeFreq		=	enSDT_TimeDelay		|	enSDT_TimeFreq,
		};
		enum enumSkillDamageRangeType{
			enSDRT_Sphere,
			enSDRT_Cone,
			enSDRT_Line,
		};
		class	Skill;
		class	ENGINE_EXPORT	SkillTemplate	:	public	Common::IProduct{
		public:
			static AString	ProductTypeName;
			struct Info{
				float				cooldownTime;
				enumSkillCastType	castType;
				enumSkillTargetType	targetType;
				enumSkillBindType	bindType;
				enumSkillDamageType	damageType;
				Float3				stt_targetPos_Dir;
				float				stt_angle;
				float				sdt_DelayTime;
				float				sdt_FreqTime;
				float				sdrt_MaxDistance_Radius;
				AChar				sbt_strBindBoneName[16];
				AChar				strEffectName[16];
			};
			SkillTemplate(CAString& strName,Info* pInfo);
			virtual	U1		Create();
			virtual	U1		Destroy();
			virtual	void	Update(const FrameTime& frameTime,Skill* pSkill);
			inline	float	GetCoolDownTime(){return m_pInfo->cooldownTime;}

			Info*	m_pInfo;
		};
		class	Actor;
		class	ENGINE_EXPORT	Skill	:	public	Common::IProduct{
		public:
			static AString	ProductTypeName;
			struct Info{
				enumSkillCastType	castType;
				enumSkillTargetType	targetType;
			};
			Skill(CAString&	strName,Info* pInfo);
			virtual	U1	Create();
			virtual	U1	Destroy();
			virtual	void	Update(const FrameTime& frameTime,Actor* pActor);

			float		m_fCurrentDown;
		};
	}
}
#endif // AirGameSkill_h__