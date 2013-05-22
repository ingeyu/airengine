#include "AirEngineEntity.h"
#include "AirGlobalSetting.h"
#include "AirRenderSystem.h"
#include "AirResourceSystem.h"
//#include "AirInterfacePhysicsSystem.h"
#include "AirEngineSubEntity.h"
#include "AirEngineSystem.h"
namespace Air{
	
	
	namespace	Engine{
		
	
		Entity::Entity( CAString& strName,Info* pInfo ):TProduct(strName){
			if(pInfo!=NULL)
				m_Info	=	*pInfo;
			m_pNode	=	NULL;

			m_pRenderObj	=	NULL;
	
		}
	
		U1 Entity::Create(){
			if(m_Info.pParentNode!=NULL){
				m_pNode	=	new	SceneNode();//m_Info.pParentNode->CreateChildSceneNode();
				m_pNode->SetName(m_strProductName);
				//m_pNode->AddListener(this);
			}
	
			if(!ParseConfig()){
				Destroy();
				return	false;
			}
			m_pNode->AddListener(this);
			m_Info.pParentNode->AddChild(m_pNode);
	
			return	true;
		}
	
		U1 Entity::Destroy(){
			m_Info.pParentNode->RemoveChild(m_pNode);
	
			if(m_pRenderObj!=NULL){
				m_pRenderObj->ReleaseRef();
				m_pRenderObj=NULL;
			}
			if(m_pNode!=NULL){
				m_pNode->RemoveListener(this);
				delete	(m_pNode);
				m_pNode	=	NULL;
			}
			
	
			m_pObject	=	NULL;
			return	true;
		}
	
		SceneNode* Entity::GetSceneNode(){
			return	m_pNode;
		}
	

		SubEntity* Entity::GetSubEntity(){
			return	m_pRenderObj;
		}
	
		void Entity::UpdateMatrix( Float44* pMatrix,Float4*	pQuat,Float3*	pScale ){

		}
	
		U1 Entity::ParseConfig(){
			IniFile	file;
	
			if(m_Info.strConfigName.empty()){
				//从字符串加载
				if(!file.LoadFileFromString(m_Info.strConfigMemery)){
					return	false;
				}
			}else{
				//从资源包加载
				Data*	pData	=	NULL;//ResourceSystem::GetSingleton()->Find(m_Info.strConfigName);
				if(pData==NULL)
					return	false;
	
				if(!file.LoadFileFromMemory(pData)){
					return	false;
				}
			}
	
	
			SubEntity::Info	rInfo;
			rInfo.strMeshName		=	file.Get("Render","Name");
			rInfo.strMaterialName	=	file.Get("Render","Material");
	
			m_pRenderObj	=	EngineSystem::GetSingleton()->CreateProduct<SubEntity>(m_strProductName,&rInfo);
			
	
			return	true;
		}
	}
};