#include "stdafx.h"
#include "DumpSymbol.h"

namespace	Dump{


	BinaryFile::BinaryFile()
	{

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

	U1 BinaryFile::Open( const std::wstring& strName )
	{
		if(strName.empty())
			return false;

		if(LoadFile(strName.c_str(),m_pBuffer,m_uiSize)){
			m_strName	=	strName;
			return true;
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

	void* BinaryFile::GetOffset(U32 uiOffset) const
	{
		return (U8*)m_pBuffer	+	uiOffset;
	}


	SymbolFile::SymbolFile()
	{

	}


	FileManager::FileManager()
	{

	}

	U1 FileManager::Initialization()
	{
		m_lstSearchPath.push_back(L"");
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

	BinaryFile* FileManager::AddModuleFile( const wchar_t* strName )
	{
		if(strName==NULL)
			return false;
		if(wcslen(strName)==0)
			return false;

		std::tr1::unordered_map<std::wstring,BinaryFile*>::iterator	itr	=	m_mapBinaryFile.find(strName);
		if(itr!=m_mapBinaryFile.end()){
			return itr->second;
		}

		BinaryFile* pFile = new BinaryFile;
		std::list<std::wstring>::iterator i = m_lstSearchPath.begin();
		for(;i!=m_lstSearchPath.end();i++){
			std::wstring str = (*i)	+	strName;
			if(pFile->Open(str)){
				m_mapBinaryFile[strName]	=	pFile;
				return pFile;
			}
		}
		SAFE_DELETE(pFile);
		return NULL;
	}

	SymbolFile* FileManager::AddSymbolFile( const wchar_t* strName )
	{
		if(strName==NULL)
			return false;
		if(wcslen(strName)==0)
			return false;

		std::tr1::unordered_map<std::wstring,SymbolFile*>::iterator	itr	=	m_mapSymbolFile.find(strName);
		if(itr!=m_mapSymbolFile.end()){
			return itr->second;
		}
		SymbolFile* pFile = new SymbolFile;
		std::list<std::wstring>::iterator i = m_lstSearchPath.begin();
		for(;i!=m_lstSearchPath.end();i++){
			std::wstring str = (*i)	+	strName;
			if(pFile->Open(str)){
				m_mapSymbolFile[strName]	=	pFile;
				return pFile;
			}
		}
		SAFE_DELETE(pFile);
		return NULL;
	}

}