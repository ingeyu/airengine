#include "AirGameActor.h"
#include "AirEngineCharacterAnimationModel.h"
#include "AirEngineSystem.h"
#include "AirGameSystem.h"
#include "AirGameSection.h"
#include "AirGlobalSetting.h"
namespace	Air{
	namespace	Game{

		AString	Actor::ProductTypeName	=	"Actor";
		Actor::Actor( CAString& strName,Info* pInfo ):Common::IProduct(strName)
		{
			if(pInfo!=NULL){
				m_Info	=	*pInfo;
			}
			m_vFaceDir	=	Float3(0,0,1);
			m_pNode		=	NULL;
			m_uiLowBodyBoneIndex	=	0;
			m_pTarget				=	NULL;
			m_vecSkill.resize(12);
			m_pModel				=	NULL;
		}

		Air::U1 Actor::Create()
		{
			if (m_Info.strModelName.empty()	||	m_Info.pSection	==	NULL)
			{
				return false;
			}
			m_pNode	=	m_Info.pSection->GetActorNode()->CreateChildSceneNode();
			SetModelName(m_Info.strModelName);
			return true;
		}

		Air::U1 Actor::Destroy()
		{
			U32 uiSkillCount	=	m_vecSkill.size();
			for(U32 i=0;i<uiSkillCount;i++){
				SAFE_RELEASE_REF(m_vecSkill[i]);
			}
			m_vecSkill.clear();

			SAFE_RELEASE_REF(m_pModel);
			if(m_pNode!=NULL){
				m_pNode->GetParentSceneNode()->RemoveChild(m_pNode,true);
				m_pNode=NULL;
			}
			m_uiLowBodyBoneIndex=0;
			return true;
		}

		void Actor::Update( const FrameTime& frameTime )
		{
			float fDot =	acos(m_vFaceDir.Dot(Float3(0,0,1)));
			//Float3 vAxis	=	Float3(0,0,1).Cross(vDir).Normalize();

			if(m_vFaceDir.x < 0){
				fDot*=-1;
			}
			m_pNode->SetQuat(Float4(Float3(0,1,0),fDot));
				
			if(m_uiLowBodyBoneIndex!=0xffffffff){
				if(m_vMoveDir.Length()	<	0.5){
					m_pModel->DisableBoneExtraRotate(m_uiLowBodyBoneIndex);
				}else{

					Float3 vNewMoveDir	=	m_vMoveDir;

					float fRun	=	vNewMoveDir.Dot(m_vFaceDir);
					if(fRun	<0){
						vNewMoveDir*=-1;//m_pModel->EnableBoneExtraRotate(uiIndex,Float4(Float3(0,0,-1),fFootDot));
					}

					float	fFootAngle	=	acos(vNewMoveDir.Dot(m_vFaceDir));
					if(fFootAngle	< 0.00001f){
						m_pModel->EnableBoneExtraRotate(m_uiLowBodyBoneIndex,Float4(Float3(0,0,1),0));
					}else{
						Float3 vAxis		=	m_vFaceDir.Cross(vNewMoveDir).Normalize();
						m_pModel->EnableBoneExtraRotate(m_uiLowBodyBoneIndex,Float4(Float3(0,0,vAxis.y),-fFootAngle));
					}

				}
			}

			//UpdateSkill
			U32 uiSkillCount	=	m_vecSkill.size();
			for(U32 i=0;i<uiSkillCount;i++){
				Skill* pSkill	=	m_vecSkill[i];
				if(pSkill!=NULL){
					pSkill->Update(frameTime,this);
				}
			}
		}

		const	Float3& Actor::GetPosition()
		{
			return m_pNode->GetPosition();
		}

		void Actor::SetPosition( const Float3& v )
		{
			m_pNode->SetPosition(v);
		}

		void Actor::SetMoveState( enumActorMoveState state )
		{
			
			{
				if(state	==	enAMS_NoMove){
					m_pModel->SetActionState("stand.CAF");
					m_vMoveDir	=	Float3(0,0,0);
				}else{
					switch(state){
					case	enAMS_Left		:{
						m_vMoveDir	=	Float3(-1,0,0);
											 }break;
					case	enAMS_Right		:{
						m_vMoveDir	=	Float3(1,0,0);
											 }break;
					case	enAMS_Run		:{
						m_vMoveDir	=	Float3(0,0,1);
											 }break;
					case	enAMS_Back		:{
						m_vMoveDir	=	Float3(0,0,-1);
											 }break;
					case	enAMS_RunLeft	:{
						m_vMoveDir	=	Float3(-1,0,1).Normalize();
											 }break;
					case	enAMS_RunRight	:{
						m_vMoveDir	=	Float3(1,0,1).Normalize();
											 }break;
					case	enAMS_BackLeft	:{
						m_vMoveDir	=	Float3(-1,0,-1).Normalize();
											 }break;
					case	enAMS_BackRight	:{
						m_vMoveDir	=	Float3(1,0,-1).Normalize();
											 }break;
					}
					float fRun	=	m_vMoveDir.Dot(m_vFaceDir);
					if(fRun	>	0){
						m_pModel->SetActionState("run.CAF");
					}else{
						m_pModel->SetActionState("runback.CAF");
					}
				}
			}
		}

		void Actor::SetModelName( CAString& strModelName )
		{
			if(strModelName.empty())
				return;
			SAFE_RELEASE_REF(m_pModel);
			m_Info.strModelName	=	strModelName;
			AnimationModel::Info info;
			info.strTemplate	=	m_Info.strModelName;
			m_pModel	=	EngineSystem::GetSingleton()->CreateProduct<AnimationModel>(m_strProductName,&info);
			m_pModel->SetActionState("stand.CAF");
			m_uiLowBodyBoneIndex	=	m_pModel->GetBoneIndex("BoneWaist");
			m_pNode->CreateChildSceneNode(Float3(0,0,0),Float4(Float3(-1,0,0),1.57))->attachObject(m_pModel);
		}

		void Actor::SetSkill( U32 uiIndex,Skill* pSkill )
		{
			if(uiIndex>=m_vecSkill.size())
				return;
			Skill* pOldSkill	=	m_vecSkill[uiIndex];
			SAFE_RELEASE_REF(pOldSkill);
			if(pSkill!=NULL){
				pSkill->AddRef();
			}
			m_vecSkill[uiIndex]	=	pSkill;
		}

		void Actor::CastSkill( U32 uiIndex )
		{
			if(uiIndex	>=	m_vecSkill.size())
				return;
			Skill* pSkill	=	m_vecSkill[uiIndex];
			if(pSkill==NULL)
				return;
			//技能没有冷却
			if(pSkill->GetLeftCoolDownTime()>0){
				return;
			}
			pSkill->Cast(this);
		}

		void Actor::StopCastSkill( U32 uiIndex )
		{
			if(uiIndex	>=	m_vecSkill.size())
				return;
			Skill* pSkill	=	m_vecSkill[uiIndex];
			if(pSkill==NULL)
				return;
			//技能没有冷却
			if(pSkill->GetLeftCoolDownTime()>0){
				return;
			}
			pSkill->StopCast(this);
		}

	}
}