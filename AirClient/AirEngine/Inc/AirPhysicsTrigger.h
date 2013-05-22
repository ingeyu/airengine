#ifndef AirPhysicsTrigger_h__
#define AirPhysicsTrigger_h__

#include "AirEngineHeader.h"
#include "AirPhysicsShape.h"

namespace	Air{
	namespace	Physics{
		class	ENGINE_EXPORT	Trigger	:	public	Common::IProduct
		{
		public:
			Trigger(CAString& strName,Info* pInfo);
			virtual	U1	Create();
			virtual	U1	Destroy();
		};
	}
}
#endif // AirPhysicsTrigger_h__
