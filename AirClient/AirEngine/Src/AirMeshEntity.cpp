#include "AirMeshEntity.h"
#include "AirEngineMaterial.h"

namespace	Air{
	namespace	Client{


		MeshEntity::MeshEntity( CAString& strName,Info* pInfo ):IProduct(strName)
		{
			if(pInfo!=NULL){
				m_Info	=	*pInfo;
			}

			m_pMesh	=	NULL;

			SetNeedWorldMatrix(true);

			AddFlag(enMOF_DEFAULT			);
			AddFlag(enMOF_REFLECT			);
			AddFlag(enMOF_CASTSHADOW		);
			AddFlag(enMOF_VISIABLE			);
			AddFlag(enMOF_DYNAMIC			);
			AddFlag(enMOF_UPDATE			);
			AddFlag(enMOF_NEED_FRUSTUM_CULL	);
		}

		Air::U1 MeshEntity::Create()
		{
			if(m_Info.strMeshName.empty())
				return	false;
			m_pMesh	=	m_pFactoryMgr->CreateProduct<StaticMesh*>(m_Info.strMeshName,"StaticMesh");
			if(m_pMesh==NULL)
				return	false;
			if(!m_Info.strMaterial.empty())
				SetMaterialName(m_Info.strMaterial);
			else
				SetMaterialName(m_pMesh->GetMaterialName());

			m_BoundingBox	=	m_pMesh->GetBoundingBox();
			m_DrawBuff		=	m_pMesh->GetDrawBuffer();

			return true;
		}

		Air::U1 MeshEntity::Destroy()
		{
			SAFE_RELEASE_REF(m_pMesh);
			return	true;
		}

		void MeshEntity::ProcessRenderObject( U32 uiPhaseFlag )
		{
			for(U32	i=0;i<32;i++){
				if(m_pMaterial[i]!=NULL	&&	(uiPhaseFlag&1<<i)){
					m_pMaterial[i]->AddRenderObject(this);
				}
			}
		}
		Matrix* MeshEntity::GetWorldMatrix()
		{
			return	&m_WorldMatrix;
		}
	}
}