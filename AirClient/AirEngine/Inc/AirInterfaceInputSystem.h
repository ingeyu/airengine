#ifndef INTERFACEINPUTSYSTEM_HEAD_FILE
#define INTERFACEINPUTSYSTEM_HEAD_FILE

#include "AirEngine.h"
#include "AirEngineHeader.h"
#include "OIS.h"

namespace Air{
	
	namespace	Engine{
		namespace	Input{
			typedef	Air::Common::IPlugin	IPlugin;
		
			class State{
			public:
				State(){
					m_iX				=	0;
					m_iY				=	0;
					m_iXDelta			=	0;
					m_iYDelta			=	0;
					m_iZDelta			=	0;
		
					memset(m_KeyArray,	0,MAX_NAME);
					memset(m_MouseArray,0,8);
				};
				Air::SInt			m_iX;
				Air::SInt			m_iY;
				Air::SInt			m_iXDelta;
				Air::SInt			m_iYDelta;
				Air::SInt			m_iZDelta;
				Air::S8				m_KeyArray[MAX_NAME];		///<	键盘按键状态
				Air::S8				m_MouseArray[8];			///<	鼠标按键状态
			};
		
			/**	\brief	输入系统接口
			*
			*	输入系统接口
			*
			***/
			class	ISystem	:	
				public	Common::ISystem,
				public	State{
			public:
				ISystem():Common::ISystem("InputSystem"){

				};
		
				enum	enumType{
					enKey,
					enMouse,
					enJoyStick
				};
				/**	\brief	添加键盘回调
				*   
				*	@remarks 	添加键盘回调
				*	@see		ISystem
				*	@return   	void
				*	@param		KeyListener * pListener
				*	@note
				*
				**/
				virtual void		Add(::OIS::KeyListener*	pListener)					=	NULL;
				/**	\brief	添加鼠标回调
				*   
				*	@remarks 	添加鼠标回调
				*	@see		ISystem
				*	@return   	void
				*	@param		MouseListener * pListener
				*	@note
				*
				**/
				virtual	void		Add(::OIS::MouseListener*	pListener)				=	NULL;
				/**	\brief	添加手柄回调
				*   
				*	@remarks 	添加手柄回调
				*	@see		ISystem
				*	@return   	void
				*	@param		JoyStickListener * pListener
				*	@note
				*
				**/
				virtual void		Add(::OIS::JoyStickListener*	pListener)		=	NULL;
		
				/**	\brief	移除键盘回调
				*   
				*	@remarks 	移除键盘回调
				*	@see		ISystem
				*	@return   	void
				*	@param		KeyListener * pListener
				*	@note
				*
				**/
				virtual void		Remove(::OIS::KeyListener*	pListener)				=	NULL;
				/**	\brief	移除鼠标回调
				*   
				*	@remarks 	移除鼠标回调
				*	@see		ISystem
				*	@return   	void
				*	@param		KeyListener * pListener
				*	@note
				*
				**/
				virtual	void		Remove(::OIS::MouseListener*	pListener)			=	NULL;
				/**	\brief	移除手柄回调
				*   
				*	@remarks 	移除手柄回调
				*	@see		ISystem
				*	@return   	void
				*	@param		KeyListener * pListener
				*	@note
				*
				**/
				virtual void		Remove(::OIS::JoyStickListener*	pListener)		=	NULL;
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
				virtual void		Enable(enumType	type,U1	bEnable)					=	NULL;
				/**	\brief	回调是否已启用
				*   
				*	@remarks 	回调是否已启用
				*	@see		ISystem
				*	@return   	U1
				*	@param		AString strName
				*	@note
				*
				**/
				virtual U1			IsEnable(enumType	type)							=	NULL;
				/**	\brief	启用所有回调
				*   
				*	@remarks 	启用所有回调
				*	@see		ISystem
				*	@return   	void
				*	@param		U1 bEnable
				*	@note
				*
				**/
				virtual void		EnableAll(U1	bEnable)								=	NULL;
		
		
				/**	\brief	获取消息
				*
				*	获取消息
				*
				***/
				virtual U1			Capture()	=	NULL;
		
				
				/**	\brief	设置鼠标位置
				*   
				*	@remarks 	设置鼠标位置
				*	@see		ISystem
				*	@return   	void
				*	@param		SInt x
				*	@param		SInt y
				*	@note
				*
				**/
				//virtual	void		SetCursorPosition(SInt x,SInt y)	=	NULL;
		
			public:
		
			};
		};
	};
};


#endif // INTERFACEINPUTSYSTEM_HEAD_FILE