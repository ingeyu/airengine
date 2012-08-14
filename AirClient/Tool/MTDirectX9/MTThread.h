//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/03/29
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  MT_Thread.h
 \note     
       
 \attention:线程类
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef MTTHREAD_HEAD_FILE
#define MTTHREAD_HEAD_FILE

#include "MTHeader.h"

typedef bool			U1;
typedef	unsigned int	UInt;

		/**	\brief	线程类
		*
		*	单独开一条线程 请使用这个类
		*
		***/
		class MT_Thread{
	
		public:
			MT_Thread();
			virtual ~MT_Thread();
			/**	\brief	开始执行
			*   
			*	@remarks 	开始执行
			*	@see		MT_Thread
			*	@return   	bool
			*	@note		不论线程当前的状态是 挂起 暂停 停止，调用此函数都会激活线程
			*
			**/
			virtual bool StartThread();
			/**	\brief	停止线程
			*   
			*	@remarks 	停止线程
			*	@see		MT_Thread
			*	@return   	bool
			*	@note
			*
			**/
			virtual bool StopThread();
	
			/**	\brief	停止线程
			*   
			*	@remarks 	并且等到到线程退出
			*	@see		MT_Thread
			*	@return   	bool
			*	@note
			*
			**/
			virtual	bool StopThreadWaitForExit();
	
			/**	\brief	停止线程
			*   
			*	@remarks 	等到超时	超时就强行终结
			*	@see		MT_Thread
			*	@return   	bool
			*	@param		int iTime
			*	@note
			*
			**/
			virtual	bool StopThreadWaitTimeOut(int iTime);
	
			/**	\brief	挂起
			*   
			*	@remarks 	挂起
			*	@see		MT_Thread
			*	@return   	bool
			*	@note
			*
			**/
			virtual bool Suspend();
			/**	\brief	恢复
			*   
			*	@remarks 	恢复
			*	@see		MT_Thread
			*	@return   	bool
			*	@note
			*
			**/
			virtual bool Resume();
			/**	\brief	设置暂停时的休眠间隔
			*   
			*	@remarks 	仅在休眠时有效
			*	@see		MT_Thread
			*	@return   	void
			*	@param		unsigned int dwMilliseconds
			*	@note		
			*
			**/
			virtual void SetSleepTime(unsigned int dwMilliseconds = 10);
			/**	\brief	判断线程是否处于激活状态
			*   
			*	@remarks 	当暂停 停止 挂起 都会返回false
			*	@see		MT_Thread
			*	@return   	bool
			*	@note
			*
			**/
			virtual bool IsRunning();
			/**	\brief	暂停线程
			*   
			*	@remarks 	暂停线程
			*	@see		MT_Thread
			*	@return   	bool
			*	@param		bool pause
			*	@note
			*
			**/
			virtual bool PauseThread(bool pause = true);
	
			/**	\brief	同步暂停线程
			*   
			*	@remarks 	保证该线程已经执行完 一个循环 处于空闲状态
			*	@see		MT_Thread
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1		PauseThreadSync();
			/**	\brief	挂起
			*   
			*	@remarks 	挂起
			*	@see		MT_Thread
			*	@return   	bool
			*	@note
			*
			**/
			virtual U1		SuspendSync();
			/**	\brief	子类需要重写的循环调用函数
			*   
			*	@remarks 	线程自身的执行函数
			*	@see		MT_Thread
			*	@return   	bool
			*	@note
			*
			**/
			virtual bool RepetitionRun()=0;
	
			/**	\brief	获取线程句柄
			*   
			*	@remarks 	获取线程句柄
			*	@see		MT_Thread
			*	@return   	HANDLE
			*	@note
			*
			**/
			HANDLE	GetHandle(){
				return	(HANDLE)m_hHandle;
			};
			/**	\brief	线程自身的执行函数
			*   
			*	@remarks 	线程自身的执行函数
			*	@see		MT_Thread
			*	@return   	unsigned int __stdcall
			*	@param		void * pThread
			*	@note
			*
			**/
			static	unsigned int __stdcall Run(void* pThread);
		protected:	
			
			U1		m_bPause;				///<	暂停
			U1		m_bExit;				///<	退出
			U1		m_bSuspend;				///<	挂起
			HANDLE	m_hHandle;				///<	线程句柄
			UInt	m_iThreadID;			///<	线程ID
			UInt	m_pSleepTime;			///<	休眠间隔时间
	
			U1		m_bHasPause;			///<	是否已经暂停
		};

#endif
