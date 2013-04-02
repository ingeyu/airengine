#ifndef ENGINEINPUTSYSTEM_HEAD_FILE
#define ENGINEINPUTSYSTEM_HEAD_FILE

#include "AirInterfaceInputSystem.h"



namespace Air{
	
	namespace Engine{
	
		namespace	Input{
			class	System	: 
				public	::OIS::KeyListener, 
				public	::OIS::MouseListener, 
				public	::OIS::JoyStickListener,
				public	ISystem{
			public:
				System();
	
				virtual ~System();
	
				//键盘
				virtual bool keyPressed( const ::OIS::KeyEvent &arg );
				virtual bool keyReleased( const ::OIS::KeyEvent &arg );
				//鼠标
				virtual bool mouseMoved( const ::OIS::MouseEvent &arg );
				virtual bool mousePressed( const ::OIS::MouseEvent &arg, ::OIS::MouseButtonID id );
				virtual bool mouseReleased( const ::OIS::MouseEvent &arg, ::OIS::MouseButtonID id );
	
				//手柄
				virtual bool buttonPressed( const ::OIS::JoyStickEvent &arg, int button );
				virtual bool buttonReleased( const ::OIS::JoyStickEvent &arg, int button );
				virtual bool axisMoved( const ::OIS::JoyStickEvent &arg, int axis );
				virtual bool povMoved( const ::OIS::JoyStickEvent &arg, int pov );
				virtual bool vector3Moved( const ::OIS::JoyStickEvent &arg, int index);
	
				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Initialization();
	
	
				virtual U1	Start();
				virtual U1	Stop();
				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Release();
	
				/**	\brief	添加键盘回调
				*   
				*	@remarks 	添加键盘回调
				*	@see		ISystem
				*	@return   	void
				*	@param		KeyListener * pListener
				*	@note
				*
				**/
				virtual void		Add(::OIS::KeyListener*	pListener);
				/**	\brief	添加鼠标回调
				*   
				*	@remarks 	添加鼠标回调
				*	@see		ISystem
				*	@return   	void
				*	@param		MouseListener * pListener
				*	@note
				*
				**/
				virtual	void		Add(::OIS::MouseListener*	pListener);
				/**	\brief	添加手柄回调
				*   
				*	@remarks 	添加手柄回调
				*	@see		ISystem
				*	@return   	void
				*	@param		JoyStickListener * pListener
				*	@note
				*
				**/
				virtual void		Add(::OIS::JoyStickListener*	pListener);
	
				/**	\brief	移除键盘回调
				*   
				*	@remarks 	移除键盘回调
				*	@see		ISystem
				*	@return   	void
				*	@param		KeyListener * pListener
				*	@note
				*
				**/
				virtual void		Remove(::OIS::KeyListener*	pListener);
				/**	\brief	移除鼠标回调
				*   
				*	@remarks 	移除鼠标回调
				*	@see		ISystem
				*	@return   	void
				*	@param		KeyListener * pListener
				*	@note
				*
				**/
				virtual	void		Remove(::OIS::MouseListener*	pListener);
				/**	\brief	移除手柄回调
				*   
				*	@remarks 	移除手柄回调
				*	@see		ISystem
				*	@return   	void
				*	@param		KeyListener * pListener
				*	@note
				*
				**/
				virtual void		Remove(::OIS::JoyStickListener*	pListener);
	
				/**	\brief	启用回调
				*   
				*	@remarks 	启用回调
				*	@see		ISystem
				*	@return   	void
				*	@param		AString strName
				*	@param		U1 bEnable
				*	@note
				*
				**/
				virtual void		Enable(enumType	type,U1	bEnable);
				/**	\brief	回调是否已启用
				*   
				*	@remarks 	回调是否已启用
				*	@see		ISystem
				*	@return   	U1
				*	@param		AString strName
				*	@note
				*
				**/
				virtual U1			IsEnable(enumType	type);
				/**	\brief	启用所有回调
				*   
				*	@remarks 	启用所有回调
				*	@see		ISystem
				*	@return   	void
				*	@param		U1 bEnable
				*	@note
				*
				**/
				virtual void		EnableAll(U1	bEnable);
	
				/**	\brief	清空所有
				*   
				*	@remarks 	清空所有
				*	@see		System
				*	@return   	void
				*	@note
				*
				**/
				void				RemoveAll();
	
				/**	\brief	捕获输入状态
				*   
				*	@remarks 	捕获输入状态
				*	@see		System
				*	@return   	void
				*	@note
				*
				**/
				U1				Capture();
	
			private:
	
				::OIS::InputManager*	m_pInputMgr;		///<	输入管理器
				::OIS::Keyboard*		m_pKeyboard;		///<	键盘
				::OIS::Mouse*			m_pMouse;			///<	鼠标
				::OIS::JoyStick*		m_pJoyStick[4];		///<	手柄
	
				U1				m_bMouseEnable;		///<	是否启用鼠标回调
				U1				m_bKeyEnable;		///<	是否启用键盘回调
				U1				m_bJoyStickEnable;	///<	是否启用手柄回调
	
				typedef	std::list<::OIS::MouseListener*>		MouseListenList;
				typedef	std::list<::OIS::KeyListener*>			KeyListenList;
				typedef	std::list<::OIS::JoyStickListener*>	JoyStickListenList;
	
				MouseListenList		m_lstMouse;			///<	鼠标回调列表
				KeyListenList		m_lstKey;			///<	键盘回调列表
				JoyStickListenList	m_lstJoyStick;		///<	手柄回调列表
			};
	
	
		}
	
	
	};
};
#endif // ENGINEINPUTSYSTEM_HEAD_FILE