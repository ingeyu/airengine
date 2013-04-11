#include "AirAudioALDevice.h"
#include "AirAudioGlobal.h"
#include "AirAudioOggBuffer.h"
#include "AirAudioALSound.h"
namespace Air{
	
	namespace	Engine{
		namespace	Audio{
	
	
			ALDevice::ALDevice(CAString& strName):Device("OpenAL Device"){
				m_pContext		=	NULL;
				m_pDevice		=	NULL;
			}
	
			U1 ALDevice::Create(){
				//initialize OpenAL
				//Open device
				m_pDevice = alcOpenDevice((const ALCchar*)"DirectSound3D");
	
				if (m_pDevice == NULL)	{
					//we failed to initialize the device
					OutputDebugStringA("³õÊ¼»¯OpenALÊ§°Ü\n");
					return false;
				}
				//Create context(s)
				m_pContext=alcCreateContext(m_pDevice,NULL);
				//Set active context
				alcMakeContextCurrent(m_pContext);
				// Clear Error Code
				alGetError();
	
				GetGlobal().m_pContext	=	m_pContext;
				GetGlobal().m_pDevice	=	m_pDevice;
	
				AudioSystem::GetSingleton()->AddFactory(new	ParamFactory<ALSound>());
				//AddFactory(new	OggBufferFactory());
				
				return		true;
			}

	
			U1 ALDevice::Destroy(){
				AudioSystem::GetSingleton()->RemoveFactory(ALSound::ProductTypeName);
				//Get active context
				m_pContext=alcGetCurrentContext();
				//Get device for active context
				m_pDevice=alcGetContextsDevice(m_pContext);
				//Disable context
				alcMakeContextCurrent(NULL);
				//Release context(s)
				alcDestroyContext(m_pContext);
				m_pContext	=	NULL;
				//Close device
				alcCloseDevice(m_pDevice);
				m_pDevice	=	NULL;
				return		true;
			}
	
			U1 ALDevice::Update(){
	
				return		true;
			}
		}
	}
};