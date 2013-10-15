#include "AirEngineParticleEntity.h"
#include "AirEngineMaterial.h"
#include "AirEngineSystem.h"
#include "AirGlobalSetting.h"
namespace Air{
	
	
	namespace	Engine{
	
		AString	ParticleEntity::ProductTypeName="ParticleEntity";
		ParticleEntity::ParticleEntity( CAString& strName,Info* pInfo ):MovableObject(strName){
			m_strProductName	=	strName;
			m_Info	=	*pInfo;
		}
	
		U1 ParticleEntity::Create(){
			//创建顶点声明
			VertexDeclare::Info	VertexDeclareInfo;
			VertexDeclare*	pVertexDeclare	=	Render::System::GetSingleton()->CreateProduct<VertexDeclare>(("ParticleVertexDeclare"),&VertexDeclareInfo);
			if(pVertexDeclare==NULL)
				return false;
	
	
	
			//创建顶点缓冲
			VertexBuffer::Info VertexBuffInfo;//(12,720);
			//VertexBuffInfo.fvf	=	VertexDeclareInfo.m_FVF;
			VertexBuffer*	pVertexBuff	=	Render::System::GetSingleton()->CreateProduct<VertexBuffer>(AString("ScreenVertexBuff"),&VertexBuffInfo);
			if(pVertexBuff==NULL)
				return false;
			//填充顶点
// 			VertexBuff::P*	p	=	NULL;
// 			pVertexBuff->Lock(LockOption(0,0,(void**)&p));
// 			for(UInt i=0;i<120;i++){
// 				p[i*6+0].Position	=	Float3(-1.0f,	1.0f,	i);
// 				p[i*6+1].Position	=	Float3(1.0f,	1.0f,	i);
// 				p[i*6+2].Position	=	Float3(-1.0f,	-1.0f,	i);
// 	
// 				p[i*6+3].Position	=	Float3(-1.0f,	-1.0f,	i);
// 				p[i*6+4].Position	=	Float3(1.0f,	1.0f,	i);
// 				p[i*6+5].Position	=	Float3(1.0f,	-1.0f,	i);
// 			}
// 			pVertexBuff->Unlock();
	
			//将渲染需要的数据保存到渲染缓冲区
// 			m_DrawBuff.m_pVertexDeclare	=	pVertexDeclare;
// 			m_DrawBuff.m_pVertexBuff	=	pVertexBuff;
// 			//m_DrawBuff.m_pIndexBuff		=	pIndexBuff;
// 			//设置顶点数
// 			m_DrawBuff.m_DrawOption.m_uiVertexCount		=	720;
// 			//设置面数
// 			m_DrawBuff.m_DrawOption.m_DrawFuncType		=	Render::Draw::FUNC_TYPE_DP;
	
	
// 			if(!m_Info.strParticleName.empty()){
// 				m_pMaterial	=	Render::System::GetSingleton()->CreateProduct<Render::IMaterial*>(m_Info.strParticleName,AString("Material"));
// 			}
	
			//m_pObject	=	(UInt*)&m_DrawBuff;
	
			return true;
		}
	
		U1 ParticleEntity::Destroy(){
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
	
// 			if(m_pMaterial!=NULL){
// 				RenderSystem::GetSingleton()->DestroyProduct(m_pMaterial);
// 				m_pMaterial	=	NULL;
// 			}
	
			m_pObject	=	NULL;
			return true;
		}
	
		void ParticleEntity::Update(const FrameTime& frameTime){
			__super::Update(frameTime);
			m_Info.fLife	-=	GetGlobalSetting().m_ShaderParam.m_fTimeDelta;
		}
	

	}
};
