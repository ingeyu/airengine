#include "AirInterfaceResourceStream.h"
#include "AirInterfaceResourceSystem.h"

namespace	Air{
	namespace	Engine{
		namespace	Resource{


			IStream::IStream( CAString& strName ):IProduct(strName){
				m_State	=	enSS_UnLoad;
			}

			Air::U1 IStream::Create(){
				ISystem*	pSys	=	static_cast<ISystem*>(m_pFactoryMgr);
				if(pSys==NULL){
					return	false;
				}

				if(!pSys->Find(m_strProductName))
					return	false;

				//进入加载队列
				pSys->LoadBackground(this);

				return	true;
			}

			Air::U1 IStream::Destroy(){
				ForceUnLoad();
				return	true;
			}

			void IStream::PushRecycle(){
				ISystem*	pSys	=	static_cast<ISystem*>(m_pFactoryMgr);
				if(pSys!=NULL){
					pSys->PushRecycle(this);
				}
			}

			void IStream::ForceReLoad(){
				ForceUnLoad();

				ForceLoad();
			}

			Air::U1 IStream::ForceLoad(){
				ISystem*	pSys	=	static_cast<ISystem*>(m_pFactoryMgr);
				if(pSys==NULL)
					return	false;
				m_DataCS.Enter();

				m_Data.Clear();

				m_State	=	enSS_Loading;
				
				//读取数据
				pSys->Find(m_strProductName,m_Data);

				m_State	=	enSS_Loaded;
				m_DataCS.Leave();
				return	true;
			}

			Air::U1 IStream::ForceUnLoad(){
				
				m_DataCS.Enter();

				if(!m_Data.IsNull()){
					m_State	=	enSS_UnLoading;

					m_Data.Clear();

					m_State	=	enSS_Loaded;
				}

				m_DataCS.Leave();
				
				return	true;
			}
		}
	}
}