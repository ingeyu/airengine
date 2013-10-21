// MServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "IOCPModel.h"
#include "MCommon.h"
#include "AirCommonLock.h"
#include "MNetData.h"




class FileServer	:	public	IOCPListener{
public:
	FileServer(){
		m_uiTaskCount	=	0;
		m_uiClientCount	=	0;
		for(U32 i=0;i<FILEDATA_COUNT;i++)
			m_DataArray[i]=NULL;
	};

	void		Initialization(){

		
		LoadFileData();
		iocp.SetListener(this);
		iocp.LoadSocketLib();
		iocp.SetPort(54322);
		iocp.Start();
	};
	void		Release(){

		iocp.Stop();

		iocp.UnloadSocketLib();

		m_lstFileDataInfo.clear();

		for(U32 i=0;i<FILEDATA_COUNT;i++){
			free(m_DataArray[i]);
			m_DataArray[i]=NULL;
		}
	};
	void		Update(){
		m_Event.Wait(100);

		FileDataInfo info;
		m_CS.Enter();
		if(!m_lstFileDataInfo.empty()){
			info	=	*m_lstFileDataInfo.begin();
			m_lstFileDataInfo.pop_front();
			//m_uiTaskCount--;
		}else{
			m_CS.Leave();
			return;
		}
		m_CS.Leave();


		
		U32	uiOffset	=	info.uiOffset;
		U32	idx			=	info.idx;
		//printf(_T("File idx=%d offset=%d size=%d \n"),idx,uiOffset,info.uiSize);
		if(m_DataArray[idx]!=NULL){

			U32	uiSendCount	=	(info.uiSize+4095)/4096;
			U32	uiSendByte	=	0;
			for(U32	i=0;i<uiSendCount;i++){
				U8*	pData	=	m_DataArray[idx];
				NtPack<NT_FS_FileData>	ntData(enNT_SF_FileData);
				ntData.data.idx			=	idx;
				ntData.data.uiOffset	=	4096*i;
				ntData.data.uiSize		=	4096;
				ntData.data.uiComplated	=	0;
				U32	uiSendSize	=	4096;
				if(i==uiSendCount-1){
					ntData.data.uiComplated	=	1;
					uiSendSize	=	info.uiSize%4096;
					if(uiSendSize==0)
						uiSendSize	=	4096;
					ntData.data.uiSize		=	uiSendSize;
					ntData.uiSize			+=	(uiSendSize-4096);
				}
				memcpy(ntData.data.data,&pData[uiOffset+ntData.data.uiOffset],uiSendSize);

				uiSendByte	+=	send(info.uiSocket,(const char*)&ntData,ntData.uiSize+4,0);
			}
		}

		
	}

	virtual	void	OnConnect(unsigned __int64 uiSocket,const IN_ADDR& ip,unsigned int uiPort){
		InterlockedIncrement(&m_uiClientCount);
		printf(_T("Client %lld %s:%d Connected!\n"),uiSocket,inet_ntoa(ip),uiPort);
	};
	virtual	void	OnRecv(unsigned __int64 uiSocket,const void* pData,unsigned int uiSize){
		NtBase* pBase	=	(NtBase*)pData;
		switch(pBase->t){
			case enNT_FS_Hello:{
				NtReturnPackT<NT_SF_Hello>	ntData(enNT_FS_Hello);
				ntData.data.uiClient	=	m_uiClientCount;
				ntData.data.uiTaskCount	=	m_uiTaskCount;
				send(uiSocket,(const char*)&ntData,ntData.uiSize,0);
							   }break;
			case enNT_FS_LoadFile:{
				NtPack<FileDataInfo>* p	=	(NtPack<FileDataInfo>*)pData;
				
				m_CS.Enter();
				p->data.uiSocket	=	uiSocket;
				m_lstFileDataInfo.push_back(p->data);
				m_uiTaskCount++;
				m_CS.Leave();
				m_Event.Reset();
				if((m_uiTaskCount&0xff)==0){
					printf("%d\n",m_uiTaskCount);
				}
							  }break;
		}

	};

	virtual	void	OnClose(unsigned __int64 uiSocket){
		InterlockedDecrement(&m_uiClientCount);
		printf(_T("Client %lld Disconnected!"),uiSocket);
	};


	void	LoadFileData(){

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
				U32 uiSize	=	GetFileSize(h,0);
				m_DataArray[i]	=	(U8*)malloc(uiSize);
				DWORD	dwRead=0;
				ReadFile(h,m_DataArray[i],uiSize,&dwRead,NULL);
				CloseHandle(h);
			}else{
				m_DataArray[i]=NULL;
			}
		}
	}

protected:
	U32								m_uiClientCount;
	U32								m_uiTaskCount;
	Air::Common::CriticalSection	m_CS;
	Air::Common::Event				m_Event;
	STD_LIST<FileDataInfo>			m_lstFileDataInfo;
	U8*								m_DataArray[FILEDATA_COUNT];
	CIOCPModel						iocp;
};

int _tmain(int argc, _TCHAR* argv[])
{

	FileServer server;
	server.Initialization();

	while(1){
		server.Update();
	}

	server.Release();

	//CIOCPModel iocp;

	//iocp.LoadSocketLib();

	//while(!iocp.Start()){
	//	TRACE(_T("Server Start Failed!\n"));
	//	getchar();
	//}
	//TRACE(_T("Server Start OK!\n"));

	//getchar();

	//iocp.Stop();
	return 0;
}

