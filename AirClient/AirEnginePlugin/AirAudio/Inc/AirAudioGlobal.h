#ifndef AUDIOGLOBAL_HEAD_FILE
#define AUDIOGLOBAL_HEAD_FILE

#include "AirAudioHeader.h"

namespace Air{
	
	namespace Engine{
	
		namespace	Audio{
			class	Global{
			public:
				Global();
				AContext*	m_pContext;
				ADevice*	m_pDevice;
			};
	
			Global&	GetGlobal();
		}
	
	};
};
#endif // AUDIOGLOBAL_HEAD_FILE