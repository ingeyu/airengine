#include "AirParticleRenderer.h"
#include "AirParticle.h"
#include "AirRenderSystem.h"
namespace	Air{
	namespace	Engine{

		AString	ParticleRenderer::ProductTypeName	=	"DefaultRenderer";
		ParticleRenderer::ParticleRenderer(CAString& strName,Info* pInfo):IProduct(strName)
		{

		}

		Air::U1 ParticleRenderer::Create()
		{
			static Float2 quad[]={
				Float2(-1,1),
				Float2(1,1),
				Float2(-1,-1),

				Float2(-1,-1),
				Float2(1,1),
				Float2(1,-1)
			};

			Render::System*	pSys	=	RenderSystem::GetSingleton();
			Buffer::Info	vbInfo;
			vbInfo.SetVertexBuffer(6,8);
			vbInfo.InitData			=	quad;
			m_DrawBuffer.m_pVertexBuffer[0]	=	pSys->CreateProduct<Buffer>("QuadVB",&vbInfo);
			Render::Vertex::IDeclare::Info	vdInfo;
			vdInfo.SetDeclP2();
			m_DrawBuffer.m_pVertexDeclare	=	pSys->CreateProduct<Render::Vertex::IDeclare>("QuadVD",&vdInfo);

			m_DrawBuffer.m_DrawOption.m_DrawFuncType	=	Render::Draw::FUNC_TYPE_DP_I;
			m_DrawBuffer.m_DrawOption.m_DrawType		=	Render::Draw::enPT_TRIANGLELIST;
			m_DrawBuffer.m_DrawOption.m_uiVertexCount	=	6;
			m_DrawBuffer.m_DrawOption.m_uiInstanceCount	=	1;
			vbInfo.SetStructureBuffer(1024,sizeof(Float4));
			vbInfo.SetViewFlag(enVF_SRV);
			m_pInstanceBuffer							=	pSys->CreateProduct<Buffer>("ParticleInstanceVB",&vbInfo);
			return true;
		}

		Air::U1 ParticleRenderer::Destroy()
		{
			SAFE_RELEASE_REF(m_DrawBuffer.m_pVertexBuffer[0]);
			SAFE_RELEASE_REF(m_DrawBuffer.m_pVertexDeclare);
			SAFE_RELEASE_REF(m_pInstanceBuffer);
			return true;
		}

		void ParticleRenderer::OnParticleRender( Render::Device* pDevice,Particle* pParticle )
		{
			PElementList& lst = pParticle->GetElementList();
			m_DrawBuffer.m_DrawOption.m_uiInstanceCount	=	lst.size();
			if(m_DrawBuffer.m_DrawOption.m_uiInstanceCount==0)
				return;

			static Float4 vBuffer[1024];
			PElementList::iterator itr = lst.begin();
			U32 i=0;
			for(;itr!=lst.end();itr++){
				Float3& vp = (*itr)->vPos;

				vBuffer[i++]	=	Float4(vp.x,vp.y,vp.z,(*itr)->m_fSize);
			}
			m_pInstanceBuffer->UpdateData(vBuffer);



			pDevice->SetVD(m_DrawBuffer.m_pVertexDeclare);
			Buffer*	pVB=	NULL;
			for(int i=0;i<4;i++){
				pVB	=	m_DrawBuffer.m_pVertexBuffer[i];
				if(pVB==NULL)
					break;
				else
					pDevice->SetVB(i,pVB);
			}
			//如果IB为空 则不设置
			//if(m_DrawBuff.m_pIndexBuff!=NULL)
			pDevice->SetIB(m_DrawBuffer.m_pIndexBuff);
			pDevice->SetSRV(enVS,0,m_pInstanceBuffer->GetSRV());

			pDevice->DrawOpt(m_DrawBuffer.m_DrawOption);
		}

	}
}