#include "AirAudioSound.h"

namespace	Air{
	namespace	Engine{
		namespace	Audio{

			AString	Sound::ProductTypeName	=	"Sound";
			Sound::Sound( CAString& strName,Info* pInfo ):MovableObject(strName)
			{
				if(pInfo!=NULL){
					m_Info	=	*pInfo;
				}
				m_State		=	enUnknown;
			}

			void Sound::Play()
			{
				m_State	=	enPlaying;
			}

			void Sound::Pause()
			{
				m_State	=	enPause;
			}

			void Sound::Stop()
			{
				m_State	=	enInit;
			}

			void Sound::RePlay()
			{
				m_State	=	enPlaying;
			}

			void Sound::Update()
			{

			}

			void Sound::SetVolume( float fVolume )
			{
				m_Info.fVolume	=	fVolume;
			}

			float Sound::GetVolume() const
			{
				return m_Info.fVolume;
			}

			void Sound::SetPitch( float fPitch )
			{
				m_Info.fPitch	=	fPitch;
			}

			float Sound::GetPitch() const
			{
				return m_Info.fPitch;
			}

		}
	}
}