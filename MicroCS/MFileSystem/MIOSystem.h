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

	U1			LoadFile(U64	fileID,STD_VECTOR<U8>& data);
	U1			SaveFile(U64	fileID,const	STD_VECTOR<U8>& data);

	STD_VECTOR<U32>		m_vecFileMask;
};
#endif // MIOSystem_h__
