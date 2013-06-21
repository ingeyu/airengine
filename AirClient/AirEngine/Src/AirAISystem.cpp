#include "AirAISystem.h"
#include "AirMeshEntity.h"
#include "AirRenderbuffer.h"
namespace	Air{
	namespace	AI{


		System::System()
		{
			m_SVO		=	NULL;
			m_uiDepth	=	0;
			m_fSVOScale	=	1.0f;
			m_pCurrentDevice	=	NULL;
			m_pDeviceArray.reserve(4);
		}

		Air::U1 System::Create()
		{
			if(!m_pDeviceArray.empty()){
				m_pCurrentDevice	=	m_pDeviceArray[0];
				m_pCurrentDevice->Create();
			}
			return true;
		}

		Air::U1 System::Destroy()
		{
			if(m_pCurrentDevice){
				m_pCurrentDevice->Destroy();
				m_pCurrentDevice=NULL;
			}
			m_pDeviceArray.clear();
			return true;
		}

		void System::SVOUpdate( U32* svoData,U32 uiDepth,float fScale )
		{
			m_SVO		=	svoData;
			m_uiDepth	=	uiDepth;
			m_fSVOScale	=	fScale;
		}

		U1 System::FindPath( const Float3& vStart,const Float3& vTarget,STD_VECTOR<Float3>* pPath )
		{
			if(m_pCurrentDevice!=NULL)
			{
				return m_pCurrentDevice->PathFind(vStart,vTarget,pPath);
			}

			return false;
		}

		void System::AddDevice( Device* pDevice )
		{
			if(pDevice==NULL)
				return;
			m_pDeviceArray.push_back(pDevice);
		}

		Air::U1 System::AddMesh( Engine::MeshEntity** pMeshArray,U32 uiCount )
		{
			if(m_pCurrentDevice!=NULL)
			{
				STD_VECTOR<Float3>	vecVB;
				vecVB.reserve(10000);

				for(U32 i=0;i<uiCount;i++){
					Float44& matWorld	=	*pMeshArray[i]->GetWorldMatrix();
					Engine::StaticMesh* pMesh	=	pMeshArray[i]->GetMesh();
					U32 uiVertexCount	=	pMesh->GetVertexCount();
					Engine::Render::PNTT* pVB	=	(Engine::Render::PNTT*)pMesh->GetVB();
					for(U32 uiV=0;uiV<uiVertexCount;uiV++){
						vecVB.push_back(matWorld*pVB[uiV].Position);
					}
					U32 uiIndexCount	=	pMesh->GetFaceCount()*3;
					m_pCurrentDevice->AddMesh(&vecVB[0],uiVertexCount,(U32*)pMesh->GetIB(),uiIndexCount);
					vecVB.clear();
				}
				return true;//m_pCurrentDevice->Build();
			}

			return false;
		}

		Air::U1 System::Build()
		{
			if(m_pCurrentDevice!=NULL)
			{
				return m_pCurrentDevice->Build();
			}

			return false;
		}

		AString	Device::ProductTypeName="AIDevice";
		Device::Device( CAString& strName ):Common::IProduct(strName)
		{

		}

		Air::U1 Device::Create()
		{

			return true;
		}

		Air::U1 Device::Destroy()
		{
			return true;
		}

		Air::U1 Device::AddMesh( void* pVB, U32 uiVertexCount, U32* pIB, U32 uiIndexCount ,U32		uiStride)
		{
			U32 uiVertexBase	=	m_vecPosition.size();
			U8*	pVBData	=	(U8*)pVB;
			for(U32 i=0;i<uiVertexCount;i++){
				Float3* pPos	=	(Float3*)pVBData;
				m_vecPosition.push_back(*pPos);
				pVBData+=uiStride;
			}
			for(U32 i=0;i<uiIndexCount;i++){
				m_vecFaceIndex.push_back(pIB[i]+uiVertexBase);
			}

			return false;
		}

		Air::U1 Device::Build()
		{
			return false;
		}

		Air::U1 Device::PathFind( const Float3& vStart,const Float3& vTarget,STD_VECTOR<Float3>* pPath /*= NULL*/ )
		{
			return false;
		}

	}
}