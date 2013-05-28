#include "AirAIDeviceRecast.h"
#include "Sample_TileMesh.h"
#include "InputGeom.h"
#include "NavMeshTesterTool.h"
namespace	Air{
	namespace	AI{


		DeviceRecast::DeviceRecast():Device("DeviceRecast")
		{
			m_pInputGeom  =	NULL;
			m_pSample	  =	NULL;
			m_pTestTool	  =	NULL;
		}

		Air::U1 DeviceRecast::Create()
		{
			m_pSample	=	new	Sample_TileMesh();
			m_pTestTool	=	new NavMeshTesterTool();
			return true;
		}

		Air::U1 DeviceRecast::Destroy()
		{
			SAFE_DELETE(m_pSample);
			SAFE_DELETE(m_pTestTool);
			return true;
		}

		Air::U1 DeviceRecast::AddMesh( void* pVB, U32 uiVertexCount, void* pIB, U32 uiIndexCount )
		{
			if(m_pInputGeom==NULL){
				m_pInputGeom	=	new InputGeom();
			}

			rcMeshLoaderObj* pMesh	=	(rcMeshLoaderObj*)m_pInputGeom->getMesh();
			if(pMesh==NULL){
				//pMesh	=	m_pInputGeom->createMesh();
			}
			return false;
		}

	}
}