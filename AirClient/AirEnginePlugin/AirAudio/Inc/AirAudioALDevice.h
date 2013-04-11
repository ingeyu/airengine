#ifndef AUDIOSYSTEM_HEAD_FILE
#define AUDIOSYSTEM_HEAD_FILE

#include "AirAudioHeader.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Audio{
			class	ALDevice	:
				public	Device{
			public:
	
				ALDevice(CAString& strName);

	
				virtual	U1	Create();
				virtual	U1	Destroy();
				
				virtual	U1	Update();

			protected:
				AContext*	m_pContext;
				ADevice*	m_pDevice;
			};
		}
	
	};
};
#endif // AUDIOSYSTEM_HEAD_FILE