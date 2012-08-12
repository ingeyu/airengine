#ifndef INTERFACEPHYSICSSYSTEM_HEAD_FILE
#define INTERFACEPHYSICSSYSTEM_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirInterfacePhysicsScene.h"
namespace Air{
	
	namespace Client{
	
		namespace	Physics{
			/**	\brief	物理系统
			*
			*	物理系统
			*
			***/
			class	ISystem	:	
				public	Common::ISystem{
			public:
				ISystem(CAString&	strType):Common::ISystem(strType){

				}
				/**	\brief	创建场景
				*   
				*	@remarks 	创建场景
				*	@see		ISystem
				*	@return   	IScene*
				*	@param		AString strName
				*	@note
				*
				**/
				virtual	IScene*	CreateScene(AString	strName)	=	NULL;
				/**	\brief	摧毁场景
				*   
				*	@remarks 	摧毁场景
				*	@see		ISystem
				*	@return   	void
				*	@param		IScene * pScene
				*	@note
				*
				**/
				virtual	void	DestroyScene(IScene*	pScene)	=	NULL;
	
			protected:
			private:
			};
		}
	
	};
};
#endif // INTERFACEPHYSXSYSTEM_HEAD_FILE