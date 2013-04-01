// PEFile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <Windows.h>
#include <ImageHlp.h>
#include <dia2.h>

void ToLower(TCHAR* str){
#ifdef UNICODE
	int iLen=wcslen(str);
#else
	int iLen=strlen(str);
#endif
	static int iOffset = _T('A')-_T('a');
	for(int i=0;i<iLen;i++){
		if(str[i]>=_T('A') && str[i]<=_T('Z')){
			str[i]-=iOffset;
		}
	}
}

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

void	InitDia(){
	//	Initialize Appartment
	HRESULT hr = CoInitialize(NULL);
	_ASSERT( hr==S_OK );

	// Access the DIA provider


}

void	ReleaseDia(){
	//	Leave COM appartment
	CoUninitialize();
}


bool	GetPdbGUIDAge(const TCHAR*	strName,MODLOAD_PDBGUID_PDBAGE* pPdbAge){

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
	
	pSymbol->get_guid(&pPdbAge->PdbGuid);
	pSymbol->get_age(&pPdbAge->PdbAge);
	pSymbol->Release();
	
	pSession->Release();

	pIDiaDataSource->Release();
	pIDiaDataSource=NULL;
	
};

std::wstring strOutputDir;



void	AddToSymbolServer(const TCHAR* strOldName,const TCHAR* strFileName,const TCHAR* strVersion){
	std::wstring	strFileDirectory		=	strOutputDir+		+	_T("\\")		+	strFileName;
	std::wstring	strVersionDirectory		=	strFileDirectory	+	_T("\\")		+	strVersion	;
	std::wstring	strFile					=	strVersionDirectory	+	_T("\\")		+	strFileName;

	HANDLE pFile	=	CreateFile(strFile.c_str(),GENERIC_READ,FILE_SHARE_READ ,NULL,OPEN_EXISTING ,FILE_ATTRIBUTE_NORMAL ,NULL);
	if(pFile==INVALID_HANDLE_VALUE){
		CreateDirectory(strFileDirectory.c_str(),NULL);
		CreateDirectory(strVersionDirectory.c_str(),NULL);
		CopyFile(strOldName,strFile.c_str(),TRUE);
		wprintf(L"File=%s\n",strFile.c_str());
	}else{
		CloseHandle(pFile);
	}
}

void	FileCallBack(const TCHAR*	strFileName,const TCHAR* strPath){
	TCHAR strOldFileName[256];
	wcscpy(strOldFileName,strFileName);
	int iLen = wcslen(strOldFileName);
	ToLower(strOldFileName);
	if(iLen<5){
		return;
	}
	if(wcscmp(&strOldFileName[iLen-4],_T(".pdb"))==0)
	{
		wsprintf(strOldFileName,L"%s\\%s",strPath,strFileName);
		MODLOAD_PDBGUID_PDBAGE pdbGUIDAge;
		GetPdbGUIDAge(strOldFileName,&pdbGUIDAge);
		

		TCHAR	strGUID[64];
		wsprintf(strGUID,L"%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X%d",
			pdbGUIDAge.PdbGuid.Data1,
			pdbGUIDAge.PdbGuid.Data2,
			pdbGUIDAge.PdbGuid.Data3,
			pdbGUIDAge.PdbGuid.Data4[0],
			pdbGUIDAge.PdbGuid.Data4[1],
			pdbGUIDAge.PdbGuid.Data4[2],
			pdbGUIDAge.PdbGuid.Data4[3],
			pdbGUIDAge.PdbGuid.Data4[4],
			pdbGUIDAge.PdbGuid.Data4[5],
			pdbGUIDAge.PdbGuid.Data4[6],
			pdbGUIDAge.PdbGuid.Data4[7],
			pdbGUIDAge.PdbAge);

		AddToSymbolServer(strOldFileName,strFileName,strGUID);

	}
	else	if(wcscmp(&strOldFileName[iLen-4],_T(".dll"))==0	||	wcscmp(&strOldFileName[iLen-4],_T(".exe"))==0)
	{
		wsprintf(strOldFileName,L"%s\\%s",strPath,strFileName);
		PEFile file(strOldFileName);

		AddToSymbolServer(strOldFileName,strFileName,file.uniqueName.c_str());
	}
};
void	Search(const std::wstring& strPath){

	std::wstring strSearchPath=strPath+L"\\*.*";
	WIN32_FIND_DATA fileData;
	HANDLE hFile	=	FindFirstFile(strSearchPath.c_str(),&fileData);
	while(hFile!=INVALID_HANDLE_VALUE){
		if(	wcscmp(fileData.cFileName,_T("."))	!=0	&&
			wcscmp(fileData.cFileName,_T(".."))	!=0)
		{
			if(fileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY){
				
				std::wstring strNewPath =strPath+L"\\"+fileData.cFileName;
				
				Search(strNewPath);
			}else{
				FileCallBack(fileData.cFileName,strPath.c_str());
			}
		}

		BOOL b	=	FindNextFile(hFile,&fileData);
		if(!b){
			break;
		}
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	if(argc<2){
		wprintf(L"SymbolServer InputDir OutputDir\n");
		getchar();
		return -1;
	}
	if(argc < 3){
		strOutputDir=_T(".\\SymbolServer\\");
		CreateDirectory(strOutputDir.c_str(),NULL);
	}else{
		strOutputDir	=	argv[2];
		CreateDirectory(strOutputDir.c_str(),NULL);
	}
	

	InitDia();

	Search(argv[1]);

	ReleaseDia();
	return 0;
}

