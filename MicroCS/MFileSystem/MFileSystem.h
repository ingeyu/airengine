#ifndef MFileSystem_h__
#define MFileSystem_h__
#include "MFileSystemCommon.h"


class MFile;

class MFileSystem	:	
	public	Air::Common::IFactoryManager,
	public	Singleton<MFileSystem>,
	public	Air::Common::NetListener
{
public:
	MFileSystem();
	virtual	~MFileSystem();

	U1		Initialization();
	U1		Release();

	virtual	U1	OnConnected(U32	socket,CAString&	strIP,CAString&	strPort);
	virtual	U1	OnClose(U32	uiSocket);
	virtual	U1	OnReceive(U32	uiSocket,AChar*	pData,U32	uiSize);

	MFile*		CreateFile(U64	id);
	void		SendToClient(U32 uiSocket,const void* p,U32 uiSize);
	void		DisConnectClient(U32 uiSocket);

	Air::Common::NetServer*	m_pServer;
};
#endif // MFileSystem_h__
