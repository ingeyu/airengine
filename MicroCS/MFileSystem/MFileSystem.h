#ifndef MFileSystem_h__
#define MFileSystem_h__
#include "MFileSystemCommon.h"


class MFile;
class MClient;

class MFileSystem	:	
	public	Air::Common::IFactoryManager,
	public	Singleton<MFileSystem>
{
public:
	MFileSystem();
	virtual	~MFileSystem();

	U1				Initialization();
	U1				Release();
	void			Update(float fTimeDelta);


	MFile*			CreateMFile(U64	id);

	void			ScanProcess(const TCHAR* strName);
	const FileInfo& GetFileInfo(U32 idx);
protected:
	void			LoadFileIndex();
protected:
	STD_MAP<U32,MClient*>	m_mapClient;
	Air::FileMapping*		m_pShareFileInfo;
	FileInfoMap				m_mapFileInfo;
	HANDLE					m_hFileSystemInit;
};
#endif // MFileSystem_h__
