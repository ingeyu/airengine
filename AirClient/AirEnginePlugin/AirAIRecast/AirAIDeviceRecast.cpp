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


		Air::U1 DeviceRecast::Build()
		{
			if(m_pInputGeom==NULL){
				m_pInputGeom	=	new InputGeom();
			}

			m_pInputGeom->loadMesh((float*)&m_vecPosition[0],m_vecPosition.size(),&m_vecFaceIndex[0],m_vecFaceIndex.size()/3);

			BuildContext ctx;
			m_pSample->setContext(&ctx);
			m_pSample->handleMeshChanged(m_pInputGeom);
			m_pSample->handleSettings();
			m_pSample->handleBuild();
			m_vecPosition.clear();
			m_vecFaceIndex.clear();
			return true;
		}

	}
}