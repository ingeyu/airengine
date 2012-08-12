#ifndef VIDEOPLUGIN_HEAD_FILE
#define VIDEOPLUGIN_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"

interface	IMediaEventEx;
interface	IMediaPosition;
interface	IMediaControl;
interface	IGraphBuilder;
interface	IVideoWindow;
namespace Air{
	
	namespace	Common{
	
		/**	\brief	视频片头播放插件
		*
		*	视频片头播放
		*
		***/
		class COMMON_EXPORT CVideoPlugin{
		public:
			CVideoPlugin();
			virtual ~CVideoPlugin();
			void	LoadWmvA(char* tcFileName,HWND hWnd);
			void	LoadWmv(wchar_t* tcFileName);
			void	LoadWmvA(char* tcFileName);
			void	LoadAvi(TCHAR* tcFileName);
			void	Play();
			void	Pause(bool bPause = true);
			void	Stop();
			void	SetSpeed(double fSpeed);
			bool	IsPlaying();
			double	GetLength();
			double	GetCurrentTime();
			double	GetSpeed();
	
		private:
			WString				m_sFileName;
			double				m_fSpeed;
			double				m_fLength;
			double				m_fCurrentTime;
			bool				m_bInit;
			bool				m_bIsFullScreen;
			HWND				m_hWnd;				
	
		private:
			IMediaEventEx*		m_pMediaEventEx;	//可以从directshow接受事件消息
			IMediaPosition*		m_pMediaPosition;	//用这个来取得/设置媒体播放的位置等。
			IMediaControl*		m_pMediaControl;    //用于向Filter Graph Manager发送Command
			IGraphBuilder*		m_pGraphBuilder;    // 用于创建Filter Graph的接口
			IVideoWindow*		m_pVideoWindow;		// 窗口指针
		};
	}
};

#endif