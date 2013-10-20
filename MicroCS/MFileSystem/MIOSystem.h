#ifndef MIOSystem_h__
#define MIOSystem_h__

#include "MFileSystemCommon.h"

class MFile;

class MIOSystem	:	
	public	Air::Common::IFactoryManager,
	public	Singleton<MIOSystem>
{
public:
	MIOSystem();
	virtual	~MIOSystem();

	U1			Initialization();
	U1			Release();
	U1			SaveFileBackground(MFile* pFile);
	void		Update(float fTimeDelta);

	U1			LoadFile(FileInfo& info,STD_VECTOR<U8>& data);
	U1			SaveFile(FileInfo& info,const void* pData,U32 uiSize);//const	STD_VECTOR<U8>& data);
	void		SaveFile(FileInfo& info,const	STD_VECTOR<U8>& data);
	
	HANDLE		GetFileHandleByIndex(U32	idx);
protected:

	HANDLE							m_FileData[FILEDATA_COUNT];
	HANDLE							m_FileIndex;
	STD_VECTOR<MFile*>				m_lstFile;
	Air::Common::CriticalSection	m_CS;
};
#endif // MIOSystem_h__
