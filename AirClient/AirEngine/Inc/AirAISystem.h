#ifndef AirAISystem_h__
#define AirAISystem_h__

#include "AirEngineHeader.h"

namespace	Air{
	namespace	Engine{
		class	MeshEntity;
	};
	namespace	AI{
		class	ENGINE_EXPORT	Device	:public	Common::IProduct{
		public:
			static	AString	ProductTypeName;
			Device(CAString& strName);

			virtual	U1	Create();
			virtual	U1	Destroy();

			virtual	U1	AddMesh(
				void*	pVB,
				U32		uiVertexCount,
				U32*	pIB,
				U32		uiIndexCount,
				U32		uiStride	=	sizeof(Float3));
			virtual	U1	Build();
			virtual	U1	PathFind(const Float3& vStart,const Float3& vTarget,STD_VECTOR<Float3>* pPath	=	NULL);
		protected:
			STD_VECTOR<Float3>	m_vecPosition;
			STD_VECTOR<U32>		m_vecFaceIndex;
		};
		class	ENGINE_EXPORT	System	:	
			public	Common::IFactoryManager,
			public	Singleton<System>
		{
		public:
			System();

			
			virtual	U1	Create();
			virtual	U1	Destroy();

			void		AddDevice(Device* pDevice);
			U1			AddMesh(Engine::MeshEntity** pMeshArray,U32 uiCount);
			U1			Build();

			void		SVOUpdate(U32* svoData,U32 uiDepth,float fScale);
			U1			FindPath(const Float3& vStart,const Float3& vTarget,STD_VECTOR<Float3>* pPath	=	NULL);
		protected:
			U32*				m_SVO;
			U32					m_uiDepth;
			float				m_fSVOScale;
			STD_VECTOR<Device*>	m_pDeviceArray;
			Device*				m_pCurrentDevice;
		};
	}
}
#endif // AirAISystem_h__
