#include "AirAudioSystem.h"
#include "AirAudioBuffer.h"

namespace	Air{
	namespace	Engine{
		namespace	Audio{


			System::System()
			{
				m_pDevice	=	NULL;
			}

			Air::U1 System::Initialization()
			{
				AddFactory(new NoParamFactory<Buffer>());

				if(m_pDevice!=NULL){
					m_pDevice->Create();
				}
				return true;
			}

			Air::U1 System::Release()
			{
				DestroyAllProduct();
				if(m_pDevice!=NULL){
					m_pDevice->Destroy();
				}
				m_pDevice	=	NULL;
				return true;
			}

			void System::AddDevice( Device* pDevice )
			{
				m_vecDevice.push_back(pDevice);
				if(m_pDevice==NULL	&&	!m_vecDevice.empty()){
					m_pDevice	=	m_vecDevice[0];
				}
			}

			Air::U32 System::GetDeviceCount()
			{
				return m_vecDevice.size();
			}

			Device* System::GetDevice()
			{
				return m_pDevice;
			}

			Air::AString System::GetDeviceName(U32 uiIndex)
			{
				return m_vecDevice[uiIndex]->GetProductName();
			}

			void System::SelectDevice( U32 uiIndex )
			{
				if(m_pDevice==NULL	&&	!m_vecDevice.empty()){
					m_pDevice	=	m_vecDevice[0];
				}
			}

		}
	}
}