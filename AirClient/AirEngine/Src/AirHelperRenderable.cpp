#include "AirHelperRenderable.h"
#include "AirRenderSystem.h"
#include "AirEngineMaterial.h"
#include "AirEngineSceneNode.h"
#include "AirBoxRenderable.h"

namespace	Air{
	namespace	Engine{


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


			Float4 line[]={
				Float4(0,0,0,0),
				Float4(1,0,0,0),
				Float4(0,0,0,1),
				Float4(0,1,0,1),
				Float4(0,0,0,2),
				Float4(0,0,1,2),
			};

			Render::System*	pSys	=	Render::System::GetSingleton();
			Buffer::Info	vbInfo;
			vbInfo.SetVertexBuffer(6,16);
			vbInfo.InitData			=	line;
			m_DrawBuff.m_pVertexBuffer[0]	=	pSys->CreateProduct<Buffer>("MoveVB",&vbInfo);

			Render::Vertex::IDeclare::Info	vdInfo;
			vdInfo.SetDeclP4();
			m_DrawBuff.m_pVertexDeclare	=	pSys->CreateProduct<Render::Vertex::IDeclare>("MoveVD",&vdInfo);


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

		void MoveRenderable::BeforeRender( Material* pMaterial )
		{
			if(pMaterial!=NULL){
				pMaterial->GetConstantBuffer()->GetBuffer();
				Buffer* pCB	=	pMaterial->GetConstantBuffer();
				if(pCB){
					pCB->GetBuffer();
					Float4 v(1,1,1,1);
					if(m_pControl->GetType()	!=	eMRCT_None){
						v*=0.0f;
						v[m_pControl->GetType()-1] =	1.0f;
					}
					pCB->UpdateData(&v);
				}
			}
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
			m_DrawBuff.m_pVertexBuffer[0]	=	pSys->CreateProduct<Buffer>("RotateRenderableVB",&vbInfo);

			Render::Vertex::IDeclare::Info	vdInfo;
			vdInfo.SetDeclP4();
			m_DrawBuff.m_pVertexDeclare	=	pSys->CreateProduct<Render::Vertex::IDeclare>("RotateRenderableVD",&vdInfo);

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
			m_DrawBuff.m_pIndexBuff	=	pSys->CreateProduct<Buffer>("RotateRenderableIB",&vbInfo);

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

		void RotateRenderable::BeforeRender( Material* pMaterial )
		{
			if(pMaterial!=NULL){
				pMaterial->GetConstantBuffer()->GetBuffer();
				Buffer* pCB	=	pMaterial->GetConstantBuffer();
				if(pCB){
					pCB->GetBuffer();
					Float4 v(1,1,1,1);
					if(m_pControl->GetType()	!=	eMRCT_None){
						v*=0.25f;
						v[m_pControl->GetType()-1] =	1.0f;
					}
					
					pCB->UpdateData(&v);
				}
			}
		}


		ObjectController::ObjectController()
		{

			m_pMove		=	new MoveRenderable(this);
			m_pMove->SetMaterialName("Move");
			m_pMove->SetNeedWorldMatrix(true);
			m_pRotate	=	new	RotateRenderable(this);
			m_pRotate->SetMaterialName("Rotate");
			m_pRotate->SetNeedWorldMatrix(true);
			m_pSelectBox	=	new Engine::BoxRenderable();
			m_pRayCastBox	=	new BoxRenderable();
			m_pSelectBox->SetMaterialName("WorldHelperWireFrame");
			m_pRayCastBox->SetMaterialName("RedHelperWireFrame");
			m_ControlMode	=	eMCM_Select;
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
					m_pRayCastBox->AddToRenderQueue(uiPhaseFlag);
						}break;
			}
			m_pSelectBox->AddToRenderQueue(uiPhaseFlag);
			
		}

		ObjectController::~ObjectController()
		{
			SAFE_DELETE(m_pRayCastBox);
			SAFE_DELETE(m_pSelectBox);
			SAFE_DELETE(m_pMove);
			SAFE_DELETE(m_pRotate);
		}

		Air::Engine::enumMouseRayCastType ObjectController::ChangeType( const Float3& vStart,const Float3& vDir )
		{
			Float44 matWorldInv	=	m_WorldMatrix;
			matWorldInv.Inverse();
			Float3 vNewStart	= matWorldInv*vStart;
			Float3 vNewDir		=	matWorldInv*(vStart+vDir)	-	vNewStart;
			vNewDir.Normalize();

			float	fDistance	=	vStart.Distance(m_WorldMatrix.GetPosition())*0.1;

			//if(m_WorldBound.RayCast(vStart,vDir))
			{
				switch(m_ControlMode){
					case eMCM_Select:{

								 }break;
					case eMCM_Move:
					case eMCM_Scale:{
						BoundingBox AXIS[3];
						AXIS[0].vMin	=	Float3(0,-0.05,-0.05)*fDistance;
						AXIS[0].vMax	=	Float3(1,0.05,0.05)*fDistance;

						AXIS[1].vMin	=	Float3(-0.05,0,-0.05)*fDistance;
						AXIS[1].vMax	=	Float3(0.05,1,0.05)*fDistance;

						AXIS[2].vMin	=	Float3(-0.05,-0.05,0)*fDistance;
						AXIS[2].vMax	=	Float3(0.05,0.05,1)*fDistance;

						for(int i=0;i<3;i++){
							if(AXIS[i].RayCast(vNewStart,vNewDir)){
								m_RayCastType	=	enumMouseRayCastType(i+1);
#if 0
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
						AXIS[0].vMin	=	Float3(-0.01,-1,-1)*fDistance;
						AXIS[0].vMax	=	Float3(0.01,1,1)*fDistance;

						AXIS[1].vMin	=	Float3(-1,-0.01,-1)*fDistance;
						AXIS[1].vMax	=	Float3(1,0.01,1)*fDistance;

						AXIS[2].vMin	=	Float3(-1,-1,-0.01)*fDistance;
						AXIS[2].vMax	=	Float3(1,1,0.01)*fDistance;

						float fDis[3]={10000,10000,10000};
						bool bHit	=	false;
						for(int i=0;i<3;i++){
							if(AXIS[i].RayCast(vNewStart,vNewDir,&fDis[i],NULL)){
								Float3 hitPos	=	vNewDir*fDis[i]+vNewStart;
								float dis	=	(hitPos.Distance(Float3(0,0,0)))/fDistance;
								if(dis < 1.0	&& dis > 0.8f){
									bHit	=	true;
								}else{
									fDis[i]	=	10000.0f;
								}
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
#if 0
							char str[64];
							sprintf_s(str,"%d\n",m_RayCastType);
							OutputDebugStringA(str);
#endif

						}else{
							m_RayCastType	=	eMRCT_None;
						}
								 }break;
				}
			}

			return m_RayCastType;
		}

		Air::Engine::enumMouseControlMode ObjectController::ChangeMode( enumMouseControlMode mode )
		{
			m_ControlMode	=	mode;
			return m_ControlMode;
		}

		void ObjectController::SetPosition( const Float3& vPos)
		{
			SceneNode* pNode	=	GetParentSceneNode();
			if(pNode!=NULL){
				pNode->SetPosition(vPos);
				static Float44 matWorld;
				static Float4  rot;
				static Float3  scale;
				pNode->Update(matWorld,rot,scale,false);
			}
		}

		void ObjectController::SetSelectObjectBoundingBox( const BoundingBox& bound )
		{
			if(m_pSelectBox!=NULL){
				Float3 vPos =	bound.GetCenter();
				Float3 vScale = bound.GetHalfSize();
				m_pSelectBox->m_WorldMatrix	=	Float44(vPos,vScale,Float4(0,0,0,1));
			}
		}

		void ObjectController::SetRayCastObjectBoundingBox( const BoundingBox& bound )
		{
			if(m_pRayCastBox!=NULL){
				Float3 vPos =	bound.GetCenter();
				Float3 vScale = bound.GetHalfSize();
				m_pRayCastBox->m_WorldMatrix	=	Float44(vPos,vScale,Float4(0,0,0,1));
			}
		}

	}
}