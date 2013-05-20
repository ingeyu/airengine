#include "AirGameFPSControl.h"
#include "AirGameSection.h"

#include "OIS.h"
#include "AirEngineScene.h"
#include "AirEngineSceneNode.h"
#include "AirGlobalSetting.h"

using namespace OIS;
namespace Air{
	

	namespace	Game{
	
		AString	FPSControl::ProductTypeName	=	"FPSControl";
		FPSControl::FPSControl( CAString& strName,Info* pInfo ):Control(strName){
			m_Info		=	*pInfo;
			m_pNode		=	NULL;
	
			m_fLRAngle	=	0.0f;
			m_fUDAngle	=	0.0f;
			m_fCurrentLRAngle	=	0.0f;
			m_fCurrentUDAngle	=	0.0f;
	
		//	m_pController	=	NULL;
			m_State			=	enAS_Stand;
			m_Action		=	enA_None;
			m_LastState		=	enAS_Death;
			m_LastMoveState	=	(enumMoveState)0;
			m_MoveState		=	(enumMoveState)0;
	

		}
	
		U1 FPSControl::Create(){
			Engine::Scene*			pScene	=	m_Info.pSection->GetScene();
			//Audio::IScene*	pAScene	=	m_Info.pSection->GetAudioScene();
			//Physx::IScene*	pXScene	=	m_Info.pSection->GetPhysxScene();
	
			m_pNode				=	pScene->GetRootNode()->CreateChildSceneNode();
			m_pNode->SetPosition(m_Info.vPosition);
	


	
	
			return	true;
		}
	
		U1 FPSControl::Destroy(){
			Engine::Scene*			pScene	=	m_Info.pSection->GetScene();

	

			return	true;
		}
	
		bool FPSControl::keyPressed( const OIS::KeyEvent &arg ){
	
			return	true;
		}
	
		bool FPSControl::keyReleased( const OIS::KeyEvent &arg ){
			if(arg.key	==	OIS::KC_ESCAPE){
				m_pActionStateCallback->OnGameState(enExit);
			}
			return	true;
		}
	
		bool FPSControl::mouseMoved( const OIS::MouseEvent &arg ){
	
			if(m_pInputState->m_MouseArray[OIS::MB_Right]){
				Engine::GlobalSetting&		setting	=	Engine::GetGlobalSetting();
				Engine::ShaderShareParam&	sParam	=	setting.m_ShaderParam;
	
				Real fXDelta	=	Real(arg.state.X.rel) * 0.9f;
				Real fYDelta	=	Real(arg.state.Y.rel) * 0.9f;	
	
				m_fLRAngle	+=	fXDelta*sParam.m_fEngineTimeDelta;
				m_fUDAngle	+=	fYDelta*sParam.m_fEngineTimeDelta;
	
				if(m_fUDAngle	>=	1.57f)m_fUDAngle	=	1.56f;
				if(m_fUDAngle	<=	-1.57f)m_fUDAngle	=	-1.56f;
			}
			return	true;
		}
	
		bool FPSControl::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
	
			return	true;
		}
	
		bool FPSControl::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
	
			return	true;
		}
	
		bool FPSControl::buttonPressed( const OIS::JoyStickEvent &arg, int button ){
	
			return	true;
		}
	
		bool FPSControl::buttonReleased( const OIS::JoyStickEvent &arg, int button ){
	
			return	true;
		}
	
		bool FPSControl::axisMoved( const OIS::JoyStickEvent &arg, int axis ){
	
			return	true;
		}
	
		Engine::Camera* FPSControl::GetCamera(){
			return	m_pCamera;
		}
	
		U1 FPSControl::Update(const FrameTime& frameTime){
			static	Real	fFireTime	=	0.0f;
			Real	fTimeDelta			=	frameTime.fTimeDelta;
			if(m_pInputState->m_MouseArray[OIS::MB_Left])
				fFireTime+=fTimeDelta;
	
			m_Action	=	enA_None;
			if(fFireTime>0.1f){
				m_Action	=	enA_LAttack;
				if(m_pActionStateCallback!=NULL)
					m_pActionStateCallback->OnAction(m_Action);
	
				fFireTime	-=	0.1f;
			}
	
			//m_pNode->SetPosition(m_pController->GetPosition());
	
						//计算灵敏度
			Real	fSensitivity		=	fTimeDelta;
	
			//更新根节点位置
			Float3	vCurrentPos	;//=	//m_pController->GetPosition();
			m_pNode->SetPosition(vCurrentPos);
	
	
			//更新摄像机方向
			m_fCurrentLRAngle	+=	(m_fLRAngle	-	m_fCurrentLRAngle)*fSensitivity;
			m_fCurrentUDAngle	+=	(m_fUDAngle	-	m_fCurrentUDAngle)*fSensitivity;
			Float4	qY	=	Float4(Float3(0,1,0),m_fCurrentLRAngle);

			Float4	qX	=	Float4(Float3(1,0,0),m_fCurrentUDAngle);

	
			m_LastState		=	m_State;
			m_LastMoveState	=	m_MoveState;
			m_State		=	enAS_Stand;	
	
			Float4	vMove	=	Float4(0,0,0,0);
			int iFB	=0;int iLR=0;
			if(m_pInputState->m_KeyArray[KC_W]==1){
				vMove.x	=	5.0f;
				iFB	=	1;
			}
			if(m_pInputState->m_KeyArray[KC_S]==1){
				vMove.y	=	-2.0f;
				iFB	-=	1;
			}
			if(m_pInputState->m_KeyArray[KC_A]==1){
				vMove.z	=	3.0f;
				iLR=-1;
			}
			if(m_pInputState->m_KeyArray[KC_D]==1){
				vMove.z	=	-3.0f;
				iLR+=1;
			}
			
			if(iFB==1){
				m_MoveState	|=	enMS_Run;
			}else if(iFB==-1){
				m_MoveState	|=	enMS_Back;
			}

			if(iLR==1){
				m_MoveState	|=	enMS_Right;
			}else if(iLR==-1){
				m_MoveState	|=	enMS_Left;
			}
	
			if(IsStateChange()	||	m_pActionStateCallback!=NULL){
				m_pActionStateCallback->OnActorState(m_State,(enumMoveState)m_MoveState);
			}
	
			Float3	vPos	=	m_pNode->GetPosition();
			Float3	vDir	=	m_pCamera->GetRealDirection();
			Float3	vRight	=	m_pCamera->GetRealRightDirection();
			//vRight.y		=	30;
			vDir.Normalize();
			vRight.Normalize();
			Float3	vMoveDir	=	vDir*(vMove.x+vMove.y)	-	vRight*(vMove.z+vMove.w);
			vMoveDir.y=0.0f;
			vMoveDir.Normalize();
	 		//Vector3	vDelta	=	m_Info.vVelocity*vMoveDir*GetGlobalSetting().m_fTimeDelta;
// 			m_pCamera->SetPosition(vPos+vDelta);
// 			m_pCamera->SetLookAt(vLook+vDelta);
// 			m_pNode->SetPosition(m_pCamera->GetPosition());
	
			//m_pNode->SetPosition(vPos+vDelta);
// 			AChar	str[MAX_NAME];
// 			sprintf_s(str,"%f,%f,%f---%f,%f,%f\n",vPos.x,vPos.y,vPos.z,vDelta.x,vDelta.y,vDelta.z);
// 			::OutputDebugStringA(str);
	
			//m_pController->Move(m_Info.vVelocity*vMoveDir);
			return true;
		}
	
		Engine::SceneNode* FPSControl::GetControlNode(){
			return	m_pNode;
		}
	
		void FPSControl::SetPosition( Float3 vPosition ){
// 				if(m_pController!=NULL){
// 					m_pController->SetPosition(vPosition);
// 				}
			if(m_pNode!=NULL){
				m_pNode->SetPosition(vPosition);
			}
		}
	}
	
};