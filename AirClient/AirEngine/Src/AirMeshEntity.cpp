#include "AirMeshEntity.h"
#include "AirEngineMaterial.h"
#include "AirBoxRenderable.h"
#include "AirEngineSystem.h"

namespace	Air{
	namespace	Client{


		MeshEntity::MeshEntity( CAString& strName,Info* pInfo ):IProduct(strName)
		{
			if(pInfo!=NULL){
				m_Info	=	*pInfo;
			}

			m_pBoxRenderable		=	NULL;
			m_pBoundingBoxMaterial	=	NULL;

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
#if 1
			m_pBoxRenderable	=	new	BoxRenderable();
			((BoxRenderable*)m_pBoxRenderable)->m_WorldMatrix	=	Float44(m_BoundingBox.GetCenter(),m_BoundingBox.GetHalfSize(),Float4(0,0,0,1));

			m_pBoundingBoxMaterial	=	EngineSystem::GetSingleton()->CreateProduct<Material*>("WorldHelperWireFrame","Material");
#endif
			return true;
		}

		Air::U1 MeshEntity::Destroy()
		{
			SAFE_RELEASE_REF(m_pBoundingBoxMaterial);
			SAFE_DELETE(m_pBoxRenderable);
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
#if 1
			if((1<<m_pBoundingBoxMaterial->GetPhaseIndex()) & uiPhaseFlag){
				((BoxRenderable*)m_pBoxRenderable)->m_WorldMatrix	=	Float44(m_WorldBound.GetCenter(),m_WorldBound.GetHalfSize(),Float4(0,0,0,1));
				m_pBoundingBoxMaterial->AddRenderObject(m_pBoxRenderable);
			}
#endif

		}
		Matrix* MeshEntity::GetWorldMatrix()
		{
			return	&m_WorldMatrix;
		}

		Air::U1 MeshEntity::RayCast( const Ray& ray ,float*	pOutDistance)
		{
#if 1
			if(!GetWorldBoundingBox().RayCast(ray.GetOrigin(),ray.GetDirection())){//.Intersect(GetWorldBoundingBox())){
				return	false;
			}
#endif

			Matrix	matWorld	=	*GetWorldMatrix();
			Matrix	matWorldInv	=	matWorld;
			matWorldInv.Inverse();
			Float3	vStart	=	ray.m_vStart;
			Float3	vLookAt	=	vStart	+	ray.m_vDirection;
			vStart			=	matWorldInv*vStart;
			vLookAt			=	matWorldInv*vLookAt;
			Float3	vDir	=	(vLookAt	-	vStart);
			vDir.Normalize();

			Ray	objSpaceRay(vStart,vDir);

			float	fDistance	=	999999.0f;

			U1	bHit	=	m_pMesh->RayCast(objSpaceRay,&fDistance);
			if(bHit	&&	pOutDistance!=NULL){
				Float3	vObjSpaceHitPostion		=	vStart	+	vDir*fDistance;
				Float3	vWorldSpaceHiPosition	=	matWorld*vObjSpaceHitPostion;
				*pOutDistance	=	(vWorldSpaceHiPosition	-	ray.m_vStart).Length();
			}
			return	bHit;
		}

	}
}