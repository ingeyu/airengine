#ifndef INTERFACEUISYSTEM_HEAD_FILE
#define INTERFACEUISYSTEM_HEAD_FILE


#include "AirInterfaceUIWindowControl.h"
#include "AirInterfaceUIRenderer.h"
#include "AirInterfaceUIKeyProcess.h"
#include "AirInterfaceUIStaticText.h"
namespace Air{
	
	namespace Engine{
	
		namespace	UI{
	
			typedef		Window::IControl	IWindow;
			/**	\brief	界面系统基类
			*
			*	界面系统基类
			*
			***/
			class	ENGINE_EXPORT	ISystem	:
				public	IPlugin,
				public	IFactoryManager,
				public	Renderer,
				public	::OIS::KeyListener,
				public	::OIS::MouseListener,
				public	KeyProcess{
			public:
				ISystem();
	
				/**	\brief	初始化
				*   
				*	@remarks 	
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Initialization();
				/**	\brief	开始
				*   
				*	@remarks 	开始
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual U1	Start();
				/**	\brief	释放
				*   
				*	@remarks 	释放
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Release();
	
				/**	\brief	更新UI
				*   
				*	@remarks 	更新UI 用于处理鼠标消息键盘消息 以便处理是否有窗口被激活
				*	@see		ISystem
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	Update();
	
				/**	\brief	渲染
				*   
				*	@remarks 	渲染
				*	@see		ISystem
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	Render();
				/**	\brief	设置激活窗口
				*   
				*	@remarks 	设置激活窗口
				*	@see		ISystem
				*	@return   	void
				*	@param		IControl * pWindow
				*	@note
				*
				**/
				virtual	void	SetActive(Window::IControl*	pWindow);
	
				/**	\brief	创建一个窗口
				*   
				*	@remarks 	创建一个窗口
				*	@see		ISystem
				*	@return   	IControl*
				*	@param		AString strName
				*	@param		AString strType
				#	@param		void*	pParam
				*	@note
				*
				**/
				virtual	Window::IControl*	CreateIWindow(AString	strName,AString	strType,void*	pParam	=	NULL);
				/**	\brief	摧毁一个窗口
				*   
				*	@remarks 	摧毁一个窗口
				*	@see		ISystem
				*	@return   	void
				*	@param		Window::IControl * pWindow
				*	@note
				*
				**/
				virtual	void		DestroyIWindow(Window::IControl*	pWindow);
	
				/**	\brief	设置激活窗口
				*   
				*	@remarks 	设置激活窗口
				*	@see		ISystem
				*	@return   	void
				*	@param		Window::IControl * pWindow
				*	@note
				*
				**/
				virtual	void		SetRootWindow(Window::IControl*	pWindow);
	
				/**	\brief	获取跟窗口
				*   
				*	@remarks 	获取跟窗口
				*	@see		ISystem
				*	@return   	Window::IControl*
				*	@note
				*
				**/
				Window::IControl*	GetRootWindow(){
					return	m_pRootWindow;
				};
				/**	\brief	获取激活窗口
				*   
				*	@remarks 	获取激活窗口
				*	@see		ISystem
				*	@return   	Window::IControl*
				*	@note
				*
				**/
				Window::IControl*	GetActiveWindow(){
					return	m_pActiveWindow;
				};
				/**	\brief	键盘按下事件
				*   
				*	@remarks 	键盘按下事件
				*	@see		Control
				*	@return   	bool
				*	@param		const Input::KeyEvent & arg
				*	@note
				*
				**/
				virtual bool	keyPressed( const ::OIS::KeyEvent &arg );
				/**	\brief	键盘释放事件
				*   
				*	@remarks 	键盘释放事件
				*	@see		Control
				*	@return   	bool
				*	@param		const Input::KeyEvent & arg
				*	@note
				*
				**/
				virtual bool	keyReleased( const ::OIS::KeyEvent &arg );
				/**	\brief	鼠标移动事件
				*   
				*	@remarks 	鼠标移动事件
				*	@see		Control
				*	@return   	bool
				*	@param		const Input::MouseEvent & arg
				*	@note
				*
				**/
				virtual bool	mouseMoved( const ::OIS::MouseEvent &arg );
				/**	\brief	鼠标按下事件
				*   
				*	@remarks 	鼠标按下事件
				*	@see		Control
				*	@return   	bool
				*	@param		const Input::MouseEvent & arg
				*	@param		Input::MouseButtonID id
				*	@note
				*
				**/
				virtual bool	mousePressed( const ::OIS::MouseEvent &arg, ::OIS::MouseButtonID id );
				/**	\brief	鼠标释放事件
				*   
				*	@remarks 	鼠标释放事件
				*	@see		Control
				*	@return   	bool
				*	@param		const Input::MouseEvent & arg
				*	@param		Input::MouseButtonID id
				*	@note
				*
				**/
				virtual bool	mouseReleased( const ::OIS::MouseEvent &arg, ::OIS::MouseButtonID id );
				/**	\brief	Windows消息回调
				*   
				*	@remarks 	Windows消息回调
				*	@see		IEngine
				*	@return   	long
				*	@param		HWND hWnd
				*	@param		UINT uMsg
				*	@param		WPARAM wParam
				*	@param		LPARAM lParam
				*	@param		bool * pbNoFurtherProcessing
				*	@param		void * pUserContext
				*	@note
				*
				**/
				virtual long	MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing,void* pUserContext );
	
				virtual	void	OnResetDevice();
			protected:
				/**	\brief	渲染窗口树
				*   
				*	@remarks 	渲染窗口树
				*	@see		ISystem
				*	@return   	void
				*	@param		Window::IControl * pWindow
				*	@note
				*
				**/
				void	RenderWindowTree(Window::IControl*	pWindow);
	
				/**	\brief	更新当前按键状态
				*   
				*	@remarks 	更新当前按键状态
				*	@see		ISystem
				*	@return   	void
				*	@param		KeyUnion & k
				*	@param		const OIS::KeyCode & code
				*	@param		U1 bDown
				*	@param		U1 bMouse
				*	@note
				*
				**/
				void	UpdateKey(KeyUnion&	k,const ::OIS::KeyCode&	code,U1	bDown,U1	bMouse	=	false);
			protected:
				Window::IControl*		m_pRootWindow;
				Window::IControl*		m_pActiveWindow;
				KeyUnion				m_Key;
			};
		}
	
	};
};
#endif // INTERFACEUISYSTEM_HEAD_FILE