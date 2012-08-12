#ifndef COMMONNETRECEIVETHREAD_HEAD_FILE
#define COMMONNETRECEIVETHREAD_HEAD_FILE

#include "AirCommonNet.h"
#include "AirCommonThread.h"
#include "AirCommonLock.h"

namespace Air{
	
	
	namespace Common{
	
		/**	\brief	接收线程
		*
		*	接收线程
		*
		***/
		class	COMMON_EXPORT	NetReceiveThread	
			:	public	Thread{
		public:
			NetReceiveThread();
	
			/**	\brief	启动
			*   
			*	@remarks 	启动
			*	@see		NetReceiveThread
			*	@return   	U1
			*	@param		U32 uiSocket
			*	@param		NetListener * pListener
			*	@note
			*
			**/
			virtual	U1	Start(U32	uiSocket,NetListener*	pListener);
	
			/**	\brief	消息接收循环
			*   
			*	@remarks 	消息接收循环
			*	@see		NetReceiveThread
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	RepetitionRun();
	
			U32				m_Socket;					///<	SOCKET	ID
			U32				m_ReceiveSize;				///<	接收到的数据大小
			AChar			m_ReceiveBuffer[1024*1024*10];	///<	接收缓冲区
			NetListener*	m_pListener;				///<	监听器
		};
		
		typedef	std::map<U32,NetReceiveThread*>	ReceiveThreadMap;
		typedef	std::list<NetReceiveThread*>	ReceiveThreadList;
	
	};
};
#endif // COMMONNETRECEIVETHREAD_HEAD_FILE