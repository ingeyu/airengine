// ttt.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <ImageHlp.h>
#include <dia2.h>
#include <string>
/*
对于VS2005，经过反复测试，其PDB签名生成的规则如下：


	（1）如果增量编译，并且编译前对应的pdb文件存在，则不修改GUID，每次Age数值增1。


	（2）如果增量编译，但编译前pdb不存在，则重新生成新GUID，并重置Age为1。


	（3）如果是全量编译，无论编译前是否存在pdb，都重新生成新GUID，并重置Age为2。
*/

struct PDB_INFO{
	DWORD	PdbTimeStamp;
	DWORD   PdbAge;                 // Pdb Age 
	GUID    PdbGuid;                // Pdb Guid 
};
struct PDBINFO{
	DWORD						unknown;
	MODLOAD_PDBGUID_PDBAGE		pdbage;
	char						pdbName[128];
};
class PEFile{
public:
	PEFile(const TCHAR* strName){
		pBase		=	NULL;
		uiSize		=	0;
#ifdef UNICODE
		wcscpy(strFileName,strName);
#else
		strcpy(strFileName,strName);
#endif
		Load();
	};
	~PEFile(){
		if(pBase!=NULL){
			free(pBase);
			pBase=0;
		}
		uiSize=0;
	}
	bool	Load(){
		HANDLE pFile	=	CreateFile(strFileName,GENERIC_READ,FILE_SHARE_READ ,NULL,OPEN_EXISTING ,FILE_ATTRIBUTE_NORMAL ,NULL);//,"rb");
		if(pFile!=INVALID_HANDLE_VALUE){
			//SetEndOfFile(pFile);
			uiSize	=	GetFileSize(pFile,0);
			//SetFilePointer(pFile)

			pBase	=	(unsigned char*)malloc(uiSize);
			DWORD uiRead=0;
			while(uiRead	<	uiSize){
				ReadFile(pFile,&pBase[uiRead],uiSize-uiRead,&uiRead,NULL);
			}
			CloseHandle(pFile);
			return Read();
		}else{
			return false;
		}

		return true;
	};
	PIMAGE_SECTION_HEADER GetSectionHeader(PSTR name)
	{
		PIMAGE_SECTION_HEADER section = sectionHeader;//IMAGE_FIRST_SECTION(pNTHeader);
		unsigned i;

		for ( i=0; i < ntHeader->FileHeader.NumberOfSections; i++, section++ )
		{
			if ( 0 == strncmp((char *)section->Name,name,IMAGE_SIZEOF_SHORT_NAME) )
				return section;
		}

		return 0;
	};
	PIMAGE_SECTION_HEADER GetEnclosingSectionHeader(DWORD rva)
	{
		PIMAGE_SECTION_HEADER section = sectionHeader;//IMAGE_FIRST_SECTION(pNTHeader);
		unsigned i;

		for ( i=0; i < ntHeader->FileHeader.NumberOfSections; i++, section++ )
		{
			// Is the RVA within this section?
			if ( (rva >= section->VirtualAddress) && 
				(rva < (section->VirtualAddress + section->Misc.VirtualSize)))
				return section;
		}

		return 0;
	}
	bool	Read(){
		unsigned char* pData = pBase;
		if(pData[0]==0X4D&&pData[1]==0X5A){

		}
		dosHeader=(IMAGE_DOS_HEADER*)pData;
		pData	+=	dosHeader->e_lfanew;//sizeof(IMAGE_DOS_HEADER);


		ntHeader=(IMAGE_NT_HEADERS*)pData;
		pData+=sizeof(IMAGE_NT_HEADERS);//-sizeof(IMAGE_OPTIONAL_HEADER)+ntHeader->FileHeader.SizeOfOptionalHeader;

		//int iBack = (16-file.OptionalHeader.NumberOfRvaAndSizes)*sizeof(IMAGE_DATA_DIRECTORY);
		//pData-=iBack;

		sectionHeader=(IMAGE_SECTION_HEADER*)pData;
		pData+=(ntHeader->FileHeader.NumberOfSections)*sizeof(IMAGE_SECTION_HEADER);
		{
			TCHAR strUniqueName[256];
			wsprintf(strUniqueName,L"%08X%X",ntHeader->FileHeader.TimeDateStamp,ntHeader->OptionalHeader.SizeOfImage);
			uniqueName	=	strUniqueName;
		}


		PIMAGE_SECTION_HEADER header;
		DWORD va_debug_dir;
		DWORD size;
		IMAGE_DATA_DIRECTORY& data	=	ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG];

		va_debug_dir = data.VirtualAddress;

		if ( va_debug_dir == 0 )
			return false;

		// If we found a .debug section, and the debug directory is at the
		// beginning of this section, it looks like a Borland file
		header = GetSectionHeader(".debug");
		if(header==NULL){
			header = GetSectionHeader(".rsrc");
		}

		if ( header && (header->VirtualAddress == va_debug_dir) )
		{
			debugDir = (PIMAGE_DEBUG_DIRECTORY)(pBase+header->PointerToRawData);
			size = data.Size* sizeof(IMAGE_DEBUG_DIRECTORY);
		}
		else    // Look for the debug directory
		{
			header = GetEnclosingSectionHeader( va_debug_dir );
			if ( !header )
				return false;

			size = data.Size;

			debugDir = debugDir = (PIMAGE_DEBUG_DIRECTORY)(pBase+DWORD(header->PointerToRawData+va_debug_dir - header->VirtualAddress));
		}

		switch( debugDir->Type )
		{
		case IMAGE_DEBUG_TYPE_COFF:
			COFFHeader	=	(PIMAGE_COFF_SYMBOLS_HEADER)(pBase+ debugDir->PointerToRawData);
			break;

		case IMAGE_DEBUG_TYPE_MISC:
			debugMisc	=	(PIMAGE_DEBUG_MISC)(pBase + debugDir->PointerToRawData);
			break;

		case IMAGE_DEBUG_TYPE_CODEVIEW:
			pdbInfo		=	(PDBINFO*)(pBase + debugDir->PointerToRawData);
			break;
		}

		return true;
	}

	TCHAR			strFileName[256];
	std::string		symbolName;
	std::wstring	uniqueName;
	unsigned char*	pBase;
	DWORD			uiSize;
	IMAGE_DOS_HEADER*		dosHeader;
	IMAGE_NT_HEADERS*		ntHeader;
	IMAGE_SECTION_HEADER*	sectionHeader;
	IMAGE_DEBUG_DIRECTORY*	debugDir;
	IMAGE_DEBUG_MISC*		debugMisc;
	IMAGE_COFF_SYMBOLS_HEADER*	COFFHeader;
	PDBINFO*				pdbInfo;

};


static bool bRecord	=	false;
DWORD	uiOffset	=	0;
typedef DWORD
	(WINAPI
	*T_SetFilePointer)(
	__in        HANDLE hFile,
	__in        LONG lDistanceToMove,
	__inout_opt PLONG lpDistanceToMoveHigh,
	__in        DWORD dwMoveMethod
	);
T_SetFilePointer	pOldSetFilePointer	=	(T_SetFilePointer)NULL;
typedef	BOOL
	(WINAPI
	*T_ReadFile)(
	__in        HANDLE hFile,
	__out_bcount_part_opt(nNumberOfBytesToRead, *lpNumberOfBytesRead) __out_data_source(FILE) LPVOID lpBuffer,
	__in        DWORD nNumberOfBytesToRead,
	__out_opt   LPDWORD lpNumberOfBytesRead,
	__inout_opt LPOVERLAPPED lpOverlapped
	);
T_ReadFile	pOldReadFile	=	(T_ReadFile)NULL;
DWORD
	WINAPI
	EX_SetFilePointer(
	__in        HANDLE hFile,
	__in        LONG lDistanceToMove,
	__inout_opt PLONG lpDistanceToMoveHigh,
	__in        DWORD dwMoveMethod
	)
{
	if(!bRecord&&pOldSetFilePointer!=NULL){
		return (*pOldSetFilePointer)(hFile,lDistanceToMove,lpDistanceToMoveHigh,dwMoveMethod);
	}
	switch(dwMoveMethod){
		case FILE_BEGIN:{
			uiOffset	=	lDistanceToMove;
						}break;
		case FILE_CURRENT:{
			uiOffset	+=	lDistanceToMove;
						}break;
		case FILE_END:{
			uiOffset	=	GetFileSize(hFile,0);
			uiOffset	+=	lDistanceToMove;
						}break;
	}
	
	return (*pOldSetFilePointer)(hFile,lDistanceToMove,lpDistanceToMoveHigh,dwMoveMethod);
};
T_SetFilePointer	pNewSetFilePointer	=	(T_SetFilePointer)EX_SetFilePointer;
BOOL
	WINAPI
	EX_ReadFile(
	__in        HANDLE hFile,
	__out_bcount_part_opt(nNumberOfBytesToRead, *lpNumberOfBytesRead) __out_data_source(FILE) LPVOID lpBuffer,
	__in        DWORD nNumberOfBytesToRead,
	__out_opt   LPDWORD lpNumberOfBytesRead,
	__inout_opt LPOVERLAPPED lpOverlapped
	)
{
	if(!bRecord&&pOldReadFile!=NULL){
		return (*pOldReadFile)(hFile,lpBuffer,nNumberOfBytesToRead,lpNumberOfBytesRead,lpOverlapped);
	}
	if(nNumberOfBytesToRead==0x40){
		bRecord	=	false;
	}
	return (*pOldReadFile)(hFile,lpBuffer,nNumberOfBytesToRead,lpNumberOfBytesRead,lpOverlapped);
};

T_ReadFile	pNewReadFile	=	(T_ReadFile)EX_ReadFile;


bool	GetPdbGUIDAge(const TCHAR*	strName,PDB_INFO* pPDBInfo){
	bRecord	=	true;
	IDiaDataSource* pIDiaDataSource = NULL;

	HRESULT		hr = CoCreateInstance(__uuidof(DiaSource), 
		NULL, CLSCTX_INPROC_SERVER, 
		__uuidof(IDiaDataSource), 
		(void**)&pIDiaDataSource);

	hr	=	pIDiaDataSource->loadDataFromPdb(strName);
	IDiaSession* pSession=NULL;
	pIDiaDataSource->openSession(&pSession);
	if(pSession==NULL){
		return false;
	}

	IDiaSymbol*	pSymbol=NULL;
	pSession->get_globalScope(&pSymbol);
	if(pSymbol==NULL)
	{
		pSession->Release();
		return false;
	}
	pSymbol->get_timeStamp(&pPDBInfo->PdbTimeStamp);
	pSymbol->get_guid(&pPDBInfo->PdbGuid);
	pSymbol->get_age(&pPDBInfo->PdbAge);
	pSymbol->Release();

	pSession->Release();

	pIDiaDataSource->Release();
	pIDiaDataSource=NULL;
	bRecord	=	false;
	return true;
};

void ViewEXE(const TCHAR* strExe){
	PEFile	file(strExe);
	if(file.Load()){
		PDB_INFO info;
		info.PdbTimeStamp	=	file.ntHeader->FileHeader.TimeDateStamp;
		info.PdbAge			=	file.pdbInfo->pdbage.PdbAge;
		info.PdbGuid		=	file.pdbInfo->pdbage.PdbGuid;
		wprintf(L"PE\n");
		wprintf(L"Name=%s\n",strExe);
		wprintf(L"TimeStamp=%08x\n",info.PdbTimeStamp);
		wprintf(L"Age=%08x\n",info.PdbAge);
		wprintf(L"GUID=%08X-%04X-%04X-%02X%02X%02X%02X%02X%02X%02X%02X\n",
			info.PdbGuid.Data1,
			info.PdbGuid.Data2,
			info.PdbGuid.Data3,
			info.PdbGuid.Data4[0],
			info.PdbGuid.Data4[1],
			info.PdbGuid.Data4[2],
			info.PdbGuid.Data4[3],
			info.PdbGuid.Data4[4],
			info.PdbGuid.Data4[5],
			info.PdbGuid.Data4[6],
			info.PdbGuid.Data4[7]);
	}else{
		wprintf(L"load exe file failed!\n");
	}
}

void ViewPDB(const TCHAR* strPDB){
	PDB_INFO info;
	if(GetPdbGUIDAge(strPDB,&info)){
		//TCHAR	strGUID[64];
		wprintf(L"PDB\n");
		wprintf(L"Name=%s\n",strPDB);
		wprintf(L"TimeStamp=%08x\n",info.PdbTimeStamp);
		wprintf(L"Age=%08x\n",info.PdbAge);
		wprintf(L"GUID=%08X-%04X-%04X-%02X%02X%02X%02X%02X%02X%02X%02X\n",
			info.PdbGuid.Data1,
			info.PdbGuid.Data2,
			info.PdbGuid.Data3,
			info.PdbGuid.Data4[0],
			info.PdbGuid.Data4[1],
			info.PdbGuid.Data4[2],
			info.PdbGuid.Data4[3],
			info.PdbGuid.Data4[4],
			info.PdbGuid.Data4[5],
			info.PdbGuid.Data4[6],
			info.PdbGuid.Data4[7]);
		wprintf(L"AgeOffset=%08x\n",uiOffset);


	}else{
		printf("load pdb file failed!\n");
	}
}

unsigned char* MemoryCompare(unsigned char* pDest,unsigned int uiSize,unsigned char* pSrc,unsigned int uiSrcSize)
{
	for(unsigned int i=0;i<uiSize	-	uiSrcSize;i++){
		unsigned int uiMatchCount=0;
		for(unsigned int j=0;j<uiSrcSize;j++)
		{
			if(pDest[i+j] != pSrc[j]){
				break;
			}else{
				uiMatchCount++;
			}
		}
		if(uiMatchCount==uiSrcSize){
			return &pDest[i];
		}
	}
	return NULL;
}

bool	ModifyPDB(const TCHAR* strPDB,PDB_INFO* pInfo)
{
	PDB_INFO oldInfo;
	if(!GetPdbGUIDAge(strPDB,&oldInfo)){
		printf("load pdb file failed!\n");
		return false;
	}else{
		std::wstring strBakFile	=	strPDB;
		strBakFile	+=	L".bak";
		CopyFile(strPDB,strBakFile.c_str(),FALSE);
		wprintf(L"backup pdb file!\n");
		HANDLE hFile =  CreateFile(
			strPDB,
			GENERIC_READ |GENERIC_WRITE ,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL );
		if(hFile!=NULL){
			DWORD uiSize	=	GetFileSize(hFile,0);
			if(uiSize	>0	&&uiSize	<	2048*1048576){
				unsigned char* pData	=	(unsigned char*)malloc(uiSize);
				if(pData!=NULL){
					DWORD uiRead=0;
					ReadFile(hFile,pData,uiSize,&uiRead,NULL);
					//修改 第一个 GUID AGE
					unsigned char* pModify = MemoryCompare(pData,uiSize,(unsigned char*)&oldInfo.PdbGuid,sizeof(GUID));
					if(pModify!=NULL){
						pModify-=8;
						memcpy(pModify,&pInfo->PdbTimeStamp,sizeof(DWORD));pModify+=sizeof(DWORD);
						memcpy(pModify,&pInfo->PdbAge,sizeof(DWORD));pModify+=sizeof(DWORD);
						memcpy(pModify,&pInfo->PdbGuid,sizeof(GUID));pModify+=sizeof(GUID);
						wprintf(L"write first guid and age!\n");
						//修改 第二个 GUID AGE
						DWORD uiNewSize	=	uiSize-(pModify-pData);
						pModify = MemoryCompare(pData,uiSize,(unsigned char*)&oldInfo.PdbGuid,sizeof(GUID));
						if(pModify!=NULL){
							pModify-=8;
							memcpy(pModify,&pInfo->PdbTimeStamp,sizeof(DWORD));pModify+=sizeof(DWORD);
							memcpy(pModify,&pInfo->PdbAge,sizeof(DWORD));pModify+=sizeof(DWORD);
							memcpy(pModify,&pInfo->PdbGuid,sizeof(GUID));pModify+=sizeof(GUID);
							wprintf(L"write second guid and age!\n");
						}
					}
					//修改 第三个 AGE
					unsigned char* pModifyAge =MemoryCompare(&pData[uiOffset],0x40,(unsigned char*)&oldInfo.PdbAge,sizeof(DWORD));
					if(pModify!=NULL){
						memcpy(pModifyAge,&pInfo->PdbAge,sizeof(DWORD));
						wprintf(L"write third age!\n");
					}

					SetFilePointer(hFile,0,0,FILE_BEGIN);
					DWORD uiWrite=0;
					WriteFile(hFile,pData,uiSize,&uiWrite,NULL);
					wprintf(L"save pdb file!\n");
					free(pData);
				}else{
					wprintf(L"alloc memory failed!\n");
				}
			}else{
				wprintf(L"pdb file size is too large!\n");
			}

			CloseHandle(hFile);
		}
		wprintf(L"pdb file save finished!\n");
	}
	return true;
}

void _tmain(int argc, _TCHAR* argv[])
{
	HRESULT hr= S_OK;
	HMODULE hKernel	=	GetModuleHandle(L"kernel32.dll");
	pOldSetFilePointer	=	(T_SetFilePointer)GetProcAddress(hKernel,"SetFilePointer");
	pOldReadFile		=	(T_ReadFile)GetProcAddress(hKernel,"ReadFile");
	unsigned char* p	=	(unsigned char*)VirtualAlloc(NULL,4096,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
	DWORD TempProtectFlag2=0;
	hr	=	VirtualProtect(p,4096,PAGE_READWRITE|PAGE_EXECUTE_READWRITE,&TempProtectFlag2);
	memset(p,0x90,4096);

	memcpy(p,pOldSetFilePointer,5);
	DWORD iSFPOffset	=	(DWORD)pOldSetFilePointer-(DWORD)p-5;
	p[5]=0xE9;
	memcpy(&p[6],&iSFPOffset,sizeof(DWORD));
	memcpy(&p[20],pOldReadFile,7);
	DWORD iRFOffset		=	(DWORD)pOldReadFile-(DWORD)&p[20]-5;
	p[27]=0xE9;
	memcpy(&p[28],&iRFOffset,sizeof(DWORD));
	
	DWORD ProtectFlag=0;
	hr	=	VirtualProtect(pOldSetFilePointer,5,PAGE_READWRITE|PAGE_EXECUTE_READWRITE,&ProtectFlag);
	DWORD ProtectFlag2=0;
	hr	=	VirtualProtect(p,4096,TempProtectFlag2,&ProtectFlag2);
	hr	=	VirtualProtect(pOldReadFile,7,PAGE_READWRITE|PAGE_EXECUTE_READWRITE,&ProtectFlag2);

	unsigned char strCode[8];
	strCode[0]=0xE9;
	DWORD iExToOldSFP	=	(DWORD)pNewSetFilePointer	-	(DWORD)pOldSetFilePointer -5;
	memcpy(&strCode[1],&iExToOldSFP,sizeof(DWORD));
	WriteProcessMemory(GetCurrentProcess(),pOldSetFilePointer,strCode,5,NULL);

	DWORD iExToOldRF	=	(DWORD)pNewReadFile	-	(DWORD)pOldReadFile -5;
	memcpy(&strCode[1],&iExToOldRF,sizeof(DWORD));
	WriteProcessMemory(GetCurrentProcess(),pOldReadFile,strCode,5,NULL);


	hr	=	VirtualProtect(pOldSetFilePointer,5,ProtectFlag,&ProtectFlag2);
	hr	=	VirtualProtect(pOldReadFile,7,ProtectFlag,&ProtectFlag2);

	pOldSetFilePointer	=	(T_SetFilePointer)p;
	pOldReadFile		=	(T_ReadFile)&p[20];

	//ReadFile()
	

	hr = CoInitialize(NULL);
	//HANDLE h = CreateFile(L"D:\\AirEngine\\AirClient\\Tool\\SymbolServer\\Debug\\a\\ttt.pdb",GENERIC_READ ,FILE_SHARE_READ,NULL,OPEN_EXISTING ,FILE_FLAG_RANDOM_ACCESS ,NULL);
	//unsigned char str[0x40];
	//DWORD uiSize=0;
	//SetFilePointer(h,0x29400,0,FILE_BEGIN );
	//ReadFile(h,str,0x40,&uiSize,0);
	if(argc<2){
		wprintf(L"PDBMatcher pdbfile\n");
		wprintf(L"PDBMatcher exefile\n");
		wprintf(L"PDBMatcher pdbfile exefile\n");
		wprintf(L"PDBMatcher pdbfile guid age timestamp\n");
		getchar();
	}else	if(argc==2){
		int ilen = wcslen(argv[1]);
		if(ilen>3){
			TCHAR s[4]={
				argv[1][ilen-3],
				argv[1][ilen-2],
				argv[1][ilen-1],
				0
			};
			for(int i=0;i<3;i++){
				s[i]	=	tolower(s[i]);
			}
			if(wcscmp(s,L"pdb")==0){
				ViewPDB(argv[1]);
			}
			if(wcscmp(s,L"exe")==0){
				ViewEXE(argv[1]);
			}
			if(wcscmp(s,L"dll")==0){
				ViewEXE(argv[1]);
			}
		}else{
			wprintf(L"unknown file!\n");
		}

		
	}else if(argc==3){
		
		PEFile	file(argv[2]);
		if(file.Load()){
			PDB_INFO info;
			info.PdbTimeStamp	=	file.ntHeader->FileHeader.TimeDateStamp;
			info.PdbAge			=	file.pdbInfo->pdbage.PdbAge;
			info.PdbGuid		=	file.pdbInfo->pdbage.PdbGuid;
			ModifyPDB(argv[1],&info);
		}else{
			wprintf(L"load pefile failed!\n");
		}
		
	}else if(argc==5){
		PDB_INFO info;
		swscanf(argv[2],L"%08x-%04x-%04x-%02x%02x%02x%02x%02x%02x%02x%02x",
			&info.PdbGuid.Data1,
			&info.PdbGuid.Data2,
			&info.PdbGuid.Data3,
			&info.PdbGuid.Data4[0],
			&info.PdbGuid.Data4[1],
			&info.PdbGuid.Data4[2],
			&info.PdbGuid.Data4[3],
			&info.PdbGuid.Data4[4],
			&info.PdbGuid.Data4[5],
			&info.PdbGuid.Data4[6],
			&info.PdbGuid.Data4[7]);
		swscanf(argv[3],L"%d",&info.PdbAge);
		swscanf(argv[4],L"%08x",&info.PdbTimeStamp);
		ModifyPDB(argv[1],&info);
	}

	CoUninitialize();
	//getchar();
	return;
}

