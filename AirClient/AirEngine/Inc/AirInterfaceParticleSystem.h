#ifndef INTERFACEPARTICLESYSTEM_HEAD_FILE
#define INTERFACEPARTICLESYSTEM_HEAD_FILE

#include "AirInterfaceBaseParticle.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Particle{
			/**	\brief	粒子系统类
			*
			*	粒子系统类
			*
			***/
			class	ISystem	:
				public	IPlugin,
				public	IFactoryManager{
			public:
				/**	\brief	创建粒子
				*   
				*	@remarks 	创建粒子
				*	@see		ISystem
				*	@return   	IBaseObject*
				*	@param		AString strName
				*	@param		Info * pInfo
				*	@note
				*
				**/
				virtual	IBaseObject*	CreateParticle(AString	strName,Info*	pInfo)	=	NULL;
				/**	\brief	摧毁粒子
				*   
				*	@remarks 	摧毁粒子
				*	@see		ISystem
				*	@return   	void
				*	@param		IBaseObject * pObject
				*	@note
				*
				**/
				virtual	void			DestroyParticle(IBaseObject*	pObject)		=	NULL;
			};
		}
	
	};
};
#endif // INTERFACEPARTICLESYSTEM_HEAD_FILE