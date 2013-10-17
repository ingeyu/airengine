#include "MClient.h"

struct CSInfo 
{
	U32	FileSystemPID;
	U32	mark;
	U32	ret;
	U64	FileID;
	U32	uiSize;
};

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
	if(pBuffer==NULL)
		return itr->second->size;
	if(itr->second->offset!=0xffffffff){
		return ReadFromHD(pBuffer,itr->second);
	}


	CSInfo* pInfo	=	(CSInfo*)m_pFile->GetLockedBuffer();
	//Wait Other Thread 
	while(InterlockedCompareExchange(&pInfo->mark,0xffffffff,0)!=0){

	}
	pInfo->FileID	=	fileID;
	pInfo->uiSize	=	0;
	InterlockedExchange(&pInfo->mark,1);
	//Wait IO Process(MFileSystem)
	while(InterlockedCompareExchange(&pInfo->mark,0xeeeeeeee,0xffffffff)!=0xffffffff){

	}
	U32 bRet	=	pInfo->ret;
	U8* p = (U8*)pInfo;//+1;
	p+=sizeof(CSInfo);
	if(bRet){
		U32	destSize	=	itr->second->size;
		MDescompress(p,itr->second->compressize,pBuffer,destSize);
		bRet	=	destSize;
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
	m_pFileInfo	=	NULL;
}

U1 MClient::Initialization()
{

	AddFactory(new Air::ParamFactory<Air::FileMapping>());

	//Create Client->FileSystem ShareMemory
	char strName[MAX_PATH];
	sprintf_s(strName,"%d",GetProcessId(GetCurrentProcess()));

	Air::FileMapping::Info info;
	info.type		=	Air::FileMapping::enFMT_Create;
	info.uiFileSize	=	16*1048576;
	m_pFile	=	CreateProduct<Air::FileMapping>(strName,&info);

	//Create File Data Handle


	//Wait FileSystem Init
	HANDLE hMutex	=	NULL;
	while(hMutex==NULL){
		
		hMutex	=	OpenMutex(MUTEX_ALL_ACCESS,false,L"MFileSystem");
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
	m_pFileInfo	=	CreateProduct<Air::FileMapping>(strName,&info);

	U32	uiCount	=	uiSize/sizeof(FileInfo);
	FileInfo* pInfo	=(FileInfo*)m_pFileInfo->GetLockedBuffer();
	for(U32 i=0;i<uiCount;i++){
		FileInfo& finfo = pInfo[i];
		m_mapFileInfo[finfo.fileid]	=	&finfo;
	}

	return true;
}

U1 MClient::Release()
{

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
	if(pInfo->idx>=FILEDATA_COUNT)
		return 0;
	void* pTemp	=	malloc(pInfo->compressize);

	HANDLE	hFile	=	GetFileHandle(pInfo->idx);

	DWORD	dwRead=0;
	ReadFile(hFile,
			pTemp,
			pInfo->compressize,
			&dwRead,
			NULL);
	U32 uiDest=0;
	MDescompress(pTemp,pInfo->compressize,pBuffer,uiDest);
	free(pTemp);
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


