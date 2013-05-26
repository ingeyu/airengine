#ifndef AirGameSkill_h__
#define AirGameSkill_h__

#include "AirEngineHeader.h"
#include "AirParticle.h"
namespace	Air{
	namespace	Engine{
		class	Particle;
		class	ParticleElement;
	};
	namespace	Game{
		enum enumSkillCastType{
			enSCT_Immediately,
			enSCT_TimeDelay,
			enSCT_HoldOn,
		};
		enum enumSkillTargetType{
			enSTT_None,
			enSTT_Actor,
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
			enSDRT_Parabola,			//Å×ÎïÏß
		};
		enum enumSkillState{
			enSS_Ready,
			enSS_Casting,
			enSS_CoolDown,
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
				float				sct_castTime;
				Float3				stt_targetPos_Dir;
				float				stt_angle;
				float				sdt_DelayTime;
				float				sdt_FreqTime;
				float				sdrt_MaxDistance_Radius;
				AChar				sbt_strBindBoneName[16];
				AChar				strEffectName[16];
				AChar				strAnimationName[16];
			};
			SkillTemplate(CAString& strName,Info* pInfo);
			virtual	U1		Create();
			virtual	U1		Destroy();
			virtual	void	Update(const FrameTime& frameTime,Skill* pSkill);
		public:
			inline	Info&	GetInfo(){return *m_pInfo;};
		public:
			inline	float				GetCoolDownTime(){return m_pInfo->cooldownTime;}
			inline	enumSkillCastType	GetCastType(){return m_pInfo->castType;};
			inline	float				GetCastTime(){return m_pInfo->sct_castTime;};
			Info*	m_pInfo;
		};
		class	Actor;
		class	ENGINE_EXPORT	Skill	:	public	Common::IProduct{
		public:
			static AString	ProductTypeName;
			struct Info{
				AString	strTemplate;
				Actor*	pActor;
			};
			Skill(CAString&	strName,Info* pInfo);
			virtual	U1		Create();
			virtual	U1		Destroy();
			virtual	void	Update(const FrameTime& frameTime,Actor* pActor);
			virtual	void	Cast(Actor* pActor);
			virtual	void	StopCast(Actor* pActor);
		public:
			inline	enumSkillState	GetState(){return m_State;};
			inline	float			GetLeftCoolDownTime(){return m_fCurrentCoolDown;};
			inline	float			GetCoolDownTime(){return m_pTemplate->GetCoolDownTime();};
			inline	float			GetLeftCastTime(){return m_fCurrentCastTime;};
			inline	float			GetCastTime(){return m_pTemplate->GetCastTime();};

		protected:
			void	__stdcall		HitCallback(
				const Engine::ParticleElement&	element,
				U32								hitMask,
				void*							pObject
				);
		protected:
			float				m_fCurrentCoolDown;
			float				m_fCurrentCastTime;
			enumSkillState		m_State;
			SkillTemplate*		m_pTemplate;
			Info				m_Info;
			Engine::Particle*	m_pParticle;
			float				m_fAnimationLength;
			float				m_fAnimationUpdateTime;
		};
	}
	typedef	STD_VECTOR<Game::Skill*>	SkillVector;
}
#endif // AirGameSkill_h__