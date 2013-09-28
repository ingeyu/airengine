#include "AirQuadRenderable.h"
#include "AirRenderSystem.h"

namespace	Air{
	namespace	Engine{

		QuadRenderable::QuadRenderable()
		{
			m_bNeedWorldMatrix	=	false;
			static Float2 quad[]={
				Float2(-1,1),
				Float2(1,1),
				Float2(-1,-1),

				Float2(-1,-1),
				Float2(1,1),
				Float2(1,-1)
			};

			Render::System*	pSys	=	Render::System::GetSingleton();
			Buffer::Info	vbInfo;
			vbInfo.SetVertexBuffer(6,8);
			vbInfo.InitData			=	quad;
			m_DrawBuff.m_pVertexBuffer[0]	=	pSys->CreateProduct<Buffer>("QuadVB",&vbInfo);

			Render::Vertex::IDeclare::Info	vdInfo;
			vdInfo.SetDeclP2();
			m_DrawBuff.m_pVertexDeclare	=	pSys->CreateProduct<Render::Vertex::IDeclare>("QuadVD",&vdInfo);


			m_DrawBuff.m_DrawOption.m_DrawFuncType	=	Render::Draw::FUNC_TYPE_DP;
			m_DrawBuff.m_DrawOption.m_DrawType		=	Render::Draw::enPT_TRIANGLELIST;
			m_DrawBuff.m_DrawOption.m_uiVertexCount	=	6;
			m_DrawBuff.m_DrawOption.m_uiIndexCount	=	6;
		}

		QuadRenderable::~QuadRenderable()
		{
			SAFE_RELEASE_REF(m_DrawBuff.m_pVertexBuffer[0]);
			SAFE_RELEASE_REF(m_DrawBuff.m_pVertexDeclare);
		}


		void CSRenderable::OnRender( Render::Device* pDevice )
		{
			pDevice->Dispatch(m_Dispatch[0],m_Dispatch[1],m_Dispatch[2]);
		}

		CSRenderable::CSRenderable()
		{
			m_Dispatch[0]	=	1;
			m_Dispatch[1]	=	1;
			m_Dispatch[2]	=	1;
			SetNeedWorldMatrix(false);
		}

	}

}