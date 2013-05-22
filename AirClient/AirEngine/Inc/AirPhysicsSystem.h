#ifndef AirPhysicsSystem_h__
#define AirPhysicsSystem_h__

#include "AirEngineHeader.h"

namespace	Air{
	namespace	Physics{
		class	SVO;
		class	ENGINE_EXPORT	System :	
			public	Common::IFactoryManager,
			public	Singleton<System>
		{
		public:
			System();

			virtual	U1		Initialization();
			virtual	U1		Release();
			
			void			Update(const FrameTime& frameTime);
			void			UpdateSVO(const STD_VECTOR<U32>& svoData,U32 uiDepth,float fScale);
			U1				CollisionDetect(const Float3& p,Float3& v);
		public:
			SVO*			m_pSVO;
		};
	}
	typedef	Physics::System	PhysicsSystem;
}
#endif // AirPhysicsSystem_h__
