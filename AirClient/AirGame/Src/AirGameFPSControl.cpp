#include "AirGameFPSControl.h"
#include "AirGameSection.h"
#include "AirGameGlobal.h"
#include "OIS.h"

using namespace OIS;
namespace Air{
	
	namespace	Engine{
		namespace	Game{
	
	
			FPSControl::FPSControl( AString strName,Info* pInfo ):IProduct(strName){
				m_Info		=	*pInfo;
				m_pNode		=	NULL;
	
				m_fLRAngle	=	0.0f;
				m_fUDAngle	=	0.0f;
				m_fCurrentLRAngle	=	0.0f;
				m_fCurrentUDAngle	=	0.0f;
	
			//	m_pController	=	NULL;
				m_State		=	enStand;
				m_Action	=	enNone;
				m_LastState	=	enDeath;
	
				m_pLRNode	=	NULL;
				m_pCameraUDNode	=	NULL;
				m_pCameraNode	=	NULL;
			}
	
			U1 FPSControl::Create(){
				Scene*			pScene	=	m_Info.pSection->GetScene();
				Audio::IScene*	pAScene	=	m_Info.pSection->GetAudioScene();
				//Physx::IScene*	pXScene	=	m_Info.pSection->GetPhysxScene();
	
				m_pNode				=	pScene->GetRootNode()->CreateChildSceneNode();
				m_pNode->SetPosition(m_Info.vPosition);
	
				m_pLRNode			=	m_pNode->CreateChildSceneNode();
				m_pCameraUDNode		=	m_pLRNode->CreateChildSceneNode();
				m_pCameraNode		=	m_pCameraUDNode->CreateChildSceneNode();
	
				
				m_pCamera	=	m_Info.pCamera;
				m_pNode->attachObject(m_pCamera);
				//m_pNode->SetPosition(m_pCamera->GetPosition());
	// 			if(m_pCamera!=NULL)
	// 				m_pCamera->SetPosition(m_Info.vPosition);
	
				//添加控制器到关卡中
				m_Info.pSection->AddControl(this);
	
// 				Physx::IController::Info	info;
// 				info.initPosition	=	m_Info.vPosition;
// 				info.size			=	Vector3(0.5,1.7,0.5);
// 				m_pController	=	pXScene->Create<Physx::IController*>(m_strProductName,"Controller",&info);
	
	
				return	true;
			}
	
			U1 FPSControl::Destroy(){
				Scene*			pScene	=	m_Info.pSection->GetScene();
				Audio::IScene*	pAScene	=	m_Info.pSection->GetAudioScene();
				//Physx::IScene*	pXScene	=	m_Info.pSection->GetPhysxScene();
				//移除控制器
				m_Info.pSection->RemoveControl(this);
	
				//GetGlobalSetting().m_pEngine->DestroyProduct(m_pCamera);
				m_pCamera	=	NULL;
				pScene->GetRootNode()->RemoveChild(m_pNode,true);
				m_pNode	=	NULL;
	
// 				if(m_pController!=NULL){
// 					pXScene->DestroyProduct(m_pController);
// 					m_pController	=	NULL;
// 				}
	
				m_pLRNode	=	NULL;
				m_pCameraUDNode	=	NULL;
				m_pCameraNode	=	NULL;
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
					GlobalSetting&		setting	=	GetGlobalSetting();
					ShaderShareParam&	sParam	=	setting.m_ShaderParam;
	
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
	
			Camera* FPSControl::GetCamera(){
				return	m_pCamera;
			}
	
			U1 FPSControl::OnFrameMove(){
				static	Real	fFireTime	=	0.0f;
				Real	fTimeDelta			=	GetGlobalSetting().m_ShaderParam.m_fTimeDelta;
				if(m_pInputState->m_MouseArray[OIS::MB_Left])
					fFireTime+=fTimeDelta;
	
				m_Action	=	enNone;
				if(fFireTime>0.1f){
					m_Action	=	enAttack;
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
				m_pLRNode->SetQuat(qY);
				Float4	qX	=	Float4(Float3(1,0,0),m_fCurrentUDAngle);
				m_pCameraUDNode->SetQuat(qX);
	
				m_LastState	=	m_State;
				m_State		=	enStand;	
	
				Float4	vMove	=	Float4(0,0,0,0);
				if(m_pInputState->m_KeyArray[KC_W]==1){
					vMove.x	=	5.0f;
					m_State	=	enRun;
				}
				if(m_pInputState->m_KeyArray[KC_S]==1){
					vMove.y	=	-2.0f;
					m_State	=	enBack;
				}
				if(m_pInputState->m_KeyArray[KC_A]==1){
					vMove.z	=	3.0f;
					m_State	=	enRun;
				}
				if(m_pInputState->m_KeyArray[KC_D]==1){
					vMove.z	=	-3.0f;
					m_State	=	enRun;
				}
	
				if(IsStateChange()	||	m_pActionStateCallback!=NULL){
					m_pActionStateCallback->OnActorState(m_State);
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
	
			SceneNode* FPSControl::GetControlNode(){
				return	m_pLRNode;
			}
	
			void FPSControl::SetPosition( Float3 vPosition ){
// 				if(m_pController!=NULL){
// 					m_pController->SetPosition(vPosition);
// 				}
				if(m_pNode!=NULL){
					m_pNode->SetPosition(vPosition);
				}
			}
	
	
			FPSControlFactory::FPSControlFactory(){
				m_strTypeName	=	"FPSControl";
			}
	
			IProduct* FPSControlFactory::NewProduct( CAString& strName,IFactoryParamList* lstParam /* = NULL */ ){
				if(lstParam	==	NULL)
					return NULL;
	
				FPSControl::Info*	pInfo	=	(FPSControl::Info*)lstParam;
				FPSControl*			pBuff	=	new	FPSControl(strName,pInfo);
				return	pBuff;
			}
		}
	}
};