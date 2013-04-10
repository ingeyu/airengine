#include "AirGameSection.h"
#include "AirGameGlobal.h"
//#include "DecorationShowSystem.h"
#include "AirGameSystem.h"
#include "AirEngineSystem.h"
namespace Air{
	
	
	namespace	Engine{
		namespace	Game{
	
			SubEntity*		pEntity	=	NULL;
			RenderTarget*	pTarget	=	NULL;
	//		DecorationShowSystem*	pShowSys	=	NULL;
	
			
	
			Section::Section( CAString& strName ):Common::IProduct(strName){
				m_pScene		=	NULL;
				m_pAudioScene	=	NULL;
				//m_pPhysxScene	=	NULL;
				m_pDefaultCamera	=	NULL;
				
	
				AChar	str[128];
				sprintf_s(str,128,"%s = %x\n",strName.c_str(),(UInt)this);
				OutputDebugStringA(str);
			}
	
			U1 Section::Create(){
				GlobalSetting&	setting	=	GetGlobalSetting();
				Log::GetSingleton()->Write("创建渲染场景");
				//创建场景
				if(setting.m_pEngine!=NULL){
					m_pScene		=	setting.m_pEngine->CreateScene(m_strProductName);
				}
				Log::GetSingleton()->Write("创建音频场景");
				//创建音频场景
				if(setting.m_pAudioSystem!=NULL){
					m_pAudioScene	=	setting.m_pAudioSystem->CreateScene(m_strProductName);
				}
// 				Log::GetSingleton()->Write("创建物体场景");
// 				//创建物理场景
// 				if(setting.m_pPhysxSystem!=NULL){
// 					m_pPhysxScene	=	setting.m_pPhysxSystem->CreateScene(m_strProductName);
// 				}
// 				
	
	// 			RenderTarget::Info	info;
	// 			info.SetRenderToTexture(512,512,true);
	// 			pTarget			=	Render::System::GetSingleton()->Create<RenderTarget*>("Test","Target",&info);
	// 			if(pTarget!=NULL){
	//  				Camera*			pTargetCamera	=	m_pScene->CreateCamera("TargetCamera");
	//  				pTarget->SetCamera(pTargetCamera);
	// 				pTarget->SetBKColor(0xAAAAAAAA);
	//  				pTargetCamera->SetPosition(Vector3(100,100,100));
	// 				pTargetCamera->SetLookAt(Vector3::ZERO);
	// 				m_pScene->AddTarget(pTarget);
	// 			}
	
	
				m_pDefaultCamera	=	CreateDefaultCamera();
				//SetCamera(m_pDefaultCamera);
				m_pDefaultControl	=	CreateDefaultControl(m_pDefaultCamera);
				//AddControl(m_pDefaultControl);
	
				m_pObject	=	(UInt*)m_pScene;
				return true;
			}
	
			U1 Section::Destroy(){
	
				if(m_pDefaultControl!=NULL){
					GetGlobal().m_pSystem->DestroyProduct(m_pDefaultControl);
					m_pDefaultControl	=	NULL;
				}
	
	
				if(m_pScene!=NULL){
					if(pTarget!=NULL){
						
	 					Camera*	pTargetCamera	=	NULL;//pTarget->GetCamera();
	 					m_pScene->DestroyCamera(pTargetCamera);
						//pTarget->SetCamera(NULL);
						//m_pScene->RemoveTarget(pTarget);
						//场景会自动帮你摧毁
						//Render::System::GetSingleton()->DestroyProduct(pTarget);
						pTarget=NULL;
					}
	
					//Camera*	pCamera	=	m_pScene->GetCamera();
					if(m_pDefaultCamera!=NULL)
						m_pScene->DestroyCamera(m_pDefaultCamera);
					m_pDefaultCamera	=	NULL;
// 					m_pScene->SetCamera(NULL);
// 					EngineSystem::GetSingleton()->DestroyScene(m_pScene);
					m_pScene	=	NULL;
				}
				m_pObject	=	NULL;
	
	
				if(m_pAudioScene!=NULL){
					GetGlobalSetting().m_pAudioSystem->DestroyScene(m_pAudioScene);
					m_pAudioScene=NULL;
				}
// 				if(m_pPhysxScene!=NULL){
// 					GetGlobalSetting().m_pPhysxSystem->DestroyScene(m_pPhysxScene);
// 					m_pPhysxScene=NULL;
// 				}
	
				return true;
			}
	
			void Section::OnRender(){

			}
	
			U1 Section::Load( AString strName ){
				//AString strMaterial	=	"..\\Data\\Model\\8192.Material";
				//AString	strMaterialTest	=	"..\\Data\\Material\\NoTexture.Material";
				//pEntity	=	GetGlobalSetting().m_pEngine->Create<SubEntity*>("..\\Data\\Model\\Sphere.X","SubEntity",&strMaterialTest);
				//m_pScene->GetRootNode()->attachObject(pEntity);
				//m_pScene->GetRootNode()->SetScale(Vector3(0.01f,0.01f,0.01f));
	// 			DecorationShowSystem::Info info;
	// 			info.pParentNode	=	m_pScene->GetRootNode();
	// 			info.pCamera		=	m_pScene->GetCamera();
	// 			pShowSys	=	GetGlobalSetting().m_pGameSystem->Create<DecorationShowSystem*>("..\\Data\\Model\\final.txt","DecorationShowSystem",&info);
	
				//声音测试
	// 			Audio::ISound::Info	bginfo;
	// 			//bginfo.fVolume	=	0.2f;
	// 			bginfo.fPitch	=	0.5f;
	// 			//bginfo.vPosition	=	Vector3(-132.067f,-56.14f,8.813f);
	// 			bginfo.fDistance	=	1000.0f;
	// 			bginfo.SetDynamic("..\\Data\\Audio\\mouse_click.wav",Vector3(0,200,0),1000);
	// 			//bginfo.strName	=	"..\\Data\\Audio\\mouse_click.wav";
	// 			if(m_pAudioScene!=NULL){
	// 				m_pAudioScene->Play(&bginfo);
	// 			}
	
				//物理测试
	// 			Physx::ICollision::Info	cInfo;
	// 			cInfo.shape.SetPlane(Vector3::UNIT_Y,0);
	// 			m_pPhysxScene->Create("Ground","Collision",&cInfo);
	// 
	// 			cInfo.shape.Clear();
	// 			cInfo.SetDynamic(10.0f);
	// 			cInfo.shape.SetBox(Vector3(3,3,3));
	// 			Physx::ICollision*	p	=	m_pPhysxScene->Create<Physx::ICollision*>("Box","Collision",&cInfo);
	// 			p->SetPosition(Vector3(0,10,0));
	// 			p->AddVelocity(Vector3(0,0,1));
				return true;
			}
	
			U1 Section::UnLoad(){
	// 			if(pShowSys!=NULL){
	// 				GetGlobalSetting().m_pGameSystem->DestroyProduct(pShowSys);
	// 				pShowSys=NULL;
	// 			}
				if(pEntity!=NULL){
					m_pScene->GetRootNode()->detachObject(pEntity);
					EngineSystem::GetSingleton()->DestroyProduct(pEntity);
					pEntity	=	NULL;
				}
				return true;
			}
	
			void Section::OnRenderTarget(){
	// 			if(pEntity!=NULL){
	// 				Render::IMaterial*	pT	=	pEntity->GetMaterial();//->GetTechnique(Render::IMaterial::enTECH_HIGH);
	// 				pT->SetTechnique(Render::IMaterial::enTECH_HIGH);
	// 			}
// 				if(m_pScene!=NULL){
// 					m_pScene->RenderTarget();
// 				}
	// 			if(pEntity!=NULL){
	// 				Render::IMaterial*	pT	=	pEntity->GetMaterial();//->GetTechnique(Render::IMaterial::enTECH_HIGH);
	// 				pT->SetTechnique(Render::IMaterial::enTECH_VERYHIGH);
	// 			}
			}
	
			void Section::OnGUIEvent( UINT nEvent, int nControlID, void* pControl, void* pUserContext ){
	// 			if(pShowSys!=NULL){
	// 				switch(nControlID){
	// 				case	15:{
	// 						pShowSys->SetState(0.0f);
	// 					break;}
	// 				case	16:{
	// 						pShowSys->SetState(0.5f);
	// 					break;}
	// 				case	17:{
	// 						pShowSys->SetState(1.0f);
	// 					break;}
	// 				case	18:{
	// 						pShowSys->SetState(1.5f);
	// 					break;}
	// 				case	19:{
	// 						pShowSys->NextView();
	// 					break;}
	// 				}
	// 			}
			}
	
			void Section::OnUpdata(){
				OnFrameMove();
	
				if(m_pScene!=NULL)
					m_pScene->Updata();
				//这里物理部分采用异步模拟  物理模拟时 在单独的一个线程中进行
// 				if(m_pPhysxScene!=NULL)
// 					m_pPhysxScene->Simulate(false);
				if(m_pAudioScene!=NULL)
					m_pAudioScene->Updata();
	
				//射线检测测试代码
	// 			if(m_pPhysxScene!=NULL){
	// 				static	UInt	iNum	=	0;
	// 				iNum++;
	// 				if(iNum%60==0){
	// 					Vector3 v;
	// 					Vector3	n;
	// 					Real	d;
	// 					U1	b	=	m_pPhysxScene->RayCast(GetGlobalSetting().GetCursorPostionRay(),&v,&n,&d);
	// 					if(b){
	// 						AChar	str[100];
	// 						sprintf_s(str,100,"位置%f %f %f 法线%f %f %f 距离%f\n",v.x,v.y,v.z,n.x,n.y,n.z,d);
	// 						OutputDebugStringA(str);
	// 					}else{
	// 						OutputDebugStringA("无效\n");
	// 					}
	// 				}
	// 			}
			}
	
			void Section::SetCamera( Camera* pCamera ){
// 				m_pScene->SetCamera(pCamera);
// 				if(m_pAudioScene!=NULL)
// 					m_pAudioScene->SetCamera(pCamera);
			}
	
			Camera* Section::CreateDefaultCamera(){
// 				Camera*	pCamera	=	m_pScene->CreateCamera(m_strProductName+"DefaultCamera");
// 				pCamera->SetPosition(Float3(0,100,-400));
// 				pCamera->SetDir(0,0,-1);
// 				return	pCamera;
				return	NULL;
			}
	
			Control* Section::CreateDefaultControl(Camera*	pSceneCamera){
				return	NULL;
			}
	
			void Section::OnEnter(){
				SetCamera(m_pDefaultCamera);
			}

		}
	}
};