#ifndef GAMECONTROL_HEAD_FILE
#define GAMECONTROL_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirInterfaceInputSystem.h"

namespace Air{
	namespace	Game{
		/**	\brief	状态
		*
		*	状态
		*
		***/
		enum	enumMoveState{
			enMS_NoMove			=	0,
			enMS_Left			=	1,
			enMS_Right			=	2,
			enMS_Run			=	4,
			enMS_Back			=	8,
			enMS_RunLeft		=	enMS_Run	|enMS_Left,
			enMS_RunRight		=	enMS_Run	|enMS_Right,
			enMS_BackLeft		=	enMS_Back	|enMS_Left,
			enMS_BackRight		=	enMS_Back	|enMS_Right,
		};
		enum	enumActorState{
			enAS_Stand,
			enAS_Walk,
			enAS_Idle,
			enAS_Jump,
			enAS_Jumping,
			enAS_Dieing,
			enAS_Death,
			enAS_Casting
		};
		/**	\brief	动作
		*
		*	动作
		*
		***/
		enum	enumAction{
			enA_None,
			enA_LAttack,
			enA_MAttack,
			enA_RAttack,
			enA_SpaceAction,
			enA_MagicAttack1,
			enA_MagicAttack2,
			enA_MagicAttack3,
			enA_MagicAttack4,
			enA_MagicAttack5,
			enA_Health,
		};
	
		enum	enumGameState{
			enLogin,
			enGame,
			enExit
		};

		enum	enumKeyEventType{
			enKET_MouseDown,
			enKET_MouseUp,
			enKET_MouseMove,
			enKET_KeyDown,
			enKET_KeyUp,
		};
		enum	enumKeyHelpType{
			enKHT_Control,
			enKHT_Alt,
			enKHT_Shift
		};

		struct Key;
		typedef 	void	(__stdcall *KeyCallback)(void*	pThis,const Key& k);
		template <typename T>
		inline KeyCallback	ConverertFunction(T t){
#ifdef _X86_
			U32* pp =	(U32*)&t;	
#else
			U64* pp	=	(U64*)&t;	
#endif
			KeyCallback* ppCB	=	(KeyCallback*)pp;
			return *ppCB;
		};
		struct Key{
			union{
				struct{
					U32 control	:	1;
					U32	alt		:	1;
					U32	shift	:	1;
					U32	evt		:	8;
					U32	mouse	:	8;
					U32	key		:	8;
					
				};
				U32 uiKeyValue;
			};
			void*			pObject;
			KeyCallback		pCB;
		};
		typedef STD_HASHMAP<U32,Key>	KeyCallBackMap;
		/**	\brief	动作状态回调
		*
		*	动作状态回调
		*
		***/
		class	IActionState{
		public:
			virtual	void	OnActorState(enumActorState	state,enumMoveState mstate)	=	NULL;
			virtual	void	OnAction(enumAction	action)	=	NULL;
			virtual	void	OnGameState(enumGameState	state)	=	NULL;
		};
			
		/**	\brief	游戏输入控制
		*
		*	游戏输入控制
		*
		***/
		class	ENGINE_EXPORT	Control	:
			public	Common::IProduct,
			public	::OIS::KeyListener,
			public	::OIS::MouseListener,
			public	::OIS::JoyStickListener{
		public:
			Control(CAString& strName);
			/**	\brief	键盘按下事件
			*   
			*	@remarks 	键盘按下事件
			*	@see		Control
			*	@return   	bool
			*	@param		const Input::KeyEvent & arg
			*	@note
			*
			**/
			virtual bool	keyPressed( const OIS::KeyEvent &arg );
			/**	\brief	键盘释放事件
			*   
			*	@remarks 	键盘释放事件
			*	@see		Control
			*	@return   	bool
			*	@param		const Input::KeyEvent & arg
			*	@note
			*
			**/
			virtual bool	keyReleased( const OIS::KeyEvent &arg );
			/**	\brief	鼠标移动事件
			*   
			*	@remarks 	鼠标移动事件
			*	@see		Control
			*	@return   	bool
			*	@param		const Input::MouseEvent & arg
			*	@note
			*
			**/
			virtual bool	mouseMoved( const OIS::MouseEvent &arg );
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
			virtual bool	mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
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
			virtual bool	mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	
			/**	\brief	手柄按钮按下
			*   
			*	@remarks 	手柄按钮按下
			*	@see		Control
			*	@return   	bool
			*	@param		const Input::JoyStickEvent & arg
			*	@param		int button
			*	@note
			*
			**/
			virtual bool	buttonPressed( const OIS::JoyStickEvent &arg, int button );
			/**	\brief	手柄按钮释放
			*   
			*	@remarks 	手柄按钮释放
			*	@see		Control
			*	@return   	bool
			*	@param		const Input::JoyStickEvent & arg
			*	@param		int button
			*	@note
			*
			**/
			virtual bool	buttonReleased( const OIS::JoyStickEvent &arg, int button );
			/**	\brief	手柄方向键
			*   
			*	@remarks 	手柄方向键
			*	@see		Control
			*	@return   	bool
			*	@param		const Input::JoyStickEvent & arg
			*	@param		int axis
			*	@note
			*
			**/
			virtual bool	axisMoved( const OIS::JoyStickEvent &arg, int axis );
	
			/**	\brief	每帧调用
			*   
			*	@remarks 	每帧调用
			*	@see		Control
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1		Update(const FrameTime& frameTime);
	
			/**	\brief	启用键盘消息处理
			*   
			*	@remarks 	启用键盘消息处理
			*	@see		Control
			*	@return   	void
			*	@param		U1 bEnable
			*	@note
			*
			**/
			inline	void	SetKeyboardEnable(U1	bEnable){m_bEnableKeyboard	=	bEnable;};
			/**	\brief	启用鼠标消息处理
			*   
			*	@remarks 	启用鼠标消息处理
			*	@see		Control
			*	@return   	void
			*	@param		U1 bEnable
			*	@note
			*
			**/
			inline	void	SetMouseEnable(U1	bEnable){m_bEnableMouse	=	bEnable;};
			/**	\brief	启用手柄消息处理
			*   
			*	@remarks 	启用手柄消息处理
			*	@see		Control
			*	@return   	void
			*	@param		U1 bEnable
			*	@note
			*
			**/
			inline	void	SetJoyStickEnable(U1	bEnable){m_bEnableJoyStick	=	bEnable;};
			/**	\brief	键盘是否启用
			*   
			*	@remarks 	键盘是否启用
			*	@see		Control
			*	@return   	U1
			*	@note
			*
			**/
			inline	U1		GetKeyboardEnable(){return	m_bEnableKeyboard;};
			/**	\brief	鼠标是否启用
			*   
			*	@remarks 	鼠标是否启用
			*	@see		Control
			*	@return   	U1
			*	@note
			*
			**/
			inline	U1		GetMouseEnable(){return	m_bEnableMouse;};
			/**	\brief	手柄是否启用
			*   
			*	@remarks 	手柄是否启用
			*	@see		Control
			*	@return   	U1
			*	@note
			*
			**/
			inline	U1		GetJoyStickEnable(){return	m_bEnableJoyStick;};
	
			/**	\brief	启用所有消息处理
			*   
			*	@remarks 	启用所有消息处理
			*	@see		Control
			*	@return   	void
			*	@note
			*
			**/
			inline	void	SetAllEnable(U1	bEnable){
				m_bEnableKeyboard	=	bEnable;
				m_bEnableMouse		=	bEnable;
				m_bEnableJoyStick	=	bEnable;
			};
	
			/**	\brief	添加一个子控制
			*   
			*	@remarks 	添加一个子控制
			*	@see		Control
			*	@return   	void
			*	@param		Control * pControl
			*	@note
			*
			**/
			void	AddControl(Control*	pControl);
			/**	\brief	移除一个子控制
			*   
			*	@remarks 	移除一个子控制
			*	@see		Control
			*	@return   	void
			*	@param		Control * pControl
			*	@note
			*
			**/
			void	RemoveControl(Control*	pControl);
	
			/**	\brief	获取控制节点
			*   
			*	@remarks 	获取控制节点
			*	@see		Control
			*	@return   	ISceneNode*
			*	@note
			*
			**/
			virtual	Engine::SceneNode*		GetControlNode();
	
			/**	\brief	设置回调
			*   
			*	@remarks 	设置回调
			*	@see		Control
			*	@return   	void
			*	@param		IActionState * pCallback
			*	@note
			*
			**/
			inline	void	SetCallback(IActionState*	pCallback){
				m_pActionStateCallback	=	pCallback;
			}
			void			RegisterMouseCallback(OIS::MouseButtonID	mouse,const void* pObject,KeyCallback pCB,enumKeyEventType evt=enKET_MouseUp,U1 bControl=false,U1 bAlt=false,U1 bShift=false);
			void			RegisterKeyCallback(OIS::KeyCode		key,const void* pObject,KeyCallback pCB,enumKeyEventType evt=enKET_KeyUp,U1 bControl=false,U1 bAlt=false,U1 bShift=false);
			void			RegisterKeyCallback(const Key& k);
			void			UnRegisterKeyCallback(U32 key);

			Ray				GetMouseRay(S32 x,S32 y);
		protected:
			Engine::Input::State*	m_pInputState;			///<	键盘状态
			U1						m_bEnableKeyboard;		///<	是否启用键盘消息
			U1						m_bEnableMouse;			///<	是否启用鼠标消息
			U1						m_bEnableJoyStick;		///<	是否启用手柄消息
			typedef		std::list<Control*>		ControlList;
			typedef		ControlList::iterator	ControlListItr;
	
			ControlList		m_lstControl;
	
			IActionState*	m_pActionStateCallback;
			KeyCallBackMap			m_mapKeyCallback;
		};

	}
	

};
#endif // GAMECONTROL_HEAD_FILE