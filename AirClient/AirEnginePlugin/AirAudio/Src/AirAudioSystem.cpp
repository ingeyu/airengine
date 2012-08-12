#include "AirAudioSystem.h"
#include "AirAudioGlobal.h"

#include "AirAudioBuffer.h"
#include "AirAudioOggBuffer.h"
#include "AirAudioScene.h"
namespace Air{
	
	namespace	Client{
		namespace	Audio{
	
	
			System::System():ISystem("AudioSystem"){
				m_strName		=	"OpenAL	AudioSystem";
				m_pContext		=	NULL;
				m_pDevice		=	NULL;
				GetGlobalSetting().m_pAudioSystem	=	this;
			}
	
			U1 System::Initialization(){
				//initialize OpenAL
				//Open device
				m_pDevice = alcOpenDevice((const ALCchar*)"DirectSound3D");
	
				if (m_pDevice == NULL)	{
					//we failed to initialize the device
					MessageBoxA(0,"³õÊ¼»¯OpenalÊ§°Ü","Error",0);
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
	
				AddFactory(new	BufferFactory());
				//AddFactory(new	OggBufferFactory());
				
				return		true;
			}
	
			U1 System::Start(){
	
				return		true;
			}

			U1 System::Stop(){

				return		true;
			}
	
			U1 System::Release(){
				GetGlobal().m_pContext	=	NULL;
				GetGlobal().m_pDevice	=	NULL;
	
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
	
			U1 System::Updata(){
	
				return		true;
			}
	
			IScene* System::CreateScene( AString strName ){
				if(strName.empty())
					return	NULL;
				IScene*	pScene	=	new	Scene(strName);
				pScene->Initialization();
				return pScene;
			}
	
			void System::DestroyScene( IScene* pScene ){
				if(pScene!=NULL)
					pScene->Release();
				delete	pScene;
			}
	
			System::~System(){
				GetGlobalSetting().m_pAudioSystem	=	NULL;
			}
		}
	}
};