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
	HANDLE		GetFileHandle(U32 uiSize,U32* pIndex=NULL);
	HANDLE		GetFileHandleByIndex(U32	idx);
protected:

	HANDLE		m_FileData[FILEDATA_COUNT];
	U32			m_uiOffset[FILEDATA_COUNT];
	STD_LIST<MFile*>	m_lstFile;
};
#endif // MIOSystem_h__
