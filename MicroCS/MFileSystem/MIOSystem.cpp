#include "MIOSystem.h"
#include "MFile.h"

MIOSystem::MIOSystem()
{
	for(U32 i=0;i<FILEDATA_COUNT;i++){
		m_FileData[i]=NULL;
		m_uiOffset[i]=0;
	}
}

MIOSystem::~MIOSystem()
{

}

U1 MIOSystem::Initialization()
{
	return true;
}

U1 MIOSystem::Release()
{
	Update(0);
	for(U32 i=0;i<FILEDATA_COUNT;i++){
		CloseHandle(m_FileData[i]);
		m_FileData[i]=NULL;
		m_uiOffset[i]	=	0;
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
	HANDLE h = GetFileHandle(uiSize,&Index);
	SetFilePointer(h,m_uiOffset[Index],0,FILE_BEGIN);
	DWORD dwWrite=0;
	WriteFile(h,pData,uiSize,&dwWrite,NULL);
	info.idx		=	Index;
	info.offset		=	m_uiOffset[Index];
	m_uiOffset[Index]+=uiSize;

	return TRUE;
}

void MIOSystem::SaveFile( FileInfo& info,const STD_VECTOR<U8>& data )
{
	SaveFile(info,&data[0],data.size());
}

U1 MIOSystem::SaveFileBackground( MFile* pFile )
{
	m_lstFile.push_back(pFile);
	return true;
}

void MIOSystem::Update( float fTimeDelta )
{
	STD_LIST<MFile*>::iterator	i	=	m_lstFile.begin();
	for(;i!=m_lstFile.end();i++){
		SaveFile((*i)->GetFileInfo(),(*i)->GetData(),(*i)->GetDataSize());
		(*i)->ReleaseRef();
	}
	m_lstFile.clear();
}

HANDLE MIOSystem::GetFileHandle( U32 uiSize,U32* pIndex )
{
	for(U32 i=0;i<FILEDATA_COUNT;i++){
		if(m_FileData[i]==NULL){
			m_FileData[i]	=	GetFileHandleByIndex(i);
		}
			
		if(m_uiOffset[i] + uiSize	>	MAX_DATA_SIZE){
			continue;
		}
		if(pIndex!=NULL){
			*pIndex	=	i;
		}
		return	m_FileData[i];
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
		}else{
			m_uiOffset[idx]	=	GetFileSize(m_FileData[idx],0);
		}
	}
	return m_FileData[idx];
}
