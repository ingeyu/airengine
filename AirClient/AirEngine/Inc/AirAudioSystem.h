#ifndef INTERFACEAUDIOSYSTEM_HEAD_FILE
#define INTERFACEAUDIOSYSTEM_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirAudioBuffer.h"
#include "AirAudioSound.h"
#include "AirAudioDevice.h"

namespace Air{
	
	namespace Engine{
		
		namespace	Audio{
			class	Sound;
			class	ENGINE_EXPORT	System	:
				public	Common::IFactoryManager,
				public	Singleton<System>{
			public:
				System();
	
				U1	Initialization();
				U1	Release();

				Device*	GetDevice();
				//Device Select
				void	AddDevice(Device*	pDevice);
				U32		GetDeviceCount();
				AString	GetDeviceName(U32 uiIndex);
				void	SelectDevice(U32 uiIndex);
			protected:
				AudioDeviceVector	m_vecDevice;
				Device*				m_pDevice;
			};
		}
	
	};
	typedef Engine::Audio::System	AudioSystem;
};
#endif // INTERFACEAUDIOSYSTEM_HEAD_FILE