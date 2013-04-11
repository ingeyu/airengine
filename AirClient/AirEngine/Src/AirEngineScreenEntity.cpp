#include "AirEngineScreenEntity.h"
#include "AirEngineMaterial.h"
#include "AirEngineSystem.h"
#include "AirGlobalSetting.h"
#include "AirEngineSceneNode.h"
namespace Air{
	
	namespace	Engine{
	
	
	
		AString ScreenEntity::ProductTypeName="ScreenEntity";
		ScreenEntity::ScreenEntity( CAString& strName,Info*	pInfo):Common::IProduct(strName){

			if(pInfo!=NULL)
				m_Info	=	*pInfo;
			//m_pMaterial	=	NULL;
			m_bNeedCheckView	=	false;
		}
	
		U1 ScreenEntity::Create(){
			using	namespace	Render;
			Log::GetSingleton()->Write("创建屏幕物体顶点声明");
			//创建顶点声明
			DeclareElement e[]	=	{
				{ enDU_POSITION,0, enTFMT_R32G32B32_FLOAT,0,0,enDT_PER_VERTEX_DATA,		0 }

			};
			VertexDeclare::Info	VertexDeclareInfo;
			VertexDeclareInfo.CopyElement(e,1);
			VertexDeclare*	pVertexDeclare	=	Render::System::GetSingleton()->CreateProduct<VertexDeclare>("ScreenVertexDeclare",&VertexDeclareInfo);
			if(pVertexDeclare==NULL)
				return false;
	
			Log::GetSingleton()->Write("创建屏幕物体顶点缓冲");
			Float3 vPos[4]	=	{
				Float3(-1.0f,	1.0f,	1.0f),
				Float3(1.0f,	1.0f,	1.0f),
				Float3(-1.0f,	-1.0f,	1.0f),
				Float3(1.0f,	-1.0f,	1.0f)
			};
			//创建顶点缓冲
			VertexBuffer::Info VertexBuffInfo;
			//VertexBuffInfo.pInitData	=	NULL;
			VertexBuffer*	pVertexBuff	=	Render::System::GetSingleton()->CreateProduct<VertexBuffer>(AString("ScreenVertexBuff"),&VertexBuffInfo);
			if(pVertexBuff==NULL)
				return false;
			//填充顶点
	// 		VertexBuff::P*	p	=	NULL;
	// 		pVertexBuff->Lock(LockOption(0,0,(void**)&p));
	// 		p[0].Position	=	Float3(-1.0f,	1.0f,	1.0f);
	// 		p[1].Position	=	Float3(1.0f,	1.0f,	1.0f);
	// 		p[2].Position	=	Float3(-1.0f,	-1.0f,	1.0f);
	// 		p[3].Position	=	Float3(1.0f,	-1.0f,	1.0f);
	// 		pVertexBuff->Unlock();
	
			Log::GetSingleton()->Write("创建屏幕物体顶点索引缓冲");
			DWORD indexArray[6]	=	{0,1,2,2,1,3};
			//创建索引缓冲
			IndexBuffer::Info	IndexBuffInfo;
			IndexBuffInfo.SetIndexBuffer16(6);
			IndexBuffInfo.InitData	=	NULL;//indexArray;
			IndexBuffer*	pIndexBuff	=	Render::System::GetSingleton()->CreateProduct<IndexBuffer>("ScreenIndexBuff",&IndexBuffInfo);
			if(pIndexBuff==NULL){
				Destroy();
				return false;
			}
			//填充索引
	// 		WORD*	pIndex	=	NULL;
	// 		pIndexBuff->Lock(LockOption(0,0,(void**)&pIndex));
	// 		pIndex[0]	=	0;
	// 		pIndex[1]	=	1;
	// 		pIndex[2]	=	2;
	// 		pIndex[3]	=	2;
	// 		pIndex[4]	=	1;
	// 		pIndex[5]	=	3;
	// 
	// 		pIndexBuff->Unlock();
	
			//将渲染需要的数据保存到渲染缓冲区
// 			m_DrawBuff.m_pVertexDeclare	=	pVertexDeclare;
// 			m_DrawBuff.m_pVertexBuff	=	pVertexBuff;
// 			m_DrawBuff.m_pIndexBuff		=	pIndexBuff;
// 			//设置顶点数
// 			m_DrawBuff.m_DrawOption.m_uiVertexCount		=	4;
// 			//设置面数
// 			m_DrawBuff.m_DrawOption.m_uiFaceCount		=	2;
	
	
// 			if(!m_Info.strMaterialName.empty()){
// 				m_pMaterial	=	Render::System::GetSingleton()->CreateProduct<Render::IMaterial*>(m_Info.strMaterialName,AString("Material"));
// 			}
// 			
// 			m_pObject	=	(UInt*)&m_DrawBuff;
	
			return true;
		}
	
		U1 ScreenEntity::Destroy(){
	
			GlobalSetting&	setting	=	GetGlobalSetting();
	
// 			if(m_DrawBuff.m_pIndexBuff!=NULL){
// 				RenderSystem::GetSingleton()->DestroyProduct(m_DrawBuff.m_pIndexBuff);
// 				m_DrawBuff.m_pIndexBuff=NULL;
// 			}
// 			if(m_DrawBuff.m_pVertexBuff!=NULL){
// 				RenderSystem::GetSingleton()->DestroyProduct(m_DrawBuff.m_pVertexBuff);
// 				m_DrawBuff.m_pVertexBuff=NULL;
// 			}
// 			if(m_DrawBuff.m_pVertexDeclare!=NULL){
// 				RenderSystem::GetSingleton()->DestroyProduct(m_DrawBuff.m_pVertexDeclare);
// 				m_DrawBuff.m_pVertexDeclare=NULL;
// 			}
// 	
// 			if(m_pMaterial!=NULL){
// 				RenderSystem::GetSingleton()->DestroyProduct(m_pMaterial);
// 				m_pMaterial	=	NULL;
// 			}
	
			m_pObject	=	NULL;
			return true;
		}
	
	
		void ScreenEntity::Update(){
	
		}
	
		void ScreenEntity::RenderPostComposer( Material* pMaterial/*,Render::ITexture* pInputTexture*/ ){
			if(pMaterial==NULL/*	||	pInputTexture==NULL*/)
				return;
			//IMaterial::Technique*	pTechnique	=	pMaterial->GetCurrentTechnique();
			//pTechnique->SetParam("InputTexture",pInputTexture);
			//pMaterial->Render(m_DrawBuff);
		}
	
		void ScreenEntity::Render(){
// 	// 		if(m_pMaterial!=NULL)
// 	// 			m_pMaterial->Render(m_DrawBuff);
// 			if(m_pMaterial->IsAlphaBlend()){
// 				AlphaObject obj;
// // 				if(m_pParentNode!=NULL)
// // 					obj.mat			=	m_ResultMatrix;
// // 				else
// // 					obj.mat			=	Float44::getTrans(0,0,0);
// 				obj.pRenderObj		=	this;
// 				EngineSystem::GetSingleton()->PushAlphaObject(obj);
// 			}else{
// 				m_pMaterial->Render(m_DrawBuff);
// 			}
		}

	}
};