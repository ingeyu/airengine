#include "AirEngineEntityCloth.h"
#include "AirEngineSubEntity.h"
#include "AirGlobalSetting.h"
#include "AirEngineSystem.h"
#include "AirRenderSystem.h"
//#include "AirInterfacePhysicsSystem.h"
namespace Air{
	
	namespace	Engine{
	
	
		EntityCloth::EntityCloth( CAString& strName,Info* pInfo ):TProduct(strName){
			if(pInfo!=NULL)
				m_Info	=	*pInfo;
			//m_pCloth	=	NULL;
		}
	
		U1 EntityCloth::Create(){
			if(!CreatePhysxMesh())
				return	false;
			if(!CreateRenderMesh())
				return	false;
	
			//m_pMaterial	=	Render::System::GetSingleton()->CreateProduct<Render::IMaterial*>(m_Info.strMaterialName,AString("Material"));
	
			//m_pObject	=	m_pMaterial;
	
			return	true;
		}
	
		U1 EntityCloth::Destroy(){
// 			if(m_DrawBuff.m_pVertexBuff!=NULL){
// 				Render::System::GetSingleton()->DestroyProduct(m_DrawBuff.m_pVertexBuff);
// 				m_DrawBuff.m_pVertexBuff	=	NULL;
// 			}
// 			if(m_DrawBuff.m_pVertexDeclare!=NULL){
// 				Render::System::GetSingleton()->DestroyProduct(m_DrawBuff.m_pVertexDeclare);
// 				m_DrawBuff.m_pVertexDeclare	=	NULL;
// 			}
// 			if(m_DrawBuff.m_pIndexBuff!=NULL){
// 				Render::System::GetSingleton()->DestroyProduct(m_DrawBuff.m_pIndexBuff);
// 				m_DrawBuff.m_pIndexBuff	=	NULL;
// 			}
// 	
// 			if(m_pMaterial!=NULL){
// 				Render::System::GetSingleton()->DestroyProduct(m_pMaterial);
// 				m_pMaterial	=	NULL;
// 			}
	

			return	true;
		}
	
		const BoundingBox& EntityCloth::GetWorldBoundingBox()const {
	// 		static	BoundBox	b;
	// 		b	=	m_pCloth->GetWorldBounds();
	// 		return	b;
			return	m_BoundingBox;
		}
	
		void EntityCloth::Update(){
			//__super::Update();
	
		//	m_BoundingBox	=	m_pCloth->GetWorldBoundingBox();
	
			SBuff*	pV	=	NULL;
			
// 			m_DrawBuff.m_pVertexBuff->Lock(Render::LockOption(0,0,(void**)&pV));
// 			m_DrawBuff.m_DrawOption.m_uiVertexCount	=	m_pCloth->GetVertexBuff(pV);
// 			m_DrawBuff.m_pVertexBuff->Unlock();
	
			UInt*	pI	=	NULL;
// 			m_DrawBuff.m_pIndexBuff->Lock(Render::LockOption(0,0,(void**)&pI));
// 			m_DrawBuff.m_DrawOption.m_uiFaceCount	=	m_pCloth->GetIndexBuff(pI)/3;
// 			m_DrawBuff.m_pIndexBuff->Unlock();
		}
	
		void EntityCloth::Render(){
			//MovableObject::Render();
		}
	
		U1 EntityCloth::CreatePhysxMesh(){
			//Physics::Shape&	shape	=	m_Info.clothInfo.shape;
	
// 			if(!m_Info.strMeshName.empty()){
// 				Render::IXObject*	pXObject	=	Render::System::GetSingleton()->CreateProduct<Render::IXObject*>(m_Info.strMeshName,AString("XObject"));
// 				if(pXObject==NULL)
// 					return	false;
// 				pXObject->GetShape(&shape,Float3(1,1,1),true);
// 	
// 				Render::System::GetSingleton()->DestroyProduct(pXObject);
// 			}
// 	
// 			m_pCloth	=	m_Info.pXScene->CreateProduct<Physics::ICloth*>(m_strProductName,AString("Cloth"),&m_Info.clothInfo);
// 			if(m_pCloth==NULL)
// 				return	false;
	
			return	true;
		}
	
		U1 EntityCloth::CreateRenderMesh(){
			//Physics::Shape&	shape	=	m_Info.clothInfo.shape;
	
//			UInt	uiNumVertex	=	shape.m_VertexArray.size();
//			UInt	uiNumIndex	=	shape.m_FaceArray.size();
//			SBuff*	pVertexData	=	new	SBuff[uiNumVertex*3];
			//m_pCloth->GetVertexBuff(pVertexData);
//			UInt*	pIndexData				=	&shape.m_FaceArray[0];
			VertexBuffer::Info	vInfo;//(Render::,uiNumVertex*3);
			
			//vInfo.size			=	uiNumVertex;
			//vInfo.pInitData		=	NULL;//pVertexData;
			//m_DrawBuff.m_pVertexBuff	=	Render::System::GetSingleton()->CreateProduct<VertexBuff*>(m_strProductName,AString("VertexBuff"),&vInfo);
	
//			SAF_DA(pVertexData);
	
			VertexDeclare::Info	dInfo;
			dInfo.SetDeclPNTT();
			//m_DrawBuff.m_pVertexDeclare	=	Render::System::GetSingleton()->CreateProduct<VertexDeclare*>(AString("PNTT"),AString("VertexDeclare"),&dInfo);
	
			IndexBuffer::Info		iInfo;

			//iInfo.size		=	uiNumIndex*3;
			iInfo.InitData	=	NULL;//pIndexData;
// 			m_DrawBuff.m_pIndexBuff	=	Render::System::GetSingleton()->CreateProduct<IndexBuff*>(m_strProductName,AString("IndexBuff"),&iInfo);
// 	
// 			m_DrawBuff.m_DrawOption.m_DrawFuncType	=	Render::Draw::FUNC_TYPE_DIP;
// 			m_DrawBuff.m_DrawOption.m_uiVertexCount	=	uiNumVertex;
// 			m_DrawBuff.m_DrawOption.m_uiFaceCount	=	uiNumIndex/3;
			return	true;
		}
	}
};