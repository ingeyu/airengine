#include "WinSock2.h"
#include "AirCommonNetClient.h"


namespace Air{
	
	namespace	Common{
	
		AString	NetClient::ProductTypeName="NetClient";
		NetClient::NetClient( CAString& strName,Info* pInfo )
			:IProduct(strName){
			if(pInfo!=NULL)
				m_Info	=	*pInfo;
			m_pListener	=	m_Info.pListener;
		}
	
		U1 NetClient::Create(){
			return	true;
		}
	
		U1 NetClient::Destroy(){
			if(IsConnected())
				DisConnect();
			return	true;
		}
	
		U1 NetClient::OnConnected( U32 socket,CAString& strIP,CAString& strPort ){
			if(socket	==	NULL){
				return	false;
			}
			//启动发送线程
			m_ThreadSend.Start(this);
			//启动接收线程
			m_ThreadReceive.Start(socket,this);
	
			return	NetConnect::OnConnected(socket,strIP,strPort);
		}
	
		U1 NetClient::OnClose( U32 uiSocket ){
			//停止发送线程
			m_ThreadSend.StopThreadWaitForExit();
			//摧毁SOCKET
			DestroySocket();
			//停止接收线程
			m_ThreadReceive.StopThread();
	
			
			return	NetConnect::OnClose(uiSocket);
		}
	
		U1 NetClient::OnReceive( U32 uiSocket,AChar* pData,U32 uiSize ){
			return	NetConnect::OnReceive(uiSocket,pData,uiSize);
		}
	
		U1 NetClient::IsConnected(){
			return	m_Socket!=NULL;
		}
	
		U1 NetClient::Connect( Info& info ){
			//如果已经连接	断开前面的链接
			if(IsConnected()){
				DisConnect();
			}
			m_Info	=	info;
	
			CreateSocket();
	
			U16	PORT	=	(info.usPort);
	
			sockaddr_in servAddr; 
			servAddr.sin_family = AF_INET; 
			servAddr.sin_port = htons(PORT); 
			servAddr.sin_addr.S_un.S_addr = ::inet_addr(info.strIP.c_str()); 
			if (INVALID_SOCKET == (::connect(m_Socket, (sockaddr*)&servAddr, sizeof(sockaddr_in)))) 
			{ 
				OutputDebugStringA("连接服务器失败\n"); 
				DestroySocket();
				return	false;
			} 
			char strport[32];
			itoa(m_Info.usPort,strport,10);
			OnConnected(m_Socket,info.strIP,strport);
			
			return	true;
		}
	
		U1 NetClient::DisConnect(){
			//判断当前状态
			if(!IsConnected())
				return	false;
			//停止发送线程
			m_ThreadSend.StopThreadWaitForExit();
			//摧毁SOCKET	//接收线程会自动关闭
			DestroySocket();
	
			//等待接收线程关闭
			m_ThreadReceive.StopThreadWaitForExit();
			return	true;
		}
	}
};