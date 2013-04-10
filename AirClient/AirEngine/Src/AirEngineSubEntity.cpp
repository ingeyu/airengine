#include "AirEngineSubEntity.h"
#include "AirEngineSystem.h"
#include "AirGlobalSetting.h"

#include "AirEngineMesh.h"
#include "AirInterfaceResourceSystem.h"
#include "AirRenderSystem.h"
namespace Air{
	
	namespace	Engine{
	
	
		AString	SubEntity::ProductTypeName="SubEntity";
		SubEntity::SubEntity( CAString& strName,Info*	pInfo ):Common::IProduct(strName){
			if(pInfo!=NULL)
				m_Info	=	*pInfo;
		}
	
		U1 SubEntity::Create(){
			if(m_Info.strMeshName.empty())
				return false;
			
			AString	strMeshName		=	m_Info.strMeshName;	
			UInt	uiSize	=	strMeshName.size();
			//创建网格	判断是否为X文件 如果不是则 从3DS加载
			if(strMeshName[uiSize-1] == 'X'	||	strMeshName[uiSize-1]=='x'){
				//m_DrawBuff.m_pXObject		=	Render::System::GetSingleton()->CreateProduct<Client::Render::IXObject*>(strMeshName,AString("XObject"));
			}else{
				
				Data*	pData	=	NULL;//GetGlobalSetting().m_pResourceSystem->Find(strMeshName);
				if(pData==NULL)
					return	false;
	
	// 			Mesh	mesh(strMeshName);
	// 			if(!mesh.Create()){
	// 				//Common::Logger("Engine","Error","创建模型失败");
	// 				return false;
	// 			}
	// 			mesh.ComputeNormalTangent();
	// 
	// 			UInt	uiNumVertex	=	mesh.GetVertexCount();
	// 			UInt	uiNumFace	=	mesh.GetFaceCount();
	// 			Render::IXObject::Info	info(uiNumVertex,uiNumFace);
	// 			m_DrawBuff.m_pXObject		=	Render::System::GetSingleton()->Create<Client::Render::IXObject*>(strMeshName,"XObject",&info);
	// 
	// 			Render::Vertex::IBuff::PNT*	p	=	NULL;
	// 			Mesh::Vertex*	pSrc	=	mesh.GetVertexArray();
	// 			m_DrawBuff.m_pXObject->LockVertexBuff((void**)&p);
	// 			for(UInt	i=0;i<uiNumVertex;i++){
	// 				p[i].Position	=		pSrc[i].Position;
	// 				p[i].Normal		=		pSrc[i].Normal;
	// 				p[i].TexCoord	=		pSrc[i].TexCoord;
	// 			}
	// 			m_DrawBuff.m_pXObject->UnLockVertexBuff();
	// 
	// 			WORD*	pIndex	=	NULL;
	// 			m_DrawBuff.m_pXObject->LockIndexBuff((void**)&pIndex);
	// 			memcpy(pIndex,mesh.GetFace32Array(),uiNumFace*3*sizeof(DWORD));
	// 			m_DrawBuff.m_pXObject->UnLockIndexBuff();
			}
			
// 			if(m_DrawBuff.m_pXObject==NULL){
// 				return false;
// 			}		
			
			//创建材质
// 			m_pMaterial					=	Render::System::GetSingleton()->CreateProduct<Render::IMaterial*>(m_Info.strMaterialName,AString("Material"));
// 			if(m_pMaterial==NULL){
// 				m_pMaterial	=	Render::System::GetSingleton()->CreateProduct<Render::IMaterial*>(AString("Material\\NoTexture.Material"),AString("Material"));
// 			}
// 	
// 			m_Bound		=	m_DrawBuff.m_pXObject->ComputeBoundBox();
// 	
// 			m_DrawBuff.m_DrawOption.m_DrawFuncType	=	Render::Draw::FUNC_TYPE_DS;
// 			m_pObject	=	m_DrawBuff.m_pXObject;
	
			return true;
		}
	
		U1 SubEntity::Destroy(){
// 			if(m_DrawBuff.m_pXObject!=NULL){
// 				Render::System::GetSingleton()->DestroyProduct(m_DrawBuff.m_pXObject);
// 				m_DrawBuff.m_pXObject	=	NULL;
// 			}
// 			if(m_pMaterial!=NULL){
// 				Render::System::GetSingleton()->DestroyProduct(m_pMaterial);
// 				m_pMaterial	=	NULL;
// 			}
			m_pObject	=	NULL;
			return	true;
		}
	
		void SubEntity::Updata(){
			__super::Updata();
		}
	
		void SubEntity::GetShape(Physics::Shape*	pShape,Float3 vScale){
// 			Render::IXObject*	p	=	m_DrawBuff.m_pXObject;
// 			if(p!=NULL)
// 				p->GetShape(pShape,vScale);
		}

	}
};