#pragma once

struct	_PER_IO_CONTEXT;
struct	_PER_SOCKET_CONTEXT;

class	IOCPListener
{
public:
	virtual	void	OnConnected(_PER_SOCKET_CONTEXT* pSocketContext)=0;
	virtual	void	OnRecvComplated(_PER_SOCKET_CONTEXT* pSocketContext,_PER_IO_CONTEXT* pIOContext)=0;
	virtual	void	OnSendComplated(_PER_SOCKET_CONTEXT* pSocketContext,_PER_IO_CONTEXT* pIOContext)=0;
	virtual	void	OnClosed(_PER_SOCKET_CONTEXT* pSocketContext)=0;
};