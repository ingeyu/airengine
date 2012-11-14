#include "AirEngineScene.h"
#include "AirRenderSystem.h"
#include "AirRenderTarget.h"


#include "AirEngineSystem.h"
#include "AirGlobalSetting.h"

#include "AirEngineCamera.h"
#include "AirEngineMesh.h"
#include "AirEngineMaterial.h"
#include "AirEngineSubEntity.h"
#include "AirEngineLight.h"
#include "AirEngineScreenEntity.h"
#include "AirEnginePostComposer.h"
#include "AirInterfaceParticle.h"

#include "AirEngineEntity.h"
#include "AirEngineEntityCloth.h"
#include "AirStaticMesh.h"

#include "AirEngineCharacterManager.h"
#include "AirMeshEntity.h"



namespace Air{
	
	namespace	Client{

		Character::Manager	g_mgr;
	
	
		Scene::Scene( CAString& strName ){
			m_strTypeName				=	strName;
			m_pMainCamera				=	NULL;
			m_bShadowEnable				=	true;
			m_pSceneTarget				=	NULL;
			m_pAlphaSceneTarget			=	NULL;
			//m_pScreenMaterial			=	NULL;
			m_bRenderWithoutComposer	=	false;
			m_pScreenEntity				=	NULL;
			m_bDeferredRender			=	true;
			m_bRenderAlphaObject		=	false;
	
			//m_pDefferedMaterial			=	NULL;
			m_pDefferedResult			=	NULL;
	
			//m_pRenderQueue				=	NULL;
			
		}
	
		U1 Scene::Initialization(){
	
			//AddFactory(new	EntityFactory());
			//AddFactory(new	EntityClothFactory());
			AddFactory(new	NoParamFactory<Camera>("Camera"));

			EngineSystem::GetSingleton()->CreateProduct<Material*>("NoMaterial","Material");

 			m_pMainCamera	=	CreateProduct<Camera*>("MainCamera","Camera");
			U32	uiSize	=	sizeof(Camera);
			m_pMainCamera->SetType(enCT_MAIN);

			m_pMainCamera->SetPosition(0,0,100);
			Float3	p	=	m_pMainCamera->GetPosition();

			m_pMainCamera->SetDir(-p.NormalizeCopy());
			m_pMainCamera->SetUpDir(0,1,0);

			MeshEntity::Info	info;
			info.strMaterial	=	"WorldHelperWireFrame";
			info.strMeshName	=	"AirMesh/NAV2.ame";
 			//MeshEntity*	pMesh	=	EngineSystem::GetSingleton()->CreateProduct<MeshEntity*>(info.strMeshName,"MeshEntity",&info);;
// 			pMesh->Create();
// 			//Material*	pMaterial	=	CreateProduct<Material*>("Test2","Material");
// 			pMesh->SetMaterialName("Test2");
 			//m_pRootNode.attachObject(pMesh);

			m_Loader.SetNode(&m_pRootNode);
			//"..\\Data\\AirMesh\\jianxia3\\jianxia3.ame.Scene"
			m_Loader.Load("AirMesh/Strom/Strom.ame.Scene");

			//m_pRootNode.SetScale(Float3(0.1,0.1,0.1));
			g_mgr.LoadSLK("Character.slk");
			g_mgr.SetSceneNode(&m_pRootNode);
			//AString	strSkele	=	"Mage.CSF";
			//Character::Resource*	pRes	=	EngineSystem::GetSingleton()->CreateProduct<Character::Resource*>("Character/Mage/","Character",&strSkele);
			Character::Animation::Model*	pModel	=	g_mgr.Create("1","法师");
			pModel->SetActionState("Walk.CAF");

			//Texture*	pTex	=	Render::System::GetSingleton()->CreateProduct<Texture*>("AirMesh/agrm/ORCHANGINGTARP.dds","Texture");
			//std::vector<DWORD>	vecData;
			//vecData.resize(256*256);
			//RECT r={0,0,256,256};
			//pTex->Write(&vecData[0],1024,&r);
			//pTex->ReleaseRef();
			return	true;
		}
	
		U1 Scene::Release(){
			//释放渲染队列
			//SAF_D(m_pRenderQueue);
			//if()

			//m_Loader.Unload();
			g_mgr.Destroy();

			if(m_pMainCamera!=NULL){
				m_pMainCamera->ReleaseRef();
				m_pMainCamera=NULL;
			}

			m_pRootNode.RemoveAllChild(true);
			m_DynamicNode.RemoveAllChild(true);
			m_StaticNode.RemoveAllChild(true);
			m_ParticleNode.RemoveAllChild(true);
			m_TerrainNode.RemoveAllChild(true);


			DestroyAllProduct();
	
	
			
			return true;
		}
	
		void Scene::Updata(){
			//判断是否需要更新渲染队列
// 			if(m_pRenderQueue->Begin()){
// 				//更新一次矩阵
// 				//m_pRootNode.Updata(m_pRenderQueue);
// 				//m_pRenderQueue->End();
// 			}else{
// 				m_pRootNode.Updata(NULL);
// 			}
		}
	
	
		SceneNode* Scene::GetRootNode(){
			return &m_pRootNode;
		}
	
	
		void Scene::SetMainCamera( Camera* pCamera ){
// 			if(m_pSceneTarget!=NULL)
// 				m_pSceneTarget->SetCamera(pCamera);
// 			if(m_pAlphaSceneTarget!=NULL)
// 				m_pAlphaSceneTarget->SetCamera(pCamera);
// 			m_pCamera	=	pCamera;
		}
	
		Camera* Scene::GetMainCamera(){
			return	m_pMainCamera;
		}
	
		Light* Scene::CreateLight( AString strName,Light::enumType type,U1	bCastShadow ){
			Light::Info	info;
			//if(type	!=	Light::enPoint)
			//	info.SetDirection(Float3::NEGATIVE_UNIT_Y);
			info.type	=	type;
			info.vDiff	=	Float4(1,1,1,1);
			info.vPosition	=	Float4(0,0,0,1);
			info.bCastShadow	=	bCastShadow;
			Light*	pLight	=	EngineSystem::GetSingleton()->CreateProduct<Light*>(strName,AString("Light"),&info);
			
			if(pLight!=NULL){
				m_lstLight.push_back(pLight);
				//pLight->SetScene(this);
			}
			return pLight;
		}
	
		void Scene::DestroyLight( Light* pLight ){
			if(pLight!=NULL){
				m_lstLight.remove(pLight);
				EngineSystem::GetSingleton()->DestroyProduct(pLight);
			}
		}

	
		Camera* Scene::CreateCamera(AString	strName){
			Camera*	pCamera	=	CreateProduct<Camera*>(strName,"Camera");

			return pCamera;
		}
	
		void Scene::DestroyCamera(Camera*	pCamera){
			DestroyProduct(pCamera);
		}
	


	
		void Scene::PlayParticle( AString strName,Float3 vPosition,Float3 vNormal ){
			IParticle::Info info;
			info.strParticleFile	=	strName;
			info.vVelocity			=	vNormal;
			info.vPosition			=	vPosition;
			IParticle*	pParticle	=	EngineSystem::GetSingleton()->CreateProduct<IParticle*>(Number::Increase(""),AString("Particle"),&info);
			if(pParticle!=NULL)
				m_pRootNode.attachObject(pParticle);
		}
	
		void Scene::SaveTargetToFile(){
			if(m_pSceneTarget!=NULL){
// 				m_pSceneTarget->GetTexture()->SaveToFile("1");
// 				m_pAlphaSceneTarget->GetTexture()->SaveToFile("2");
			}
		}

		void Scene::FindMovableObject( Camera* pCamera ){
			m_pRootNode.FindMovableObject(pCamera);

			m_DynamicNode.FindMovableObject(pCamera);
			m_StaticNode.FindMovableObject(pCamera);
			m_ParticleNode.FindMovableObject(pCamera);
			m_TerrainNode.FindMovableObject(pCamera);
		}

		void Scene::UpdateSceneTree(const FrameTime& frameTime){
			static	Matrix	matWorld(	1,0,0,0,
										0,1,0,0,
										0,0,1,0,
										0,0,0,1);
			static	Float4	quat(0,0,0,1);
			static	Float3	scale(1,1,1);

			m_pRootNode.Updata(matWorld,quat,scale,false);
			m_DynamicNode.Updata(matWorld,quat,scale,false);
			//m_StaticNode.Updata(true)
			m_ParticleNode.Updata(matWorld,quat,scale,false);
			
		}

		SceneNode* Scene::GetDynamicSceneNode(){
			return	&m_DynamicNode;
		}

		SceneNode* Scene::GetStaticSceneNode(){
			return	&m_StaticNode;
		}

		SceneNode* Scene::GetParticleSceneNode(){
			return	&m_ParticleNode;
		}

		SceneNode* Scene::GetTerrainSceneNode(){

			return	&m_TerrainNode;
		}
	}
};