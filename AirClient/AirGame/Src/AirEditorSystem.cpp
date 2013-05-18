#include "AirEditorSystem.h"
#include "AirGlobalSetting.h"
#include "AirInterfaceInputSystem.h"
#include "AirMeshEntity.h"
namespace	Air{
	namespace	Editor{


		System::System()
		{
			m_CM			=	enCM_Select;
			m_CT			=	enCT_Object;
			m_pRayCastMesh	=	NULL;
			m_bIsControl	=	FALSE;
			m_bLoading		=	false;
			m_bInit			=	false;
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
			if(m_bLoading){
				return true;
			}
			if(m_bIsControl){
				//Update Control Object
				switch(m_CM){
					case enCM_Move:{

					break;}
					case enCM_Rotate:{

					break;}
					case enCM_Scale:{

					break;}
					default:{
					break;}
				}
				return true;
			}else{
				UpdateRayCastPoint(arg);
			}
			
			return true;
		}

		bool System::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
		{
			if(m_bLoading){
				return true;
			}
			if(id==OIS::MB_Left){
				Engine::Scene* pScene	=	GameSystem::GetSingleton()->GetCurrentSection()->GetScene();
				switch(m_CM){
				case enCM_Select:{

					break;}
				case enCM_SelectList:{

					break;}
				case enCM_Move:
				case enCM_Rotate:
				case enCM_Scale:{
					m_bIsControl	=	true;
					break;}
				case enCM_Create:{
					
					break;}
				}
			}
			return true;
		}

		bool System::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
		{
			if(m_bLoading){
				return true;
			}
			if(id==OIS::MB_Left){
				Engine::Scene* pScene	=	GameSystem::GetSingleton()->GetCurrentSection()->GetScene();
				switch(m_CM){
					case enCM_Select:{
						m_lstSelectObj.clear();
						if(m_pRayCastMesh!=NULL){
							m_lstSelectObj.push_back(m_pRayCastMesh);
							Engine::SceneNode* pNode = m_pRayCastMesh->GetParentSceneNode();
							if(pNode!=NULL){
								const Float3 vObjPos = pNode->GetGlobalPosition();
								float fDis = pScene->GetMainCamera()->GetPosition().Distance(vObjPos);
								m_pObjController->SetPosition(pNode->GetGlobalPosition(),fDis*0.05);
							}
						}

						break;}
					case enCM_SelectList:{

						break;}
					case enCM_Move:{
						m_bIsControl	=	false;
						break;}
					case enCM_Rotate:{
						m_bIsControl	=	false;
						break;}
					case enCM_Scale:{
						m_bIsControl	=	false;
						break;}
					case enCM_Create:{
						AddObject(m_strCreateObjectName,m_vRayCastPoint);
						break;}
				}
			}
			return true;
		}

		bool System::keyPressed( const OIS::KeyEvent &arg )
		{
			if(m_bLoading){
				return true;
			}
			return true;
		}

		bool System::keyReleased( const OIS::KeyEvent &arg )
		{
			if(m_bLoading){
				return true;
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

		void System::UpdateRayCastPoint(const OIS::MouseEvent &arg)
		{
			Engine::Scene* pScene	=	GameSystem::GetSingleton()->GetCurrentSection()->GetScene();
			POINT	p;
			p.x	=	arg.state.X.abs;
			p.y	=	arg.state.Y.abs;

			RECT	r;
			GetClientRect(Engine::GetGlobalSetting().m_EngineParam.hWnd,&r);

			POINT	size;
			size.x	=	r.right		-	r.left;
			size.y	=	r.bottom	-	r.top;

			Ray	ray	=	pScene->GetMainCamera()->BuildRay(p.x/(float)size.x,p.y/(float)size.y);

			float	fDis	=	9999999.0f;
			Engine::MovableObject* pObj = NULL;
			if(pScene->GetStaticSceneNode()->RayCast(ray,pObj,&fDis)){
				m_vRayCastPoint	=	ray.m_vStart+ray.m_vDirection*fDis;
				m_pRayCastMesh	=	dynamic_cast<Engine::MeshEntity*>(pObj);
			}
		}

		void System::LoadScene( CAString& strName )
		{
			if(!m_bInit){
				m_strDelaySceneName	=	strName;
				return;
			}
			m_bLoading	=	true;
			m_lstSelectObj.clear();
			m_pRayCastMesh=NULL;
			m_CM		=	enCM_Select;
			Engine::SceneLoader& loader	=	GameSystem::GetSingleton()->GetCurrentSection()->GetScene()->GetLoader();
			loader.Load(strName);
			m_bLoading	=	false;
		}

		void System::SaveScene( CAString& strName )
		{

		}

		Air::AString System::AbsPath2Relatve( const AChar* strPath )
		{
			Air::AString	strSceneName	=	strPath;
			char* p = (char*)strstr(strSceneName.c_str(),"\\Data");
			p-=2;
			p[0]='.';
			p[1]='.';
			return p;
		}

	}
}