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
