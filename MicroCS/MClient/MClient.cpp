#include	"MClient.h"
#include	"MClientFile.h"

ThreadHandle::ThreadHandle(){
	memset(m_FileHandle,0,sizeof(HANDLE)*FILEDATA_COUNT);
	m_uiThreadID	=	0;
}
ThreadHandle::~ThreadHandle(){
	for(U32 i=0;i<FILEDATA_COUNT;i++){
		if(m_FileHandle[i]!=NULL){
			CloseHandle(m_FileHandle[i]);
			m_FileHandle[i]=0;
		}
	}
	m_uiThreadID=0;
}
HANDLE	ThreadHandle::GetFileHandle(U32	idx){
	if(m_FileHandle[idx]!=NULL)
		return m_FileHandle[idx];
	TCHAR str[MAX_PATH];
	swprintf_s(str,_T("Data%d"),idx);
	 m_FileHandle[idx]	=	CreateFile(
		 str,
		 GENERIC_READ,
		 FILE_SHARE_READ|FILE_SHARE_WRITE,
		 NULL,
		 OPEN_EXISTING,
		 NULL,
		 NULL
		 );
	 return  m_FileHandle[idx];
}

U32 MClient::LoadFile( const char* strName,void* pBuffer)
{
	char str[MAX_PATH]={0};
	for(int i=0;strName[i]!=0;i++){
		str[i]	=	toupper(strName[i]);	
	}
	S64	fileID	=	StringHash(str);

	STD_HASHMAP<U64,FileInfo*>::iterator	itr	=	m_mapFileInfo.find(fileID);
	if(itr==m_mapFileInfo.end())
		return 0;

	U1	bDownloadOnly		=	false;
	U32	uiUnCompressSize	=	itr->second->size;
	U32	uiCompressSize		=	itr->second->compressize;
	U32	bReady				=	itr->second->idx&0xffff0000;


	if(pBuffer==MFILE_EXIST){
		return uiUnCompressSize;
	}else if(pBuffer==MFILE_READY){
		return	bReady!=0;
	}else if(pBuffer==MFILE_DOWNLOAD){
		bDownloadOnly	=	true;
	}
	if(bReady){
		if(bDownloadOnly){
			return uiUnCompressSize;
		}
		return ReadFromHD(pBuffer,itr->second);
	}


	CSInfo* pInfo	=	(CSInfo*)m_pFile->GetLockedBuffer();
	//Wait Other Thread 
	while(InterlockedCompareExchange(&pInfo->mark,0xffffffff,0)!=0){

	}
	pInfo->FileID	=	fileID;
	pInfo->uiSize	=	0;
	if(bDownloadOnly){
		pInfo->ret	=	0;
	}else{
		pInfo->ret	=	1;
	}
	InterlockedExchange(&pInfo->mark,1);

	if(m_pWaitClient!=NULL){
		m_pWaitClient->Reset();
	}

	if(bDownloadOnly){
		return uiUnCompressSize;
	}
	

	//Wait IO Process(MFileSystem)
	while(InterlockedCompareExchange(&pInfo->mark,0xeeeeeeee,0xffffffff)!=0xffffffff){

	}
	U32 bRet	=	pInfo->ret;
	U8* p = (U8*)pInfo;//+1;
	p+=sizeof(CSInfo);
	if(bRet){
		if(uiUnCompressSize==uiCompressSize){
			memcpy(pBuffer,p,uiUnCompressSize);
		}else{
			U32	destSize	=	uiUnCompressSize;
			MDescompress(p,uiCompressSize,pBuffer,destSize);
		}
		U32	crc32	=	CRC32(pBuffer,uiUnCompressSize);
		if(crc32!=itr->second->crc32){
			char str[MAX_PATH];
			sprintf_s(str,"%016llx CM CRC32 Failed!\n",itr->second->fileid);
			OutputDebugStringA(str);
			InterlockedExchange(&pInfo->mark,0);

			if(itr->second->idx&0xffff0000){
				return ReadFromHD(pBuffer,itr->second);
			}
			return 0;
		}
		bRet	=	uiUnCompressSize;
	}
	//Release Mark
	InterlockedExchange(&pInfo->mark,0);

	return bRet;
}

MClient::MClient()
{
	m_pFile		=	NULL;
	for(U32 i=0;i<FILEDATA_COUNT;i++){
		m_FileData[i]	=	NULL;
	}
	m_pFileInfo		=	NULL;
	m_pWaitClient	=	NULL;
}

void	StartProcess(const TCHAR* strExe){

		TCHAR	strTempName[MAX_PATH];
		wcscpy_s(strTempName,strExe);
	    STARTUPINFO si = { sizeof(si) };     
		PROCESS_INFORMATION pi;     
		si.dwFlags = STARTF_USESHOWWINDOW; // 指定wShowWindow成员有效     
		si.wShowWindow = TRUE; // 此成员设为TRUE的话则显示新建进程的主窗口     
		BOOL bRet = CreateProcess (     NULL,// 不在此指定可执行文件的文件名     
			strTempName,//命令行参数     
			NULL,// 默认进程安全性     
			NULL,// 默认进程安全性     
			FALSE,// 指定当前进程内句柄不可以被子进程继承     
			0,// 为新进程创建一个新的控制台窗口     
			NULL,// 使用本进程的环境变量     
			NULL,// 使用本进程的驱动器和目录     
			&si,     
			&pi) ;     
		if(bRet)     
		{         
			// 不使用的句柄最好关掉         
			CloseHandle(pi.hThread);         
			CloseHandle(pi.hProcess);         
			printf("新进程的ID号：%d\n",pi.dwProcessId);         
			printf("新进程的主线程ID号：%d\n",pi.dwThreadId);     
		} 
}

U1 MClient::Initialization()
{

	AddFactory(new Air::ParamFactory<Air::FileMapping>());

	//Create Client->FileSystem ShareMemory
	char strName[MAX_PATH];
	sprintf_s(strName,"%dFileMapping",GetProcessId(GetCurrentProcess()));

	Air::FileMapping::Info info;
	info.type		=	Air::FileMapping::enFMT_Create;
	info.uiFileSize	=	16*1048576;
	m_pFile	=	CreateProduct<Air::FileMapping>(strName,&info);
	printf("Create FileMapping %s \n",strName);

	//Create MFileSystem Process
	StartProcess(_T("MFileSystem.exe"));

	//Wait FileSystem Init
	HANDLE hMutex	=	NULL;
	while(hMutex==NULL){
		
		hMutex	=	OpenMutex(MUTEX_ALL_ACCESS,false,L"MFileSystemInit");
		if(hMutex!=NULL){
			CloseHandle(hMutex);
			break;
		}else{
			Sleep(10);
		}
	}

	//Get Total File Count
	U32	uiSize	=	0;
	HANDLE h = CreateFile(
		L"Index",
		GENERIC_READ ,
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING ,
		0,
		0 );
	if(h!=INVALID_HANDLE_VALUE){
		uiSize	=	GetFileSize(h,0);
		CloseHandle(h);
	}
	//Create File Index Map
	info.type	=	Air::FileMapping::enFMT_Open;
	if(uiSize!=0){
		info.uiFileSize	=	uiSize;
	}
	m_pFileInfo	=	CreateProduct<Air::FileMapping>("MFileSystemShareMemory",&info);

	U32	uiCount	=	uiSize/sizeof(FileInfo);
	FileInfo* pInfo	=(FileInfo*)m_pFileInfo->GetLockedBuffer();
	for(U32 i=0;i<uiCount;i++){
		FileInfo& finfo = pInfo[i];
		m_mapFileInfo[finfo.fileid]	=	&finfo;
	}
	char strEventName[MAX_PATH];
	sprintf_s(strEventName,"%d",GetProcessId(GetCurrentProcess()));
	m_pWaitClient	=	new	Air::Common::Event(strEventName);
	return true;
}

U1 MClient::Release()
{
	if(m_pWaitClient!=NULL){
		delete m_pWaitClient;
		m_pWaitClient=NULL;
	}

	SAFE_RELEASE_REF(m_pFile);
	SAFE_RELEASE_REF(m_pFileInfo);
	m_mapFileInfo.clear();
	for(U32 i=0;i<FILEDATA_COUNT;i++){
		CloseHandle(m_FileData[i]);
		m_FileData[i]=NULL;
	}
	return true;
}

U32 MClient::ReadFromHD( void* pBuffer,FileInfo* pInfo )
{
	U32	DataIdx	=	pInfo->idx&0xffff;

	if(DataIdx>=FILEDATA_COUNT)
		return 0;

	U32	threadid	=	GetCurrentThreadId();
	U32	count		=	m_uiThreadCount;
	HANDLE	pFile	=	NULL;
	for(U32	i=0;i<count;i++){
		ThreadHandle& th	=	m_ThreadHandle[i];
		if(th.m_uiThreadID==threadid){
			pFile	=	th.GetFileHandle(DataIdx);
		}
	}
	if(pFile==NULL){
		U32	ti	=	InterlockedIncrement(&m_uiThreadCount);
		ThreadHandle& th	=	m_ThreadHandle[ti];
		if(th.m_uiThreadID==threadid){
			pFile	=	th.GetFileHandle(DataIdx);
		}
	}

	LARGE_INTEGER fpos;
	fpos.QuadPart	=	pInfo->offset;
	LARGE_INTEGER oldpos;
	SetFilePointerEx(pFile,fpos,&oldpos,FILE_BEGIN);
	DWORD	dwRead=0;
	ReadFile(pFile,
			pBuffer,
			pInfo->compressize,
			&dwRead,
			NULL);
	U32 uiDest=pInfo->size;
	if(uiDest!=pInfo->compressize){
		CSInfo* pCSInfo	=	(CSInfo*)m_pFile->GetLockedBuffer();
		//Wait Other Thread 
		while(InterlockedCompareExchange(&pCSInfo->mark,0xffffffff,0)!=0){

		}
		MDescompress(pTemp,pInfo->compressize,pBuffer,uiDest);

		InterlockedExchange(&pCSInfo->mark,0);
	}
	
	return uiDest;
}

HANDLE MClient::GetFileHandle( U32 idx )
{
	if(m_FileData[idx]==NULL){
		TCHAR strName[MAX_PATH];
		swprintf_s(strName,_T("Data%d"),idx);
		m_FileData[idx]	=CreateFile(
			strName,
			GENERIC_READ ,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			0,
			0 );
		if(m_FileData[idx]==INVALID_HANDLE_VALUE){
			m_FileData[idx]	=	NULL;
		}
	}
	return m_FileData[idx];
}


