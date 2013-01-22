// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <process.h>
#include <Windows.h>
#include <iostream>
#include <stdio.h>


HANDLE	hMutex	=	NULL;

enum enumHeapBlockType{
	enHBT_VirtualAlloc,
	enHBT_HeapRegion,
};

struct HeapBlock{
	VOID*					pAddress;
	int						iVirtualSize;
	int						iCommontSize;
	unsigned	short		iType;
	unsigned	short		iHeapIndex;
};

unsigned char* g_Buffer	=	NULL;

void	WalkHeapBlock(void*	pDest){
	DWORD dwWriteFlag	=	1;
	DWORD dwReadFlag	=	0;

	unsigned char*	pFlag	=	(unsigned char*)pDest;
	memcpy(pFlag,&dwWriteFlag,sizeof(DWORD));

	unsigned char*	pBase	=	pFlag+4;

	

	unsigned char*	pChar	=	pBase+4;

	DWORD iTotalHeapCount	=	0;

	HANDLE	hHeapArray[50];
	DWORD	dwHeapCount	=	GetProcessHeaps(0,0);
	if(dwHeapCount>0){
		dwHeapCount	=	GetProcessHeaps(dwHeapCount,hHeapArray);

		for(int i=0;i<dwHeapCount;i++){

			unsigned char*	pHeapHeader	=	pChar;
			DWORD	dwBlockCount	=	0;
			//pChar+=4;

			HANDLE	hHeap	=	hHeapArray[i];

			DWORD dwCompareSize	=	508*1024-23;

			DWORD	dwTotalVirtualSize	=	0;
			DWORD	dwTotalCommitSize	=	0;

			HeapLock(hHeap);

			PROCESS_HEAP_ENTRY	e;
			memset(&e,0,sizeof(e));
			while(HeapWalk(hHeap,&e)	==	TRUE){
				if(e.wFlags&PROCESS_HEAP_ENTRY_BUSY){
					if(e.wFlags&PROCESS_HEAP_ENTRY_DDESHARE){

					}
					if(e.wFlags&PROCESS_HEAP_ENTRY_MOVEABLE){

					}
					DWORD	dwTempSize	=	e.cbData+e.cbOverhead;
					if(dwTempSize	>=dwCompareSize){
						DWORD	dwVirtualSize	=	(dwTempSize+4095)&0xfffff000;
						dwTotalVirtualSize		+=	dwVirtualSize;
						
						HeapBlock	block;
						block.pAddress	=	(VOID*)(((DWORD)e.lpData)&0xfffff000);
						block.iVirtualSize	=	dwVirtualSize;
						block.iCommontSize	=	e.cbData;
						block.iType			=	enHBT_VirtualAlloc;
						block.iHeapIndex	=	i;
						memcpy(pChar,&block,sizeof(HeapBlock));
						pChar+=sizeof(HeapBlock);
						dwBlockCount++;
					}
					dwTotalCommitSize	+=	e.cbData;
				}
				if(e.wFlags&PROCESS_HEAP_REGION){
					dwTotalVirtualSize	+=	e.Region.dwCommittedSize	+	e.Region.dwUnCommittedSize;
					dwTotalCommitSize	+=	e.Region.dwCommittedSize;

					HeapBlock	block;
					block.pAddress	=	(VOID*)(((DWORD)e.lpData)&0xfffff000);
					block.iVirtualSize	=	e.Region.dwCommittedSize	+	e.Region.dwUnCommittedSize;
					block.iCommontSize	=	e.Region.dwCommittedSize;
					block.iType			=	enHBT_HeapRegion;
					block.iHeapIndex	=	i;
					memcpy(pChar,&block,sizeof(HeapBlock));
					pChar+=sizeof(HeapBlock);
					dwBlockCount++;
				}
				if(e.wFlags&PROCESS_HEAP_UNCOMMITTED_RANGE){

				}
				//unused
				if(e.wFlags==0){

				}
			}


			HeapUnlock(hHeap);
			iTotalHeapCount	+=	dwBlockCount;
			//memcpy(pHeapHeader,&dwBlockCount,sizeof(DWORD));
		}
	}
	memcpy(pBase,&iTotalHeapCount,sizeof(DWORD));

	memcpy(pFlag,&dwReadFlag,sizeof(DWORD));
	
	if(hMutex==NULL){
		char strMutexName[256];
		sprintf_s(strMutexName,256,"HeapViewMutex%d",GetCurrentProcessId());
		hMutex	=	CreateMutexA(NULL,TRUE,strMutexName);
	}
}

void	ThreadFunc(void*	pParam){

	
	if(hMutex==NULL){
		char strMutexName[256];
		sprintf_s(strMutexName,256,"HeapViewMutex%d",GetCurrentProcessId());
		hMutex	=	OpenMutexA(MUTEX_ALL_ACCESS,TRUE,strMutexName);
		if(hMutex!=NULL){
			CloseHandle(hMutex);
			hMutex=NULL;
			//已经加载过 直接退出
			return;
		}
	}

	g_Buffer	=	(unsigned char*)VirtualAlloc(0,1048576,MEM_COMMIT,PAGE_READWRITE);

	char strName[256];
	sprintf_s(strName,256,"HeapView%d",GetCurrentProcessId());
	HANDLE	hFileMapping	=	CreateFileMappingA(0,0,PAGE_READWRITE,0,1048576,strName);
	if(hFileMapping!=NULL){
		void*	pFilePtr	=	MapViewOfFile(hFileMapping,FILE_MAP_ALL_ACCESS,0,0,1048576);
		if(pFilePtr!=NULL){

			while(true){
				//MessageBoxA(0,"Sleep 1000\n",0,0);
				//OutputDebugStringA("Sleep 1000\n");
				WalkHeapBlock(g_Buffer);
				memcpy(pFilePtr,g_Buffer,1048576);
				Sleep(1000);
			}
			UnmapViewOfFile(pFilePtr);
		}
		CloseHandle(hFileMapping);
	}
	VirtualFree(g_Buffer,0,MEM_RELEASE);
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:{
		_beginthread(ThreadFunc,1048576,NULL);

							}break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

