#include "AirCascadedShadowMap.h"
#include "AirEngineMaterial.h"
#include "AirEngineSystem.h"
#include "AirEngineCamera.h"
#include "AirQuadRenderable.h"
namespace	Air{
	namespace	Engine{


		CascadedShadowMap::CascadedShadowMap()
		{
			m_pMainCamera	=	NULL;
			m_pShadowDepth	=	NULL;
			m_pShadowDepthTemp	=	NULL;
			m_pMaskMaterial	=	NULL;
			m_pQuad			=	NULL;
			m_pBlurX		=	NULL;
			m_pBlurY		=	NULL;

			m_vLightDirection	=	Float3(1,-1,1);
			m_vLightDirection.Normalize();
		}

		CascadedShadowMap::~CascadedShadowMap()
		{

		}

		Air::U1 CascadedShadowMap::Init( Camera* pMainCamera,U32 uiSplite /*= 4*/ )
		{
			if(uiSplite==0)
				return false;

			m_pQuad			=	new QuadRenderable();

			m_pMainCamera	=	pMainCamera;
			RenderTarget::Info rtinfo;
			rtinfo.SetSingleTarget(1024,1024,enTFMT_R32_FLOAT,true);
			m_pShadowDepth	=	RenderSystem::GetSingleton()->CreateProduct<RenderTarget>("CascadedShadowMapDepth",&rtinfo);
			m_pShadowDepth->SetClearFlag(true,true,true);
			m_pShadowDepth->AddPhaseFlag(enPI_Shadow);
			m_pShadowDepth->SetBKColor(Float4(1,1,1,1));

			

			Material::Info	blurinfo;
			blurinfo.strTemplate	=	"MT_BlurX";
			m_pBlurX		=	EngineSystem::GetSingleton()->CreateProduct<Material>("BlurX",&blurinfo);
			blurinfo.strTemplate	=	"MT_BlurY";
			m_pBlurY		=	EngineSystem::GetSingleton()->CreateProduct<Material>("BlurY",&blurinfo);

			m_pMaskMaterial	=	EngineSystem::GetSingleton()->CreateProduct<Material>("ShadowMask");


			m_vecCSMCamera.resize(uiSplite);
			AString	strCameraName	=	"CascadedShadowCamera";
			//Camera::Info info;
			//info.SetDirection(m_vLightDirection);
			for(U32 i=0;i<uiSplite;i++){
				m_vecCSMCamera[i]	=	EngineSystem::GetSingleton()->CreateProduct<Camera>(strCameraName+Common::Converter::ToString(i));
				m_vecCSMCamera[i]->SetDir(m_vLightDirection);
				m_vecCSMCamera[i]->SetOrtho(true);
				float Scale	=	pow(3.0f,(float)(i))*10.24f;
	

				m_vecCSMCamera[i]->SetWidth(Scale);
				m_pShadowDepth->AddCamera(m_vecCSMCamera[i],i);
			}
			return true;
		}

		Air::U1 CascadedShadowMap::Release()
		{
			SAFE_RELEASE_REF(m_pShadowDepth);
			SAFE_RELEASE_REF(m_pShadowDepthTemp);
			SAFE_RELEASE_REF(m_pMaskMaterial);
			SAFE_DELETE(m_pQuad);
			SAFE_RELEASE_REF(m_pBlurX);
			SAFE_RELEASE_REF(m_pBlurY);
			U32	uiSize	=	m_vecCSMCamera.size();
			for(U32 i=0;i<uiSize;i++){
				SAFE_RELEASE_REF(m_vecCSMCamera[i]);
			}
			return true;
		}

		Air::U1 CascadedShadowMap::UpdateCamera( Camera* pMainCamera )
		{
			Float3 axis(1,0.001,0.005);
			axis.Normalize();
			float fSec = -13;//floor(GetTimer().GetTotalTime());
			Common::Quaternion q(axis,fSec*0.001);//m_vLightDirection
			m_vLightDirection	=	q*Float3(-1,1,0.5).Normalize();//m_vLightDirection;
			m_vLightDirection.Normalize();
			if(m_vLightDirection.y>0){
				m_vLightDirection	=	-m_vLightDirection;
			}
			for(U32 i=0;i<m_vecCSMCamera.size();i++){
				m_vecCSMCamera[i]->SetDir(m_vLightDirection);
			}

			Float3 vCamPos	=	m_pMainCamera->GetRealPosition();
			Float3 vCamDir	=	m_pMainCamera->GetRealDirection();

			Matrix matPInv = m_pMainCamera->GetProjMatrix();
			matPInv.Inverse();
			Float3 v =	matPInv*Float3(1,1,0);
			float fSlope	=	sqrt(v.x*v.x+v.y*v.y);

			float fLastZ	=	1.0f;

			for(U32 i=0;i<m_vecCSMCamera.size();i++){
				Camera*	pLight	=	m_vecCSMCamera[i];
				float fRadius	=	pLight->GetWidth()*0.5f;
				float fSize	=	fSlope*fLastZ;
				float fDis	=	fLastZ+sqrt(fRadius*fRadius-fSize*fSize);
				Float3 vPos	=	vCamPos+vCamDir*fDis;

				float a		=	(fSlope*fSlope+1);
				float b		=	-2*fDis;
				float c		=	fDis*fDis-fRadius*fRadius;
				fLastZ		=	(-b+sqrt(b*b-4*a*c))/(2*a);
				

				float fScale	=	pLight->GetWidth()/1024.0f;
				///float fScale2	=	fScale*2/256.0f;
				Float3 pos		=	vPos-m_vLightDirection*200;

				Float44	view = pLight->GetViewMatrix();
				Float3 viewpos	=	view*pos;
				view.Inverse();
				viewpos/=fScale;
				viewpos	=	Float3(floor(viewpos.x),floor(viewpos.y),floor(viewpos.z))*fScale;
				Float3 vpos	=	view*viewpos;
				pLight->SetPosition(vpos);
			}


			return true;
		}

		Air::U1 CascadedShadowMap::UpdateTarget(RenderTarget* pLighting)
		{
			Air::Engine::PhaseOption opt;
			opt.AddIndex(enPI_Shadow);

			for(U32 i=0;i<m_vecCSMCamera.size();i++){
	
				m_pShadowDepth->SetClearFlag(true,true,true);
				if(m_pShadowDepth->BeforeUpdate()){
					m_vecCSMCamera[i]->Render2D(m_pShadowDepth->GetWidth(),m_pShadowDepth->GetHeight());
					RenderSystem::GetSingleton()->RenderPhase(opt);
					m_pShadowDepth->AfterUpdate();
				}

				//BlurRenderTarget(m_pShadowDepthTemp,m_pShadowDepth);

				//Shadow Mask
				
				pLighting->SetClearFlag(false,false,false);
				
				if(pLighting->BeforeUpdate()){
					Float4	matArray[15];
					Float44*	pMVPInv	=	(Float44*)&matArray[0];
					Float44*	pSVP	=	(Float44*)&matArray[4];
					Float44*	pSVPInv	=	(Float44*)&matArray[8];

					m_pMaskMaterial->GetConstantBuffer()->GetBuffer();
					*pMVPInv	=	m_pMainCamera->GetViewProjMatrix();
					pMVPInv->Inverse();

					*pSVP	=	m_vecCSMCamera[i]->GetViewProjMatrix();
					*pSVPInv	=	*pSVP;
					pSVPInv->Inverse();
					matArray[12]	=	Float4(1.0f/pLighting->GetWidth(),1.0f/pLighting->GetHeight(),1.0f/pLighting->GetWidth(),1.0f/pLighting->GetHeight());
					matArray[13]	=	m_pMainCamera->GetPosition();
					matArray[13].w	=	m_vecCSMCamera[i]->GetWidth()/(float)m_pShadowDepth->GetWidth();
					matArray[14]	=	Float4(1,1,1,1);
					m_pMaskMaterial->GetConstantBuffer()->UpdateData(matArray);
					m_pMaskMaterial->RenderOneObject(m_pQuad);

					pLighting->AfterUpdate();
				}
			}
			return true;
		}
		void CascadedShadowMap::BlurRenderTarget( RenderTarget* pDst,RenderTarget* pSrc )
		{
			if(pDst==NULL	||	pSrc	==	NULL)
				return;
			if(pDst->BeforeUpdate()){

				RenderSystem::GetSingleton()->GetDevice()->SetSRV(enPS,0,pSrc->GetSRV());
				m_pBlurX->RenderOneObject(m_pQuad);

				pDst->AfterUpdate();
			}

			if(pSrc->BeforeUpdate()){
				RenderSystem::GetSingleton()->GetDevice()->SetSRV(enPS,0,pDst->GetSRV());
				m_pBlurY->RenderOneObject(m_pQuad);

				pSrc->AfterUpdate();
			}
		}
	}
}