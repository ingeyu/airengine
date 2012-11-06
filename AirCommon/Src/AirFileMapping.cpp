#include "AirFileMapping.h"

namespace	Air{
	void* FileMapping::Lock( U32 uiOffset,U32 uiSize )
	{
		if(m_pLockBuffer!=NULL)
			return NULL;
		m_pLockBuffer	=	MapViewOfFile(m_hFile,FILE_MAP_ALL_ACCESS,0,uiOffset,uiSize);
		return m_pLockBuffer;
	}

	FileMapping::FileMapping( CAString& strFileName,Info* pInfo ):IProduct(strFileName)
	{
		m_hFile			=	NULL;
		m_pLockBuffer	=	NULL;
		if(pInfo!=NULL)
			m_Info			=	*pInfo;
	}

	FileMapping::~FileMapping( void )
	{

	}

	void FileMapping::UnLock()
	{
		if(m_pLockBuffer!=NULL){
			UnmapViewOfFile(m_pLockBuffer);
			m_pLockBuffer	=	NULL;
		}
	}

	Air::U1 FileMapping::CreateFile()
	{
		if(m_hFile==NULL){
			m_hFile	=	CreateFileMappingA(INVALID_HANDLE_VALUE,
				0,
				PAGE_READWRITE,
				0,
				m_Info.uiFileSize,
				m_strProductName.c_str());
			if(m_hFile!=NULL){
				Lock(0,m_Info.uiFileSize);
			}
		}
		return m_hFile!=NULL;;
	}

	Air::U1 FileMapping::OpenFile()
	{
		if(m_hFile==NULL){
			m_hFile	=	OpenFileMappingA(FILE_MAP_ALL_ACCESS,NULL,m_strProductName.c_str());
			if(m_hFile!=NULL){
				Lock(0,m_Info.uiFileSize);
			}
			
		}
		return m_hFile!=NULL;
	}

	Air::U1 FileMapping::CloseFile()
	{
		if(m_hFile!=NULL){
			UnLock();
			CloseHandle(m_hFile);
			m_hFile	=	NULL;
		}
		return true;
	}

	Air::U1 FileMapping::Create()
	{
		switch(m_Info.type){
			case enFMT_Create:{
				return	CreateFile();
						  }break;
			case	enFMT_Open:{
				return	OpenFile();
						   }break;
		}
		return false;
	}

	Air::U1 FileMapping::Destroy()
	{
		return CloseFile();
	}

}
