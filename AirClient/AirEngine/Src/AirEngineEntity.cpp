#include "AirEngineEntity.h"
#include "AirGlobalSetting.h"
#include "AirRenderSystem.h"
#include "AirInterfaceResourceSystem.h"
#include "AirInterfacePhysicsSystem.h"
#include "AirEngineSubEntity.h"
#include "AirEngineSystem.h"
namespace Air{
	
	
	namespace	Client{
		
	
		Entity::Entity( CAString& strName,Info* pInfo ):IProduct(strName){
			if(pInfo!=NULL)
				m_Info	=	*pInfo;
			m_pNode	=	NULL;
			m_pCollisionObj	=	NULL;
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
	
			if(m_pCollisionObj!=NULL){
				m_Info.pXScene->DestroyProduct(m_pCollisionObj);
				m_pCollisionObj	=	NULL;
			}
			if(m_pRenderObj!=NULL){
				EngineSystem::GetSingleton()->DestroyProduct(m_pRenderObj);
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
	
		Physics::ICollision* Entity::GetCollision(){
			return	m_pCollisionObj;
		}
	
		SubEntity* Entity::GetSubEntity(){
			return	m_pRenderObj;
		}
	
		void Entity::UpdataMatrix( Float44* pMatrix,Float4*	pQuat,Float3*	pScale ){
			if(m_pNode!=NULL){
				Physics::ICollision::enumType	type	=	m_pCollisionObj->GetType();
				switch(type){
					case	Physics::ICollision::enDynamic:
						m_pNode->SetPosition(m_pCollisionObj->GetPosition());
						m_pNode->SetQuat(m_pCollisionObj->GetQuat());
						break;
					case	Physics::ICollision::enKinematic:
						//Float44 m	=	m_pNode->GetResultMatrix();
						//m_pCollisionObj->MovePosition(pMatrix->getTrans());
						m_pCollisionObj->MoveQuat(*pQuat);
						break;
				}
			}
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
				Data*	pData	=	NULL;//GetGlobalSetting().m_pResourceSystem->Find(m_Info.strConfigName);
				if(pData==NULL)
					return	false;
	
				if(!file.LoadFileFromMemory(pData)){
					return	false;
				}
			}
	
	
			SubEntity::Info	rInfo;
			rInfo.strMeshName		=	file.Get("Render","Name");
			rInfo.strMaterialName	=	file.Get("Render","Material");
	
			m_pRenderObj	=	EngineSystem::GetSingleton()->CreateProduct<SubEntity*>(m_strProductName,AString("SubEntity"),&rInfo);
	
	
			Physics::ICollision::Info	cInfo;
			AString	strType			=	file.Get("Physx","Type");
			if(strType	==	"Dynamic"){
				cInfo.type	=	Physics::ICollision::enDynamic;
			}else	if(strType	==	"Kinematic"){
				cInfo.type	=	Physics::ICollision::enKinematic;
			}else{
				cInfo.type	=	Physics::ICollision::enStatic;
			}
	
			cInfo.fMass		=	-1;//Converter::parseReal(file.Get("Physx","Mass"));
			cInfo.fDensity	=	Converter::ToFloat(file.Get("Physx","Density"));
			cInfo.vPosition	=	GlobalSetting::ParseFloat3(file.Get("Physx","Position"));
			cInfo.vQuat		=	GlobalSetting::ParseQuat(file.Get("Physx","Rotation"));
			Float3	vTempScale	=	GlobalSetting::ParseFloat3(file.Get("Physx","Scale"));
	
			m_pNode->SetScale(vTempScale);
	
			Float3 gScale	=	m_Info.pParentNode->GetGlobalScaleImmediately();
			Float3	vScale	=	Float3(gScale.x*vTempScale.x,gScale.y*vTempScale.y,gScale.z*vTempScale.z);
	
			AString		strCollisionMesh	=	file.Get("Physx","CollisionMesh");
	
			AString	strShapeType	=	file.Get("Physx","ShapeType");
	
			cInfo.shape.m_vLocalPosition	=	GlobalSetting::ParseFloat3(file.Get((AChar*)strShapeType.c_str(),"LocalPosition"));
			cInfo.shape.m_vLocalQuat		=	GlobalSetting::ParseQuat(	file.Get((AChar*)strShapeType.c_str(),"LocalQuat"));
	
	
					if(strShapeType	==	"Plane"){
				Float3	vNormal		=	GlobalSetting::ParseFloat3(file.Get("Plane","Normal"));
				Real	fHeight		=	Converter::ToFloat(file.Get("Plane","Height"));
				cInfo.shape.SetPlane(vNormal,fHeight*vScale.x);
	
	
			}else	if(strShapeType	==	"Box"){
				Float3	vSize		=	GlobalSetting::ParseFloat3(file.Get("Box","Size"));
				//cInfo.shape.SetBox(vSize*vScale);
	
	
			}else	if(strShapeType	==	"Sphere"){
				Real	f			=	Converter::ToFloat(file.Get("Sphere","Radius"));
				cInfo.shape.SetSphere(f*vScale.x);
	
	
			}else	if(strShapeType	==	"Capsule"){
				Real	f			=	Converter::ToFloat(file.Get("Capsule","Radius"));
				Real	h			=	Converter::ToFloat(file.Get("Capsule","Height"));
				cInfo.shape.SetCapsule(h*vScale.x,f*vScale.x);
	
	
			}else	if(strShapeType	==	"Convex"){
				cInfo.shape.m_Type	=	Physics::Shape::enConvex;
				if(strCollisionMesh.empty()){
					m_pRenderObj->GetShape(&cInfo.shape,vScale);
				}else{
// 					Render::IXObject*	pXObj	=	Render::System::GetSingleton()->CreateProduct<Render::IXObject*>(strCollisionMesh,AString("XObject"));
// 					pXObj->GetShape(&cInfo.shape,vScale);
// 					Render::System::GetSingleton()->DestroyProduct(pXObj);
				}
	
	
			}else	if(strShapeType	==	"TriangleMesh"){
				cInfo.shape.m_Type	=	Physics::Shape::enTriangleMesh;
				if(strCollisionMesh.empty()){
					m_pRenderObj->GetShape(&cInfo.shape,vScale);
				}else{
// 					Render::IXObject*	pXObj	=	Render::System::GetSingleton()->CreateProduct<Render::IXObject*>(strCollisionMesh,AString("XObject"));
// 					pXObj->GetShape(&cInfo.shape,vScale);
// 					Render::System::GetSingleton()->DestroyProduct(pXObj);
				}
	
	
			}else	if(strShapeType	==	"BoundBox"){
// 				BoundBox&	b	=	m_pRenderObj->GetOrginBoundBox();
// 				Float3	vSize		=	(b.m_vMax	-	b.m_vMin)/2;
// 				cInfo.shape.m_vLocalPosition	=	(b.m_vMax	+	b.m_vMin)/2*vScale;
// 				cInfo.shape.SetBox(vSize*vScale);
				
	
			}else	if(strShapeType	==	"BoundSphere"){
// 				BoundBox&	b	=	m_pRenderObj->GetOrginBoundBox();
// 				Float3	vSize		=	(b.m_vMax	-	b.m_vMax)/2;
// 				cInfo.shape.m_vLocalPosition	=	(b.m_vMax	+	b.m_vMin)/2*vScale;
// 				cInfo.shape.SetSphere(vSize.length()*vScale.x);
			}else{
				return	false;
			}
	
			cInfo.pCallback	=	m_Info.pCallback;
	
	
			
			m_pCollisionObj	=	m_Info.pXScene->CreateProduct<Physics::ICollision*>(m_strProductName,AString("Collision"),&cInfo);
	
			if(m_pCollisionObj==NULL)
				return	false;
			m_pObject		=	m_pRenderObj;
			
			if(m_pNode!=NULL){
				m_pNode->attachObject(m_pRenderObj);
				m_pNode->SetPosition(cInfo.vPosition);
				m_pNode->SetQuat(cInfo.vQuat);
			}
	
			m_pCollisionObj->SetUserString(m_strProductName);
	
			return	true;
		}
	}
};