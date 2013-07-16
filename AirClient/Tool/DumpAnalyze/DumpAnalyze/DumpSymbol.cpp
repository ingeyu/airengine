#include "stdafx.h"
#include "DumpSymbol.h"
#include "Dia2.h"
namespace	Dump{


	BinaryFile::BinaryFile()
	{
		m_Base	=	0x00400000;
		m_pBuffer	=	NULL;
		m_uiSize=0;
	}

	BinaryFile::~BinaryFile()
	{
		//Close();
		if(m_pBuffer!=NULL){
			free(m_pBuffer);
			m_pBuffer=NULL;
		}
		m_uiSize=0;
	}

	U1 BinaryFile::Open( const std::wstring& strName,DWORD timeStamp )
	{
		if(strName.empty())
			return false;

		if(LoadFile(strName.c_str(),m_pBuffer,m_uiSize)){

			U8* pData = (U8*)m_pBuffer;
			if(pData[0]==0X4D&&pData[1]==0X5A){

			}
			IMAGE_DOS_HEADER* dosHeader=(IMAGE_DOS_HEADER*)pData;
			pData	+=	dosHeader->e_lfanew;//sizeof(IMAGE_DOS_HEADER);


			IMAGE_NT_HEADERS* ntHeader=(IMAGE_NT_HEADERS*)pData;
			if(ntHeader->FileHeader.TimeDateStamp == timeStamp){
				m_strName	=	strName;
				return true;
			}else{
				free(m_pBuffer);
				m_pBuffer=NULL;
				m_uiSize=0;
			}
		}
		return false;
	}

	U1 BinaryFile::Close()
	{
		if(m_pBuffer!=NULL){
			free(m_pBuffer);
			m_pBuffer=NULL;
		}
		m_uiSize=0;
		m_strName.clear();
		return true;
	}

	void* BinaryFile::GetOffset(U32 uiOffset)
	{
		//return (U8*)m_pBuffer	+	uiOffset;
		DWORD uiFileOffset	=	AddressConvert(uiOffset,FALSE);
		if(uiFileOffset==0)
			return NULL;
		return (U8*)m_pBuffer	+	(uiFileOffset);
	}
	
	/*
	Purpose:PE文件的内存偏移与文件偏移相互转换,不考虑系统为对齐填充偏移转换
	szFileName:文件名
	dwAddr:需要转换的偏移值
	bFile2RVA:是否是文件偏移到内存偏移的转换，1 - dwAddr代表的是文件偏移，此函数返回内存偏移
		0 - dwAddr代表的是内存偏移，此函数返回文件偏移
	返回值：相对应的偏移值,失败返回-1
	*/

	DWORD BinaryFile::AddressConvert( DWORD dwAddr, BOOL bFile2RVA)
	{
		DWORD	dwRet=0;
		U8*	lpBase	=	(U8*)m_pBuffer;
		//2.读取该文件的信息（文件内存对齐方式以及区块数量，并将区块表指针指向区块表第一个区块头）
		 PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBase;
		 PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)((unsigned long)lpBase + pDosHeader->e_lfanew);
 
		 DWORD dwMemAlign = pNtHeader->OptionalHeader.SectionAlignment;
		 DWORD dwFileAlign = pNtHeader->OptionalHeader.FileAlignment;
		 int dwSecNum = pNtHeader->FileHeader.NumberOfSections;
		 PIMAGE_SECTION_HEADER pSecHeader = (PIMAGE_SECTION_HEADER)((char *)lpBase + pDosHeader->e_lfanew + sizeof(IMAGE_NT_HEADERS));
		 DWORD dwHeaderSize = 0;
 
		 if(!bFile2RVA)  // 内存偏移转换为文件偏移
		 { 
		  //看需要转移的偏移是否在PE头内，如果在则两个偏移相同
		  dwHeaderSize = pNtHeader->OptionalHeader.SizeOfHeaders;
		  if(dwAddr <= dwHeaderSize)
		  {
		   delete lpBase;
		   lpBase = NULL;
		   return dwAddr;
		  }
		  else //不再PE头里，查看该地址在哪个区块中
		  {
		   for(int i = 0; i < dwSecNum; i++)
		   {
			DWORD dwSecSize = pSecHeader[i].Misc.VirtualSize;
			if((dwAddr >= pSecHeader[i].VirtualAddress) && (dwAddr <= pSecHeader[i].VirtualAddress + dwSecSize))
			{
			 //3.找到该该偏移，则文件偏移 = 该区块的文件偏移 + （该偏移 - 该区块的内存偏移）
			 dwRet = pSecHeader[i].PointerToRawData + dwAddr - pSecHeader[i].VirtualAddress;
			}
		   }
		  }
		 }
		 else // 文件偏移转换为内存偏移
		 {
		  dwHeaderSize = pNtHeader->OptionalHeader.SizeOfHeaders;
		  //看需要转移的偏移是否在PE头内，如果在则两个偏移相同
		  if(dwAddr <= dwHeaderSize)
		  {
		   delete lpBase;
		   lpBase = NULL;
		   return dwAddr;
		  }
		  else//不再PE头里，查看该地址在哪个区块中
		  {
		   for(int i = 0; i < dwSecNum; i++)
		   {
			DWORD dwSecSize = pSecHeader[i].Misc.VirtualSize;
			if((dwAddr >= pSecHeader[i].PointerToRawData) && (dwAddr <= pSecHeader[i].PointerToRawData + dwSecSize))
			{
			 //3.找到该该偏移，则内存偏移 = 该区块的内存偏移 + （该偏移 - 该区块的文件偏移）
			 dwRet = pSecHeader[i].VirtualAddress + dwAddr - pSecHeader[i].PointerToRawData;
			}
		   }
		  }
		 }
 
		 return dwRet;
	}

	SymbolFile::SymbolFile()
	{
		pIDiaDataSource	=	NULL;
		pSession		=	NULL;
		pSymbol			=	NULL;
	}

	U1 SymbolFile::Open( const std::wstring& strName,GUID guid,DWORD age )
	{
		if(strName.empty())
			return false;
		HRESULT		hr = CoCreateInstance(__uuidof(DiaSource), 
			NULL, CLSCTX_INPROC_SERVER, 
			__uuidof(IDiaDataSource), 
			(void**)&pIDiaDataSource);
		if(pIDiaDataSource==NULL){
			Close();
			return false;
		}

		hr	=	pIDiaDataSource->loadDataFromPdb((strName).c_str());
		pIDiaDataSource->openSession(&pSession);
		if(pSession==NULL){
			Close();
			return false;
		}
		m_strName	=	strName;
		return true;
	}

	U1 SymbolFile::Close()
	{
		if(pSymbol){
			pSymbol->Release();
			pSymbol=NULL;
		}
		if(pSession){
			pSession->Release();
			pSession=NULL;
		}
		if(pIDiaDataSource){
			pIDiaDataSource->Release();
			pIDiaDataSource=NULL;
		}
		m_strName.clear();
		return true;
	}

	U1 SymbolFile::GetFunction_File_Line( U32 uiOffset,std::wstring& strFunc,std::wstring& strFile,DWORD& line )
	{
		pSession->findSymbolByRVA(uiOffset,SymTagNull,&pSymbol);
		if(pSymbol==NULL){
			strFile	=	L"NoFile";
			line	=	0;
		}else{
			DWORD tag;
			pSymbol->get_symTag( &tag );
			if(tag == SymTagFunction){
				IDiaEnumLineNumbers* pEnumLine=NULL;
				pSession->findLinesByRVA(uiOffset,1,&pEnumLine);
				if(pEnumLine!=NULL){

					IDiaLineNumber* pLine=NULL;
					DWORD celt;
					bool firstLine = true;
					while ( ( pEnumLine->Next( 1, &pLine, &celt )>=0 ) && celt == 1 ){
						IDiaSourceFile* pFile=NULL;
						pLine->get_sourceFile(&pFile);
						if(pFile!=NULL){
							BSTR filename;
							pFile->get_fileName(&filename);
							strFile	=	filename;
							SysFreeString(filename);
							pFile->Release();
							pFile=NULL;
						}
						pLine->get_lineNumber( &line );
						pLine->Release();
						pLine=NULL;
						break;
					}
					pEnumLine->Release();
					pEnumLine=NULL;
				}


				BSTR name;
				pSymbol->get_name( &name );
				strFunc	=	name;
				SysFreeString(name);
			
			}
			pSymbol->Release();
			pSymbol=NULL;
		}
		return true;
	}


	FileManager::FileManager()
	{

	}

	U1 FileManager::Initialization()
	{
		printf("[SearchPath:]\n");
		m_lstSearchPath.push_back(L"");
		void*	pData	=	NULL;
		U32		uiSize	=	0;
		if(LoadFile(L"SymbolPath.txt",pData,uiSize)){

			char* strContent	=	(char*)pData;
			{
				unsigned int size = uiSize;//strContent.size();
				int iStart = 0,iEnd = 0;

				for(unsigned int i=0;i<=size;i++,iEnd++){
					char s = strContent[iEnd];
					if(iEnd == size || strContent[iEnd] == 0x0A){
						int iCopyCount = iEnd - iStart - 1;
						if(strContent[iEnd-1]!=0x0D)
							iCopyCount++;
						if(iCopyCount<=0){
							iStart = iEnd + 1;
							continue;				
						}


						std::string tempStr;
						tempStr.resize(iCopyCount);
						memcpy(&tempStr[0],&strContent[iStart],iCopyCount);
						iStart = iEnd + 1;
						AddPath(Acsi2WideByte(tempStr).c_str());
						printf(tempStr.c_str());
						printf("\n");
					}
				}

				
			}

			free(pData);
			pData=NULL;
		}
		return true;
	}

	U1 FileManager::Release()
	{
		std::tr1::unordered_map<std::wstring,BinaryFile*>::iterator	i	=	m_mapBinaryFile.begin();
		for(;i!=m_mapBinaryFile.end();i++){
			BinaryFile* p = i->second;
			SAFE_DELETE(p);
		}
		m_mapBinaryFile.clear();
		std::tr1::unordered_map<std::wstring,SymbolFile*>::iterator	itr	=	m_mapSymbolFile.begin();
		for(;itr!=m_mapSymbolFile.end();itr++){
			SymbolFile* p = itr->second;
			SAFE_DELETE(p);
		}
		m_mapSymbolFile.clear();
		m_lstSearchPath.clear();
		return true;
	}

	U1 FileManager::AddPath( const wchar_t* strPath )
	{
		if(strPath==NULL)
			return false;
		std::wstring str = strPath;

		if(str.empty())
			return false;
		U32 uiSize = str.size();
		if(strPath[uiSize-1]!=L'\\'&&strPath[uiSize]!=L'/'){
			str+=L"\\";
		}
		m_lstSearchPath.push_back(str);
		return true;
	}

	BinaryFile* FileManager::AddModuleFile( const wchar_t* strName,DWORD timeStamp ,DWORD imageSize)
	{
		if(strName==NULL)
			return false;
		if(wcslen(strName)==0)
			return false;

		std::wstring strPath;
		std::wstring strFileName;
		std::wstring strExt;
		SplitFilePath(strName,&strPath,&strFileName,&strExt);
		strFileName	+=	(L"."+strExt);

		wchar_t strFullName[1024];
		wsprintf(strFullName,L"%s\\%08x%x\\%s",strFileName.c_str(),timeStamp,imageSize,strFileName.c_str());

		std::tr1::unordered_map<std::wstring,BinaryFile*>::iterator	itr	=	m_mapBinaryFile.find(strFullName);
		if(itr!=m_mapBinaryFile.end()){
			return itr->second;
		}

		BinaryFile* pFile = new BinaryFile;
		std::list<std::wstring>::iterator i = m_lstSearchPath.begin();
		for(;i!=m_lstSearchPath.end();i++){
			std::wstring str = (*i)	+	strFileName;
			DWORD	dwAttr = GetFileAttributes(str.c_str());
			if(dwAttr == INVALID_FILE_ATTRIBUTES){
				continue;
			}
			if(dwAttr&FILE_ATTRIBUTE_DIRECTORY){
				str	=	(*i)+strFullName;
			}
			if(pFile->Open(str,timeStamp)){
				m_mapBinaryFile[strFullName]	=	pFile;
				return pFile;
			}
		}
		SAFE_DELETE(pFile);
		return NULL;
	}

	SymbolFile* FileManager::AddSymbolFile( const wchar_t* strName,GUID guid,DWORD age )
	{
		if(strName==NULL)
			return false;
		if(wcslen(strName)==0)
			return false;

		std::wstring strPath;
		std::wstring strFileName;
		std::wstring strExt;
		SplitFilePath(strName,&strPath,&strFileName,&strExt);
		strFileName	+=	(L"."+strExt);

		wchar_t strFullName[1024];
		wsprintf(strFullName,L"%s\\%08x%04x%04x%02x%02x%02x%02x%02x%02x%02x%02x%d\\%s",
			strFileName.c_str(),
			guid.Data1,
			guid.Data2,
			guid.Data3,
			guid.Data4[0],
			guid.Data4[1],
			guid.Data4[2],
			guid.Data4[3],
			guid.Data4[4],
			guid.Data4[5],
			guid.Data4[6],
			guid.Data4[7],
			age,
			strFileName.c_str());

		std::tr1::unordered_map<std::wstring,SymbolFile*>::iterator	itr	=	m_mapSymbolFile.find(strFullName);
		if(itr!=m_mapSymbolFile.end()){
			return itr->second;
		}
		SymbolFile* pFile = new SymbolFile;
		std::list<std::wstring>::iterator i = m_lstSearchPath.begin();
		for(;i!=m_lstSearchPath.end();i++){
			std::wstring str = (*i)	+	strFileName;
			DWORD	dwAttr = GetFileAttributes(str.c_str());
			if(dwAttr == INVALID_FILE_ATTRIBUTES){
				continue;
			}
			if(dwAttr&FILE_ATTRIBUTE_DIRECTORY){
				str	=	(*i)+strFullName;
			}
			if(pFile->Open(str,guid,age)){
				m_mapSymbolFile[strFullName]	=	pFile;
				return pFile;
			}
		}
		SAFE_DELETE(pFile);
		return NULL;
	}

}