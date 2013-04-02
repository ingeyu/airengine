#include "AirEngineMaterialTemplate.h"
#include "AirEngineMaterialParse.h"
#include "AirEngineMaterial.h"
#include "AirRenderSystem.h"
#include "AirGlobalSetting.h"
#include "AirEngineRenderable.h"
namespace	Air{
	namespace	Engine{


		MaterialTemplate::MaterialTemplate( CAString& strName,MaterialTemplateInfo* pInfo )
			:Common::IProduct(strName){
			m_pInfo	=	pInfo;
			if(m_pInfo	!=	NULL){
				m_bInLibrary	=	false;
			}else{
				m_bInLibrary	=	true;
				m_pInfo			=	MaterialParse::GetSingleton()->GetMaterialTemplateInfo(strName);
			}
			m_uiPhaseIndex		=	(enumPhaseIndex)0;
			m_Hash				=	0;
		}

		Air::U1 MaterialTemplate::Create(){
			if(m_pInfo	==	NULL)
				return	false;

			U32	uiSize	=	m_pInfo->m_vecPassInfo.size();
			if(uiSize==0)
				return	false;

			m_vecPass.resize(uiSize);
			for(U32 i=0;i<uiSize;i++){
				PassInfo*	pInfo	=	m_pInfo->m_vecPassInfo[i];
				if(pInfo==NULL){
					m_vecPass[i]	=	NULL;
					continue;
				}
				if(pInfo->strName.empty()){
					m_vecPass[i]	=	NULL;
					continue;
				}
				m_vecPass[i]	=	new	Pass(pInfo);
				
				if(!m_vecPass[i]->Create()){
					m_vecPass[i]->Destroy();
					delete m_vecPass[i];
					m_vecPass[i]	=	NULL;
				}
				
			}
			PassHash	pHash	=	m_vecPass[0]->GetHash();
			pHash.uiPassNumber	=	uiSize;
			pHash.uiPriority	=	m_pInfo->uiPriority;
			U64	uiHighHash	=	pHash.uiHash;
			U64	uiLowHash	=	(U64)this;
			m_Hash			=	(uiHighHash<<32)|uiLowHash;

			m_uiPhaseIndex	=	m_pInfo->PhaseIndex;
			m_pInfo			=	NULL;

			Render::System::GetSingleton()->AddMaterialTemplate(this);
			return	true;
		}
		Air::U1 MaterialTemplate::Destroy(){
			Render::System::GetSingleton()->RemoveMaterialTemplate(this);

			U32	uiSize	=	m_vecPass.size();
			for(U32 i=0;i<uiSize;i++){
				if(m_vecPass[i]!=NULL){
					m_vecPass[i]->Destroy();
					delete m_vecPass[i];
					m_vecPass[i]	=	NULL;
				}
			}
			m_vecPass	=	PassVector();
			m_Hash		=	0;
			return	true;
		}

		void MaterialTemplate::RenderWithPass(Pass&	pass){

			Material*	pMaterial	=	NULL;
			MaterialHashMap::iterator	i	=	m_mapMaterialHash.begin();
			for(;i!=m_mapMaterialHash.end();i++){
				pMaterial	=	i->second;
				if(pMaterial!=NULL){
					if(pMaterial->HasRenderables()){
						//提交纹理
						pass.UpdateTextureArray(pMaterial->GetTextureArray());
						//渲染
						pMaterial->RenderAllObjects();
					}

				}
			}
		}

		void MaterialTemplate::AddMaterial( Material* pMaterial ){
			if(pMaterial==NULL)
				return;
			U64	uiHash	=	pMaterial->GetHash();
			m_mapMaterialHash[uiHash]	=	pMaterial;
		}

		void MaterialTemplate::RemoveMaterial( Material* pMaterial ){
			if(pMaterial==NULL)
				return;

			MaterialHashMap::iterator	i	=	m_mapMaterialHash.find(pMaterial->GetHash());
			if(i!=m_mapMaterialHash.end()){
				m_mapMaterialHash.erase(i);
			}

		}

		Pass* MaterialTemplate::GetPass( U32 uiIndex ){
			if(uiIndex	>=	m_vecPass.size())
				return	NULL;
			return	m_vecPass[uiIndex];
		}

		Air::U1 MaterialTemplate::HasRenderables(){
			MaterialHashMap::iterator	i	=	m_mapMaterialHash.begin();
			for(;i!=m_mapMaterialHash.end();i++){
				if(i->second->HasRenderables())
					return	true;
			}
			return	false;
		}

		enumPhaseIndex MaterialTemplate::GetPhaseIndex()const{
			return	m_uiPhaseIndex;
		}

		void MaterialTemplate::RenderOneObject(TextureArray& vecTexture,Renderable* pObj){
			Pass*	pPass	=	NULL;
			U32	uiSize	=	m_vecPass.size();
			for(U32 i=0;i<uiSize;i++){
				pPass	=	m_vecPass[i];
				//提交 渲染状态 Shader 采样状态
				pPass->Begin();
				//提交纹理
				pPass->UpdateTextureArray(vecTexture);
				//渲染
				Render::System::GetSingleton()->DrawObject(pObj,true);

				pPass->End();
			}
		}

		void MaterialTemplate::ClearRenderObject()
		{
			Material*	pMaterial	=	NULL;
			MaterialHashMap::iterator	i	=	m_mapMaterialHash.begin();
			for(;i!=m_mapMaterialHash.end();i++){
				pMaterial	=	i->second;
				pMaterial->ClearRenderObjects();
			}
		}

		void MaterialTemplate::RenderAllMaterial()
		{
			{
				if(!HasRenderables()){
					return;
				}
				Pass*	pPass	=	NULL;
				U32	uiSize	=	m_vecPass.size();
				for(U32 i=0;i<uiSize;i++){
					pPass	=	m_vecPass[i];

					pPass->Begin();

					RenderWithPass(*pPass);

					pPass->End();
				}
			}
		}

	}
}