#include "MIOSystem.h"
#include "MFile.h"

MIOSystem::MIOSystem()
{
	for(U32 i=0;i<FILEDATA_COUNT;i++){
		m_FileData[i]=NULL;
	}
	m_lstFile.reserve(16);
	m_FileIndex		=	NULL;
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
	return true;
}

U1 MIOSystem::Release()
{
	Update(0);
	for(U32 i=0;i<FILEDATA_COUNT;i++){
		CloseHandle(m_FileData[i]);
		m_FileData[i]=NULL;
	}
	if(m_FileIndex!=NULL){
		CloseHandle(m_FileIndex);
		m_FileIndex=NULL;
	}
	return true;
}

U1 MIOSystem::LoadFile( FileInfo& info,STD_VECTOR<U8>& data )
{

	HANDLE h = GetFileHandleByIndex(info.idx);
	if(h==NULL){
		return false;
	}

	data.resize(info.compressize);
	SetFilePointer(h,info.offset,0,FILE_BEGIN);
	DWORD dwRead=0;
	ReadFile(h,&data[0],info.compressize,&dwRead,NULL);

	return true;
}

U1 MIOSystem::SaveFile( FileInfo& info,const void* pData,U32 uiSize )
{
	U32	Index	=	0;
	HANDLE h = GetFileHandleByIndex(info.idx&0xffff);
	SetFilePointer(h,info.offset,0,FILE_BEGIN);
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
	return true;
}

void MIOSystem::Update( U32 uiTickTime )
{
	
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
		SetFilePointer(m_FileIndex,uiRA,0,FILE_BEGIN);
		WriteFile(m_FileIndex,&pFile->GetFileInfo().idx,sizeof(U32),&dWrite,NULL);
		pFile->ReleaseRef();
	}
	
}


HANDLE MIOSystem::GetFileHandleByIndex( U32 idx )
{
	if(m_FileData[idx]==NULL){
		TCHAR strName[MAX_PATH];
		swprintf_s(strName,_T("Data%d"),idx);
		m_FileData[idx]	=CreateFile(
			strName,
			GENERIC_READ|GENERIC_WRITE ,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			NULL,
			OPEN_ALWAYS,
			0,
			0 );
		if(m_FileData[idx]==INVALID_HANDLE_VALUE){
			m_FileData[idx]=NULL;
		}
	}
	return m_FileData[idx];
}
