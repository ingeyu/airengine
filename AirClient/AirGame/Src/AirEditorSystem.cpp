#include "AirEditorSystem.h"
#include "AirGlobalSetting.h"
#include "AirInterfaceInputSystem.h"
#include "AirMeshEntity.h"
#include "AirEngineCharacterAnimationModel.h"
#include "AirCommonConverter.h"
#include "AirEnginePipeline.h"
#include "AirRenderSystem.h"
namespace	Air{
	namespace	Editor{


		System::System()
		{
			m_CM			=	enCM_Select;
			m_CT			=	enCT_Object;
			m_pRayCastMesh	=	NULL;
			m_bIsControl	=	FALSE;
			m_bEnableInput	=	false;
			m_bInit			=	false;
			m_MoveType		=	Engine::eMRCT_None;
		}

		Air::U1 System::Initialization()
		{
			if(m_bInit)
				return false;
			OIS::KeyListener*	pKey	=	this;
			OIS::MouseListener*	pMouse	=	this;
			Engine::GetGlobalSetting().m_pInputSystem->Add(pKey);
			Engine::GetGlobalSetting().m_pInputSystem->Add(pMouse);

			Engine::Scene* pScene	=	GameSystem::GetSingleton()->GetCurrentSection()->GetScene();


			m_pObjController	=	new Engine::ObjectController();
			pScene->GetDynamicSceneNode()->CreateChildSceneNode()->attachObject(m_pObjController);
			
			m_bInit	=	true;
			if(!m_strDelaySceneName.empty()){
				LoadScene(m_strDelaySceneName);
				m_strDelaySceneName.clear();
			}
			EnableInput(true);
			return true;
		}

		Air::U1 System::Release()
		{
			if(!m_bInit)
				return false;
			SAFE_DELETE(m_pObjController);
			OIS::KeyListener*	pKey	=	this;
			OIS::MouseListener*	pMouse	=	this;
			Engine::GetGlobalSetting().m_pInputSystem->Remove(pKey);
			Engine::GetGlobalSetting().m_pInputSystem->Remove(pMouse);
			m_bInit	=	false;
			return true;
		}

		bool System::mouseMoved( const OIS::MouseEvent &arg )
		{
			if(!m_bEnableInput){
				return true;
			}

			Ray	ray	=	BuildRay(arg.state.X.abs,arg.state.Y.abs);


			switch(m_CM){
				case enCM_Select:{
					m_bIsControl	=	false;
					UpdateRayCastPoint(ray);
								 }break;
				case enCM_Move:{
					if(m_bIsControl){
						if(m_MoveType!=Engine::eMRCT_None&&!m_lstSelectObj.empty()){

							Engine::Camera* pCam	=	GameSystem::GetSingleton()->GetCurrentSection()->GetScene()->GetMainCamera();
							Float3 vRight	=	pCam->GetRealRightDirection();
							Float3 vUp		=	pCam->GetRealUpDirection();

							Float3 vRealDir	=	vRight*(arg.state.X.abs	-	m_MoveDir.x)+vUp*(m_MoveDir.y-arg.state.Y.abs);
							Engine::MeshEntity* pMesh  = *(m_lstSelectObj.begin());

							Float3 v = m_OldPos;
							v[m_MoveType-1]+=vRealDir[m_MoveType-1]*0.1;
							pMesh->GetParentSceneNode()->SetPosition(v);
							Float44 mat;
							Float3 scale(1,1,1);
							Float4 q;
							pMesh->GetParentSceneNode()->Update(mat,q,scale,false);
							m_pObjController->SetPosition(v);
							m_pObjController->SetSelectObjectBoundingBox(pMesh->GetWorldBoundingBox());
						}
					}else{
						//m_MoveType	=	m_pObjController->ChangeType(ray.m_vStart,ray.m_vDirection);
						//Engine::Scene* pScene	=	GameSystem::GetSingleton()->GetCurrentSection()->GetScene();
						//Float44 matVPInv = pScene->GetMainCamera()->GetViewMatrix();
						////matVPInv.Inverse();
						//Float3 vProjPos = matVPInv*m_pObjController->GetParentSceneNode()->GetPosition();
						//Float2 vUV	=	Float2(vProjPos.x,vProjPos.y)*Float2(2,-2)+Float2(-1,1);

						m_MoveType	=	m_pObjController->ChangeType(ray.m_vStart,ray.m_vDirection);
					}
					break;}
				case enCM_Rotate:{
					if(m_bIsControl){
						if(m_MoveType!=Engine::eMRCT_None&&!m_lstSelectObj.empty()){
							Engine::MeshEntity* pMesh  = *(m_lstSelectObj.begin());
							Float2 dir = Float2(arg.state.X.abs,arg.state.Y.abs)	-	m_MoveDir;

							float fAngle	=	dir.y;
							if(m_MoveType==Engine::eMRCT_Y){
								 fAngle	=	dir.x;
							}
							Float3 vAxis;
							vAxis[m_MoveType-1]	=	1;
							Float4 q(vAxis,fAngle*0.1);
							
							pMesh->GetParentSceneNode()->SetQuat(m_OldQuat*q);
							Float44 mat;
							Float3 scale(1,1,1);
							q =	Float4(0,0,0,1);
							pMesh->GetParentSceneNode()->Update(mat,q,scale,false);
						}
					}else{
						m_MoveType	=	m_pObjController->ChangeType(ray.m_vStart,ray.m_vDirection);
					}
					break;}
				case enCM_Scale:{
					if(m_bIsControl){
						if(m_MoveType!=Engine::eMRCT_None&&!m_lstSelectObj.empty()){

							Engine::Camera* pCam	=	GameSystem::GetSingleton()->GetCurrentSection()->GetScene()->GetMainCamera();
							Float3 vRight	=	pCam->GetRealRightDirection();
							Float3 vUp		=	pCam->GetRealUpDirection();

							Float3 vRealDir	=	vRight*(arg.state.X.abs	-	m_MoveDir.x)+vUp*(m_MoveDir.y-arg.state.Y.abs);
							Engine::MeshEntity* pMesh  = *(m_lstSelectObj.begin());

							Float3 v = m_OldPos;
							v[m_MoveType-1]+=vRealDir[m_MoveType-1]*0.1;
							pMesh->GetParentSceneNode()->SetScale(v);
							Float44 mat;
							Float3 scale(1,1,1);
							Float4 q;
							pMesh->GetParentSceneNode()->Update(mat,q,scale,false);
							//m_pObjController->SetPosition(v);
							m_pObjController->SetSelectObjectBoundingBox(pMesh->GetWorldBoundingBox());
						}
					}else{
						m_MoveType	=	m_pObjController->ChangeType(ray.m_vStart,ray.m_vDirection);
					}
					break;}
				default:{
					m_bIsControl	=	false;
					//UpdateRayCastPoint(ray);
					break;}
			}
				
			
			
			return true;
		}

		bool System::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
		{
			if(!m_bEnableInput){
				return true;
			}
			if(id==OIS::MB_Left){
				Engine::Scene* pScene	=	GameSystem::GetSingleton()->GetCurrentSection()->GetScene();
				switch(m_CM){
				case enCM_Select:{

					break;}
				case enCM_SelectList:{

					break;}
				case enCM_Move:{
					if(m_MoveType!=Engine::eMRCT_None){
						m_bIsControl	=	true;
						m_MoveDir		=	Float2(arg.state.X.abs,arg.state.Y.abs);
						Engine::MeshEntityList::iterator i = m_lstSelectObj.begin();
						if(i!=m_lstSelectObj.end()){

							m_OldPos	=	(*i)->GetParentSceneNode()->GetPosition();
							Float3 vPositive	=	m_OldPos+Float3(10,10,10);
						}
					}
					break;}
				case enCM_Scale:{
					if(m_MoveType!=Engine::eMRCT_None){
						m_bIsControl	=	true;
						m_MoveDir		=	Float2(arg.state.X.abs,arg.state.Y.abs);
						Engine::MeshEntityList::iterator i = m_lstSelectObj.begin();
						if(i!=m_lstSelectObj.end()){
							m_OldPos	=	(*i)->GetParentSceneNode()->GetScale();
						}
					}
					break;}
				case enCM_Rotate:{
					if(m_MoveType!=Engine::eMRCT_None){
						m_bIsControl	=	true;
						m_MoveDir		=	Float2(arg.state.X.abs,arg.state.Y.abs);
						Engine::MeshEntityList::iterator i = m_lstSelectObj.begin();
						if(i!=m_lstSelectObj.end()){
							m_OldQuat	=	(*i)->GetParentSceneNode()->GetQuat();
						}
					}
								 }break;
				case enCM_Create:{
					
					break;}
				}
			}
			return true;
		}

		bool System::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
		{
			if(!m_bEnableInput){
				return true;
			}
			if(id==OIS::MB_Left){
				Engine::Scene* pScene	=	GameSystem::GetSingleton()->GetCurrentSection()->GetScene();
				switch(m_CM){
					case enCM_Select:{
						Ray ray = BuildRay(arg.state.X.abs,arg.state.Y.abs);
						Engine::MovableObject* pObj=NULL;
						if(pScene->GetStaticSceneNode()->RayCast(ray,pObj)){
							m_pRayCastMesh	=	dynamic_cast<Engine::MeshEntity*>(pObj);
							S8*	pKey = Engine::GetGlobalSetting().m_pInputSystem->m_KeyArray;
							if(	pKey[OIS::KC_LCONTROL]	==	0	&&
								pKey[OIS::KC_RCONTROL]	==	0)
							{
								m_lstSelectObj.clear();
							}
							if(m_pRayCastMesh!=NULL){
								m_lstSelectObj.push_back(m_pRayCastMesh);
								Engine::SceneNode* pNode = m_pRayCastMesh->GetParentSceneNode();
								if(pNode!=NULL){
									const Float3 vObjPos = pNode->GetGlobalPosition();
	
									m_pObjController->SetPosition(pNode->GetGlobalPosition());
								}
								m_pObjController->SetSelectObjectBoundingBox( m_pRayCastMesh->GetWorldBoundingBox());
							}else {
								m_pObjController->SetPosition(Float3(0,0,0));
								m_pObjController->SetSelectObjectBoundingBox(BoundingBox(-1,-1,-1,1,1,1));
							}
						}
						

						break;}
					case enCM_SelectList:{

						break;}
					case enCM_Move:
					case enCM_Rotate:
					case enCM_Scale:{
						m_bIsControl	=	false;
						m_MoveType		=	Engine::eMRCT_None;
						m_MoveDir		=	Float2(arg.state.X.abs,arg.state.Y.abs);
						break;}
					case enCM_Create:{
						Ray ray = BuildRay(arg.state.X.abs,arg.state.Y.abs);
						Engine::MovableObject* pObj=NULL;
						float fDis=999999.0f;
						if(pScene->GetStaticSceneNode()->RayCast(ray,pObj,&fDis)){
							m_vRayCastPoint	=	ray.m_vStart	+	ray.m_vDirection*fDis;
							switch(m_CT){
								case enCT_Object:{
									AddObject(m_strCreateObjectName,m_vRayCastPoint);
									}break;
								case enCT_Actor:{
									AddActor(m_strCreateObjectName,m_vRayCastPoint);
									}break;
							}
						}
									 
						break;}
				}
			}
			return true;
		}

		bool System::keyPressed( const OIS::KeyEvent &arg )
		{
			if(!m_bEnableInput){
				return true;
			}
			return true;
		}

		bool System::keyReleased( const OIS::KeyEvent &arg )
		{
			if(!m_bEnableInput){
				return true;
			}
			if(arg.key	==	OIS::KC_DELETE){
				Engine::SceneLoader& loader	=	GameSystem::GetSingleton()->GetCurrentSection()->GetScene()->GetLoader();
				Engine::MeshEntityList::iterator	i	=	m_lstSelectObj.begin();
				for(;i!=m_lstSelectObj.end();i++){
					if((*i)==m_pRayCastMesh){
						m_pRayCastMesh=NULL;
					}
					loader.RemoveEntity(*i);
				}
				m_lstSelectObj.clear();
				if(m_pObjController!=NULL){
					m_pObjController->SetPosition(Float3(0,0,0));
					m_pObjController->SetSelectObjectBoundingBox(BoundingBox(-1,-1,-1,1,1,1));
					if(m_pRayCastMesh==NULL){
						m_pObjController->SetRayCastObjectBoundingBox(BoundingBox(-1,-1,-1,1,1,1));
					}
				}
			}
			return true;
		}

		Air::U32 System::GetMeshEntity( Engine::MeshEntity** pObjectArray /*= NULL*/ )
		{
			Engine::SceneLoader& loader	=	GameSystem::GetSingleton()->GetCurrentSection()->GetScene()->GetLoader();
			if(pObjectArray!=NULL){
				U32 uiCount=0;
				Engine::MeshEntityList::iterator i= loader.GetAllEntity().begin();
				for(;i!=loader.GetAllEntity().end();i++){
					pObjectArray[uiCount++]	=	(*i);
				}
			}
			return loader.GetAllEntity().size();
		}

		Air::U32 System::GetMeshEntityName( AString* pStringArray/*=NULL*/ )
		{
			Engine::SceneLoader& loader	=	GameSystem::GetSingleton()->GetCurrentSection()->GetScene()->GetLoader();
			if(pStringArray!=NULL){
				U32 uiCount=0;
				Engine::MeshEntityList::iterator i= loader.GetAllEntity().begin();
				for(;i!=loader.GetAllEntity().end();i++){
					pStringArray[uiCount++]	=	(*i)->GetProductName();
				}
			}
			return loader.GetAllEntity().size();
		}

		void System::AddObject( CAString& strName,const Float3& vPos )
		{
			if(m_strCreateObjectName.empty())
				return;
			Engine::SceneLoader& loader	=	GameSystem::GetSingleton()->GetCurrentSection()->GetScene()->GetLoader();
			Transform trans;
			trans.pos	=	vPos;
			trans.rot	=	Float4(0,0,0,1);
			trans.scale	=	Float3(1,1,1);
			loader.AddEntity(strName,&trans);
		}

		void System::UpdateRayCastPoint(const Ray& ray)
		{
			Engine::Scene* pScene	=	GameSystem::GetSingleton()->GetCurrentSection()->GetScene();
			float	fDis	=	9999999.0f;
			Engine::MovableObject* pObj = NULL;
			if(pScene->GetStaticSceneNode()->RayCast(ray,pObj,&fDis)){
				m_vRayCastPoint	=	ray.m_vStart+ray.m_vDirection*fDis;
				m_pRayCastMesh	=	dynamic_cast<Engine::MeshEntity*>(pObj);
				if(m_pRayCastMesh!=NULL&&m_pObjController!=NULL){
					m_pObjController->SetRayCastObjectBoundingBox(m_pRayCastMesh->GetWorldBoundingBox());
				}
			}
		}

		void System::LoadScene( CAString& strName )
		{
			if(!m_bInit){
				m_strDelaySceneName	=	strName;
				return;
			}
			m_bEnableInput	=	false;
			m_lstSelectObj.clear();
			m_pRayCastMesh=NULL;
			m_CM		=	enCM_Select;
			GameSystem::GetSingleton()->GetCurrentSection()->LoadScene(strName);
			m_bEnableInput	=	true;
		}

		void System::SaveScene( CAString& strName )
		{
			m_bEnableInput	=	false;

			GameSystem::GetSingleton()->GetCurrentSection()->SaveScene(strName);
			m_bEnableInput	=	true;
		}

		Air::AString System::AbsPath2Relatve( const AChar* strPath )
		{
			Air::AString	strSceneName	=	strPath;
			char* p = (char*)strstr(strSceneName.c_str(),"\\Data\\");
			p+=6;
			return p;
		}
		void System::SetControlMode( enumControlMode m )
		{
			m_CM	=	m;
			if(m_pObjController!=NULL){
				switch(m){
					case enCM_Select:{
						m_pObjController->ChangeMode(Engine::eMCM_Select);
									 }break;
					case enCM_Move:{
						m_pObjController->ChangeMode(Engine::eMCM_Move);
									 }break;
					case enCM_Rotate:{
						m_pObjController->ChangeMode(Engine::eMCM_Rotate);
									 }break;
					case enCM_Scale:{
						m_pObjController->ChangeMode(Engine::eMCM_Scale);
									 }break;
					default:{
						m_pObjController->ChangeMode(Engine::eMCM_Select);
							}break;
				}
				
			}
		}

		Air::Ray System::BuildRay( S32 x,S32 y )
		{
			Engine::Scene* pScene	=	GameSystem::GetSingleton()->GetCurrentSection()->GetScene();
			POINT	p;
			p.x	=	x;//arg.state.X.abs;
			p.y	=	y;//arg.state.Y.abs;

			RECT	r;
			GetClientRect(Engine::GetGlobalSetting().m_EngineParam.hWnd,&r);

			POINT	size;
			size.x	=	r.right		-	r.left;
			size.y	=	r.bottom	-	r.top;

			return pScene->GetMainCamera()->BuildRay(p.x/(float)size.x,p.y/(float)size.y);
		}

		void System::AddActor( CAString& strName,const Float3& vPos )
		{
			if(m_strCreateObjectName.empty())
				return;
			Engine::SceneLoader& loader	=	GameSystem::GetSingleton()->GetCurrentSection()->GetScene()->GetLoader();
			Transform trans;
			trans.pos	=	vPos;
			trans.rot	=	Float4(Float3(-1,0,0),1.57);
			trans.scale	=	Float3(1,1,1);
			static U32 iName  =0;
			Engine::Character::Animation::Model::Info info;
			info.strTemplate	=	strName;
			loader.AddObject(Common::Converter::ToString(iName++),"CharacterModel",trans,(AChar*)&info);
		}

		void System::BuildSVO()
		{
			GameSystem::GetSingleton()->GetCurrentSection()->GetPipeline()->BuildSVO();
		}

		void System::ShowSVO( U1 bShow )
		{
			GameSystem::GetSingleton()->GetCurrentSection()->GetPipeline()->ShowSVO(bShow);
		}

		void System::ReloadModifyShader()
		{
			Engine::RenderSystem::GetSingleton()->ReloadModifyShader();
		}

	}
}