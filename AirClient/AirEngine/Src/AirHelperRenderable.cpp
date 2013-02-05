#include "AirHelperRenderable.h"
#include "AirRenderSystem.h"

namespace	Air{
	namespace	Client{


		bool	RayCastTriangle(const Float3&	vStart,const Float3& vDir,const Float3& v0,const Float3& v1,const Float3& v2,float& fMaxDistance)
		{
			Float3	edge1	=	v1	-	v0;
			Float3	edge2	=	v2	-	v0;

			Float3	pvec	=	vDir.Cross(edge2);

			float det =  edge1.Dot( pvec );

			float u, v, t;

			Float3 tvec;

			if(det	>	0){
				tvec	=	vStart	-	v0;
			}else{
				tvec	=	v0	-	vStart;
				det		=	-det;
			}

			u	=	tvec.Dot(pvec);
			if(u<0.0f||u>det)
				return	false;
			Float3	qvec	=	tvec.Cross(edge1);
			v	=	vDir.Dot(qvec);
			if(v<0.0f||u+v>det)
				return	false;
			t	=	edge2.Dot(qvec)/det;
			if(t<0.0f||t>fMaxDistance)
				return	false;
			fMaxDistance	=	t;
			//nor	=	cross(edge1,edge2);
			return	true;
		};



		MoveRenderable::MoveRenderable(ObjectController* pControl):m_pControl(pControl)
		{


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

		Matrix* MoveRenderable::GetWorldMatrix()
		{
			return m_pControl->GetWorldMatrix();
		}


		RotateRenderable::RotateRenderable(ObjectController* pControl):m_pControl(pControl)
		{

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

		Matrix* RotateRenderable::GetWorldMatrix()
		{
			return m_pControl->GetWorldMatrix();
		}


		ObjectController::ObjectController()
		{

			m_pMove		=	new MoveRenderable(this);
			m_pMove->SetMaterialName("Move");
			m_pMove->SetNeedWorldMatrix(true);
			m_pRotate	=	new	RotateRenderable(this);
			m_pRotate->SetMaterialName("Rotate");
			m_pRotate->SetNeedWorldMatrix(true);
			m_ControlMode	=	eMCM_Move;
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

		Air::Client::enumMouseRayCastType ObjectController::ChangeType( const Float3& vStart,const Float3& vDir )
		{
			if(m_BoundingBox.RayCast(vStart,vDir)){
				switch(m_ControlMode){
					case eMCM_Select:{

								 }break;
					case eMCM_Move:
					case eMCM_Scale:{
						BoundingBox AXIS[3];
						AXIS[0].vMin	=	Float3(0,0,0);
						AXIS[0].vMax	=	Float3(1,0.05,0.05);

						AXIS[1].vMin	=	Float3(0,0,0);
						AXIS[1].vMax	=	Float3(0.05,1,0.05);

						AXIS[2].vMin	=	Float3(0,0,0);
						AXIS[2].vMax	=	Float3(0.05,0.05,1);

						for(int i=0;i<3;i++){
							if(AXIS[i].RayCast(vStart,vDir)){
								m_RayCastType	=	enumMouseRayCastType(i+1);
#if 1
								char str[64];
								sprintf_s(str,"%d\n",m_RayCastType);
								OutputDebugStringA(str);
#endif
								break;
							}else{
								m_RayCastType	=	eMRCT_None;
							}
						}

								}break;
					case eMCM_Rotate:{
						BoundingBox AXIS[3];
						AXIS[0].vMin	=	Float3(-0.01,-1,-1);
						AXIS[0].vMax	=	Float3(0.01,1,1);

						AXIS[1].vMin	=	Float3(-1,-0.01,-1);
						AXIS[1].vMax	=	Float3(1,0.01,1);

						AXIS[2].vMin	=	Float3(-1,-1,-0.01);
						AXIS[2].vMax	=	Float3(1,1,-0.01);

						float fDis[3]={10000,10000,10000};
						bool bHit	=	false;
						for(int i=0;i<3;i++){
							if(AXIS[i].RayCast(vStart,vDir,&fDis[i],NULL)){
								bHit	=	true;
							}	
						}
						if(bHit){
							m_RayCastType	=	eMRCT_X;
							for(int i=1;i<3;i++){
								if(fDis[i]	<	fDis[0]){
									fDis[0]	=	fDis[i];
									m_RayCastType	=	enumMouseRayCastType(i+1);
								}
							}
						}
								 }break;
				}
			}else{
				m_RayCastType	=	eMRCT_None;
			}

			return m_RayCastType;
		}

		Air::Client::enumMouseControlMode ObjectController::ChangeMode( enumMouseControlMode mode )
		{
			m_ControlMode	=	mode;
			return m_ControlMode;
		}

	}
}