#include "AirEngineRenderable.h"
#include "AirEngineMaterial.h"
#include "AirGlobalSetting.h"
#include "AirEngineSystem.h"
#include "AirRenderSystem.h"

namespace	Air{
	namespace	Client{
		


		Renderable::Renderable(){
		
			for(U32 i=0;i<32;i++){
				m_pMaterial[i]	=	NULL;
			}

			m_pObjectCB	=	NULL;
			m_pBoneCB	=	NULL;

			m_bNeedWorldMatrix	=	false;
		}

		Renderable::~Renderable(){
			for(U32 i=0;i<32;i++){
				if(m_pMaterial[i]!=NULL)
					m_pMaterial[i]->ReleaseRef();

				m_pMaterial[i]=NULL;
			}

			SAFE_RELEASE_REF(m_pBoneCB);

			SAFE_RELEASE_REF(m_pObjectCB);
		}

		Air::U1 Renderable::HasSkeleton(){
			return	false;
		}

		Air::U32 Renderable::GetBoneCount(){
			return	0;
		}

		Air::U1 Renderable::GetBoneMatrix( Float44* pMatrixArray ){
			return	true;
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

			Material*	p	=	EngineSystem::GetSingleton()->CreateProduct<Material*>(strMaterialName,"Material");
			if(p==NULL){
				return;
			}
			
			SetMaterial(p);
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

		void Renderable::FillBoneConstantBuffer( U1 bUseSkin /*= false*/ ){

			if(bUseSkin	&&	HasSkeleton()	&&	GetBoneCount()!=0){
				Buffer*	pBoneCB	=	GetBoneConstantBuffer();

// 				Float4*	pBoneBuffer	=	pBoneCB->Lock();
// 				GetBoneMatrix((Float44*)pBoneBuffer);
// 				pBoneCB->UnLock();
				//Render::System::GetSingleton()->SetConstantBuffer(Render::enCBT_Bone,pBoneCB);
			}
		}

		Buffer* Renderable::GetObjectConstantBuffer(){
			if(!m_bNeedWorldMatrix)
				return	NULL;
			if(m_pObjectCB==NULL){
				Buffer::Info	info;
				info.SetConstantBuffer(sizeof(Matrix),enCBT_Object);
				
				m_pObjectCB	=	Render::System::GetSingleton()->CreateProduct<Buffer*>(Common::Number::Increase(""),"Buffer",&info);
				m_pObjectCB->GetBuffer();
			}

			if(m_pObjectCB!=NULL){
				m_pObjectCB->UpdateData(GetWorldMatrix());
			}
			return	m_pObjectCB;
		}

		Buffer* Renderable::GetBoneConstantBuffer(){
			if(!HasSkeleton()	||	GetBoneCount()	==	0)
				return	NULL;
// 			if(m_pBoneCB==NULL){
// 				Buffer::Info	info;
// 				info.SetConstantBuffer(GetBoneCount()*sizeof(Matrix));
// 				
// 				m_pBoneCB	=	Render::System::GetSingleton()->CreateProduct<Buffer*>(m_strName+"Bone","Buffer",&info);
// 			}
			return	m_pBoneCB;
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

		void Renderable::SetObjectConstantBuffer( Buffer* pBuffer ){
			if(!m_bNeedWorldMatrix)
				return;
			if(pBuffer==NULL)
			{
				return;
			}
			m_pObjectCB	=	pBuffer;
			
		}

		void Renderable::AddToRenderQueue( U32 uiPhaseFlag ){
			Material*	pMaterial	=	NULL;
			for(U32	i=0;i<32;i++){
				pMaterial	=	m_pMaterial[i];
				if(pMaterial!=NULL){
					if(pMaterial->GetPhaseIndex()&uiPhaseFlag){
						pMaterial->AddRenderObject(this);
					}
				}
			}
		}
	}
}