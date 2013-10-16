#include "MIOSystem.h"

MIOSystem::MIOSystem()
{

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
	return true;
}

U1 MIOSystem::LoadFile( U64	fileID,STD_VECTOR<U8>& data )
{
	TCHAR* strName[MAX_PATH];
	swprintf((TCHAR*)strName,
		MAX_PATH,
		(CONST TCHAR*)_T("%016llx"),
		fileID);

	HANDLE h = (HANDLE)CreateFile((const TCHAR*)strName,GENERIC_READ ,FILE_SHARE_READ,NULL,OPEN_EXISTING ,0,0 );
	if(h==(HANDLE)0xffffffff){
		return false;
	}
	unsigned int iSize	=	GetFileSize(h,0);
	if(iSize==0)
	{
		CloseHandle(h);
		return false;
	}
	data.resize(iSize);

	DWORD dwRead=0;
	ReadFile(h,&data[0],iSize,&dwRead,NULL);

	CloseHandle(h);

	return true;
}

U1 MIOSystem::SaveFile( U64	fileID,const	STD_VECTOR<U8>& data )
{
	TCHAR* strName[MAX_PATH];
	swprintf((TCHAR*)strName,
		MAX_PATH,
		(CONST TCHAR*)_T("%016llx"),
		fileID);
	//FILE* 
	FILE* p	=	_wfopen((const TCHAR*)strName,_T("wb"));
	if(p==NULL)
		return false;
	fwrite(&data[0],data.size(),1,p);

	fclose(p);
	return TRUE;
}

U1 MIOSystem::SaveFileBackground( MFile* pFile )
{
	return true;
}
