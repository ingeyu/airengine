// MServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "IOCPModel.h"
#include "MCommon.h"
#include "AirCommonLock.h"





class FileServer	:	public	IOCPListener{
public:
	FileServer();

	void		Initialization(){

		LoadFileIndex();
		LoadFileData();

		iocp.LoadSocketLib();

		iocp.Start();
	};
	void		Release(){

		iocp.Stop();

		iocp.UnloadSocketLib();

		m_vecFileInfo.clear();
		m_mapFileInfo.clear();

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
		}else{
			m_CS.Leave();
			return;
		}
		m_CS.Leave();

		FileInfoMap::iterator	i	=	m_mapFileInfo.find(info.fileID);
		if(i==m_mapFileInfo.end()){
			return;
		}

		U32	uiOffset	=	i->second->offset+info.uiOffset;
		U32	idx			=	i->second->idx;
		if(m_DataArray[idx]!=NULL){
			U8*	pData	=	m_DataArray[idx];
			send(info.uiSocket,(const char*)pData[uiOffset],info.uiSize,0);
		}

		
	}

	virtual	void	OnConnect(unsigned __int64 uiSocket,unsigned int ip,unsigned int uiPort){
		InterlockedIncrement(&m_uiClientCount);
	};
	virtual	void	OnRecv(unsigned __int64 uiSocket,const void* pData,unsigned int uiSize){
		m_CS.Enter();
		FileDataInfo* pInfo	=	(FileDataInfo*)pData;
		pInfo->uiSocket		=	uiSocket;
		m_lstFileDataInfo.push_back(*pInfo);
		m_Event.Reset();
		m_CS.Leave();
	};

	virtual	void	OnClose(unsigned __int64 uiSocket){
		InterlockedDecrement(&m_uiClientCount);
	};


	void LoadFileIndex()
	{
		HANDLE h = CreateFile(
			"Index",
			GENERIC_READ ,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING ,
			0,
			0 );
		if(h!=INVALID_HANDLE_VALUE){
			U32 uiSize	=	GetFileSize(h,0);
			
			U32	uiCount	=	uiSize/sizeof(FileInfo);
			m_vecFileInfo.resize(uiCount);
			DWORD	dwRead=0;
			ReadFile(h,&m_vecFileInfo[0],uiCount*sizeof(FileInfo),&dwRead,NULL);
			CloseHandle(h);

			FileInfo* pInfo	=	&m_vecFileInfo[0];

			for(U32 i=0;i<uiCount;i++){
				FileInfo& info = pInfo[i];
				m_mapFileInfo[info.fileid]	=	&info;
			}
		}
	}
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
	Air::Common::CriticalSection	m_CS;
	Air::Common::Event				m_Event;
	STD_LIST<FileDataInfo>			m_lstFileDataInfo;
	FileInfoMap						m_mapFileInfo;
	FileInfoVector					m_vecFileInfo;
	U8*								m_DataArray[FILEDATA_COUNT];
	CIOCPModel						iocp;
};

int _tmain(int argc, _TCHAR* argv[])
{
	CIOCPModel iocp;

	iocp.LoadSocketLib();

	while(!iocp.Start()){
		TRACE(_T("Server Start Failed!\n"));
		getchar();
	}
	TRACE(_T("Server Start OK!\n"));

	getchar();

	iocp.Stop();
	return 0;
}

