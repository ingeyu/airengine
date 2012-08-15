#include "MTThread.h"
#include "process.h"





		MT_Thread::MT_Thread(){
			m_hHandle	=	NULL;
			m_iThreadID	=	0;
			m_bPause	=	false;
			m_bExit		=	false;
			m_bSuspend	=	false;
			m_bHasPause	=	false;
			SetSleepTime();
		}
		MT_Thread::~MT_Thread(){
			StopThread();
		}
		bool MT_Thread::StartThread(){
	
			//如果已經启动则返回
			if(m_hHandle !=NULL){
				PauseThread(false);
				Resume();
				return true;	
			}
			//不暂停
			m_bPause	= false;
			//不退出循环调用
			m_bExit		= false;
			//开始线程
			m_hHandle = (HANDLE)_beginthreadex(NULL,0,MT_Thread::Run,(void*)this,0,&m_iThreadID);
			//如果线程创建失败
			if(m_hHandle==NULL)
				return false;
			return true;
		}
		bool MT_Thread::IsRunning(){
			if(m_bSuspend || m_bPause || m_hHandle==NULL)
				return false;
			return true;
		}
		bool MT_Thread::StopThread(){
			if(m_bSuspend)
				Resume();
			m_bPause	= true;
			m_bExit		= true;
			m_iThreadID = 0;
			m_bSuspend	= false;
			return true;
		}
		void MT_Thread::SetSleepTime(unsigned int dwMilliseconds /*= 10*/){
			m_pSleepTime = dwMilliseconds;
		}
		bool MT_Thread::PauseThread(bool pause){
			m_bPause = pause;
			return true;
		}
		bool MT_Thread::Suspend(){
			if(m_hHandle ==NULL)
				return false;	
			if(m_bSuspend)
				return false;
	
			SuspendThread(m_hHandle);
			m_bSuspend = true;
			return true;
		}
		bool MT_Thread::Resume(){
			if(m_hHandle == NULL)
				return false;	
			if(!m_bSuspend)
				return false;
	
			::ResumeThread(m_hHandle);
			m_bSuspend = false;
			return true;
		}
		unsigned int __stdcall MT_Thread::Run(void* pThread){
			//OutputDebugStringA("--线程启动--\n");
			MT_Thread* p = (MT_Thread*)pThread;
			while(!p->m_bExit){
				while(!p->m_bPause){
					p->RepetitionRun();
					p->m_bHasPause	=	false;
				}
				p->m_bHasPause	=	true;
				Sleep(p->m_pSleepTime);
				
			}
			//OutputDebugStringA("--线程退出--\n");
			return true;
		}
	
		bool MT_Thread::StopThreadWaitForExit(){
			StopThread();
			DWORD dRet	=	WaitForSingleObject(m_hHandle,INFINITE);
			switch(dRet){
				case	WAIT_OBJECT_0:{
					::OutputDebugStringA("Wait	Thread Succesed Exit\n");
					return	true;
					break;}
				case	WAIT_TIMEOUT:{
					::OutputDebugStringA("[Warning]Wait	Thread Time	Out\n");
					return	true;
					break;}
				case WAIT_FAILED:{
					::OutputDebugStringA("[Warning]Wait	Thread Failed\n");
					return	false;
					break;}
				default:{
					::OutputDebugStringA("[Warning]Wait	Thread UnKnown Error\n");
					return	false;
					break;}
			}
		}
	
		U1 MT_Thread::PauseThreadSync(){
			PauseThread(true);
			while(!m_bHasPause){
				Sleep(0);
			}
			return	true;
		}
	
		U1 MT_Thread::SuspendSync(){
			PauseThreadSync();
			return	Suspend();
		}
	
		bool MT_Thread::StopThreadWaitTimeOut( int iTime ){
			HANDLE h	=	m_hHandle;
			StopThread();
			DWORD dRet	=	WaitForSingleObject(h,iTime);
			switch(dRet){
				case	WAIT_OBJECT_0:{
					return	true;
					break;}
				case	WAIT_TIMEOUT:{
					TerminateThread(h,0);
					return	false;
					break;}
				default:{
					::OutputDebugStringA("[Warning]Wait	Thread UnKnown Error\n");
					return	false;
					break;}
			}
		}
	