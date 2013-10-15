// wininet_test.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <Windows.h>

#include <tchar.h>
#include "minilzo.h"
#include <string>


void	Compress(unsigned char* p,unsigned int iSize,const _TCHAR* strName){
	unsigned char buffer[262144];
	unsigned long destSize=0;
	unsigned char* workmem = (unsigned char*)malloc(1048576);

	std::wstring strCompress	=	std::wstring(strName)+L".lzo";
	FILE* pFile	=	_wfopen(strCompress.c_str(),L"wb");



	unsigned int iBlock	=	(iSize+65535)>>16;
	fwrite(&iSize,4,1,pFile);
	fwrite(&iBlock,4,1,pFile);
	for(int i=0;i<iBlock;i++){
		int iRealSize	=	65536;
		if(i==iBlock-1){
			iRealSize	=	iSize&0xffff;
			if(iRealSize==0){
				iRealSize=65536;
			}
		}
		lzo1x_1_compress(&p[65536*i],iRealSize,buffer,&destSize,workmem);
		if(pFile!=NULL){
			fwrite(&destSize,4,1,pFile);
			fwrite(buffer,destSize,1,pFile);
		}
	}
	free(workmem);



	if(pFile!=NULL){
		fclose(pFile);
	}
}

void	DeCompress(unsigned char* p,unsigned int iSize,const _TCHAR* strName){
	unsigned char buffer[262144];
	unsigned long destSize=0;
	unsigned char* workmem = (unsigned char*)malloc(1048576);


	std::wstring strDeCompress	=	std::wstring(strName);
	for(unsigned int i=strDeCompress.size()-1;i>=0;i--){
		if(strDeCompress[i]=='.'){
			strDeCompress[i]=0;
			break;
		}
	}
	FILE* pFile	=	NULL;
	_wfopen_s(&pFile,strDeCompress.c_str(),L"wb");
	unsigned char* pStart	=	p;
	unsigned int iOldSize	=	*(unsigned int*)p;p+=4;
	unsigned int iBlock		=	*(unsigned int*)p;p+=4;
	
	for(int i=0;i<iBlock;i++){
		int iRealSize	=	65536;
		if(i==iBlock-1){
			iRealSize	=	iOldSize&0xffff;
			if(iRealSize==0){
				iRealSize=65536;
			}
		}
		unsigned int iBlockSize	=	*(unsigned int*)p;p+=4;
		lzo1x_decompress(p,iBlockSize,buffer,&destSize,workmem);
		p+=iBlockSize;
		if(pFile!=NULL){
			fwrite(buffer,iRealSize,1,pFile);
		}
	}

	free(workmem);

	if(pFile!=NULL){
		fclose(pFile);
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	if(argc<2)
		return -1;
	int len = wcslen(argv[1]);
	if(len<4)
		return -2;
	_TCHAR* str	=	argv[1];
	_TCHAR s[5]={0};
	memcpy(s,&str[len-4],sizeof(TCHAR)*4);
	for(int i=0;i<4;i++){
		if(s[i]<=L'Z'&&s[i]>=L'A'){
			s[i]+=L'a'-L'A';
		}
	}
	bool bCompress=true;
	if(memcmp(s,L".lzo",4)==0){
		bCompress	=	false;
	}
	int iRet = lzo_init();

	unsigned char* p	=	NULL;

	HANDLE h = (HANDLE)CreateFile(argv[1],GENERIC_READ ,FILE_SHARE_READ |FILE_SHARE_WRITE,NULL,OPEN_EXISTING ,0,0 );
	if(h==(HANDLE)0xffffffff){
		return -3;
	}
	unsigned int iSize	=	GetFileSize(h,0);
	if(iSize>0){
		p	=	(unsigned char*)malloc(iSize);
		DWORD	dwRead=0;
		ReadFile(h,p,iSize,&dwRead,NULL);
	}

	CloseHandle(h);

	if(p==NULL)
		return -4;
	if(bCompress){
		Compress(p,iSize,argv[1]);
	}else{
		DeCompress(p,iSize,argv[1]);
	}
	

	free(p);
	return 0;
}

