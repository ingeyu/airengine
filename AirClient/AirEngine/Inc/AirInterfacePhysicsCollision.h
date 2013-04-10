#ifndef INTERFACEPHYSICSCOLLISION_HEAD_FILE
#define INTERFACEPHYSICSCOLLISION_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirInterfaceUserData.h"
#include "AirInterfacePhysicsShape.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Physics{
			class	ICollision;
			/**	\brief	触发器回调
			*
			*	触发器回调
			*
			***/
			class	ITriggerCallback{
			public:
				/**	\brief	触发器事件类型
				*
				*	触发器事件类型
				*
				***/
				enum	enumType{
					enEnter,
					enLeave,
					enStay,
					enUnKnown
				};
				/**	\brief	回调接口
				*   
				*	@remarks 	回调接口
				*	@see		ITriggerCallback
				*	@return   	void
				*	@param		enumType type
				*	@param		ICollision * pCollision
				*	@note
				*
				**/
				virtual	void	OnTrigger(enumType	type,ICollision*	pCollision)	=	NULL;
			};
			/**	\brief	碰撞物体
			*
			*	碰撞物体
			*
			***/
			class	ICollision	:
				public	TProduct<ICollision>{
			public:
				enum	enumType{
					enDynamic,		///<	动态
					enStatic,		///<	静态
					enKinematic		///<	动力学(就是手动控制的物体)
				};
				/**	\brief	创建信息
				*
				*	创建信息
				*
				***/
				struct	Info{
					Info(){
						fMass		=	1.0f;
						type		=	enStatic;
						vPosition	=	Float3(0,0,0);//Float3::ZERO;
						vQuat		=	Float4(0,0,0,1);//Float4::IDENTITY;
						fDensity	=	-1.0f;	
						pCallback	=	NULL;
						initvelocity	=	Float3(0,0,0);//Float3::ZERO;
						angularDamping	=	0.5f;
					};
					/**	\brief	设置为动态物体
					*   
					*	@remarks 	设置为动态物体
					*	@see		Info
					*	@return   	void
					*	@param		Real density
					*	@note
					*
					**/
					void	SetDynamic(Real	density){
						type		=	enDynamic;
						fDensity	=	density;
					};
					Real		fMass;			///<	质量
					Float3		vPosition;		///<	位置
					Float4		vQuat;			///<	旋转量
					enumType	type;			///<	类型
					Real		fDensity;		///<	密度	(大于0 表面是动态物体 小于零是动态物体)
					Shape		shape;			///<	外形
					Real		angularDamping;	///<	阻尼角
					Float3		initvelocity;	///<	初识速度
					ITriggerCallback*	pCallback;	///<	触发器回调接口
				};
			public:
				ICollision(CAString&	strName,Info*	pInfo):TProduct(strName){
					if(pInfo!=NULL){
						m_Info	=	*pInfo;
					}
				}
				/**	\brief	获取位置
				*   
				*	@remarks 	获取位置
				*	@see		ICollision
				*	@return   	Float3
				*	@note
				*
				**/
				virtual	Float3		GetPosition()					=	NULL;
				virtual	void		SetPosition(Float3	vPosition)	=	NULL;
				virtual	void		MovePosition(Float3 vPosition)	=	NULL;
				/**	\brief	获取旋转量
				*   
				*	@remarks 	获取旋转量
				*	@see		ICollision
				*	@return   	Float4
				*	@note
				*
				**/
				virtual	Float4		GetQuat()						=	NULL;
				virtual	void		SetQuat(Float4	quat)		=	NULL;
				virtual	void		MoveQuat(Float4	quat)		=	NULL;
	
				/**	\brief	获取矩阵
				*   
				*	@remarks 	获取矩阵
				*	@see		ICollision
				*	@return   	Client::Float44
				*	@note
				*
				**/
				virtual	Float44		GetMatrix()						=	NULL;
				virtual	void		SetMatrix()						=	NULL;
	
				/**	\brief	获取类型
				*   
				*	@remarks 	获取类型
				*	@see		ICollision
				*	@return   	Client::Physx::ICollision::enumType
				*	@note
				*
				**/
				virtual	enumType	GetType()						=	NULL;
				virtual	void		SetType(enumType	type)		=	NULL;
	
				/**	\brief	获取重心
				*   
				*	@remarks 	获取重心
				*	@see		ICollision
				*	@return   	Client::Float3
				*	@note
				*
				**/
				virtual	Float3		GetMassPosition()						=	NULL;
				virtual	void		SetMassPosition(Float3	vMass)			=	NULL;
	
				/**	\brief	获取质量
				*   
				*	@remarks 	获取质量
				*	@see		ICollision
				*	@return   	Real
				*	@note
				*
				**/
				virtual	Real		GetMass()								=	NULL;
				virtual	void		SetMass(Real	fMass)					=	NULL;
	
	
				virtual	void		AddForce(Float3	vForce)				=	NULL;
				virtual	void		AddForceAtLocalPos(Float3	vForce,Float3	vPos)	=	NULL;
				virtual	void		AddForceAtPos(Float3	vForce,Float3	vPos)		=	NULL;
				virtual	void		AddLocalForce(Float3	vForce)			=	NULL;
				virtual	void		AddLocalForceAtLocalPos(Float3	vForce,Float3	vPos)	=	NULL;
				virtual	void		AddTorque(Float3	vTorque)			=	NULL;
				virtual	void		AddLocalTorque(Float3	vTorque)		=	NULL;
				virtual	void		AddVelocity(Float3	vVelocity)			=	NULL;
				virtual	void		AddSelfVelocity(Float3	vVelocity)		=	NULL;
	
				//virtual		void			setLinearVelocity(const NxVec3& linVel)


				Info				m_Info;
			};
		}
	
	};
};
#endif // INTERFACEPHYSXCOLLISION_HEAD_FILE