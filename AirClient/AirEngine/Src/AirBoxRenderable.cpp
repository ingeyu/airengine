#include "AirBoxRenderable.h"
#include "AirRenderSystem.h"

namespace	Air{
	namespace	Client{
		BoxMesh::BoxMesh()
		{
			Float3 box[]={
				Float3(-1,-1,-1),
				Float3(-1,-1,1),
				Float3(1,-1,-1),
				Float3(1,-1,1),

				Float3(-1,1,-1),
				Float3(-1,1,1),
				Float3(1,1,-1),
				Float3(1,1,1)
			};

			Render::System*	pSys	=	Render::System::GetSingleton();
			Buffer::Info	vbInfo;
			vbInfo.SetVertexBuffer(8,12);
			vbInfo.InitData			=	box;
			m_DrawBuff.m_pVertexBuffer[0]	=	pSys->CreateProduct<Buffer*>("BoxVB","Buffer",&vbInfo);

			U16	ib[]={
				2,3,0,
				0,3,1,

				6,7,2,
				2,7,3,

				4,5,6,
				6,5,7,

				4,6,0,
				0,6,2,

				7,5,3,
				3,5,1,

				5,4,6,
				6,4,0

			};
			vbInfo.SetIndexBuffer16(12*3);
			vbInfo.InitData	=	ib;
			m_DrawBuff.m_pIndexBuff	=	pSys->CreateProduct<Buffer*>("BoxIB","Buffer",&vbInfo);

			Render::Vertex::IDeclare::Info	vdInfo;
			vdInfo.SetDeclP3();
			m_DrawBuff.m_pVertexDeclare	=	pSys->CreateProduct<Render::Vertex::IDeclare*>("BoxVD","Declare",&vdInfo);


			m_DrawBuff.m_DrawOption.m_DrawFuncType	=	Render::Draw::FUNC_TYPE_DIP;
			m_DrawBuff.m_DrawOption.m_DrawType		=	Render::Draw::enPT_TRIANGLELIST;
			m_DrawBuff.m_DrawOption.m_uiVertexCount	=	8;
			m_DrawBuff.m_DrawOption.m_uiFaceCount	=	12;
		}

		BoxMesh::~BoxMesh()
		{
			SAFE_RELEASE_REF(m_DrawBuff.m_pVertexBuffer[0]);
			SAFE_RELEASE_REF(m_DrawBuff.m_pVertexDeclare);
			SAFE_RELEASE_REF(m_DrawBuff.m_pIndexBuff);
		}

		BoxRenderable::BoxRenderable()
		{
			m_DrawBuff	=	BoxMesh::AddRef()->m_DrawBuff;
		}

		BoxRenderable::~BoxRenderable()
		{
			BoxMesh::ReleaseRef();
		}

	}
}