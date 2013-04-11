#include "AirResourceStream.h"
#include "AirResourceSystem.h"

namespace	Air{
	namespace	Engine{
		namespace	Resource{

			AString Stream::ProductTypeName=	"Stream";
			Stream::Stream( CAString& strName ):IProduct(strName){
				m_State	=	enSS_UnLoad;
			}

			Air::U1 Stream::Create(){

				if(!ResourceSystem::GetSingleton()->Find(m_strProductName))
					return	false;

				//进入加载队列
				ResourceSystem::GetSingleton()->LoadBackground(this);

				return	true;
			}

			Air::U1 Stream::Destroy(){
				ForceUnLoad();
				return	true;
			}

			void Stream::PushRecycle(){

				ResourceSystem::GetSingleton()->PushRecycle(this);
				
			}

			void Stream::ForceReLoad(){
				ForceUnLoad();

				ForceLoad();
			}

			Air::U1 Stream::ForceLoad(){

				m_DataCS.Enter();

				m_Data.Clear();

				m_State	=	enSS_Loading;
				
				//读取数据
				ResourceSystem::GetSingleton()->Find(m_strProductName,m_Data);

				m_State	=	enSS_Loaded;
				m_DataCS.Leave();
				return	true;
			}

			Air::U1 Stream::ForceUnLoad(){
				
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