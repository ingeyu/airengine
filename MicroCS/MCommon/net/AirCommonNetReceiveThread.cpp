#include "WinSock2.h"
#include "AirCommonNetReceiveThread.h"
namespace Air{
	
	namespace	Common{
	
	
		NetReceiveThread::NetReceiveThread(){
			m_pListener	=	NULL;
			m_Socket	=	NULL;
			m_ReceiveSize	=	0;
			ZeroMemory(m_ReceiveBuffer,DEFAULT_RECEIVE_SIZE);
		}
	
		U1 NetReceiveThread::RepetitionRun(){
			//判断SOCKET 是否有效
			if(m_Socket==NULL){
				Sleep(10);
				return	false;
			}
			U32 iRecvSize	=	0;
			int	iRet	=	recv(m_Socket,&m_ReceiveBuffer[m_ReceiveSize],DEFAULT_RECEIVE_SIZE-m_ReceiveSize,0);
			if(iRet	<=	0){
				//连接关闭
				if(m_pListener!=NULL){
					m_pListener->OnClose(m_Socket);
				}
	
				m_Socket	=	NULL;
			}else{
				m_ReceiveSize	+=	iRet;

				S32 uiOffset	=	0;
				U1	bBusy	=	m_ReceiveSize	>	DEFAULT_RECEIVE_SIZE/2;
				if(bBusy){
					OutputDebugStringA("Recv Busy!\n");
				}
				while(true){
					if(m_ReceiveSize<uiOffset+4){
						S32 uiLeftSize	=	m_ReceiveSize	-	uiOffset;
						if(uiLeftSize	>0){
							memcpy(m_ReceiveBuffer,&m_ReceiveBuffer[uiOffset],uiLeftSize);
							m_ReceiveSize	=	uiLeftSize;
						}else{
							m_ReceiveSize=0;
						}
						
						return false;
					}
					S32 uiPackageSize		=	*(U32*)&m_ReceiveBuffer[uiOffset];
					S32	uiNextPackageOffset	=	uiOffset	+uiPackageSize+4;
					if(m_ReceiveSize	<	uiNextPackageOffset){
						S32	uiLeftSize	=	m_ReceiveSize	-	uiOffset;
						if(uiLeftSize>0){
							memcpy(m_ReceiveBuffer,&m_ReceiveBuffer[uiOffset],uiLeftSize);
							m_ReceiveSize	=	uiLeftSize;
						}else{
							m_ReceiveSize	=	0;
						}
						return false;
					}
					//接收数据回调
					if(m_pListener!=NULL){
						m_pListener->OnReceive(m_Socket,&m_ReceiveBuffer[uiOffset+4],uiPackageSize);
					}
					uiOffset=uiNextPackageOffset;
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