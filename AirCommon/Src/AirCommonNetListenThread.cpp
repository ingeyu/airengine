#include "WinSock2.h"
#include "AirCommonNetListenThread.h"
#include "AirCommonConverter.h"

namespace Air{
	
	
	namespace	Common{
	
	
		NetListenThread::NetListenThread(){
			m_Socket	=	0;
			m_pListener	=	NULL;
		}
	
		U1 NetListenThread::RepetitionRun(){
			if(m_Socket==0)
			{
				Sleep(10);
				return	false;
			}
			sockaddr_in saddr_client;
			int	iLength	=	sizeof(sockaddr_in);
	
			SOCKET	socket	=	accept(m_Socket, (sockaddr*)&saddr_client,&iLength);
			if(	socket	!=	INVALID_SOCKET	&&
				socket	!=	NULL)
			{
				//有客户端连入
				if(m_pListener!=NULL){
					
					m_pListener->OnConnected(socket,IP2String(saddr_client.sin_addr.S_un.S_addr),Converter::ToString(saddr_client.sin_port));
				}
			}
	
			return	true;
		}
	
		U1 NetListenThread::Start( U32 uiSocket,NetListener* pListener ){
			if(uiSocket	==	0	||
				pListener	==	NULL)
			{
				return	false;
			}
	
			m_Socket		=	uiSocket;
			m_pListener		=	pListener;
	
			if(!IsRunning())
				StartThread();
			return	true;
		}
	}
};