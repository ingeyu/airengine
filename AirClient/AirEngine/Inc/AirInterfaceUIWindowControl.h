#ifndef INTERFACEUIControlCONTROL_HEAD_FILE
#define INTERFACEUIControlCONTROL_HEAD_FILE

#include "AirInterfaceUIWindowState.h"
#include "OIS.h"
namespace Air{
	
	namespace Engine{
	
		class		Font;
	
		namespace	UI{
			namespace	Window{
	
	
				/**	\brief	UI基本元素
				*	
				*	UI基本元素
				*
				***/
				class	ENGINE_EXPORT	IControl	:
					public	State,
					public	::OIS::MouseListener,
					public	::OIS::KeyListener,
					public	Common::IProduct{
				public:
					typedef		std::list<IControl*>			WindowList;
					typedef		WindowList::iterator			WindowListItr;
				public:
					static	Float2	TopLeft;
					static	Float2	TopMiddle;
					static	Float2	TopRight;
					static	Float2	MiddleLeft;
					static	Float2	Middle;
					static	Float2	MiddleRight;
					static	Float2	BottomLeft;
					static	Float2	BottomMiddle;
					static	Float2	BottomRight;
				public:
					IControl(CAString&	strName,StateArray*	pArray,Info*	pInfo);
	
					/**	\brief	创建
					*   
					*	@remarks 	创建
					*	@see		IControl
					*	@return   	U1
					*	@note
					*
					**/
					virtual	U1	Create();
					/**	\brief	摧毁
					*   
					*	@remarks 	摧毁
					*	@see		IControl
					*	@return   	U1
					*	@note
					*
					**/
					virtual	U1	Destroy();
					/**	\brief	添加一个子节点
					*   
					*	@remarks 	添加一个子节点
					*	@see		IControl
					*	@return   	void
					*	@param		IControl * pWindow
					*	@note
					*
					**/
					void			AddChild(IControl*	pWindow);
					/**	\brief	移除一个子节点
					*   
					*	@remarks 	移除一个子节点
					*	@see		IControl
					*	@return   	void
					*	@param		IControl * pWindow
					*	@note
					*
					**/
					void			RemoveChild(IControl*	pWindow);
	
					/**	\brief	移除所有子节点
					*   
					*	@remarks 	移除所有子节点
					*	@see		IControl
					*	@return   	void
					*	@note
					*
					**/
					void			RemoveAllChild();
	
					/**	\brief	摧毁子节点
					*   
					*	@remarks 	摧毁子节点
					*	@see		IControl
					*	@return   	void
					*	@note
					*
					**/
					void			DestroyChild(IControl*	pWindow);
	
					/**	\brief	摧毁所有子节点
					*   
					*	@remarks 	摧毁所有子节点
					*	@see		IControl
					*	@return   	void
					*	@note
					*
					**/
					void			DestroyAllChild();
	
					/**	\brief	更新
					*	
					*	@remarks 	更新
					*	@see		IControl
					*	@return   	void
					*	@note
					*
					**/
					virtual	void	Updata();
					virtual	void	SetCenter(Float2	vCenter	=	TopLeft);
					virtual	Float2	GetCenter();
					virtual	void	SetPosition(Float2&	vPosition);
					virtual	Float2	GetPosition();
					virtual	Float2	GetAbsolutelyPosition();
					virtual	void	SetWindowSize(Float2&	vSize);
					virtual	Float2	GetWindowSize();
					virtual	void	SetColor(Float3 vColor);
					virtual	Float3	GetColor();
					virtual	void	SetAlpha(Real	fAlpha);
					virtual	Real	GetAlpha();
					virtual	void	SetColorAlpha(Float4	v);
					virtual	Float4	GetColorAlpha();
					virtual	Float4	GetPositionSize();
					/**	\brief	判断是否鼠标在此区域中
					*   
					*	@remarks 	判断是否鼠标在此区域中
					*	@see		IControl
					*	@return   	IControl*
					*	@note
					*
					**/
					virtual	IControl*		IsMouseInWindow();
	
					/**	\brief	渲染
					*   
					*	@remarks 	渲染
					*	@see		IControl
					*	@return   	void
					*	@note
					*
					**/
					virtual	void	Render();
	
					virtual	void	RenderCache();
					virtual	void	RenderUI();
	
					/**	\brief	是否为根窗口
					*   
					*	@remarks 	是否为根窗口
					*	@see		IControl
					*	@return   	U1
					*	@note
					*
					**/
					U1				IsRootWindow(){
						return	(m_pParent==NULL);
					}
	
					/**	\brief	刷新
					*   
					*	@remarks 	刷新
					*	@see		IControl
					*	@return   	void
					*	@note
					*
					**/
					void			Refresh();
	
					/**	\brief	获取第一个子窗口
					*   
					*	@remarks 	获取第一个子窗口
					*	@see		IControl
					*	@return   	IControl*
					*	@note
					*
					**/
					IControl*		GetFirstChildWindow();
					/**	\brief	获取子窗口
					*   
					*	@remarks 	获取子窗口
					*	@see		IControl
					*	@return   	IControl*
					*	@param		AString strName
					*	@note
					*
					**/
					IControl*		GetChildWindow(AString	strName);
					/**	\brief	渲染元素
					*   
					*	@remarks 	
					*	@see		State
					*	@return   	void
					*	@param		ElementArray&	eArray
					*	@note
					*
					**/
					virtual	void	BeforeRenderElement(ElementArray&	eArray);
	
					/**	\brief	是否被改变
					*   
					*	@remarks 	包括位置 大小 颜色 文字
					*	@see		IControl
					*	@return   	U1
					*	@note
					*
					**/
					U1				IsChanged();
					/**	\brief	设置所有UI需要重新渲染
					*   
					*	@remarks 	针对设备丢失时 的恢复
					*	@see		IControl
					*	@return   	void
					*	@note
					*
					**/
					void			SetNeedReRender();
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
				protected:
					/**	\brief	设置父节点
					*   
					*	@remarks 	设置父节点
					*	@see		IControl
					*	@return   	void
					*	@param		IControl * pParent
					*	@note
					*
					**/
					void	SetParent(IControl*	pParent);
	
					/**	\brief	刷新大小
					*   
					*	@remarks 	刷新大小
					*	@see		IControl
					*	@return   	void
					*	@note
					*
					**/
					virtual	void	RefreshSize();
					/**	\brief	刷新位置
					*   
					*	@remarks 	刷新位置
					*	@see		IControl
					*	@return   	void
					*	@note
					*
					**/
					virtual	void	RefreshPosition();
	
					/**	\brief	刷新颜色
					*   
					*	@remarks 	刷新颜色
					*	@see		IControl
					*	@return   	void
					*	@note
					*
					**/
					virtual	void	RefreshColor();
				protected:
					Float4				m_vAbsolutelyPosition;
					
					
					U32*				m_piOrginScreenWidth;			///<	屏幕宽
					U32*				m_piOrginScreenHeight;			///<	屏幕高
	
					IControl*			m_pParent;						///<	父节点
					WindowList			m_lstWindow;
	
					//Font*				m_pFont;
					RenderTarget*		m_pTarget;
				};
			}
		};
	
	};
};
#endif // INTERFACEUIControl_HEAD_FILE