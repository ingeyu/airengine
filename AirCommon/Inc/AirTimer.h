#ifndef AirTimer_h__
#define AirTimer_h__

#include "AirCommonHeader.h"

namespace	Air{
	struct	FrameTime{
		float	fTimeDelta;
		double	fTotalTime;
		U64		uiFrameIndex;
	};
	class	COMMON_EXPORT	Timer{
	public:
		Timer();

		void	AddFrame();

		inline	float	GetTimeDelta(){return	m_FrameTime.fTimeDelta;};
		inline	double	GetTotalTime(){return	m_FrameTime.fTotalTime;};
		inline	U64		GetFrameIndex(){return	m_FrameTime.uiFrameIndex;};
		U32				Random();
		double			m_Freq;
		LARGE_INTEGER	m_LastTime;
		FrameTime		m_FrameTime;
	};

	COMMON_EXPORT	Timer&	GetTimer();

}
#endif // AirTimer_h__
