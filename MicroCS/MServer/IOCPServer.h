#pragma once
#include <windows.h>
#include "IOCPListener.h"

#define	TEMP_BUFFER_SIZE 8192


class	IOCPServer;

class	IOCPClient{
public:
	IOCPClient(IOCPServer* pServer,_PER_SOCKET_CONTEXT* pContext);
	virtual	~IOCPClient();
	virtual	bool	Send(const void* pData,int uiSize);
	virtual	void	OnRecvComplated(const void* p,int iSize);
	virtual	void	OnSendComplated(_PER_IO_CONTEXT* pIO);
	virtual	void	CreateTempBuffer();
	virtual	void	DestroyTempBuffer();
protected:
	virtual	bool	push_back(const void* p,int uiSize);
	virtual	int		pop_front(void* p);
protected:
	CRITICAL_SECTION		m_CriticalSection;
	_PER_SOCKET_CONTEXT*	m_pContext;
	IOCPServer*				m_pServer;
	unsigned char*			m_TempBuffer;
	unsigned int			m_TempSize;

};
typedef void	(__stdcall *MessageProc)(void*,IOCPClient*,const void* ,int );

class	CIOCPModel;
class	IOCPServer	:	public	IOCPListener{
public:
	IOCPServer();
	virtual	~IOCPServer();

	virtual	bool	Initialization();
	virtual	void	Release();
	virtual	void	Update();

	virtual	void	OnConnected(_PER_SOCKET_CONTEXT* pSocketContext);
	virtual	void	OnRecvComplated(_PER_SOCKET_CONTEXT* pSocketContext,_PER_IO_CONTEXT* pIOContext);
	virtual	void	OnSendComplated(_PER_SOCKET_CONTEXT* pSocketContext,_PER_IO_CONTEXT* pIOContext);
	virtual	void	OnClosed(_PER_SOCKET_CONTEXT* pSocketContext);

	virtual	IOCPClient*	NewIOCPClient(_PER_SOCKET_CONTEXT* pContext);
	virtual	void		DeleteIOCPClient(IOCPClient* pClient);
	bool			RegisterMessageProc(unsigned short	id,MessageProc proc,void* pParam);
	template<typename T>
	bool			Register(unsigned short id,void(T::*proc)(IOCPClient*,const void*,int),void* pParam	=	0){
		return RegisterMessageProc(id,(MessageProc)(*(void**)&proc),pParam);
	};
	void			UnRegister(unsigned short id);
protected:
	void		DefaultMessageProc(_PER_SOCKET_CONTEXT* pSocketContext,const void* pData,int iSize);
public:
	CRITICAL_SECTION		m_ClientCS;
	CIOCPModel*				m_pIOCP;
	MessageProc				m_Proc[65536];
	void*					m_Param[65536];
};