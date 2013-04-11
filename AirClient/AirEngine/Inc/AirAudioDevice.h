#ifndef AirAudioDevice_h__
#define AirAudioDevice_h__

#include "AirEngineHeader.h"

namespace	Air{
	namespace	Engine{
		namespace	Audio{
			class ENGINE_EXPORT	Device	:
				public	IProduct
			{
			public:
				static AString	ProductTypeName;
				Device(CAString& strName);


			};
		}
	}
	typedef Engine::Audio::Device		AudioDevice;
	typedef std::vector<AudioDevice*>	AudioDeviceVector;
}
#endif // AirAudioDevice_h__
