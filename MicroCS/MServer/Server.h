#pragma once

#include "IOCPServer.h"

#ifndef FILEDATA_COUNT
#define FILEDATA_COUNT	16
#endif

struct DownloadTask{
	unsigned int	idx;
	unsigned int	offset;
	unsigned int	iSize;
	unsigned int	iSend;
	unsigned int	t;
};

class	DownloadSClient	:	public	IOCPClient{
public:
	DownloadSClient(IOCPServer* pServer,_PER_SOCKET_CONTEXT* pContext);
	virtual	void	OnRecvComplated(const void* p,int iSize);
protected:
	virtual	int		pop_front(void* p);

	DownloadTask	m_Task;
};
class	DownloadServer	:	public	IOCPServer
{
public:
	DownloadServer();
	virtual	~DownloadServer();
	virtual	bool	Initialization();
	virtual	void	Release();
	virtual	void	Update();

	virtual	IOCPClient*	NewIOCPClient(_PER_SOCKET_CONTEXT* pContext);
	virtual	void		DeleteIOCPClient(IOCPClient* pClient);

	unsigned char*	GetFileData(unsigned int idx);
	unsigned int	GetFileDataSize(unsigned int idx);
protected:
	void			LoadFileData();
protected:
	unsigned char*	m_pFileData[FILEDATA_COUNT];
	unsigned int	m_PkgSize[FILEDATA_COUNT];
};
