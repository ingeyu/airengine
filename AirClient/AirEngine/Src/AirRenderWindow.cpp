#include "AirRenderWindow.h"
#include "AirCommonConverter.h"
#include "AirRenderSystem.h"

namespace	Air{
	namespace	Engine{
		namespace	Render{


			Window::Window( CAString& strName,Info* pInfo ):Target(strName,pInfo){
				m_WndHandle		=	NULL;
				m_bMainWindow	=	false;
				AddPhaseFlag(enPI_Alpha);
				AddPhaseFlag(enPI_Helper);
				AddPhaseFlag(enPI_UI);
				AddPhaseFlag(enPI_Overlay);
			}

			Air::U1 Window::Create(){
				CreateWin32Window();
				return	true;
			}

			Air::U1 Window::Destroy(){
				DestroyWin32Window();

				RemoveAllViewport();
				return	true;
			}

			Air::U1 Window::IsMainWindow(){
				return	m_bMainWindow;
			}

			Air::U1 Window::CreateWin32Window(){
				if(m_WndHandle==NULL	&&	m_Info.extraWnd	==	NULL){
// 					m_WndHandle	=	Common::NewWindow(	m_strProductName,
// 														m_Info.vecTextureInfo[0].width,
// 														m_Info.vecTextureInfo[0].height,
// 														m_Info.parentWnd);
					HINSTANCE	hInstance = ( HINSTANCE )GetModuleHandle( NULL );

					WNDCLASSW wc;
					memset(&wc,0,sizeof(wc));

					WString		wStr	=	Converter::Acsi2WideByte(m_strProductName);


					wc.style         = CS_DBLCLKS;
					wc.lpfnWndProc   = (WNDPROC)WndProc; 
					wc.cbClsExtra    = 0;
					wc.cbWndExtra    = 0;
					wc.hInstance     = hInstance;
					wc.hIcon         = LoadIcon(0,		IDI_APPLICATION);
					wc.hCursor       = LoadCursor(0,	IDC_ARROW);
					wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
					wc.lpszMenuName  = 0;
					wc.lpszClassName = L"AirWindow";

					if( !RegisterClassW(&wc) ){
						//::MessageBoxA(0, "RegisterClass() - FAILED", 0, 0);
						return false;
					}
					HWND	hwnd	=	NULL;
					hwnd	=	::CreateWindowW(	L"AirWindow",
						wStr.c_str(),
						WS_OVERLAPPEDWINDOW, 
						0,
						0, 
						m_Info.vecTextureInfo[0].width, 
						m_Info.vecTextureInfo[0].height,
						m_Info.parentWnd/*parent hwnd*/, 
						0 /* menu */, 
						hInstance, 
						this);

					::ShowWindow(hwnd, SW_SHOW);
					::UpdateWindow(hwnd);

					m_WndHandle	=	hwnd;

					SetWindowLong(m_WndHandle,GWL_USERDATA,(LONG)this);
				}else{
					SetWindowLong(m_Info.extraWnd,GWL_USERDATA,(LONG)this);
				}
				return	true;
			}

			Air::U1 Window::DestroyWin32Window(){
				if(m_WndHandle!=NULL){
					SetWindowLong(m_WndHandle,GWL_USERDATA,(LONG)NULL);
					DestroyWindow(m_WndHandle);
					m_WndHandle	=	NULL;
				}else{
					SetWindowLong(m_Info.extraWnd,GWL_USERDATA,(LONG)NULL);
				}
				return	true;
			}

			void Window::SetSize( U32 uiWidth,U32 uiHeight ){
				HWND	hWnd	=	NULL;
				if(m_WndHandle!=NULL){
					hWnd	=	m_WndHandle;
				}else{
					hWnd	=	m_Info.extraWnd;
				}
				if(hWnd!=NULL){
					WINDOWINFO	info;
					GetWindowInfo(m_WndHandle,&info);
					SetWindowPos(m_WndHandle,NULL,info.rcWindow.left,info.rcWindow.top,uiWidth,uiHeight,0);
				}
			}

			void Window::SetFullScreen( U1 bFullScreen,U32 uiWidth,U32 uiHeight ){

				if(	m_Info.vecTextureInfo[0].width	!=	uiWidth		||
					m_Info.vecTextureInfo[0].height	!=	uiHeight	||
					bFullScreen)
				{
					HWND	hWnd	=	NULL;
					if(m_WndHandle!=NULL){
						hWnd	=	m_WndHandle;
					}else{
						hWnd	=	m_Info.extraWnd;
					}
					WINDOWINFO	info;
					GetWindowInfo(m_WndHandle,&info);
					SetWindowPos(m_WndHandle,NULL,info.rcWindow.left,info.rcWindow.top,uiWidth,uiHeight,0);

				}
			}

			HWND Window::GetWin32Window(){
				if(m_Info.extraWnd!=NULL)
					return	m_Info.extraWnd;
				return	m_WndHandle;
			}

			Air::U1 Window::IsFullScreen(){
				return	m_Info.bFullScreen;
			}

			void Window::OnSize()
			{

			}

// 			long WindowListenerManager::WindowProc( HWND wnd, UINT msg, WPARAM wp, LPARAM lp ){
// 
// 				Window*	pWin	=	(Window*)GetWindowLong(wnd,GWL_USERDATA);
// 				if(pWin!=NULL){
// 					switch(msg){
// 						case	WM_CREATE:{
// 
// 							break;}
// 						case	WM_SIZE:{
// 							if(wp	==	SIZE_RESTORED){
// 								pWin->SetSize(HIWORD(lp),LOWORD(lp));
// 							}else	if(wp	==	SIZE_MAXIMIZED){
// 								pWin->SetSize(HIWORD(lp),LOWORD(lp));
// 							}
// 							break;}
// 						case	WM_ACTIVATE:{
// 							
// 							break;}
// 						case	WM_MOVE:{
// 
// 							break;}
// 						case	WM_DESTROY:{
// 							PostQuitMessage( 0 );
// 							break;}
// 					}
// 				}
// 				return	DefWindowProc(wnd,msg,wp,lp);
// 			}

			WindowListenerManager::WindowListenerManager(){

			}

			WindowListenerManager::~WindowListenerManager(){

			}

			void WindowListenerManager::AddWindow( Window* pWin ){
				if(pWin==NULL)
					return;

				WindowListenerListMap::iterator	i	=	m_mapWindowListenerList.find(pWin);
				if(i==m_mapWindowListenerList.end()){
					m_mapWindowListenerList[pWin]	=	WindowListenerList();
				}
			}

			void WindowListenerManager::RemoveWindow( Window* pWin ){
				if(pWin==NULL)
					return;

				WindowListenerListMap::iterator	i	=	m_mapWindowListenerList.find(pWin);
				if(i!=m_mapWindowListenerList.end()){
					m_mapWindowListenerList.erase(i);
				}
			}

			void WindowListenerManager::AddWindowListener( Window* pWin,WindowListener* pListener ){
				if(pWin==NULL	||	pListener==NULL)
					return;

				m_mapWindowListenerList[pWin].push_back(pListener);
			}

			void WindowListenerManager::RemoveWindowListener( Window* pWin,WindowListener* pListener ){
				if(pWin==NULL	||	pListener==NULL)
					return;
				WindowListenerListMap::iterator	i	=	m_mapWindowListenerList.find(pWin);
				if(i!=m_mapWindowListenerList.end()){
					i->second.remove(pListener);
					if(i->second.empty()){
						m_mapWindowListenerList.erase(i);
					}
				}
			}

			void WindowListenerManager::WindowMove( Window* pWin ){
				
			}

			void WindowListenerManager::WindowResize( Window* pWin ){

			}

			void WindowListenerManager::WindowActive( Window* pWin ){
				
			}

			void WindowListenerManager::WindowUnActive( Window* pWin ){

			}
		}
		LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ){
			switch(msg){
			case WM_SIZE:{
				switch(wParam){
					case SIZE_RESTORED:
					case SIZE_MAXIMIZED:{
						Render::Window*	pWindow	=	(Render::Window*)GetWindowLong(hwnd,GWL_USERDATA);
						if(pWindow!=NULL){
							pWindow->OnSize();
						}
						break;}
					case SIZE_MINIMIZED:{

						break;}
					case SIZE_MAXSHOW:{
						Render::Window*	pWindow	=	(Render::Window*)GetWindowLong(hwnd,GWL_USERDATA);
						if(pWindow!=NULL){
							pWindow->OnSize();
						}
						break;}
					case SIZE_MAXHIDE:{

						break;}		 
				}
				break;}
			case WM_EXITSIZEMOVE:{
				Render::Window*	pWindow	=	(Render::Window*)GetWindowLong(hwnd,GWL_USERDATA);
				if(pWindow!=NULL){
					pWindow->OnSize();
				}
				break;}
			case WM_GETMINMAXINFO:{
				((MINMAXINFO*)lParam)->ptMinTrackSize.x	=	200;
				((MINMAXINFO*)lParam)->ptMinTrackSize.x	=	200;
				break;}
			case WM_CLOSE:{
				HMENU hMenu;
				hMenu = GetMenu( hwnd );
				if( hMenu != NULL )
					DestroyMenu( hMenu );
				DestroyWindow( hwnd );
				return 0;
				break;}
			case WM_DESTROY:{
				// 					Window11*	pWindow	=	(Window11*)GetWindowLong(hwnd,GWL_USERDATA);
				// 					if(pWindow!=NULL){
				// 						pWindow->Destroy();
				// 						delete pWindow;
				// 					}
				::PostQuitMessage(0);
				break;}
			}


			if(	(	msg	== WM_SYSKEYDOWN	||	msg	== WM_SYSKEYUP ) && 
				(	wParam	== VK_F10			||	wParam	== VK_MENU)){
					return 0;
			}

			// 				if(WM_SETCURSOR	==	msg)
			// 					return 0;
			return ::DefWindowProc(hwnd, msg, wParam, lParam);
		}
	}
}

