#include "AirQuadRenderable.h"
#include "AirRenderSystem.h"

namespace	Air{
	namespace	Client{

		QuadRenderable::QuadRenderable()
		{
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
			m_DrawBuff.m_pVertexBuffer[0]	=	pSys->CreateProduct<Buffer*>("QuadVB","Buffer",&vbInfo);

			Render::Vertex::IDeclare::Info	vdInfo;
			vdInfo.SetDeclP2();
			m_DrawBuff.m_pVertexDeclare	=	pSys->CreateProduct<Render::Vertex::IDeclare*>("QuadVD","Declare",&vdInfo);


			m_DrawBuff.m_DrawOption.m_DrawFuncType	=	Render::Draw::FUNC_TYPE_DP;
			m_DrawBuff.m_DrawOption.m_DrawType		=	Render::Draw::enPT_TRIANGLELIST;
			m_DrawBuff.m_DrawOption.m_uiVertexCount	=	6;
			m_DrawBuff.m_DrawOption.m_uiFaceCount	=	2;
		}

		QuadRenderable::~QuadRenderable()
		{
			SAFE_RELEASE_REF(m_DrawBuff.m_pVertexBuffer[0]);
			SAFE_RELEASE_REF(m_DrawBuff.m_pVertexDeclare);
		}

	}

}