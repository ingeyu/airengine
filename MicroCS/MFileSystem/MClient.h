#ifndef MClient_h__
#define MClient_h__

#include "MFileSystemCommon.h"
class MFile;
class MClient	:	
	public	Air::Common::IProduct,
	public	Air::Common::Thread,
	public	Air::Common::NetListener
{
public:
	static	AString	ProductTypeName;
	typedef U32	Info;
	MClient(CAString& strName,Info* pInfo);
	virtual	U1	Create();
	virtual	U1	Destroy();

	void		Update(float fTimeDelta);

	virtual	U1	OnConnected(U32	socket,CAString&	strIP,CAString&	strPort);
	virtual	U1	OnClose(U32	uiSocket);
	virtual	U1	OnReceive(U32	uiSocket,AChar*	pData,U32	uiSize);
	void		OnFileLoadComplated(U32 uiOffset,MFile* pFile);
	void		OnFileLoadFailed(U32 uiOffset,MFile* pFile);

	virtual bool RepetitionRun();
protected:
	void		LoadFile(U64 fileID);
protected:
	U32					m_pSocket;
	Air::FileMapping*	m_pFile;
	Air::Common::Event	m_FSWaitClient;
};
#endif // MClient_h__
