#include "AirTimer.h"

namespace	Air{



	Timer::Timer()
	{
		HANDLE	hThread	=	GetCurrentThread();
		SetThreadAffinityMask(hThread,0x00000001);

		LARGE_INTEGER	FREQ;
		QueryPerformanceFrequency(&FREQ);
		m_Freq	=	(double)FREQ.QuadPart	/	(double)1000000;
		QueryPerformanceCounter(&m_LastTime);

		m_FrameTime.fTimeDelta		=	0.0f;
		m_FrameTime.fTotalTime		=	0;
		m_FrameTime.uiFrameIndex	=	0;
	}

	void Timer::AddFrame()
	{
		
		LARGE_INTEGER	currenttime;
		QueryPerformanceCounter(&currenttime);

		double	dTimeDelta	=	0.000001*((currenttime.QuadPart	-	m_LastTime.QuadPart)/m_Freq);
		m_FrameTime.fTimeDelta	=	dTimeDelta;
		m_FrameTime.fTotalTime	+=	dTimeDelta;
		m_FrameTime.uiFrameIndex++;

		m_LastTime.QuadPart	=	currenttime.QuadPart;
	}

	Air::U32 Timer::Random()
	{
		return (U32)m_LastTime.QuadPart;
	}

	COMMON_EXPORT	Timer& GetTimer()
	{
		static Timer	g_Timer;
		return	g_Timer;
	}

}