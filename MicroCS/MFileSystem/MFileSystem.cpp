#include "MFileSystem.h"
#include "MDownloadSystem.h"
#include "MFile.h"
#include "MIOSystem.h"
#include <TlHelp32.h>
#include "MClient.h"

MFileSystem::MFileSystem()
{
	m_hFileSystemInit	=	NULL;
	m_pShareFileInfo	=	NULL;
}

MFileSystem::~MFileSystem()
{
	m_pShareFileInfo=NULL;
}

U1 MFileSystem::Initialization()
{
	AddFactory(new Air::ParamFactory<Air::FileMapping>());
	AddFactory(new Air::ParamFactory<Air::Common::NetServer>());
	AddFactory(new Air::ParamFactory<Air::Common::NetClient>());
	AddFactory(new Air::ParamFactory<MFile>());
	AddFactory(new Air::ParamFactory<MClient>());


	LoadFileIndex();

	MIOSystem::GetSingleton()->Initialization();
	
	MDownloadSystem::GetSingleton()->Initialization();


	return true;
}

U1 MFileSystem::Release()
{
	CloseHandle(m_hFileSystemInit);

	SAFE_RELEASE_REF(m_pShareFileInfo);

	MDownloadSystem::GetSingleton()->Release();
	MDownloadSystem::ReleaseSingleton();

	MIOSystem::GetSingleton()->Release();
	MIOSystem::ReleaseSingleton();

	return true;
}


MFile* MFileSystem::CreateMFile( U64 id )
{
	FileInfoMap::iterator	i	=	m_mapFileInfo.find(id);
	if(i==m_mapFileInfo.end()){
		return NULL;
	}

	char str[MAX_PATH];
	sprintf_s(str,"%016llx",id);
	return CreateProduct<MFile>(str,i->second);
}

void MFileSystem::Update(float fTimeDelta)
{
	m_WaitDownload.Wait(10);
	MDownloadSystem::GetSingleton()->Update(fTimeDelta);

	MIOSystem::GetSingleton()->Update(fTimeDelta);

	ScanProcess(_T("GameClient.exe"));
}

void MFileSystem::ScanProcess( const TCHAR* strName )
{
	HANDLE	hSnapshot	=	CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

	if(hSnapshot==NULL)
		return;
	PROCESSENTRY32 processinfo;
	memset(&processinfo,0,sizeof(processinfo));
	processinfo.dwSize	=	sizeof(processinfo);

	static U32 iFrame	=	0;
	iFrame++;
	STD_LIST<U32>	lstNewClient;

	BOOL	bState	=	Process32First(hSnapshot,&processinfo);
	while(bState){
		if(wcscmp(strName,processinfo.szExeFile)==0){
			STD_MAP<U32,MClient*>::iterator itr = m_mapClient.find(processinfo.th32ProcessID);
			if(itr==m_mapClient.end()){
				lstNewClient.push_back(processinfo.th32ProcessID);
			}else{
				itr->second->SetProcessExistFrame(iFrame);
			}
			
		}
		bState	=	Process32Next(hSnapshot,&processinfo);
	}
	CloseHandle(hSnapshot);

	//Remove Don't Exist Client
	STD_MAP<U32,MClient*>::iterator itr = m_mapClient.begin();
	for(;itr!=m_mapClient.end();){
		if(!itr->second->IsProcessExist(iFrame)){
			itr->second->ReleaseRef();
			itr	=	m_mapClient.erase(itr);
		}else{
			itr++;
		}
	}
	//Create	New	Client
	STD_LIST<U32>::iterator	i	=	lstNewClient.begin();
	for(;i!=lstNewClient.end();i++){
		char strName[MAX_PATH];
		U32	id	=	*i;
		sprintf_s(strName,"%d",id);
		MClient* pClient	=	CreateProduct<MClient>(strName,&id);
		if(pClient==NULL){
			__asm int 3;
		}
		m_mapClient[*i]		=	pClient;
	}
}

FileInfo& MFileSystem::GetFileInfo( U32 idx )
{
	FileInfo* pInfo	=	(FileInfo*)m_pShareFileInfo->GetLockedBuffer();
	return pInfo[idx];
}

void MFileSystem::LoadFileIndex()
{
	HANDLE h = CreateFile(
		L"Index",
		GENERIC_READ ,
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING ,
		0,
		0 );
	if(h!=INVALID_HANDLE_VALUE){
		U32 uiSize	=	GetFileSize(h,0);
		Air::FileMapping::Info fmInfo;
		fmInfo.type			=	Air::FileMapping::enFMT_Create;
		fmInfo.uiFileSize	=	uiSize;
		m_pShareFileInfo	=	CreateProduct<Air::FileMapping>("MFileSystemShareMemory",&fmInfo);
		U32	uiCount	=	uiSize/sizeof(FileInfo);
		
		DWORD	dwRead=0;
		ReadFile(h,m_pShareFileInfo->GetLockedBuffer(),uiSize,&dwRead,NULL);
		CloseHandle(h);

		FileInfo* pInfo	=	(FileInfo*)m_pShareFileInfo->GetLockedBuffer();

		for(U32 i=0;i<uiCount;i++){
			FileInfo& info = pInfo[i];
			m_mapFileInfo[info.fileid]	=	&info;
		}
	}
	m_hFileSystemInit	=	CreateMutex(NULL,FALSE,_T("MFileSystemInit"));
}

U32 MFileSystem::GetFileCount()
{
	return m_mapFileInfo.size();
}

void MFileSystem::OnDownloadComplate()
{
	m_WaitDownload.Reset();
}
