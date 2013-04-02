#ifndef INTERFACEPHYSICSCONTROLLER_HEAD_FILE
#define INTERFACEPHYSICSCONTROLLER_HEAD_FILE
namespace Air{
	
	namespace Engine{
	
		namespace	Physics{
			class	IController;
			/**	\brief	碰撞信息
			*
			*	碰撞信息
			*
			***/
			struct	CollisionHit{
				//ICollision*	pCollision;
				Float3		vPosition;
				Float3		vNormal;
				Float3		vDirection;
				Real		fLength;
			};
			/**	\brief	碰撞回调
			*
			*	碰撞回调
			*
			***/
			class	IHitCallBack{
			public:
				virtual	~IHitCallBack(){};
				/**	\brief	当碰撞到物体
				*   
				*	@remarks 	当碰撞到物体
				*	@see		IHitCallBack
				*	@return   	void
				*	@param		CollisionHit * pHit
				*	@note
				*
				**/
				virtual	void	OnCollisionHit(CollisionHit*	pHit)			=	NULL;
				/**	\brief	当碰撞到控制器
				*   
				*	@remarks 	当碰撞到控制器
				*	@see		IHitCallBack
				*	@return   	void
				*	@param		IController * pController
				*	@note
				*
				**/
				virtual	void	OnControllerHit(IController*	pController)	=	NULL;
			};
			/**	\brief	角色控制器
			*
			*	角色控制器
			*
			***/
			class	IController{
			public:
				enum	enumType{
					enBox,
					enCapsule
				};
				struct	Info{
					Info(){
						size			=	Float3(0.5f,1.8f,0.5f);
						initPosition	=	Float3(0,1,0);//::UNIT_Y;
						slopeLimit		=	0.785f;
						stepOffset		=	0.5f;
						type			=	enCapsule;
						upDirType		=	1;
						skinWidth		=	0.2f;
						pCallBack		=	NULL;
					};
					
					Float3			size;			///<	x长度 z宽度 y高度
					Float3			initPosition;	///<	初始位置
					Real			slopeLimit;		///<	坡度限制
					Real			stepOffset;		///<	可跨越的台阶高度
					Real			skinWidth;		///<	皮肤厚度
					enumType		type;			///<	碰撞类型
					UInt			upDirType;		///<	顶方向类型	x=0 y=1 z=2
					IHitCallBack*	pCallBack;		///<	回调函数
				};
	
				/**	\brief	设置位置
				*   
				*	@remarks 	设置位置
				*	@see		IController
				*	@return   	void
				*	@param		Float3 vPosition
				*	@note
				*
				**/
				virtual	void		SetPosition(Float3	vPosition)	=	NULL;
				/**	\brief	获取位置
				*   
				*	@remarks 	获取位置
				*	@see		IController
				*	@return   	Client::Float3
				*	@note
				*
				**/
				virtual	Float3		GetPosition()					=	NULL;
				/**	\brief	移动
				*   
				*	@remarks 	移动
				*	@see		IController
				*	@return   	void
				*	@param		Float3 vDirection
				*	@note
				*
				**/
				virtual	void		Move(Float3	vDirection)		=	NULL;
	
				/**	\brief	获取类型
				*   
				*	@remarks 	获取类型
				*	@see		IController
				*	@return   	Client::Physx::IController::enumType
				*	@note
				*
				**/
				virtual	enumType	GetType()						=	NULL;
			};
		}
	
	};
};
#endif // INTERFACEPHYSXCONTROLLER_HEAD_FILE