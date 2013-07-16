// stdafx.cpp : 只包括标准包含文件的源文件
// DumpAnalyze.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中
// 引用任何所需的附加头文件，而不是在此文件中引用

U1 LoadFile( const wchar_t* strName,void*& pData,U32& uiSize )
{
	HANDLE	hFile	=	CreateFile(strName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_FLAG_SEQUENTIAL_SCAN,NULL);
	if(hFile!=INVALID_HANDLE_VALUE){
		uiSize	=	GetFileSize(hFile,0);
		pData		=	malloc(uiSize);
		DWORD uiReadSize=0;
		if(pData!=NULL){	
			ReadFile(hFile,pData,uiSize,&uiReadSize,NULL);
		}
		CloseHandle(hFile);
		return true;
	}else{
		pData=NULL;
		uiSize=0;
		return false;
	}
}

U1 SplitFilePath( const std::wstring& str, std::wstring* strPath /*= NULL*/, std::wstring* strFileName /*= NULL*/, std::wstring* strExe /*= NULL*/ )
{
	if(str.empty())
		return	false;
	U32	uiStrSize	=	str.size();
	S32	uiPoint	=	uiStrSize;
	S32	uiSlash	=	-1;


	for(S32 i=uiStrSize-1;i>-1;i--){
		if(str[i]	==	L'.'	&&	uiPoint	==	uiStrSize){
			uiPoint	=	i;
		}
		if(	str[i]	==	L'/'	||
			str[i]	==	L'\\'){
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
			memcpy(&((*strPath)[0]),&str[0],sizeof(wchar_t)*(uiSlash+1));
		}else{
			*strPath	=	str;
		}
	}

	if(strFileName!=NULL){
		U32	uiFileNameSize	=	uiPoint;
		U32	uiFileNameStart	=	0;
		if(uiPoint==uiStrSize)
			uiFileNameSize--;
		if(uiSlash==-1){
			strFileName->resize(uiPoint);
			memcpy(&((*strFileName)[0]),&str[0],sizeof(wchar_t)*uiPoint);
		}else{
			if(uiSlash<uiStrSize){
				if(uiSlash!=-1){
					uiFileNameSize	-=		uiSlash+1;
					uiFileNameStart	=		uiSlash+1;
				}

				strFileName->resize(uiFileNameSize);
				memcpy(&((*strFileName)[0]),&str[uiFileNameStart],sizeof(wchar_t)*uiFileNameSize);
			}
		}
	}
	return	true;
}

