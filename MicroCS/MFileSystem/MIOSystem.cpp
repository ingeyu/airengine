#include "MIOSystem.h"
#include "MFile.h"
#include "process.h"

void	IOThreadUpdate(void* p){
	MIOSystem::GetSingleton()->Update(0);

}

MIOSystem::MIOSystem()
{
	for(U32 i=0;i<FILEDATA_COUNT;i++){
		m_FileWrite[i]=NULL;
	}
	m_lstFile.reserve(16);
	m_FileIndex		=	NULL;
	m_bExit			=	false;
}

MIOSystem::~MIOSystem()
{

}

U1 MIOSystem::Initialization()
{
	m_FileIndex	=CreateFile(
		_T("Index"),
		GENERIC_READ|GENERIC_WRITE ,
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS,
		0,
		0 );
	_beginthread(IOThreadUpdate,1048576,this);
	return true;
}

U1 MIOSystem::Release()
{
	m_bExit	=	true;
	m_WaitExit.Reset();
	
	for(U32 i=0;i<FILEDATA_COUNT;i++){
		CloseHandle(m_FileWrite[i]);
		m_FileWrite[i]=NULL;
	}
	if(m_FileIndex!=NULL){
		CloseHandle(m_FileIndex);
		m_FileIndex=NULL;
	}
	return true;
}

U1 MIOSystem::LoadFile( FileInfo& info,STD_VECTOR<U8>& data )
{

	

	data.resize(info.compressize);
	LARGE_INTEGER fpos;
	fpos.QuadPart	=	info.offset;
	LARGE_INTEGER oldpos;
	m_CSRead.Enter();
	HANDLE h = GetFileReadHandle(info.idx&0xffff);
	if(h==NULL){
		m_CSRead.Leave();
		return false;
	}
	SetFilePointerEx(h,fpos,&oldpos,FILE_BEGIN);
	DWORD dwRead=0;
	ReadFile(h,&data[0],info.compressize,&dwRead,NULL);
	m_CSRead.Leave();
	return true;
}

U1 MIOSystem::SaveFile( FileInfo& info,const void* pData,U32 uiSize )
{
	U32	Index	=	0;
	HANDLE h = GetFileWriteHandle(info.idx&0xffff);
	LARGE_INTEGER fpos;
	fpos.QuadPart	=	info.offset;
	LARGE_INTEGER oldpos;
	SetFilePointerEx(h,fpos,&oldpos,FILE_BEGIN);
	DWORD dwWrite=0;
	WriteFile(h,pData,uiSize,&dwWrite,NULL);
	info.idx		|=0xffff0000;
	
	
	return TRUE;
}

void MIOSystem::SaveFile( FileInfo& info,const STD_VECTOR<U8>& data )
{
	SaveFile(info,&data[0],data.size());
}

U1 MIOSystem::SaveFileBackground( MFile* pFile )
{
	m_CS.Enter();
	m_lstFile.push_back(pFile);
	m_CS.Leave();
	m_WaitExit.Reset();
	return true;
}

void MIOSystem::Update( U32 uiTickTime )
{
	while(true){
		m_CS.Enter();
		STD_VECTOR<MFile*>	lst	=	m_lstFile;
		m_lstFile.clear();
		m_CS.Leave();

		STD_VECTOR<MFile*>::iterator	i	=	lst.begin();
		for(;i!=lst.end();i++){
			MFile* pFile = (*i);
			SaveFile(pFile->GetFileInfo(),pFile->GetData(),pFile->GetDataSize());
			U32	uiRA	=	pFile->GetFileIndexRA();
			DWORD dWrite=0;
			LARGE_INTEGER fpos;
			fpos.QuadPart	=	uiRA;
			LARGE_INTEGER oldpos;
			SetFilePointerEx(m_FileIndex,fpos,&oldpos,FILE_BEGIN);
			WriteFile(m_FileIndex,&pFile->GetFileInfo().idx,sizeof(U32),&dWrite,NULL);
			pFile->ReleaseRef();
		}
		m_WaitExit.Wait(1000);
		if(m_bExit){
			break;
		}
	}
	
}


HANDLE MIOSystem::GetFileWriteHandle( U32 idx )
{
	if(m_FileWrite[idx]==NULL){
		TCHAR strName[MAX_PATH];
		swprintf_s(strName,_T("Data%d"),idx);
		m_FileWrite[idx]	=CreateFile(
			strName,
			GENERIC_READ|GENERIC_WRITE ,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			NULL,
			OPEN_ALWAYS,
			0,
			0 );
		if(m_FileWrite[idx]==INVALID_HANDLE_VALUE){
			m_FileWrite[idx]=NULL;
		}
	}
	return m_FileWrite[idx];
}


HANDLE MIOSystem::GetFileReadHandle( U32 idx )
{
	if(m_FileRead[idx]==NULL){
		TCHAR strName[MAX_PATH];
		swprintf_s(strName,_T("Data%d"),idx);
		m_FileRead[idx]	=CreateFile(
			strName,
			GENERIC_READ|GENERIC_WRITE ,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			NULL,
			OPEN_ALWAYS,
			0,
			0 );
		if(m_FileRead[idx]==INVALID_HANDLE_VALUE){
			m_FileRead[idx]=NULL;
		}
	}
	return m_FileRead[idx];
}
