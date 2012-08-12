#include "AirEngineCharacter.h"
#include "..\..\AirCharacter\cal3d.h"
#include "AirGlobalSetting.h"

#include "AirInterfaceRenderVertexBuff.h"
#include "AirInterfaceRenderIndexbuff.h"
#include "AirInterfaceRenderSystem.h"

namespace Client{

	namespace	Character{

		typedef	Client::Render::Vertex::IBuff		VertexBuff;
		typedef	Client::Render::Index::IBuff		IndexBuff;
		typedef	Client::Render::Vertex::IDeclare	VertexDeclare;


		SoftwareModel::SoftwareModel( AString strName,void* pInfo ){
			m_pMesh			=	new	Mesh(strName);
			m_pAnimation	=	NULL;
			m_fLodLevel		=	1.0f;
			m_fRenderScale	=	1.0f;
			m_Bound.SetMin(Common::Vector3(-0.25f,	0.0f,	-0.25f));
			m_Bound.SetMax(Common::Vector3(0.25f,	2.0f,	0.25f));
		}

		SoftwareModel::~SoftwareModel(){
			SAF_D(m_pMesh);

		}

		U1 SoftwareModel::SetAction( enumActionState actState,Real fBlendTime /*= 0.3f*/ ){
			 return m_pAnimation->getMixer()->executeAction(actState, 0.3f, fBlendTime);
		};

		Real SoftwareModel::GetLodLevel(){
			return m_fLodLevel;
		}

		void SoftwareModel::SetLodLevel( Real fLodLevel ){
			
		}

		void SoftwareModel::SetState( enumActionState state, Real fBlendTime /*= 0.3f*/ ){
			m_CurrentActionState	=	state;
		}

		Client::Character::enumActionState SoftwareModel::GetState(){
			return m_CurrentActionState;
		}

		U1 SoftwareModel::Create(){
			m_pAnimation	=	new	AnimationMesh(m_pMesh);

			UInt	uiMeshCount	=	m_pMesh->getCoreMeshCount();
			for(UInt	i = 0; i < uiMeshCount; i++){
				m_pAnimation->attachMesh(i);
			}

			if(m_DrawBuff.m_pVertexBuff==NULL){
				VertexBuff::Info vertexInfo;
				vertexInfo.SetToDynamic();
				//VertexBuff顶点缓冲会释放这块内存  不要自己去手动释放
				//-------------------------------------
				vertexInfo.InitData	=	new	VertexBuff::Data();
				//-------------------------------------
				vertexInfo.InitData->ReSize(50000);
				//pCalRenderer->getVertices()
				m_DrawBuff.m_pVertexBuff	=	GetGlobalSetting().m_pRenderSystem->Create<VertexBuff*>("asdasdasd","VertexBuff",&vertexInfo);
			}

			if(m_DrawBuff.m_pIndexBuff==NULL){
				IndexBuff::Info indexInfo;
				indexInfo.SetToDynamic();
				//不要自己去手动释放这块内存
				//-------------------------------------
				indexInfo.pData	=	new	IndexBuff::Data();
				//-------------------------------------
				indexInfo.pData->ReSize(50000);
				m_DrawBuff.m_pIndexBuff	=	GetGlobalSetting().m_pRenderSystem->Create<IndexBuff*>("asdasdasd","IndexBuff",&indexInfo);
			}

			if(m_DrawBuff.m_pVertexDeclare==NULL){
				VertexDeclare::Info declareInfo;
				m_DrawBuff.m_pVertexDeclare	=	GetGlobalSetting().m_pRenderSystem->Create<VertexDeclare*>("asdasdasd","VertexDeclare",&declareInfo);
			}
			//m_RenderB
			return true;
		}

		U1 SoftwareModel::Destroy(){
			SAF_D(m_pAnimation);

			Client::Render::ISystem*	pRenderSys	=	GetGlobalSetting().m_pRenderSystem;
			pRenderSys->DestroyProduct(m_DrawBuff.m_pVertexBuff);
			pRenderSys->DestroyProduct(m_DrawBuff.m_pIndexBuff);
			pRenderSys->DestroyProduct(m_DrawBuff.m_pVertexDeclare);
			return true;
		}

		void SoftwareModel::Render(){
			// get the renderer of the model
			CalRenderer *pCalRenderer;
			pCalRenderer = m_pAnimation->getRenderer();

			// begin the rendering loop
			if(!pCalRenderer->beginRendering()) 
				return;
			//SInt	iCurrentVertexBuffPos	=	0;
			//SInt	iCurrentIndexBuffPos	=	0;

			SInt	iNumMesh	=	pCalRenderer->getMeshCount();
			for(SInt i=0;i<iNumMesh;i++){

				SInt	iNumSubMesh	=	pCalRenderer->getSubmeshCount(i);
				for(SInt	j=0;j<iNumSubMesh;j++){
					//选择子模型
					pCalRenderer->selectMeshSubmesh(i,j);
					//写入缓存
					U8*	pVertexBuff	=	(U8*)m_DrawBuff.m_pVertexBuff->GetData()->GetBuff();
					m_DrawBuff.m_DrawOption.m_uiVertexCount	=	pCalRenderer->getVerticesNormalsAndTexCoords((Real*)pVertexBuff,sizeof(Real)*8);
					U8*	pIndexBuff	=	(U8*)m_DrawBuff.m_pIndexBuff->GetData()->GetBuff();
					m_DrawBuff.m_DrawOption.m_uiFaceCount	=	pCalRenderer->getFaces((U16*)pIndexBuff);
					//提交到GPU
					m_DrawBuff.m_pVertexBuff->UpdataData();
					m_DrawBuff.m_pIndexBuff->UpdataData();

					//m_DrawBuff.m_DrawOption.m_uiBaseVertexIndex	=	iCurrentVertexBuffPos;
					//m_DrawBuff.m_DrawOption.m_uiStartIndex		=	iCurrentIndexBuffPos*3;

					//获取默认材质
					Client::Render::IMaterial*	pMaterial	=	(Client::Render::IMaterial*)GetGlobalSetting().m_pRenderSystem->GetProduct("Default","Material");
					pMaterial->SetParam("WorldViewProjMatrix",&(GetParentSceneNode()->GetGolbalMatrix()*GetGlobalSetting().m_matViewProj));
					pMaterial->Render(m_DrawBuff);

					//iCurrentVertexBuffPos	+=	m_DrawBuff.m_DrawOption.m_uiVertexCount;
					//iCurrentIndexBuffPos	+=	m_DrawBuff.m_DrawOption.m_uiFaceCount;

					
				}
			}


			pCalRenderer->endRendering();
		}

		void SoftwareModel::Updata(){
			m_pAnimation->update(GetGlobalSetting().m_fTimeDelta);
			m_pAnimation->getSkeleton()->calculateBoundingBoxes();
		}
	}

};