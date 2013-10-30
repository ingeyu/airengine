// MServer.cpp : 定义控制台应用程序的入口点。
//


#include "IOCPModel.h"
#include "MCommon.h"
#include "IOCPServer.h"
#include "MNetData.h"

IOCPClient::IOCPClient(IOCPServer* pServer,_PER_SOCKET_CONTEXT* pContext){
	m_pServer		=	pServer;
	m_pContext		=	pContext;
	m_TempSize		=	0;
	m_TempBuffer	=	NULL;
	InitializeCriticalSection(&m_CriticalSection);
}
IOCPClient::~IOCPClient(){
	DestroyTempBuffer();
	DeleteCriticalSection(&m_CriticalSection);
}

bool	IOCPClient::Send(const void* pData,int uiSize){
	bool bRet	=	false;
	EnterCriticalSection(&m_CriticalSection);
	bRet	=	push_back(pData,uiSize);
	LeaveCriticalSection(&m_CriticalSection);
	return bRet;
}
void	IOCPClient::OnRecvComplated(const void* p,int iSize){

}
void	IOCPClient::OnSendComplated(_PER_IO_CONTEXT* pIO){
	EnterCriticalSection(&m_CriticalSection);
	pIO->m_uiTotalSize	=	pop_front(pIO->m_szBuffer);
	if(pIO->m_uiTotalSize!=0){
		//_PostSend
		pIO->m_wsaBuf.len	=	pIO->m_uiTotalSize;
		m_pServer->m_pIOCP->_PostSend(pIO);
	}
	LeaveCriticalSection(&m_CriticalSection);
}
bool	IOCPClient::push_back(const void* p,int uiSize){
	_PER_IO_CONTEXT* pIO	=	m_pContext->m_pIOContext;
	if(pIO->m_uiTotalSize==0){
		memcpy(pIO->m_szBuffer,p,uiSize);
		pIO->m_uiTotalSize	=	uiSize;
		pIO->m_wsaBuf.len	=	uiSize;
		//_PostSend
		m_pServer->m_pIOCP->_PostSend(pIO);
	}else{
		if(m_TempBuffer==NULL){
			return false;
		}
		//Push Temp Buffer
		if(uiSize+m_TempSize<TEMP_BUFFER_SIZE){
			memcpy(m_TempBuffer,p,uiSize);
			m_TempSize+=uiSize;
		}else{
			return false;
		}
	}
	return true;
}
int		IOCPClient::pop_front(void* p){
	int iSize	=	m_TempSize;
	//Get Temp Buffer
	if(iSize>0){
		memcpy(p,m_TempBuffer,iSize);
		m_TempSize=0;
	}
	return iSize;
}

void	IOCPClient::CreateTempBuffer(){
	if(m_TempBuffer==NULL){
		m_TempBuffer	=	(unsigned char*)malloc(TEMP_BUFFER_SIZE);
	}
}
void	IOCPClient:: DestroyTempBuffer(){
	if(m_TempBuffer!=NULL){
		free(m_TempBuffer);
		m_TempBuffer=NULL;
	}
}

int uiTotalByte=0;




IOCPServer::IOCPServer(){
	//m_uiTaskCount	=	0;
	//m_uiClientCount	=	0;
	//for(int i=0;i<FILEDATA_COUNT;i++)
	//	m_DataArray[i]=NULL;
	m_pIOCP	=	NULL;
};
IOCPServer::~IOCPServer()
{

}
bool		IOCPServer::Initialization(){

		
	//LoadFileData();
	if(m_pIOCP==NULL){
		m_pIOCP	=	new CIOCPModel();
		m_pIOCP->SetListener(this);
		m_pIOCP->LoadSocketLib();
		m_pIOCP->SetPort(54322);
		m_pIOCP->Start();
	}

	return true;
};
void		IOCPServer::Release(){
	if(m_pIOCP!=NULL){
		m_pIOCP->Stop();

		m_pIOCP->UnloadSocketLib();
		delete m_pIOCP;
		m_pIOCP=NULL;
	}

	//m_lstFileDataInfo.clear();

	//for(U32 i=0;i<FILEDATA_COUNT;i++){
	//	free(m_DataArray[i]);
	//	m_DataArray[i]=NULL;
	//}
};
void		IOCPServer::Update(){
	//m_Event.Wait(100);

	//FileDataInfo info;
	//m_CS.Enter();
	//if(!m_lstFileDataInfo.empty()){
	//	info	=	*m_lstFileDataInfo.begin();
	//	m_lstFileDataInfo.pop_front();
	//	//m_uiTaskCount--;
	//}else{
	//	m_CS.Leave();
	//	return;
	//}
	//m_CS.Leave();


	//
	//U32	uiOffset	=	info.uiOffset;
	//U32	idx			=	info.idx;
	////printf(_T("File idx=%d offset=%d size=%d \n"),idx,uiOffset,info.uiSize);

	//uiTotalByte+=info.uiSize;
	//if((m_uiTaskCount&0xff)==0){
	//	printf("Total Data Byte(KB) %d\n",uiTotalByte>>10);
	//}

	//if(m_DataArray[idx]!=NULL){

	//	U32	uiSendCount	=	(info.uiSize+4095)/4096;
	//	U32	uiSendByte	=	0;
	//	for(U32	i=0;i<uiSendCount;i++){
	//		U8*	pData	=	m_DataArray[idx];
	//		NtPack<NT_FS_FileData>	ntData(enNT_SF_FileData);
	//		ntData.data.idx			=	idx;
	//		ntData.data.uiOffset	=	4096*i;
	//		ntData.data.uiSize		=	4096;
	//		ntData.data.uiComplated	=	0;
	//		U32	uiSendSize	=	4096;
	//		if(i==uiSendCount-1){
	//			ntData.data.uiComplated	=	1;
	//			uiSendSize	=	info.uiSize%4096;
	//			if(uiSendSize==0)
	//				uiSendSize	=	4096;
	//			ntData.data.uiSize		=	uiSendSize;
	//			ntData.uiSize			+=	(uiSendSize-4096);
	//		}
	//		memcpy(ntData.data.data,&pData[uiOffset+ntData.data.uiOffset],uiSendSize);

	//		uiSendByte	+=	send(info.uiSocket,(const char*)&ntData,ntData.uiSize+4,0);
	//	}
	//}

		
}

void	IOCPServer::OnConnected(_PER_SOCKET_CONTEXT* pSocketContext){

	pSocketContext->m_pClient	=	NewIOCPClient(pSocketContext);

	//InterlockedIncrement((LONG*)&m_uiClientCount);
	unsigned __int64 s = pSocketContext->m_Socket;
	printf(_T("Client %lld %s:%d Connected!\n"),s,inet_ntoa(pSocketContext->m_ClientAddr.sin_addr),ntohs(pSocketContext->m_ClientAddr.sin_port));
};
void	IOCPServer::OnRecvComplated(_PER_SOCKET_CONTEXT* pSocketContext,_PER_IO_CONTEXT* pIOContext){
	U64	uiSocket	=	pSocketContext->m_Socket;
	void*	pData	=	pIOContext->m_szBuffer;
	int		iSize	=	pIOContext->m_uiTotalSize;
	IOCPClient*	pClient	=	(IOCPClient*)pSocketContext->m_pClient;
	if(pClient!=NULL){
		pClient->OnRecvComplated(pData,iSize);
	}


};
void	IOCPServer::OnSendComplated(_PER_SOCKET_CONTEXT* pSocketContext,_PER_IO_CONTEXT* pIOContext){
	IOCPClient*	pClient	=	pSocketContext->m_pClient;
	if(pClient!=NULL){
		pClient->OnSendComplated(pIOContext);
	}
};
void	IOCPServer::OnClosed(_PER_SOCKET_CONTEXT* pSocketContext){
	DeleteIOCPClient(pSocketContext->m_pClient);
	pSocketContext->m_pClient=NULL;
	

	//InterlockedDecrement((LONG*)&m_uiClientCount);
	unsigned __int64 s = pSocketContext->m_Socket;
	printf(_T("Client %lld %s:%d DisConnected!\n"),s,inet_ntoa(pSocketContext->m_ClientAddr.sin_addr),ntohs(pSocketContext->m_ClientAddr.sin_port));
};

IOCPClient*	IOCPServer::NewIOCPClient(_PER_SOCKET_CONTEXT* pContext)
{
	IOCPClient*	pClient	=	new	IOCPClient(this,pContext);
	pClient->CreateTempBuffer();
	return pClient;
}

void		IOCPServer::DeleteIOCPClient(IOCPClient* pClient){
	if(pClient!=NULL){
		delete pClient;
	}
}

void			Send(PER_SOCKET_CONTEXT* pSocketContext,const void* pData,U32 uiSize){
	
}

//void	LoadFileData(){

//	for(U32 i=0;i<FILEDATA_COUNT;i++){
//		char strName[MAX_PATH];
//		sprintf_s(strName,"Data%d",i);
//		HANDLE h = CreateFile(
//			strName,
//			GENERIC_READ ,
//			FILE_SHARE_READ|FILE_SHARE_WRITE,
//			NULL,
//			OPEN_EXISTING ,
//			0,
//			0 );
//		if(h!=INVALID_HANDLE_VALUE){
//			U32 uiSize	=	GetFileSize(h,0);
//			m_DataArray[i]	=	(U8*)malloc(uiSize);
//			DWORD	dwRead=0;
//			ReadFile(h,m_DataArray[i],uiSize,&dwRead,NULL);
//			CloseHandle(h);
//		}else{
//			m_DataArray[i]=NULL;
//		}
//	}
//}

//protected:
//	int								m_uiClientCount;
//	int								m_uiTaskCount;
//	Air::Common::CriticalSection	m_CS;
//	Air::Common::Event				m_Event;
//	STD_LIST<FileDataInfo>			m_lstFileDataInfo;
//	U8*								m_DataArray[FILEDATA_COUNT];
//	CIOCPModel						iocp;
//};


