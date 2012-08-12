#ifndef INTERFACEPHYSICSSCENE_HEAD_FILE
#define INTERFACEPHYSICSSCENE_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirInterfacePhysicsCollision.h"
#include "AirInterfacePhysicsController.h"
#include "AirInterfacePhysicsCloth.h"
namespace Air{
	
	namespace Client{
	
		namespace	Physics{
			//class	ICollision;
			/**	\brief	物理场景
			*
			*	物理场景
			*
			***/
			class	IScene	:
				public	IFactoryManager{
			public:
				/**	\brief	初始化
				*   
				*	@remarks 	初始化
				*	@see		IScene
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Initialization()	=	NULL;
				/**	\brief	释放
				*   
				*	@remarks 	释放
				*	@see		IScene
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Release()			=	NULL;
				/**	\brief	模拟
				*   
				*	@remarks 	模拟 bSynchronous为false时 为异步模拟  建议使用异步模式
				*	@see		IScene
				*	@return   	U1
				*	@param		U1 bSynchronous
				*	@note
				*
				**/
				virtual	U1	Simulate(U1	bSynchronous	=	true)	=	NULL;
	
				/**	\brief	射线检测
				*   
				*	@remarks 	射线检测
				*	@see		IScene
				*	@return   	U1
				*	@param		Ray ray
				*	@param		Float3 * pHitPosition
				*	@param		Float3 * pNormal
				*	@param		Real * fDistance
				*	@note
				*
				**/
				virtual	U1	RayCast(Ray	ray,Float3*	pHitPosition	=	NULL,Float3*	pNormal	=	NULL,Real*	fDistance	=	NULL,void**	ppUserData	=	NULL)	=	NULL;
	
				/**	\brief	是否已经模拟完毕
				*   
				*	@remarks 	是否已经模拟完毕	没有模拟完毕时 创建物理模型 摧毁模型都会失败
				*	@see		IScene
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		WaitSimulateFinished()	=	NULL;
			};
		}
	
	};
};
#endif // INTERFACEPHYSXSCENE_HEAD_FILE