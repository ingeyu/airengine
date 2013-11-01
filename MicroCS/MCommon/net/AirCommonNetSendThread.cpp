#include "WinSock2.h"
#include "AirCommonNetSendThread.h"
//#include "AirRandom.h"
namespace Air{
	
	
	
	namespace	Common{
	
	
		NetSendThread::NetSendThread(){
			m_pListener	=	NULL;
			m_SendBuffer[0].uiSize	=	0;
			m_SendBuffer[1].uiSize	=	0;
			m_SendBuffer[0].uiSend	=	0;
			m_SendBuffer[1].uiSend	=	0;
			m_uiSocket				=	0;
			//m_Overlapped.hEvent		=	WSACreateEvent();
			//m_Overlapped.
		}
	
		NetSendThread::~NetSendThread(){
	
		}
	
		U1 NetSendThread::Send(const void*	pData,U32	uiSize){
			U8*	pBuffer	=	NULL;
			m_CS.Enter();
			U32	idx	=	(m_SendIndex)&1;

			SendBuffer& buffer = m_SendBuffer[idx];

			U32 uiNew	=	uiSize+4;

			if(buffer.uiSize+uiNew>8192){
				m_CS.Leave();
				return	false;
			}
			
			pBuffer	=	&buffer.Buffer[buffer.uiSize];
			memcpy(pBuffer,&uiSize,sizeof(U32));
			pBuffer+=4;
			memcpy(pBuffer,pData,uiSize);
			buffer.uiSize+=uiNew;

			//WSABUF buf;
			//buf.buf	=	(CHAR*)pBuffer;
			//buf.len	=	buffer.uiSize;
			//DWORD dwSend	=	0;
			//int nRet = WSASend(m_uiSocket,&buf,1,&dwSend,0,&m_Overlapped, NULL);
			//if ((SOCKET_ERROR == nRet) && (WSA_IO_PENDING != WSAGetLastError()))
			//{
			//	m_CS.Leave();
			//	return false;
			//}
			m_CS.Leave();
			return	true;
		}
		U32	NetSendThread::GetSendData(void* p){
			U32 uiSize	=	0;
			m_CS.Enter();
			U32	idx	=	(m_SendIndex+1)&1;
			SendBuffer& buffer = m_SendBuffer[idx];
			uiSize	=	buffer.uiSize;
			if(uiSize	>	0){
				memcpy(p,buffer.Buffer,uiSize);
				m_SendIndex++;
			}
			m_CS.Leave();
			return uiSize;
		}
		U1 NetSendThread::RepetitionRun(){
			//U32 tempSendBuffer[8192];
			//U32	tempSize	=	0;
			//U32	tempSend	=	0;
			//DWORD ret	=	WaitForSingleObject(m_Overlapped.hEvent,0xffffffff);
			//if(ret	==	WAIT_OBJECT_0){
			//	if(tempSize>0)
			//	{
			//		
			//	}
			//}else if(ret	==	WAIT_TIMEOUT){
			//	if(tempSize==0){
			//		tempSize	=	GetSendData(tempSendBuffer);
			//		if(tempSize>0){
			//			WSABUF buf;
			//			buf.buf	=	(CHAR*)tempSendBuffer;
			//			buf.len	=	tempSize;
			//			DWORD dwSend	=	0;
			//			int nRet = WSASend(m_uiSocket,&buf,1,&dwSend,0,&m_Overlapped, NULL);
			//			if ((SOCKET_ERROR == nRet) && (WSA_IO_PENDING != WSAGetLastError()))
			//			{
			//				printf("WSASend Error%d\n",WSAGetLastError());
			//			}
			//		}
			//	}
			//}else{
			//
			//}

			//NetPack*	p	=	NULL;
	
			//m_CS.Enter();
			//if(!m_lstSendPack.empty()){
			//	p	=	m_lstSendPack.front();
			//	m_lstSendPack.pop();
			//}
	
			//m_CS.Leave();
	
			//if(p==NULL){
			//	m_bWaiting	=	true;
			//	//等待1000ms
			//	m_SendEvent.Wait(1000);
			//	m_bWaiting	=	false;
			//}else{
			//	if(p->IsValid()){
			//		int	iRet	=	send(p->uiSocket,p->pData,p->uiSize,0);
			//		if(iRet	<=	0){
			//			//发送失败
			//			if(m_pListener!=NULL)
			//				m_pListener->OnClose(p->uiSocket);
			//		}else{
			//			//OutputDebugStringA("发送成功\n");
			//		}
			//	}
			//	//删除数据
			//	delete	p;
			//}
			//			
	
			return	true;
		}
	
		U1 NetSendThread::Start(U32 uiSocket,NetListener*	pListener){
			m_pListener	=	pListener;
			m_uiSocket	=	uiSocket;
			if(!IsRunning())
				StartThread();
			return	true;
		}
	}
};