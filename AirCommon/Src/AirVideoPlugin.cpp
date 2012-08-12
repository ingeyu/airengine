#include "AirVideoPlugin.h"
#include "AirCommonConverter.h"
#include "dshow.h"


#define WM_GRAPH_NOTIFY (WM_APP + 1) //g_pMediaEventEx的消息
namespace Air{
	
	namespace	Common{
	
		CVideoPlugin::CVideoPlugin(){
			//m_sFileName			= "";
			m_fSpeed			= 1.0f;
			m_fLength			= 0.0f;
			m_fCurrentTime		= 0.0f;
			m_bInit				= false;
			m_bIsFullScreen		= false;
	
			m_pMediaEventEx		= NULL;	
			m_pMediaPosition	= NULL;	
			m_pMediaControl		= NULL;
			m_pGraphBuilder		= NULL;    
			m_pVideoWindow		= NULL;  
		}
		CVideoPlugin::~CVideoPlugin(){
	
		}
	
		void CVideoPlugin::LoadWmvA(char* tcFileName,HWND hWnd){
			AString sTempFileName(tcFileName);
			m_sFileName = Converter::Acsi2WideByte(sTempFileName);
			m_hWnd = hWnd;
			if(m_sFileName.empty())
				return;
			Play();
	
		}
		void CVideoPlugin::LoadWmv(wchar_t* tcFileName){
			m_sFileName = tcFileName;
			m_bIsFullScreen = true;
			if(m_sFileName.empty())
				return;
			Play();
	
		}
		void CVideoPlugin::LoadWmvA(char* tcFileName){
			AString sTempFileName(tcFileName);
			m_sFileName = Converter::Acsi2WideByte(sTempFileName);
			//m_hWnd = hWnd;
			if(m_sFileName.empty())
				return;
			Play();
		}
		void	CVideoPlugin::LoadAvi(TCHAR* tcFileName){
	
		}
		void	CVideoPlugin::Play(){
			if(m_bInit)
				return;
			// Initialize the COM library.
			int hr = CoInitialize(NULL);   //初始化COM Library
			if( FAILED(hr) ){
				MessageBoxA(0, "could not init the COM library!", 0, 0);
				return;
			}
			//创建Filter Graph Manager
			hr = CoCreateInstance(CLSID_FilterGraph,NULL,CLSCTX_INPROC_SERVER,IID_IGraphBuilder,(void **)&m_pGraphBuilder);     
	
			if( FAILED(hr) ){
				::MessageBoxA(0, "could not create Filter Graph Manager!", 0, 0);
				return;
			}
	
			//查询并获得接口指针
			hr = m_pGraphBuilder->QueryInterface(IID_IMediaControl,(void **)&m_pMediaControl);
			//向directshow询问MediaPosition接口:
			hr = m_pGraphBuilder->QueryInterface(IID_IMediaPosition,(LPVOID*)&m_pMediaPosition);
			//向directshow询问MediaEventsEx接口:
			hr = m_pGraphBuilder->QueryInterface(IID_IMediaEventEx,(void **)&m_pMediaEventEx);
			//我们将使用g_hwnd来接受directshow的消息：
			m_pMediaEventEx->SetNotifyWindow((OAHWND)m_hWnd,WM_GRAPH_NOTIFY, NULL);
			int size = m_sFileName.size();
			WCHAR* pName = new WCHAR[size+1];
			pName[size] = '\0';
			wcscpy_s(pName,size,m_sFileName.c_str());
			//RenderFile库函数是少数几个能够自动创建Graph的成页，所以这里省去了创建Graph这一步
			hr = m_pMediaControl->RenderFile(pName);//load the file
			delete pName;
			//向 directshow 询问 VideoWindow 接口:
			m_pGraphBuilder->QueryInterface(IID_IVideoWindow,(LPVOID*)&m_pVideoWindow);
	
			m_pVideoWindow->put_Visible(OATRUE);
			if(!m_bIsFullScreen){
				//窗口模式
				RECT rect; 
				GetClientRect( m_hWnd, &rect ); 
				m_pVideoWindow->put_Owner((OAHWND)m_hWnd); 
				m_pVideoWindow->put_WindowStyle(WS_CHILD|WS_CLIPSIBLINGS);
				m_pVideoWindow->SetWindowPosition( rect.left, rect.top, rect.right, rect.bottom ); 
			}else{
				//全屏模式
				m_pVideoWindow->put_FullScreenMode(OATRUE);
			}
			if( SUCCEEDED(hr) ){
				hr = m_pMediaControl->Run();//play
				// waiting the end of video
				long evCode;
				m_pMediaEventEx->WaitForCompletion(INFINITE, &evCode);
				//Sleep(1000);
			}	
			Stop();
	
		}
		void	CVideoPlugin::Pause(bool bPause){
			if(!m_bInit)
				return;
			if(bPause)
				m_pMediaControl->Pause();
			else
				m_pMediaControl->Run();
		}
		void	CVideoPlugin::Stop(){
	
				m_pMediaControl->Stop(); 
				m_pVideoWindow->put_FullScreenMode(OAFALSE);
				m_pVideoWindow->put_Visible(OAFALSE);
				m_pVideoWindow->put_Owner(NULL);
				m_pMediaEventEx->Release();
				m_pVideoWindow->Release();
				m_pMediaControl->Release();
				m_pGraphBuilder->Release();
				//释放接口
				CoUninitialize();   //御载COM 库
		}
		void	CVideoPlugin::SetSpeed(double fSpeed){
			m_fSpeed	= fSpeed;
			m_pMediaPosition->put_Rate(m_fSpeed);
		}
		bool	CVideoPlugin::IsPlaying(){
			double fTime = GetCurrentTime();
			if(fTime > m_fLength)
				return false;
			return true;
		}
		double	CVideoPlugin::GetLength(){
			m_pMediaPosition->get_StopTime(&m_fLength);
			return this->m_fLength;
		}
		double	CVideoPlugin::GetCurrentTime(){
			m_pMediaPosition->get_CurrentPosition(&m_fCurrentTime);
			return this->m_fCurrentTime;
		}
		double	CVideoPlugin::GetSpeed(){
			m_pMediaPosition->get_Rate(&m_fSpeed);
			return this->m_fSpeed;
		}
	}
		
};
