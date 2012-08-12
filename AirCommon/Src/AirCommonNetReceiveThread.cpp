#include "WinSock2.h"
#include "AirCommonNetReceiveThread.h"
namespace Air{
	
	namespace	Common{
	
	
		NetReceiveThread::NetReceiveThread(){
			m_pListener	=	NULL;
			m_Socket	=	NULL;
			m_ReceiveSize	=	0;
			ZeroMemory(m_ReceiveBuffer,1024*1024*10);
		}
	
		U1 NetReceiveThread::RepetitionRun(){
			//判断SOCKET 是否有效
			if(m_Socket==NULL){
				Sleep(10);
				return	false;
			}
			U32 iRecvSize	=	0;
			int	iRet	=	recv(m_Socket,&m_ReceiveBuffer[iRecvSize],1024*1024*10,0);
			if(iRet	<=	0){
				//连接关闭
				if(m_pListener!=NULL){
					m_pListener->OnClose(m_Socket);
				}
	
				m_Socket	=	NULL;
			}else{
				m_ReceiveSize	=	*(U32*)m_ReceiveBuffer;
				iRecvSize		+=	iRet;
				while(iRecvSize<m_ReceiveSize+4){
					iRet	=	recv(m_Socket,&m_ReceiveBuffer[iRecvSize],1024*1024*10,0);
					if(iRet	<=	0){
						//连接关闭
						if(m_pListener!=NULL){
							m_pListener->OnClose(m_Socket);
						}
						m_Socket	=	NULL;
						return false;
					}else{
						iRecvSize	+=	iRet;
					}
				}
				//接收数据回调
				if(m_pListener!=NULL){
					m_pListener->OnReceive(m_Socket,&m_ReceiveBuffer[4],m_ReceiveSize);
				}
			}
			return	true;
		}
	
		U1 NetReceiveThread::Start( U32 uiSocket,NetListener* pListener ){
			if(uiSocket	==	0	||
				pListener	==	NULL)
			{
				return	false;
			}
	
			m_Socket			=	uiSocket;
			m_pListener			=	pListener;
	
			if(!IsRunning())
				StartThread();
			return	true;
		}
	}
};