#include "AirEngineRenderable.h"
#include "AirEngineMaterial.h"
#include "AirGlobalSetting.h"
#include "AirEngineSystem.h"
#include "AirRenderSystem.h"

namespace	Air{
	namespace	Engine{
		


		Renderable::Renderable(){
		
			for(U32 i=0;i<32;i++){
				m_pMaterial[i]	=	NULL;
			}

			m_bNeedWorldMatrix	=	true;
		}

		Renderable::~Renderable(){
			for(U32 i=0;i<32;i++){
				if(m_pMaterial[i]!=NULL)
					m_pMaterial[i]->ReleaseRef();

				m_pMaterial[i]=NULL;
			}
		}

		Air::U1 Renderable::HasSkeleton(){
			return	false;
		}

		Air::U32 Renderable::GetBoneCount(){
			return	0;
		}

		Float44* Renderable::GetBoneMatrix( ){
			return	NULL;
		}	
		

		void Renderable::SetMaterial( Material* pMaterial ){
			if(pMaterial==NULL)
				return;
			pMaterial->AddRef();
			enumPhaseIndex	index	=	pMaterial->GetPhaseIndex();
			SetMaterialNull(index);
			m_pMaterial[index]	=	pMaterial;

		}

		void Renderable::SetMaterialName( CAString& strMaterialName ){

			Material*	p	=	EngineSystem::GetSingleton()->CreateProduct<Material>(strMaterialName);
			if(p==NULL){
				return;
			}
			
			SetMaterial(p);
			if(p!=NULL)
				p->ReleaseRef();
		}

		void Renderable::SetMaterialNull( enumPhaseIndex index ){
			if(m_pMaterial[index]!=NULL){
				m_pMaterial[index]->ReleaseRef();
				m_pMaterial[index]	=	NULL;
			}
		}

		Material* Renderable::GetMaterial( enumPhaseIndex index /*= Render::enPI_MRT*/ ){
			return	m_pMaterial[index];
		}
		Air::U1 Renderable::NeedWorldMatrix(){
			return	m_bNeedWorldMatrix;
		}

		void Renderable::SetNeedWorldMatrix(U1	bNeed){
			m_bNeedWorldMatrix	=	bNeed;
		}

		void Renderable::SetInstanceCount( U32 uiCount ){
			if(uiCount>1)
				m_DrawBuff.m_DrawOption.m_uiInstanceCount	=	uiCount;
		}

		void Renderable::BeforeRender( Material* pMaterial ){

		}

		void Renderable::AddToRenderQueue( U32 uiPhaseFlag ){
			Material*	pMaterial	=	NULL;
			for(U32	i=0;i<32;i++){
				pMaterial	=	m_pMaterial[i];
				if(pMaterial!=NULL){
					if(1<<pMaterial->GetPhaseIndex()&uiPhaseFlag){
						pMaterial->AddRenderObject(this);
					}
				}
			}
		}

		void Renderable::OnRender(Render::Device* pDevice )
		{
			if(m_DrawBuff.m_pVertexDeclare==NULL)
				return;
			pDevice->SetVD(m_DrawBuff.m_pVertexDeclare);
			Buffer*	pVB=	NULL;
			for(int i=0;i<4;i++){
				pVB	=	m_DrawBuff.m_pVertexBuffer[i];
				if(pVB==NULL)
					break;
				else
					pDevice->SetVB(i,pVB);
			}
			//如果IB为空 则不设置
			//if(m_DrawBuff.m_pIndexBuff!=NULL)
			pDevice->SetIB(m_DrawBuff.m_pIndexBuff);

			pDevice->DrawOpt(m_DrawBuff.m_DrawOption);
		}

	}
}