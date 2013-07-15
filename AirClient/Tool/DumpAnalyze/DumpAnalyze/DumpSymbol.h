#ifndef DumpSymbol_h__
#define DumpSymbol_h__

namespace	Dump{

	class	BinaryFile{
	public:
		BinaryFile();
		virtual	~BinaryFile();

		virtual	U1		Open(const std::wstring& strName,DWORD timeStamp);
		virtual	U1		Close();
		virtual	void*	GetOffset(U32 uiOffset);
		void			SetBase(DWORD dwBase){
			m_Base	=	dwBase;
		}
		const std::wstring	GetName(){
			return m_strName;
		};
	protected:
		DWORD			AddressConvert( DWORD dwAddr, BOOL bFile2RVA);
	protected:
		std::wstring	m_strName;
		void*			m_pBuffer;
		U32				m_uiSize;
		DWORD			m_Base;
	};
	class	SymbolFile	:	public	BinaryFile{
	public:
		SymbolFile();
		
	};
	class	FileManager	:	public	Singleton<FileManager>{
	public:
		FileManager();

		U1			Initialization();
		U1			Release();

		U1			AddPath(const wchar_t* strPath);
		BinaryFile*	AddModuleFile(const wchar_t* strName,DWORD timeStamp,DWORD imageSize);
		SymbolFile*	AddSymbolFile(const wchar_t* strName,GUID guid,DWORD age);
	protected:
		std::list<std::wstring>								m_lstSearchPath;
		std::tr1::unordered_map<std::wstring,SymbolFile*>	m_mapSymbolFile;
		std::tr1::unordered_map<std::wstring,BinaryFile*>	m_mapBinaryFile;
	};
}
#endif // DumpSymbol_h__