#include "AirAISystem.h"

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

		Air::U1 System::AddMesh( Engine::MeshEntity* pMeshArray,U32 uiCount )
		{
			if(m_pCurrentDevice!=NULL)
			{
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

		Air::U1 Device::AddMesh( void* pVB, U32 uiVertexCount, void* pIB, U32 uiIndexCount )
		{

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