#include "AirPipelineDefferredLight.h"
#include "AirEngineSystem.h"
#include "AirMeshEntity.h"
#include "AirEngineMaterial.h"
#include "AirEnginePipeline.h"
#include "AirQuadRenderable.h"
namespace	Air{
	namespace	Engine{


		DefferredLight::DefferredLight()
		{
			m_pPointMaterial	=	NULL;
			m_pLightBuffer		=	NULL;
			m_pSphere			=	NULL;
			m_pPipeline			=	NULL;
		}

		Air::U1 DefferredLight::Initialization(Pipeline* pPipeline)
		{
			m_pPipeline			=	pPipeline;
			RenderTarget::Info	info;
			info.SetSingleTargetScreen(enTFMT_R16G16B16A16_FLOAT,1.0f,true,pPipeline->GetMainWindow());
			m_pLightBuffer		=	RenderSystem::GetSingleton()->CreateProduct<RenderTarget>("DefferredLight",&info);
			m_pLightBuffer->AddPhaseFlag(enPI_DeferredLight);
			m_pLightBuffer->AddCamera(pPipeline->GetMainCamera());
			m_pLightBuffer->SetClearFlag(false,true,false);
			

			m_pPointMaterial	=	EngineSystem::GetSingleton()->CreateProduct<Material>("PointLight");
			MeshEntity::Info meshInfo;
			meshInfo.strMeshName	=	"AirMesh/Sphere.ame";
			meshInfo.strMaterial	=	"NoMaterial";
			m_pSphere			=	EngineSystem::GetSingleton()->CreateProduct<MeshEntity>("PointLight",&meshInfo);

			return true;
		}

		Air::U1 DefferredLight::Release()
		{
			m_pPipeline	=	nullptr;
			SAFE_RELEASE_REF(m_pPointMaterial);
			SAFE_RELEASE_REF(m_pSphere);
			SAFE_RELEASE_REF(m_pLightBuffer);
			return true;
		}

		void DefferredLight::Update(const FrameTime& frameTime)
		{
			
			if(m_pLightBuffer->BeforeUpdate()){
				if(m_vecPointLight.empty()){
					m_pLightBuffer->AfterUpdate();
					return;
				}
					
				Render::Device* pDevice	=	RenderSystem::GetSingleton()->GetDevice();

				struct {
					Float4	vParam[2];
					Float44 matViewProjInv;
				}cb;

				cb.matViewProjInv	=	m_pPipeline->GetMainCamera()->GetViewProjMatrix();
				cb.matViewProjInv.Inverse();
				memcpy(cb.vParam,&m_vecPointLight[0],sizeof(PointLightInfo));
				m_pPointMaterial->GetConstantBuffer()->UpdateData(&cb);

				m_pPointMaterial->RenderOneObject(m_pSphere);

				
				U32 uiCount	=	m_vecPointLight.size();
				for(U32 i=1;i<uiCount;i++){
					PointLightInfo& info	=	m_vecPointLight[i];
					memcpy(cb.vParam,&info,sizeof(info));
					m_pPointMaterial->GetConstantBuffer()->UpdateData(&cb);
					pDevice->DrawOpt(m_pSphere->GetMesh()->GetDrawBuffer().m_DrawOption);
				}

				m_pLightBuffer->AfterUpdate();
			}
			m_vecPointLight.clear();
			
		}

		void DefferredLight::AddPointLight( const Float3& pos,float fSize,const Float3& vColor )
		{
			PointLightInfo	point;
			point.vPos		=	pos;
			point.fSize		=	fSize;
			point.vColor	=	vColor;
			m_vecPointLight.push_back(point);
		}


		TileBaseLight::TileBaseLight()
		{
			m_pCSRenderable	=	NULL;
		}

		Air::U1 TileBaseLight::Initialization( Pipeline* pPipeline )
		{
			m_pCSRenderable		=	new	CSRenderable;
			m_pPipeline			=	pPipeline;
			RenderTarget::Info	info;
			info.SetSingleTargetScreen(enTFMT_R32_FLOAT,1.0f,true,pPipeline->GetMainWindow());
			info.vecTextureInfo[0].SetViewFlag(enVF_SRV|enVF_UAV);
			m_pLightBuffer		=	RenderSystem::GetSingleton()->CreateProduct<RenderTarget>("TileBaseLighting",&info);
			m_pLightBuffer->AddPhaseFlag(enPI_DeferredLight);
			m_pLightBuffer->AddCamera(pPipeline->GetMainCamera());
			m_pLightBuffer->SetClearFlag(false,true,false);


			m_pPointMaterial	=	EngineSystem::GetSingleton()->CreateProduct<Material>("TileBaseLighting");
			m_pSphere			=	NULL;//EngineSystem::GetSingleton()->CreateProduct<MeshEntity>("PointLight",&meshInfo);
			return true;
		}

		Air::U1 TileBaseLight::Release()
		{
			SAFE_DELETE(m_pCSRenderable);
			return __super::Release();
		}

		void TileBaseLight::Update( const FrameTime& frameTime )
		{
			Render::Device* pDevice	=	RenderSystem::GetSingleton()->GetDevice();
			void* p	=	m_pLightBuffer->GetUAV();
			pDevice->SetUAV(1,(void**)&p);
			pDevice->SetSRV(enCS,0,NULL);

			Float4 v(m_pLightBuffer->GetWidth(),m_pLightBuffer->GetHeight(),0,0);
			m_pPointMaterial->GetConstantBuffer()->Write(0,sizeof(Float4),&v);
			int x	=	(m_pLightBuffer->GetWidth()+15)>>4;
			int y	=	(m_pLightBuffer->GetHeight()+15)>>4;
			m_pCSRenderable->m_Dispatch[0]	=	x;
			m_pCSRenderable->m_Dispatch[1]	=	y;
			m_pPointMaterial->RenderOneObject(m_pCSRenderable);

			pDevice->SetShader(enCS,NULL);
			p=NULL;
			pDevice->SetUAV(1,(void**)&p);
		}
	}
}