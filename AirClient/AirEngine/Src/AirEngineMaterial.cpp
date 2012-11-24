#include "AirEngineMaterial.h"
#include "AirGlobalSetting.h"
#include "AirRenderSystem.h"
#include "AirInterfaceResourceSystem.h"
#include "AirEngineSystem.h"
#include "AirEngineMaterialParse.h"
#include "AirEngineMaterialTemplate.h"
#include "AirEngineRenderable.h"

namespace Air{
	
	namespace	Client{

		Material::Material( CAString& strName,Info* pInfo ):IProduct(strName){
			if(pInfo!=NULL){
				m_Info	=	*pInfo;
			}else{
				//从已经解析的材质文件中获取
				Info*	p	=	MaterialParse::GetSingleton()->GetMaterialInfo(strName);
				if(p!=NULL)
					m_Info	=	*p;
			}

			m_pConstantBuffer	=	NULL;
			m_pTemplate			=	NULL;
		}

		Air::U1 Material::Create(){

			//创建模板
			if(m_Info.strTemplate.empty()){
				return	false;
			}

			MaterialTemplateInfo*	pMTInfo	=	MaterialParse::GetSingleton()->GetMaterialTemplateInfo(m_Info.strTemplate);
			if(pMTInfo==NULL)
				return	false;

			m_pTemplate	=	EngineSystem::GetSingleton()->CreateProduct<MaterialTemplate*>(m_Info.strTemplate,"MaterialTemplate",pMTInfo);

			if(m_pTemplate==NULL)
				return	false;

			//创建纹理
			Render::System*	pRenderSys	=	Render::System::GetSingleton();

			U32	uiSize	=	m_Info.vecTextureName.size();
			if(uiSize!=0){
				m_vecTexture.resize(uiSize);
			}
			//计算hash
			MaterialHash	h;
			h.uiTextureNumer	=	uiSize;
			for(U32 i=0;i<uiSize;i++){
				m_vecTexture[i]	=	pRenderSys->CreateProduct<Render::Texture*>(m_Info.vecTextureName[i],"Texture");
				if(m_vecTexture[i]==NULL){
					m_vecTexture[i]	=	pRenderSys->CreateProduct<Render::Texture*>("..\\Data\\Texture\\TextureCantBeFound.png","Texture");
				}
				//计算hash
				h.AddTexture(m_vecTexture[i]);
			}
			m_Info.vecTextureName	=	StringVector();

			//计算hash
			h.uiConstantSize	=	m_Info.vecFloatParam.size();
			//创建参数
			if(!m_Info.vecFloatParam.empty()){
				Render::Buffer::Info info;
				info.SetConstantBuffer(m_Info.vecFloatParam.size()*sizeof(Float4));
				info.InitData		=	&m_Info.vecFloatParam[0];
				m_pConstantBuffer	=	pRenderSys->CreateProduct<Render::Buffer*>(m_strProductName,"Buffer",&info);
				//更新参数
				if(m_pConstantBuffer!=NULL){
					m_pConstantBuffer->GetBuffer();
					m_pConstantBuffer->UpdateData(&m_Info.vecFloatParam[0]);
				}
				//清理内存
				//m_Info.vecFloatParam	=	VectorArray();
			}
			h.uiPriority	=	m_Info.uiPriority;
			U64	uiHighHash	=	h.uiHash;
			U64	uiLowHash	=	(U64)this;
			m_Hash			=	uiHighHash<<32|uiLowHash;

			m_pTemplate->AddMaterial(this);

			return	true;
		}

		Air::U1 Material::Destroy(){
			m_pTemplate->RemoveMaterial(this);

			m_Hash	=	0;

			if(m_pConstantBuffer!=NULL){
				m_pConstantBuffer->ReleaseRef();
				m_pConstantBuffer=NULL;
			}
			U32 uiSize	=	m_vecTexture.size();
			for(U32 i=0;i<uiSize;i++){
				if(m_vecTexture[i]!=NULL){
					m_vecTexture[i]->ReleaseRef();
					m_vecTexture[i]	=	NULL;
				}
			}
			m_vecTexture	=	TextureVector();

			if(m_pTemplate!=NULL){
				m_pTemplate->ReleaseRef();
				m_pTemplate	=	NULL;
			}
			return	true;
		}
		void Material::AddRenderObject( Renderable* pObj){
			if(pObj==NULL)
				return;
			//m_ObjectCS.Enter();
			m_vecRenderObjects.push_back(pObj);
			//m_ObjectCS.Leave();
		}

		void Material::ClearRenderObjects(){
			//m_ObjectCS.Enter();
			m_vecRenderObjects.clear();
			//m_ObjectCS.Leave();
		}

		void Material::RenderAllObjects(){
			Render::System*	pSys	=	Render::System::GetSingleton();
			//SetTexture
			Buffer*	pCB	=	GetConstantBuffer();
			if(pCB	!=	NULL){
				//更新自动参数
				UpdataAutoParam();
			
				//SetConstantBuffer
				pSys->GetDevice()->SetCB(enVS,3,m_pConstantBuffer);
				pSys->GetDevice()->SetCB(enGS,3,m_pConstantBuffer);
				pSys->GetDevice()->SetCB(enPS,3,m_pConstantBuffer);
			}

			Renderable*	pObj	=	NULL;

			U32	uiSize	=	m_vecRenderObjects.size();
			for(U32 i=0;i<uiSize;i++){
				//RenderObj
				pObj	=	m_vecRenderObjects[i];
				
				//回调
				pObj->BeforeRender(this);

				pSys->DrawObject(pObj,m_Info.bUseSkin);
			}
		}

		Air::U1 Material::HasRenderables(){
			return	!m_vecRenderObjects.empty();
		}

		enumPhaseIndex Material::GetPhaseIndex()const{
			if(m_pTemplate!=NULL){
				return	m_pTemplate->GetPhaseIndex();
			}
			return	enPI_MAX;
		}

		void Material::RenderOneObject( Renderable* pObj){
			if(pObj==NULL)
				return;

			RenderSystem*	pSys	=	Render::System::GetSingleton();
			//如果为空 表示该材质没有参数需要传递
			Buffer*	pCB	=	GetConstantBuffer();
			if(pCB	!=	NULL){
				//更新自动参数
				UpdataAutoParam();
				//设置材质的shader参数
				pSys->GetDevice()->SetCB(3,m_pConstantBuffer);
			}

			m_pTemplate->RenderOneObject(m_vecTexture,pObj);
		}

		void Material::SetTexture( U32 uiIndex,Texture* pTexture ){
			if(m_vecTexture[uiIndex]!=NULL){
				m_vecTexture[uiIndex]->ReleaseRef();

			}
			m_vecTexture[uiIndex]	=	pTexture;
		}

		void Material::SetTextureName( U32 uiIndex,CAString& strTextureName ){
			if(uiIndex	>=	m_vecTexture.size())
				return;
			if(strTextureName.empty())
				return;
			Texture*	pTexture	=	Render::System::GetSingleton()->CreateProduct<Texture*>(strTextureName,"Texture");
			if(pTexture	==	NULL)
				return;
			SetTexture(uiIndex,pTexture);
		}

		void Material::UpdataAutoParam(){

		}
	}
};