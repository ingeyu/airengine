#ifndef MClient_h__
#define MClient_h__

#include "MFileSystemCommon.h"
class MFile;
class MClient	:	
	public	Air::Common::IProduct,
	public	Air::Common::Thread
{
public:
	static	AString	ProductTypeName;
	typedef U32	Info;
	MClient(CAString& strName,Info* pInfo);
	virtual	U1	Create();
	virtual	U1	Destroy();

	void		Update(float fTimeDelta);

	void		OnFileLoadComplated(U32 uiOffset,MFile* pFile);
	void		OnFileLoadFailed(U32 uiOffset,MFile* pFile);

	virtual bool RepetitionRun();

	void		SetProcessExistFrame(U32 iFrame);
	U1			IsProcessExist(U32 iFrame);
protected:
	void		LoadFile(U64 fileID);
protected:
	U32					m_ProcessID;
	Air::FileMapping*	m_pFile;
	Air::Common::Event	m_FSWaitClient;
	U32					m_bProcessExist;
};
#endif // MClient_h__
