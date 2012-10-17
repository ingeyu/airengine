// MTDirectX9Luncher.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <windows.h>
#include "../Detours/detours.h"


#include <string>
typedef std::string AString;
typedef unsigned int U32;
typedef int				S32;

bool SplitFilePath( const AString& str, AString* strPath /*= NULL*/, AString* strFileName /*= NULL*/, AString* strExe /*= NULL*/ )
{
	if(str.empty())
		return	false;
	U32	uiStrSize	=	str.size();
	S32	uiPoint	=	uiStrSize;
	S32	uiSlash	=	-1;


	for(S32 i=uiStrSize-1;i>-1;i--){
		if(str[i]	==	'.'	&&	uiPoint	==	uiStrSize){
			uiPoint	=	i;
		}
		if(	str[i]	==	'/'	||
			str[i]	==	'\\'){
				uiSlash	=	i;
				break;
		}
	}

	if(	uiPoint	!=	uiStrSize	&&
		strExe	!=	NULL)
	{
		if(uiPoint!=uiStrSize-1)
			*strExe	=	&str[uiPoint+1];
	}

	if(	uiSlash	!=	-1		&&
		strPath	!=	NULL)
	{
		if(uiSlash<uiStrSize){
			strPath->resize(uiSlash+1);
			memcpy(&((*strPath)[0]),&str[0],uiSlash+1);
		}else{
			*strPath	=	str;
		}
	}

	if(strFileName!=NULL){
		U32	uiFileNameSize	=	uiPoint;
		U32	uiFileNameStart	=	0;
		if(uiPoint==uiStrSize)
			uiFileNameSize--;

		if(uiSlash<uiStrSize){
			if(uiSlash!=-1){
				uiFileNameSize	-=		uiSlash+1;
				uiFileNameStart	=		uiSlash+1;
			}

			strFileName->resize(uiFileNameSize);
			memcpy(&((*strFileName)[0]),&str[uiFileNameStart],uiFileNameSize);
		}
	}
	return	true;
}

AString	GetLuncherDll(const AString&	strBaseName){
	AString	cfgname	=	strBaseName	+	".cfg";
	FILE*	p	=	fopen(cfgname.c_str(),"rb");

	AString	strDll;

	if(p!=NULL){
		fseek(p,0,SEEK_END);
		U32	uiLength	=	ftell(p);
		fseek(p,0,SEEK_SET);
		if(uiLength!=0){
			strDll.resize(uiLength);
		}
		fread(&strDll[0],uiLength,1,p);
		fclose(p);
		return	strDll;
	}else{
		return	"";
	}

};

int _tmain(int argc, _TCHAR* argv[])
{
	//FreeLibrary(LoadLibraryW(L"DirectXMonitor.dll"));
	//return 0;
	if(argc<2){
		printf("Usage:Luncher.exe [*.exe]");
		getchar();
		return -1;
	}

	char strModuleName[1024];
	GetModuleFileNameA(NULL,strModuleName,1024);

	AString	strLuncherPath;
	AString	strFileName;
	SplitFilePath(strModuleName,&strLuncherPath,&strFileName,0);

	AString	strTargetPath;
	SplitFilePath(argv[1],&strTargetPath,NULL,NULL);

	AString	strDllFileName	=	GetLuncherDll(strLuncherPath+strFileName);
	if(strDllFileName.empty())
		strDllFileName	=	"MTDirectX9.dll";

	AString	strDLL	=	strLuncherPath	+	strDllFileName;
	
	//create nvperf process
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si,sizeof(STARTUPINFO));
	ZeroMemory(&pi,sizeof(PROCESS_INFORMATION));

	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOWNORMAL;

	if(TRUE != DetourCreateProcessWithDllA(
		0,
		argv[1], 
		0, 
		0, 
		FALSE, 
		CREATE_DEFAULT_ERROR_MODE,
		0, 
		strTargetPath.c_str(), 
		&si, 
		&pi, 
		strDLL.c_str(), 
		NULL))
	{
		printf("DetourCreateProcessWithDll	Failed!\n");
		getchar();
	}


	return 0;
}

