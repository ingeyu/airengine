#ifndef AUDIOSYSTEM_HEAD_FILE
#define AUDIOSYSTEM_HEAD_FILE

#include "AirAudioHeader.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Audio{
			class	System	:
				public	ISystem{
			public:
	
				System();
				virtual	~System();
	
				virtual	U1	Initialization();
				virtual	U1	Start();
				virtual U1  Stop();
				virtual	U1	Release();
				
				virtual	U1	Updata();
	
				virtual	IScene*	CreateScene(AString	strName);
				virtual	void	DestroyScene(IScene*	pScene);
			protected:
				AContext*	m_pContext;
				ADevice*	m_pDevice;
			};
		}
	
	};
};
#endif // AUDIOSYSTEM_HEAD_FILE