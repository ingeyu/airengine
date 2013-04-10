#include "AirGameThirdControl.h"
#include "AirGameSection.h"
#include "AirGameGlobal.h"
#include "OIS.h"
#include "AirGameSystem.h"

using namespace OIS;
namespace Air{
	
	namespace	Engine{
		namespace	Game{
	
	
			ThirdControl::ThirdControl( AString strName,Info* pInfo )	:
				FPSControl(strName,pInfo){
				m_fMinCameraDis	=	3.0f;
				m_fMaxCameraDis	=	20.0f;
				m_fCurrentDis	=	10.0f;
				m_fTargetDis	=	m_fCurrentDis;
				m_vTargetPosition	=	m_Info.vPosition;
				m_fMoveSensitivity	=	4.0f;
			}
	
			U1 ThirdControl::Create(){
				Scene*			pScene	=	m_Info.pSection->GetScene();
				Audio::IScene*	pAScene	=	m_Info.pSection->GetAudioScene();
				//Physx::IScene*	pXScene	=	m_Info.pSection->GetPhysxScene();
	
				m_pNode				=	pScene->GetRootNode()->CreateChildSceneNode();
				m_pNode->SetPosition(m_Info.vPosition);
				m_pNode->SetName("第三视角控制器 跟节点");
	
				//创建控制节点
				m_pLRNode			=	m_pNode->CreateChildSceneNode();
				m_pCameraUDNode		=	m_pLRNode->CreateChildSceneNode();
				m_pCameraUDNode->SetPosition(Float3(0,1.5f,0));
				m_pCameraNode		=	m_pCameraUDNode->CreateChildSceneNode();
				m_pCameraNode->SetPosition(Float3(0,0,m_fCurrentDis));
	
	
				m_pCamera	=	m_Info.pCamera;
	
				//绑定摄像机
				m_pCameraNode->attachObject(m_pCamera);
				//变更摄像机的方向
				m_pCamera->SetDir(Float3(0,0,-1));
	
				
				//m_pNode->attachObject(m_pCamera);
	
				//添加控制器到关卡中
				m_Info.pSection->AddControl(this);
// 	
// 				Physx::IController::Info	info;
// 				info.initPosition	=	m_Info.vPosition;
// 				info.size			=	Vector3(0.35f,1.7f,0.35f);
// 				m_pController	=	pXScene->Create<Physx::IController*>(m_strProductName,"Controller",&info);
	
				return	true;
			}
	
			U1 ThirdControl::Destroy(){
				Scene*			pScene	=	m_Info.pSection->GetScene();
				Audio::IScene*	pAScene	=	m_Info.pSection->GetAudioScene();
			//	Physx::IScene*	pXScene	=	m_Info.pSection->GetPhysxScene();
				//移除控制器
				m_Info.pSection->RemoveControl(this);
	
				//GetGlobalSetting().m_pEngine->DestroyProduct(m_pCamera);
				m_pCamera	=	NULL;
				pScene->GetRootNode()->RemoveChild(m_pNode,true);
				m_pNode	=	NULL;
// 	
// 				if(m_pController!=NULL){
// 					pXScene->DestroyProduct(m_pController);
// 					m_pController	=	NULL;
// 				}
				return	true;
			}
	
			U1 ThirdControl::OnFrameMove(){
	
				static	Real&	fTimeDelta	=	GetGlobalSetting().m_ShaderParam.m_fTimeDelta;
				//计算灵敏度
				Real	fSensitivity		=	fTimeDelta*m_fMoveSensitivity;
	
				Float3	vDir	=	m_pCamera->GetRealDirection();
				Float3	vRight	=	m_pCamera->GetRealRightDirection();
	
				//更新根节点位置
	 //			m_vTargetPosition	=	m_pController->GetPosition();
	// 			AString	strName	=	AString("[Control]")+Converter::toString(m_vTargetPosition)	+	AString("\n");
	// 			OutputDebugStringA(strName.c_str());
	
	 			Float3	vCurrentPos	=	m_pNode->GetPosition();
	 			vCurrentPos			+=	(m_vTargetPosition	-	vCurrentPos)*fSensitivity;
				m_pNode->SetPosition(m_vTargetPosition);
				
	
				//更新摄像机距离
				m_fCurrentDis	+=	(m_fTargetDis-m_fCurrentDis)*fSensitivity;
				m_pCameraNode->SetPosition(Float3(0,0,m_fCurrentDis));
	
				//更新摄像机方向
				m_fCurrentLRAngle	+=	(m_fLRAngle	-	m_fCurrentLRAngle)*fSensitivity;
				m_fCurrentUDAngle	+=	(m_fUDAngle	-	m_fCurrentUDAngle)*fSensitivity;
				Float4	qY	=	Float4(Float3(0,1,0),(m_fCurrentLRAngle));
				m_pNode->SetQuat(qY);
				
	
	
				Float4	qX	=	Float4(Float3(1,0,0),(m_fCurrentUDAngle));
				m_pCameraUDNode->SetQuat(qX);
	
					
	
					
	
	
					m_LastState	=	m_State;
					m_State		=	enStand;	
	
					Float4	vMove	=	Float4(0,0,0,0);
					if(m_pInputState->m_KeyArray[KC_W]==1){
						vMove.x	=	1.5f;
						m_State	=	enRun;
					}
					if(m_pInputState->m_KeyArray[KC_S]==1){
						vMove.y	=	-0.5f;
						m_State	=	enBack;
					}
					if(m_pInputState->m_KeyArray[KC_A]==1){
						vMove.z	=	-1.0f;
						m_State	=	enLeft;
					}
					if(m_pInputState->m_KeyArray[KC_D]==1){
						vMove.w	=	1.0f;
						m_State	=	enRight;
					}
	
					if(IsStateChange()	&&	m_pActionStateCallback!=NULL){
						m_pActionStateCallback->OnActorState(m_State);
					}
	
	
					vDir.Normalize();
					vRight.Normalize();
					Float3	vMoveDir	=	vDir*(vMove.x+vMove.y)	+	vRight*(vMove.z+vMove.w);
					vMoveDir.y=0.0f;
					vMoveDir.Normalize();
	
					//m_pController->Move(m_Info.vVelocity*vMoveDir);
					return true;
			}
			bool ThirdControl::mouseMoved( const OIS::MouseEvent &arg ){
	
				if(m_pInputState->m_MouseArray[OIS::MB_Right]){
					GlobalSetting&		setting	=	GetGlobalSetting();
					ShaderShareParam&	sParam	=	setting.m_ShaderParam;
	
					Real fXDelta	=	Real(arg.state.X.rel) * 0.9f;
					Real fYDelta	=	Real(arg.state.Y.rel) * 0.9f;	
	
					m_fLRAngle	+=	fXDelta*sParam.m_fEngineTimeDelta;
					m_fUDAngle	+=	-fYDelta*sParam.m_fEngineTimeDelta;
	
					if(m_fUDAngle	>=	1.57f)m_fUDAngle	=	1.56f;
					if(m_fUDAngle	<=	-1.57f)m_fUDAngle	=	-1.56f;
	
				}
	
				m_fTargetDis	-=	GetGlobalSetting().m_ShaderParam.m_fEngineTimeDelta*arg.state.Z.rel*0.5f;
				if(m_fTargetDis<m_fMinCameraDis)
					m_fTargetDis	=	m_fMinCameraDis;
				if(m_fTargetDis>m_fMaxCameraDis)
					m_fTargetDis	=	m_fMaxCameraDis;
				return	true;
			}
	
			bool ThirdControl::keyReleased( const OIS::KeyEvent &arg ){
				if(arg.key	==	OIS::KC_ESCAPE){
					m_pActionStateCallback->OnGameState(enExit);
				}
				using namespace OIS;
				if(m_pActionStateCallback!=NULL){
					enumAction	act	=	enNone;
					switch(arg.key){
						case	KC_SPACE:act	=	enHealth;
							break;
						case	KC_1:act		=	enMagicAttack1;
							break;
						case	KC_2:act		=	enMagicAttack2;
							break;
						case	KC_3:act		=	enMagicAttack3;
							break;
						case	KC_4:act		=	enMagicAttack4;
							break;
						case	KC_5:act		=	enMagicAttack5;
							break;
					}
					m_pActionStateCallback->OnAction(act);
				}
				return	true;
			}
	
		}
	}
};