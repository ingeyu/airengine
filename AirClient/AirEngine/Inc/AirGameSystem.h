#ifndef AirGameSystem_h__
#define AirGameSystem_h__

#include "AirEngineHeader.h"

namespace	Air{
	namespace	Game{
		class	System	:	
			public	IFactoryManager,
			public	Singleton<System>
		{
		public:
			System();


			virtual	U1	Initialization();
			virtual	U1	Release();


		};
	}
	typedef	Game::System	GameSystem;
}
#endif // AirGameSystem_h__
