#ifndef AirAIDeviceRecast_h__
#define AirAIDeviceRecast_h__

#include "AirAISystem.h"
class	InputGeom;
class	Sample_TileMesh;
class	NavMeshTesterTool;

namespace	Air{
	namespace	AI{
		struct	PlayerInfo{
			float				m_fHeight;
			float				m_fRadius;
			float				m_fMaxClimb;
			float				m_fMaxSlope;
		};
		struct Setting{
			PlayerInfo	player;
			float		vertexPerPoly;
			float		regionMinSize;
		};
		class	DeviceRecast	:	public	Device
		{
		public:
			DeviceRecast();

			virtual	U1	Create();
			virtual	U1	Destroy();
			virtual	U1	AddMesh( void* pVB, U32 uiVertexCount, void* pIB, U32 uiIndexCount );

			InputGeom*			m_pInputGeom;
			Sample_TileMesh*	m_pSample;
			NavMeshTesterTool*	m_pTestTool;

			Setting				m_Setting;
		};
	}
}
#endif // AirAIDeviceRecast_h__
