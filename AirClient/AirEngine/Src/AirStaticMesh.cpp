#include "AirStaticMesh.h"
#include "AirRenderSystem.h"
#include "AirEngineMaterial.h"

namespace	Air{
	namespace	Client{


		StaticMesh::StaticMesh( CAString& strName ):IProduct(strName)
		{
			m_pData		=	NULL;
			m_uiSize	=	0;

			m_uiNumVertex	=	NULL;
			m_uiNumFace		=	NULL;
			pVB				=	NULL;
			pIB				=	NULL;
		}

		Air::U1 StaticMesh::Create()
		{
			if(Common::File::Load(m_strProductName,m_pData,m_uiSize)){
				int	version	=	*(int*)m_pData;
				if(version	==	'0EMA'){
					LoadAME0();

					//memcpy(m_Bound,)
				}
				Render::System*	pSys	=	Render::System::GetSingleton();
				Buffer::Info	vbInfo;
				vbInfo.SetVertexBuffer(m_uiNumVertex,44);
				vbInfo.InitData			=	pVB;
				m_DrawBuff.m_pVertexBuff	=	pSys->CreateProduct<Buffer*>(m_strProductName+"VB","Buffer",&vbInfo);

				Buffer::Info	ibInfo;
				ibInfo.SetIndexBuffer32(m_uiNumFace*3);
				ibInfo.InitData			=	pIB;
				m_DrawBuff.m_pIndexBuff	=	pSys->CreateProduct<Buffer*>(m_strProductName+"IB","Buffer",&ibInfo);

				Render::Vertex::IDeclare::Info	vdInfo;
				vdInfo.SetDeclPNTT();
				m_DrawBuff.m_pVertexDeclare	=	pSys->CreateProduct<Render::Vertex::IDeclare*>(m_strProductName,"Declare",&vdInfo);

				m_DrawBuff.m_DrawOption.m_DrawFuncType	=	Render::Draw::FUNC_TYPE_DIP;
				m_DrawBuff.m_DrawOption.m_DrawType		=	Render::Draw::enPT_TRIANGLELIST;
				m_DrawBuff.m_DrawOption.m_uiVertexCount	=	m_uiNumVertex;
				m_DrawBuff.m_DrawOption.m_uiFaceCount	=	m_uiNumFace;
				
				return	true;
			}

			return	true;
		}

		Air::U1 StaticMesh::LoadAME0()
		{
			U8*	p	=	m_pData;
			p+=sizeof(U32);
			m_BoundingBox				=	*(BoundingBox*)p;		p+=sizeof(BoundingBox);
			U32	uiMaterialNameLength	=	0;
			uiMaterialNameLength		=	*(U32*)p;				p+=sizeof(U32);
			m_strMaterialName.resize(uiMaterialNameLength);
			memcpy(&m_strMaterialName[0],p,uiMaterialNameLength);	p+=uiMaterialNameLength;
			U32	uiVBSize				=	(*(U32*)p);				p+=sizeof(U32);
			m_uiNumVertex				=	uiVBSize/44;
			pVB							=	p;						p+=uiVBSize;
			U32	uiIBSize				=	(*(U32*)p);				p+=sizeof(U32);
			m_uiNumFace					=	uiIBSize/12;
			pIB							=	p;
			return	true;
		}

		Air::U1 StaticMesh::Destroy()
		{
			SAFE_RELEASE_REF(m_DrawBuff.m_pVertexBuff);
			SAFE_RELEASE_REF(m_DrawBuff.m_pIndexBuff);
			SAFE_RELEASE_REF(m_DrawBuff.m_pVertexDeclare);

			SAF_DA(m_pData);
			m_pData		=	NULL;
			m_uiSize	=	0;

			m_uiNumVertex	=	NULL;
			m_uiNumFace		=	NULL;
			pVB				=	NULL;
			pIB				=	NULL;
			return	true;
		}

		const BoundingBox& StaticMesh::GetBoundingBox() const
		{
			return m_BoundingBox;
		}

		const Render::Draw::Buff& StaticMesh::GetDrawBuffer() const
		{
			return	m_DrawBuff;
		}

	}
}