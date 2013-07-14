#ifndef DumpFile_h__
#define DumpFile_h__

enum enumOpenType{
	enOT_File,
	enOT_Memory
};
enum enumFileState{
	enFS_Open,
	enFS_Close,
};

struct DumpModule{
	ULONG64		BaseOfImage;
	ULONG32		SizeOfImage;
	ULONG32		TimeDateStamp;
	wchar_t*	Name;
	ULONG32		RSDS;
	GUID		Guid;
	ULONG32		Age;
	char		PDBName[256];
	void*		pBinary;
	void*		pPDB;
};
struct DumpThread{
	ULONG32		ThreadId;
	ULONG32		SuspendCount;
	ULONG32		PriorityClass;
	ULONG32		Priority;
	ULONG64		Teb;
	ULONG64		StartOfMemoryRange;
	ULONG32		MemorySize;
	void*		StackMemory;
	CONTEXT*	pContext;
};

class DumpFile{
public:
	DumpFile();
	~DumpFile();

	bool	Open(const wchar_t* strName);
	bool	Open(const void* pData,unsigned int uiSize);
	bool	Close();
protected:
	char*						dump_want_n(unsigned sz);
	const char*					get_time_str(unsigned long _t);
	void						dump_unicode_str( const wchar_t *str, int len );
	const void*					PRD(unsigned long prd, unsigned long len);
	void						dump_data( const unsigned char *ptr, unsigned int size, const char *prefix );
	void						dump_mdmp_data(const MINIDUMP_LOCATION_DESCRIPTOR* md, const char* pfx);
	void						dump_mdmp_string(DWORD rva);
	const MINIDUMP_DIRECTORY*	get_mdmp_dir(const MINIDUMP_HEADER* hdr, unsigned int str_idx);
	enum FileSig				get_kind_mdmp(void);
	void						mdmp_dump(void* pBase,unsigned int uiSize);
protected:
	bool		BuildCallstack();
	U1			IsCall(const void* p);
protected:
	void*			m_pBuffer;
	U32				m_uiSize;
	MINIDUMP_SYSTEM_INFO*		m_pSystemInfo;
	MINIDUMP_MISC_INFO*			m_pMiseInfo;
	MINIDUMP_EXCEPTION_STREAM*	m_pExceptionStream;
	MINIDUMP_MEMORY_LIST*       m_pMemoryList;
	MINIDUMP_MODULE_LIST*		m_pModuleList;
	MINIDUMP_THREAD_LIST*		m_pThreadList;
	enumFileState			m_State;
	enumOpenType			m_Type;

	std::vector<DumpModule>		m_vecModule;
	std::vector<DumpThread>		m_vecThread;
	CONTEXT*					m_pExceptionThreadContext;
	std::wstring				m_strDumpName;
};
#endif // DumpFile_h__
