#include "IOCPModel.h"
#include "Server.h"
#include "MNetData.h"

DownloadSClient::DownloadSClient(IOCPServer* pServer,_PER_SOCKET_CONTEXT* pContext)
	:IOCPClient(pServer,pContext)
{
	m_Task.idx		=	0;
	m_Task.iSize	=	0;
	m_Task.offset	=	0;
	m_Task.iSend	=	0;
}
void	DownloadSClient::OnRecvComplated(const void* p,int iSize)
{
	NetHeader* pBase	=	(NetHeader*)p;
	switch(pBase->t){
		case enNT_FS_Hello:{
			NtReturnPackT<NT_SF_Hello>	ntData(enNT_FS_Hello);
			ntData.data.uiClient	=	0;
			ntData.data.uiTaskCount	=	0;
			for(U32 i=0;i<FILEDATA_COUNT;i++){
				ntData.data.pkgSize[i]	=	((DownloadServer*)m_pServer)->GetFileDataSize(i);
			}
			Send((const char*)&ntData,ntData.uiSize+4);
							}break;
		case enNT_FS_LoadFile:{
			NT_Data<FileDataInfo>* pInfo	=	(NT_Data<FileDataInfo>*)p;
				
			if(pInfo->data.uiSize > 0){

				//New Task
				m_Task.idx		=	pInfo->data.idx;
				m_Task.offset	=	pInfo->data.uiOffset;
				m_Task.iSize	=	pInfo->data.uiSize;
				m_Task.iSend	=	0;
				m_Task.t		=	enNT_FS_LoadFile;
				//Send Data
				OnSendComplated(m_pContext->m_pIOContext);
			}

							}break;
	}
}

int		DownloadSClient::pop_front(void* p)
{
	int iTemp	=	__super::pop_front(p);
	if(iTemp>0){
		return iTemp;
	}
	if(m_Task.iSize==0)
		return 0;
	if(m_Task.iSend>=m_Task.iSize){
		return 0;
	}
	unsigned char* pData	=	((DownloadServer*)m_pServer)->GetFileData(m_Task.idx);
	if(pData==NULL){
		return 0;
	}


	NtPack<NT_FS_FileData>*	pSendData	=		new(p) NtPack<NT_FS_FileData>(enNT_SF_FileData);
	pSendData->data.idx			=	m_Task.idx;
	pSendData->data.uiOffset	=	m_Task.iSend;
	pSendData->data.uiSize		=	4096;
	pSendData->data.uiComplated	=	0;
	unsigned int	iLeft	=	m_Task.iSize	-	m_Task.iSend;
	if(iLeft	<	4096){
		m_Task.iSend			=	m_Task.iSize;
		pSendData->data.uiSize		=	iLeft;
		pSendData->data.uiComplated	=	1;
		pSendData->uiSize			+=	(iLeft-4096);

		//Clean Task
		m_Task.iSend	=	0;
		m_Task.iSize	=	0;
		m_Task.idx		=	0;
		//m_Task.offset	=	0;
		m_Task.t		=	enNT_Unknown;
	}else{
		m_Task.iSend	+=	4096;
	}

	memcpy(pSendData->data.data,&pData[m_Task.offset+pSendData->data.uiOffset],pSendData->data.uiSize);

	return pSendData->uiSize+4;
}

DownloadServer::DownloadServer()
{
	for(int i=0;i<FILEDATA_COUNT;i++){
		m_pFileData[i]=0;
		m_PkgSize[i]=0;
	}
}
DownloadServer::~DownloadServer()
{
	for(int i=0;i<16;i++){
		m_pFileData[i]=0;
	}
}

bool	DownloadServer::Initialization(){
	LoadFileData();
	return __super::Initialization();
}
void	DownloadServer::Release(){

	__super::Release();

	for(int i=0;i<FILEDATA_COUNT;i++){
		if(m_pFileData[i]){
			free(m_pFileData[i]);
			m_pFileData[i]=NULL;
		}
	}
}
void	DownloadServer::Update(){
	Sleep(1000);
}

IOCPClient*	DownloadServer::NewIOCPClient(_PER_SOCKET_CONTEXT* pContext){
	IOCPClient* pClient	= new DownloadSClient(this,pContext);
	if(pClient)
		pClient->CreateTempBuffer();
	return pClient;
}
void		DownloadServer::DeleteIOCPClient(IOCPClient* pClient){
	if(pClient!=NULL){
		delete pClient;
	}
}

unsigned char*	DownloadServer::GetFileData(unsigned int idx)
{
	return m_pFileData[idx];
}


void	DownloadServer::LoadFileData(){

	for(U32 i=0;i<FILEDATA_COUNT;i++){
		char strName[MAX_PATH];
		sprintf_s(strName,"Data%d",i);
		HANDLE h = CreateFile(
			strName,
			GENERIC_READ ,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING ,
			0,
			0 );
		if(h!=INVALID_HANDLE_VALUE){
			m_PkgSize[i]	=	GetFileSize(h,0);
			m_pFileData[i]	=	(U8*)malloc(m_PkgSize[i]);
			DWORD	dwRead=0;
			ReadFile(h,m_pFileData[i],m_PkgSize[i],&dwRead,NULL);
			CloseHandle(h);
		}else{
			m_pFileData[i]=NULL;
		}
	}
}

unsigned int DownloadServer::GetFileDataSize( unsigned int idx )
{
	return m_PkgSize[idx];
}
