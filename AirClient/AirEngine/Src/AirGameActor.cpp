#include "AirGameActor.h"
#include "AirEngineCharacterAnimationModel.h"
#include "AirEngineSystem.h"
#include "AirGameSystem.h"
#include "AirGameSection.h"
#include "AirGlobalSetting.h"
#include "AirPhysicsObject.h"
#include "AirPhysicsSystem.h"
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
			m_pHitShape				=	NULL;
			m_pMoveShape			=	NULL;
			m_MoveState				=	enAMS_NoMove;
			m_fMoveVelocity			=	1.5f;
		}

		Air::U1 Actor::Create()
		{
			if (m_Info.strModelName.empty()	||	m_Info.pSection	==	NULL)
			{
				return false;
			}
			m_pNode	=	m_Info.pSection->GetActorNode()->CreateChildSceneNode();
			SetModelName(m_Info.strModelName);

			Physics::Object::Info poInfo;
			poInfo.fMass	=	1;
			poInfo.uiShapeCount	=	1;
			poInfo.pShapeArray[0].SetCylinder(Float3(0,0,0),0.5,1);
			m_pHitShape	=	PhysicsSystem::GetSingleton()->CreateProduct<Physics::Object>(m_strProductName+"_CD",&poInfo);
			m_pHitShape->SetUserData(this);
			m_pNode->attachObject(m_pHitShape);
			return true;
		}

		Air::U1 Actor::Destroy()
		{
			SAFE_RELEASE_REF(m_pHitShape);
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
			Move(frameTime.fTimeDelta);
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
			if(m_MoveState	==	state)
				return;
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

		Air::U1 Actor::Move(float fTimeDelta)
		{
			if(m_MoveState==enAMS_NoMove){
				return false;
			}

			Float3	vMoveDir	=	m_vMoveDir;
			vMoveDir.y=0.0f;
			vMoveDir.Normalize();

			Float3 vOldPos		=	m_pNode->GetPosition();
			Float3	vCurrentPos	=	m_pNode->GetPosition();
			//vCurrentPos			+=	vMoveDir*fSensitivity;
			Float3 vNewVelocity	=	vMoveDir*m_fMoveVelocity;
			vNewVelocity.y	=	m_vMoveDir.y;
			PhysicsSystem::GetSingleton()->Silumation(vCurrentPos,0.5,1,vNewVelocity,fTimeDelta);
			m_vMoveDir.y		=	vNewVelocity.y;
			if(vCurrentPos.y<-1){
				vCurrentPos.y=1;
				m_vMoveDir.y		=	0;
			}

			m_pNode->SetPosition(vCurrentPos);

			return true;
		}

		void Actor::SetMoveDirection( const Float3& v )
		{
			m_vMoveDir.x	=	v.x;
			m_vMoveDir.z	=	v.z;
			
			if(v.Length()	<0.00001){
				if(m_MoveState!=enAMS_NoMove){
					m_pModel->SetActionState("stand.CAF");
					m_MoveState	=	enAMS_NoMove;
				}
			}else{
				float fRun	=	m_vMoveDir.Dot(m_vFaceDir);
				if(fRun	>	0){
					
					if(m_MoveState!=enAMS_CustomRun){
						m_MoveState	=	enAMS_CustomRun;
						m_pModel->SetActionState("run.CAF");
					}
				}else{
					if(m_MoveState!=enAMS_CustomBack){
						m_MoveState	=	enAMS_CustomBack;
						m_pModel->SetActionState("runback.CAF");
					}
				}

				
			}


		}

		void Actor::UpdateActionState( enumActorMoveState state )
		{
			
		}

	}
}