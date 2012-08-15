#ifndef MTRENDERTHREAD_HEAD_FILE
#define MTRENDERTHREAD_HEAD_FILE

#include "MTDoubleBuffer.h"
#include "MTThread.h"

enum enumRenderThreadState{
	enRTS_UNKNOWN,
	enRTS_Waiting,
	enRTS_Rendering,
	enRTS_RenderComplated,
	enRTS_EventResetComplated,
};

class	MT_RenderThread	:public	MT_Thread{
public:
	MT_RenderThread(IDirect3DDevice9*	pDevice);
	virtual	~MT_RenderThread();
	//交换
	void			Swap();
	//线程函数
	virtual bool	RepetitionRun();
	//获取双Buffer
	MT_DoubleBuffer&	GetDBuffer(){
		return	m_DBuffer;
	};
	enumRenderThreadState	GetRenderThreadState(){
		return	m_State;
	}

	virtual bool StopThread();
protected:
	void			RenderFrame();

	void			WaitRenderComplated();
protected:
	IDirect3DDevice9*		m_pDevice;
	Event					m_evtRenderWaitMain;
	Event					m_evtMainWaitRender;
	MT_DoubleBuffer			m_DBuffer;
	enumRenderThreadState	m_State;
};

#endif