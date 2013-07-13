#include "stdafx.h"
#include "DumpLog.h"
#include <Windows.h>

DumpLog::DumpLog()
{
	SYSTEMTIME t;
	GetLocalTime(&t);
	sprintf_s(strFileName,"%02d_%02d_%02d__%02d_%02d_%02d.log",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond);

	//m_hFile	=	CreateFile();
}

DumpLog::~DumpLog()
{

}

void DumpLog::Write( const char* str )
{
	FILE* pFile=fopen(strFileName,"a+");
	if(pFile!=NULL){
		printf(str);
		fprintf(pFile,str);
		fclose(pFile);
	}

}

DumpLog& GetLog()
{	
	static DumpLog log;
	return log;
}
