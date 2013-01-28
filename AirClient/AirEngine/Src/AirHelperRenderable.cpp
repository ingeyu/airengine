#include "AirHelperRenderable.h"
#include "AirRenderSystem.h"

namespace	Air{
	namespace	Client{


		MoveRenderable::MoveRenderable()
		{
			m_WorldMatrix	=	Float44(
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1
				);

			Float3 line[]={
				Float3(0,0,0),
				Float3(1,0,0),
				Float3(0,0,0),
				Float3(0,1,0),
				Float3(0,0,0),
				Float3(0,0,1),
			};

			Render::System*	pSys	=	Render::System::GetSingleton();
			Buffer::Info	vbInfo;
			vbInfo.SetVertexBuffer(6,12);
			vbInfo.InitData			=	line;
			m_DrawBuff.m_pVertexBuffer[0]	=	pSys->CreateProduct<Buffer*>("MoveVB","Buffer",&vbInfo);

			Render::Vertex::IDeclare::Info	vdInfo;
			vdInfo.SetDeclP3();
			m_DrawBuff.m_pVertexDeclare	=	pSys->CreateProduct<Render::Vertex::IDeclare*>("BoxVD","Declare",&vdInfo);


			m_DrawBuff.m_DrawOption.m_DrawFuncType	=	Render::Draw::FUNC_TYPE_DP;
			m_DrawBuff.m_DrawOption.m_DrawType		=	Render::Draw::enPT_LINELIST;
			m_DrawBuff.m_DrawOption.m_uiVertexCount	=	6;
			m_DrawBuff.m_DrawOption.m_uiIndexCount	=	0;
		}

		MoveRenderable::~MoveRenderable()
		{
			SAFE_RELEASE_REF(m_DrawBuff.m_pVertexBuffer[0]);
			SAFE_RELEASE_REF(m_DrawBuff.m_pVertexDeclare);
			SAFE_RELEASE_REF(m_DrawBuff.m_pIndexBuff);
		}


		RotateRenderable::RotateRenderable()
		{
			m_WorldMatrix	=	Float44(
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1
				);

			Float4 line[]={
				Float4(0,-1,1,0),
				Float4(0,1,1,0),
				Float4(0,-1,-1,0),
				Float4(0,1,-1,0),

				Float4(-1,0,1,1),
				Float4(1,0,1,1),
				Float4(-1,0,-1,1),
				Float4(1,0,-1,1),

				Float4(-1,1,0,2),
				Float4(1,1,0,2),
				Float4(-1,-1,0,2),
				Float4(1,-1,0,2),
			};

			Render::System*	pSys	=	Render::System::GetSingleton();
			Buffer::Info	vbInfo;
			vbInfo.SetVertexBuffer(12,16);
			vbInfo.InitData			=	line;
			m_DrawBuff.m_pVertexBuffer[0]	=	pSys->CreateProduct<Buffer*>("RotateRenderableVB","Buffer",&vbInfo);

			Render::Vertex::IDeclare::Info	vdInfo;
			vdInfo.SetDeclP4();
			m_DrawBuff.m_pVertexDeclare	=	pSys->CreateProduct<Render::Vertex::IDeclare*>("RotateRenderableVD","Declare",&vdInfo);

			U16	ib[]={
				0,1,2,
				2,1,3,

				4,5,6,
				6,5,7,

				8,9,10,
				10,9,11
			};
			vbInfo.SetIndexBuffer16(18);
			vbInfo.InitData	=	ib;
			m_DrawBuff.m_pIndexBuff	=	pSys->CreateProduct<Buffer*>("RotateRenderableIB","Buffer",&vbInfo);

			m_DrawBuff.m_DrawOption.m_DrawFuncType	=	Render::Draw::FUNC_TYPE_DIP;
			m_DrawBuff.m_DrawOption.m_DrawType		=	Render::Draw::enPT_TRIANGLELIST;
			m_DrawBuff.m_DrawOption.m_uiVertexCount	=	12;
			m_DrawBuff.m_DrawOption.m_uiIndexCount	=	18;
		}

		RotateRenderable::~RotateRenderable()
		{
			SAFE_RELEASE_REF(m_DrawBuff.m_pVertexBuffer[0]);
			SAFE_RELEASE_REF(m_DrawBuff.m_pVertexDeclare);
			SAFE_RELEASE_REF(m_DrawBuff.m_pIndexBuff);
		}


		ObjectController::ObjectController()
		{

			m_pMove		=	new MoveRenderable;
			m_pMove->SetMaterialName("Move");
			m_pMove->SetNeedWorldMatrix(true);
			m_pRotate	=	new	RotateRenderable;
			m_pRotate->SetMaterialName("Rotate");
			m_pRotate->SetNeedWorldMatrix(true);
			m_ControlMode	=	eMCM_Rotate;
			m_RayCastType	=	eMRCT_None;

			m_BoundingBox.vMin	=	Float3(-1,-1,-1);
			m_BoundingBox.vMax	=	Float3(1,1,1);

			AddFlag(enMOF_DEFAULT);

		}

		void ObjectController::ProcessRenderObject( U32 uiPhaseFlag )
		{
			switch(m_ControlMode){
				case eMCM_Move:{
					m_pMove->AddToRenderQueue(uiPhaseFlag);
							   }break;
				case eMCM_Rotate:{
					m_pRotate->AddToRenderQueue(uiPhaseFlag);
								 }break;
				case eMCM_Scale:{
					m_pMove->AddToRenderQueue(uiPhaseFlag);
								}break;
				default:{

						}break;
			}
		}

		ObjectController::~ObjectController()
		{
			SAFE_DELETE(m_pMove);
			SAFE_DELETE(m_pRotate);
		}

	}
}