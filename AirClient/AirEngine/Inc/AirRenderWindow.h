/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InterfalHell	Xinhe
 \date      2011/08/30
 \version   ver 0.6.0.0
 \filepath  f:\Air\trunk\AirClient\AirEngine\Inc
 \filename  AirRenderWindow.h
 \note     
       
 \attention:
			
 \remarks    created by InterfalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef AIRRENDERWINDOW_HEAD_FILE
#define AIRRENDERWINDOW_HEAD_FILE

#include "AirRenderTarget.h"

namespace	Air{
	namespace Engine{
		/**	\brief	消息回调
		*   
		*	@remarks 	消息回调
		*	@see		
		*	@return   	LRESULT CALLBACK
		*	@param		HWND hwnd
		*	@param		UINT msg
		*	@param		WPARAM wParam
		*	@param		LPARAM lParam
		*	@note
		*
		**/
		ENGINE_EXPORT	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		namespace	Render{

			//RenderWindow
			class	ENGINE_EXPORT	Window	:	
				public	Target{
			public:
				static AString	ProductTypeName;
				Window(CAString&	strName,Info*	pInfo);
				virtual	U1	Create();
				virtual	U1	Destroy();

				virtual	U1	IsMainWindow();
				virtual	U1	CreateWin32Window();
				virtual	U1	DestroyWin32Window();
				HWND		GetWin32Window();
				virtual		void	OnSize();
				virtual	void	SetSize(U32	uiWidth,U32	uiHeight);
				virtual	void	SetFullScreen(U1	bFullScreen,U32	uiWidth,U32	uiHeight);
				U1				IsFullScreen();

				virtual	void	ReCreate(Info& info){};


				HWND		m_WndHandle;
				U1			m_bMainWindow;
			};

			class	WindowListener{
			public:

				virtual	void	WindowMove(Window*	pWin){};
				virtual	void	WindowResize(Window*	pWin){};
				virtual	void	WindowActive(Window*	pWin){};
				virtual	void	WindowUnActive(Window*	pWin){};
			};

			typedef	std::list<WindowListener*>				WindowListenerList;
			typedef	std::map<Window*,WindowListenerList>	WindowListenerListMap;

			class	WindowListenerManager{
			public:
				WindowListenerManager();
				virtual	~WindowListenerManager();

				virtual	void	AddWindow(Window*	pWin);
				virtual	void	RemoveWindow(Window*	pWin);
				virtual	void	AddWindowListener(Window*	pWin,WindowListener*	pListener);
				virtual	void	RemoveWindowListener(Window*	pWin,WindowListener*	pListener);

				virtual	void	WindowMove(Window*	pWin);
				virtual	void	WindowResize(Window*	pWin);
				virtual	void	WindowActive(Window*	pWin);
				virtual	void	WindowUnActive(Window*	pWin);


				WindowListenerListMap	m_mapWindowListenerList;
			};
		}
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // AIRRENDERWINDOW_HEAD_FILE