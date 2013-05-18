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
				Float2(1,-1)
			};

			Render::System*	pSys	=	RenderSystem::GetSingleton();
			Buffer::Info	vbInfo;
			vbInfo.SetVertexBuffer(4,8);
			vbInfo.InitData			=	quad;
			m_DrawBuffer.m_pVertexBuffer[0]	=	pSys->CreateProduct<Buffer>("ParticleQuadVB",&vbInfo);
			vbInfo.SetIndexBuffer16(6);
			U16 uiIndex[]={
				0,1,2,
				2,1,3
			};
			vbInfo.InitData	=	uiIndex;
			m_DrawBuffer.m_pIndexBuff		=	pSys->CreateProduct<Buffer>("ParticleQuadIB",&vbInfo);

			Render::Vertex::IDeclare::Info	vdInfo;
			vdInfo.SetDeclP2();
			m_DrawBuffer.m_pVertexDeclare	=	pSys->CreateProduct<Render::Vertex::IDeclare>("QuadVD",&vdInfo);

			m_DrawBuffer.m_DrawOption.m_DrawFuncType	=	Render::Draw::FUNC_TYPE_DIP_I;
			m_DrawBuffer.m_DrawOption.m_DrawType		=	Render::Draw::enPT_TRIANGLELIST;
			m_DrawBuffer.m_DrawOption.m_uiVertexCount	=	4;
			m_DrawBuffer.m_DrawOption.m_uiIndexCount	=	6;
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
			SAFE_RELEASE_REF(m_DrawBuffer.m_pIndexBuff	);
			return true;
		}

		void ParticleRenderer::OnParticleRender( Render::Device* pDevice,Particle* pParticle )
		{
			PElementList& lst = pParticle->GetElementList();
			m_DrawBuffer.m_DrawOption.m_uiInstanceCount	=	lst.size();
			if(m_DrawBuffer.m_DrawOption.m_uiInstanceCount==0)
				return;

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

			static Float4 vBuffer[1024];
			PElementList::iterator itr = lst.begin();
			U32 i=0;
			for(;itr!=lst.end();itr++){
				Float3& vp = (*itr)->vPos;
				if(i==1024){
					m_pInstanceBuffer->UpdateData(vBuffer);
					__Draw(pDevice,1024);
					i=0;
				}
				vBuffer[i++]	=	Float4(vp.x,vp.y,vp.z,(*itr)->fSize);
			}
			
			m_pInstanceBuffer->UpdateData(vBuffer);
			__Draw(pDevice,i);
		}

		void* ParticleRenderer::ScriptParser( StringVector& vecWord,U32& i )
		{
			while(true){
				AString& strTemp2	=	vecWord[i++];
				if(strTemp2=="}"){
					break;
				}
			}
			return NULL;
		}

		void ParticleRenderer::__Draw( Render::Device* pDevice,U32 uiCount )
		{


			m_DrawBuffer.m_DrawOption.m_uiInstanceCount	=	uiCount;
			pDevice->DrawOpt(m_DrawBuffer.m_DrawOption);
		}

		AString	DirectionRenderer::ProductTypeName	=	"DirectionRenderer";
		void* DirectionRenderer::ScriptParser( StringVector& vecWord,U32& i )
		{
			return ParticleRenderer::ScriptParser(vecWord,i);
		}

		DirectionRenderer::DirectionRenderer( CAString& strName,Info* pInfo ):ParticleRenderer(strName,pInfo)
		{

		}

		void DirectionRenderer::OnParticleRender( Render::Device* pDevice,Particle* pParticle )
		{
			PElementList& lst = pParticle->GetElementList();
			m_DrawBuffer.m_DrawOption.m_uiInstanceCount	=	lst.size();
			if(m_DrawBuffer.m_DrawOption.m_uiInstanceCount==0)
				return;

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

			static Float4 vBuffer[1024];
			PElementList::iterator itr = lst.begin();
			U32 i=0;
			for(;itr!=lst.end();itr++){
				Float3& vp			= (*itr)->vPos;
				Float3& velocity	=	(*itr)->vVelocity;
				if(i==1024){
					m_pInstanceBuffer->UpdateData(vBuffer);
					__Draw(pDevice,i/2);
					i=0;
				}
				vBuffer[i++]	=	Float4(vp.x,vp.y,vp.z,(*itr)->fSize);
				vBuffer[i++]	=	Float4(velocity.x,velocity.y,velocity.z,(*itr)->fBornTime);
			}

			m_pInstanceBuffer->UpdateData(vBuffer);
			__Draw(pDevice,i/2);
		}


	}
}