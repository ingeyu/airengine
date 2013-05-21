#include "AirEditorFreeControl.h"

namespace	Air{
	namespace	Editor{

		AString FreeControl::ProductTypeName="FreeControl";
		FreeControl::FreeControl( CAString& strName,Info* pInfo ):Game::FPSControl(strName,pInfo)
		{

		}

		Air::U1 FreeControl::Create()
		{
			return true;
		}

		Air::U1 FreeControl::Destroy()
		{
			return true;
		}

		bool FreeControl::mouseMoved( const OIS::MouseEvent &arg )
		{
			Engine::Camera*	pCam	=	m_Info.pCamera;

			S8*	pMouseArray	=	m_pInputState->m_MouseArray;

			if(pMouseArray[OIS::MB_Right]){
				Float3	dir		=	pCam->GetDir();
				Float3	pos		=	pCam->GetPosition();
				Float3 vRelativePos;//	=	pos	-	TargetPos;

				Float3	updir	=	pCam->GetUpDir();
				Float3	right	=	updir.Cross(dir);

				Common::Quaternion	quat(updir,arg.state.X.rel*0.0025f);


				Common::Quaternion	quat2(right,arg.state.Y.rel*0.0025f);



				vRelativePos	=	quat2*dir;


				vRelativePos	=	quat*vRelativePos;

				if(abs(vRelativePos.Dot(updir))	<0.99f){

					//dir	=	-vRelativePos.NormalizeCopy();
					pCam->SetDir(vRelativePos);

					//TargetPos	+=	dir*(arg.state.Z.rel*0.05f);
					//pos =	vRelativePos + TargetPos;//
					//m_pMainCamera->SetPosition(pos);
				}
			}else	if(pMouseArray[OIS::MB_Middle]){
				Float3	dir		=	pCam->GetDir();
				Float3	pos		=	pCam->GetPosition();
				//Float3 vRelativePos	=	pos	-	TargetPos;

				Float3	updir	=	pCam->GetUpDir();
				Float3	right	=	updir.Cross(dir);
				Float3  vRealUp	=	dir.Cross(right);

				Float3	Offset	=	-right*arg.state.X.rel*0.1f	+	vRealUp*arg.state.Y.rel*0.1f;
				//TargetPos		+=	Offset;
				pCam->SetPosition(pos+Offset);
			}
			Float3	dir		=	pCam->GetDir();
			Float3	pos		=	pCam->GetPosition();
			pCam->SetPosition(pos+dir*arg.state.Z.rel*0.1f);

			return true;
		}

		Air::U1 FreeControl::Update( const FrameTime& frameTime )
		{
			Float3 vMoveDirection;

			if(m_pInputState->m_KeyArray[OIS::KC_A]){
				vMoveDirection.x=	-m_Info.vVelocity;
			}else if(m_pInputState->m_KeyArray[OIS::KC_D]){
				vMoveDirection.x=	m_Info.vVelocity;
			}else{
				vMoveDirection.x=	0.0f;
			}

			if(m_pInputState->m_KeyArray[OIS::KC_S]){
				vMoveDirection.z=	-m_Info.vVelocity;
			}else if(m_pInputState->m_KeyArray[OIS::KC_W]){
				vMoveDirection.z=	m_Info.vVelocity;
			}else{
				vMoveDirection.z=	0.0f;
			}

			Engine::Camera*	pCam	=	m_Info.pCamera;
			Float3	vUp	=	pCam->GetUpDir();
			Float3	vDir	=	pCam->GetDir();
			Float3	vRight	=	vUp.Cross(vDir);
			vUp				=	vDir.Cross(vRight);
			Float3	x	=	vRight*vMoveDirection.x*frameTime.fTimeDelta;
			Float3	y	=	vUp*vMoveDirection.y*frameTime.fTimeDelta;
			Float3	z	=	vDir*vMoveDirection.z*frameTime.fTimeDelta;

			pCam->SetPosition(pCam->GetPosition()+x+y+z);


			return true;
		}

		Air::U1 FreeControl::keyReleased( const OIS::KeyEvent &arg )
		{


			return true;
		}

	}
}