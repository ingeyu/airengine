#ifndef COMMONNETSENDTHREAD_HEAD_FILE
#define COMMONNETSENDTHREAD_HEAD_FILE

#include "AirCommonNet.h"
#include "AirCommonThread.h"
#include "AirCommonLock.h"

namespace Air{
	
	
	namespace Common{
	
		
		typedef	std::queue<NetPack*>	SendPackList;
		/**	\brief	发送队列
		*
		*	发送队列
		*
		***/
		class	MCOMMON_EXPORT	NetSendThread	
			:	public	Thread{
		public:
			NetSendThread();
			virtual	~NetSendThread();
	
			/**	\brief	启动
			*   
			*	@remarks 	启动
			*	@see		NetSendThread
			*	@return   	U1
			*	@param		NetListener * pListener
			*	@note
			*
			**/
			virtual	U1	Start(NetListener*	pListener);
	
			/**	\brief	放入队列中
			*   
			*	@remarks 	放入队列中
			*	@see		NetSendThread
			*	@return   	U1
			*	@param		SendPack * pack
			*	@note
			*
			**/
			virtual	U1	Push(NetPack*	pack);
	
			/**	\brief	发送循环
			*   
			*	@remarks 	发送循环
			*	@see		NetSendThread
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	RepetitionRun();
	
		protected:
			CriticalSection	m_CS;
			Event			m_SendEvent;
			bool			m_bWaiting;
			SendPackList	m_lstSendPack;
			NetListener*	m_pListener;
		};
		
	
	};
};
#endif // COMMONNETSENDTHREAD_HEAD_FILE