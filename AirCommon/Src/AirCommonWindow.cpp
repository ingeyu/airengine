#include "AirCommonWindow.h"
#include "AirCommonConverter.h"


namespace	Air{
	namespace	Common{


		HWND NewWindow(CAString&	strName,U32 iWidth,U32 iHeight,WNDPROC pWinFunc,HWND	hParentWnd){

			HINSTANCE	hInstance = ( HINSTANCE )GetModuleHandle( NULL );

			WNDCLASSA wc;
			memset(&wc,0,sizeof(wc));


			wc.style         = CS_DBLCLKS;
			wc.lpfnWndProc   = (WNDPROC)pWinFunc; 
			wc.cbClsExtra    = 0;
			wc.cbWndExtra    = 0;
			wc.hInstance     = hInstance;
			wc.hIcon         = LoadIcon(0,		IDI_APPLICATION);
			wc.hCursor       = LoadCursor(0,	IDC_ARROW);
			wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
			wc.lpszMenuName  = 0;
			wc.lpszClassName = "DirectXWindow";

			if( !RegisterClassA(&wc) ){
				::MessageBoxA(0, "RegisterClass() - FAILED", 0, 0);
				return NULL;
			}
			HWND	hwnd	=	NULL;
			hwnd	=	::CreateWindowA(	"DirectXWindow",
											strName.c_str(),
											WS_OVERLAPPEDWINDOW, 
											0,
											0, 
											iWidth, 
											iHeight,
											hParentWnd/*parent hwnd*/, 
											0 /* menu */, 
											hInstance, 
											0 /*extra*/);

			::ShowWindow(hwnd, SW_SHOW);
			::UpdateWindow(hwnd);


			return	hwnd;
		}

		COMMON_EXPORT	LRESULT WindowProc( HWND wnd, UINT msg, WPARAM wp, LPARAM lp ){
		
			return	DefWindowProc(wnd,msg,wp,lp);
		}
	}
}