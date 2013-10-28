#ifndef MClient_h__
#define MClient_h__

#include "MClientCommon.h"

struct ThreadHandle{
	ThreadHandle();
	~ThreadHandle();
	HANDLE	GetFileHandle(U32	idx);

	HANDLE	m_FileHandle[FILEDATA_COUNT];
	U32		m_uiThreadID;
};

class	MClient	:	
	public	Air::Common::IFactoryManager,
	public	Singleton<MClient>
{
public:


	MClient();
	virtual	U1	Initialization();
	virtual	U1	Release();


	U32	LoadFile(const char* strName,void* pBuffer);
public:
	U32	ReadFromHD(void* pBuffer,FileInfo* pInfo);
	HANDLE	GetFileHandle(U32 idx);
protected:
	STD_HASHMAP<U64,FileInfo*>		m_mapFileInfo;
	Air::FileMapping*				m_pFile;
	Air::FileMapping*				m_pFileInfo;
	HANDLE							m_FileData[FILEDATA_COUNT];
	Air::Common::Event*				m_pWaitClient;
	ThreadHandle					m_ThreadHandle[10];
	U32								m_uiThreadCount;
};
#endif // MClient_h__
