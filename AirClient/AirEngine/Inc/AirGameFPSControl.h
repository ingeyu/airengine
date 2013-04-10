#ifndef GAMEFPSCONTROL_HEAD_FILE
#define GAMEFPSCONTROL_HEAD_FILE


#include "AirGameControl.h"
namespace Air{
	
	
	
	namespace	Game{
		class Section;
			
		/**	\brief	第一人称射击
		*
		*	第一人称射击
		*
		***/
		class	ENGINE_EXPORT	FPSControl	:
			public	Common::IProduct,
			public	Control
			{
		public:
			static AString	ProductTypeName;
			/**	\brief	创建信息
			*
			*	创建信息
			*
			***/
			struct	Info{
				Info(){
					pSection		=	NULL;
					//vPosition		=	Vector3::ZERO;
					vVelocity		=	3.0f;
					vCameraHeight	=	1.8f;
					pCamera			=	NULL;
				};
				Section*	pSection;		///<	关卡名字
				Float3		vPosition;		///<	初始位置
				Real		vVelocity;		///<	移动速度
				Real		vCameraHeight;	///<	摄像机高度
				Engine::Camera*		pCamera;
					
			};
		public:
			FPSControl(AString	strName,Info*	pInfo);
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		FPSControl
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Create();
			/**	\brief	摧毁
			*   
			*	@remarks 	摧毁
			*	@see		FPSControl
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Destroy();
	
			/**	\brief	获取摄像机
			*   
			*	@remarks 	获取摄像机
			*	@see		FPSControl
			*	@return   	Camera*
			*	@note
			*
			**/
			virtual	Engine::Camera*	GetCamera();
	
	
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
			virtual	U1		OnFrameMove();
	
			/**	\brief	获取控制节点
			*   
			*	@remarks 	
			*	@see		FPSControl
			*	@return   	SceneNode*
			*	@note
			*
			**/
			virtual	Engine::SceneNode*	GetControlNode();
			/**	\brief	位置
			*   
			*	@remarks 	位置
			*	@see		FPSControl
			*	@return   	void
			*	@param		Vector3 vPosition
			*	@note
			*
			**/
			virtual	void		SetPosition(Float3	vPosition);
	
			inline	U1			IsStateChange(){
				return	(m_State!=m_LastState);
			};
	
		protected:
			Info					m_Info;
			Section*				m_pSection;
			Engine::Camera*			m_pCamera;				///<	控制摄像机
			Engine::SceneNode*		m_pNode;				///<	控制器基本节点
			Engine::SceneNode*		m_pLRNode;				///<	左右旋转控制节点
			Engine::SceneNode*		m_pCameraUDNode;		///<	镜头上下摇动控制节点
			Engine::SceneNode*		m_pCameraNode;			///<	摄像机节点
			Real					m_fLRAngle;				///<	左右旋转角度
			Real					m_fUDAngle;				///<	上下旋转角度
			Real					m_fCurrentLRAngle;		///<	当前左右旋转角度
			Real					m_fCurrentUDAngle;		///<	上下旋转角度
			//Physics::IController*		m_pController;			///<	物理模块的控制器
			enumActorState			m_State;			
			enumActorState			m_LastState;
			enumAction				m_Action;
		};

	}
	
};
#endif // GAMEFPSCONTROL_HEAD_FILE