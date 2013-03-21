// DumpReader.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include "dbghelp.h"

void mdmp_dump(void* pBase,unsigned int uiSize);

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc<2)
	{
		printf("no enough parameter!\n");
		return -1;
	}
	printf("dump file name=[");
	printf(argv[1]);
	printf("]\n");
	//getchar();

	
	FILE* pFile =	fopen(argv[1],"rb");
	if(pFile==NULL){
		printf("open dump file failed!\n");
		getchar();
		return -2;
	}
	//MINIDUMP_HEADER header;
	//fread(&header,sizeof(header),1,pFile);
	fseek(pFile,0,SEEK_END);
	unsigned int uiSize	 = ftell(pFile);
	fseek(pFile,0,SEEK_SET);
	void* pBuffer = malloc(uiSize);
	fread(pBuffer,uiSize,1,pFile);
	fclose(pFile);

	mdmp_dump(pBuffer,uiSize);
	printf("------------------Finished!--------------\n");
	//getchar();
	return 0;
}

