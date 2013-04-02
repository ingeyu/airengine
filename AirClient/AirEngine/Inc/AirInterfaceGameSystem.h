#ifndef INTERFACEGAMESYSTEM_HEAD_FILE
#define INTERFACEGAMESYSTEM_HEAD_FILE

#include "AirEngineHeader.h"
namespace Air{
	
	namespace Engine{
		namespace	Game{
			/**	\brief	游戏系统基类
			*
			*	游戏系统基类
			*
			***/
	// 		class	ENGINE_EXPORT	ISystem	:	
	// 			public	IPlugin,	
	// 			public	IFactoryManager{
	// 		public:
	// 			ISystem();
	// 			virtual ~ISystem();
	// 			
	// 			/**	\brief	帧回调通知
	// 			*   
	// 			*	@remarks 	帧回调通知
	// 			*	@see		ISystem
	// 			*	@return   	void
	// 			*	@param		Real fTotalTime
	// 			*	@param		Real fDeltaTime
	// 			*	@note
	// 			*
	// 			**/
	// 			virtual void	OnFrameMove(Real fTotalTime,Real fDeltaTime)	=	NULL;
	// 			/**	\brief	渲染前通知
	// 			*   
	// 			*	@remarks 	渲染通知
	// 			*	@see		ISystem
	// 			*	@return   	void
	// 			*	@note
	// 			*
	// 			**/
	// 			virtual void	OnBeforeRender()	=	NULL;
	// 			/**	\brief	渲染通知
	// 			*   
	// 			*	@remarks 	渲染通知
	// 			*	@see		ISystem
	// 			*	@return   	void
	// 			*	@note
	// 			*
	// 			**/
	// 			virtual void	OnRender()			=	NULL;
	// 			/**	\brief	渲染后通知
	// 			*   
	// 			*	@remarks 	渲染后通知
	// 			*	@see		ISystem
	// 			*	@return   	void
	// 			*	@note
	// 			*
	// 			**/
	// 			virtual void	OnAfterRender()		=	NULL;
	// 			/**	\brief	GUI事件回调
	// 			*   
	// 			*	@remarks 	GUI事件回调
	// 			*	@see		IEngine
	// 			*	@return   	void
	// 			*	@param		UINT nEvent
	// 			*	@param		int nControlID
	// 			*	@param		CDXUTControl * pControl
	// 			*	@param		void * pUserContext
	// 			*	@note
	// 			*
	// 			**/
	// 			virtual void	OnGUIEvent( UINT nEvent, int nControlID, void* pControl, void* pUserContext )	=	NULL;
	// 		};
		}
		
	
	};
};
#endif // INTERFACEGAMESYSTEM_HEAD_FILE