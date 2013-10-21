#ifndef MDownloadSystem_h__
#define MDownloadSystem_h__

#include "MFileSystemCommon.h"

class MFile;
struct DownloadFile
{
	U64	fileID;
	U32	state;
};
class MDownloadSystem	:
	public	MemoryObject,
	public	Singleton<MDownloadSystem>,
	public	Air::Common::NetListener
{
public:
	MDownloadSystem();
	virtual	~MDownloadSystem();

	U1		Initialization();
	U1		Release();

	U1		AddFile(MFile* pFile);
	void	Update(U32 uiTickTime);

	virtual	U1	OnConnected(U32	socket,CAString&	strIP,CAString&	strPort);
	virtual	U1	OnClose(U32	uiSocket);
	virtual	U1	OnReceive(U32	uiSocket,AChar*	pData,U32	uiSize);
	virtual	U1	OnReturn(NT_Return* pRet);
	void		OnDownloadComplated(MFile* pFile,U1	bOK);
protected:
	MFile*							m_pDownloadingFile;
	STD_LIST<MFile*>				m_lstFile;
	Air::Common::NetClient*			m_pClient;
	Air::Common::CriticalSection	m_CS;
	U32								m_uiCurrent;
};
#endif // MDownloadSystem_h__
