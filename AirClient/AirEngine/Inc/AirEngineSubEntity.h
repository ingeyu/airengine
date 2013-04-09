#ifndef ENGINESUBENTITY_HEAD_FILE
#define ENGINESUBENTITY_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineMovableObject.h"
#include "AirInterfacePhysicsShape.h"
#include "AirInterfaceUserData.h"

namespace Air{
	
	namespace Engine{
		namespace	Physx{
			class	Shape;
		}
	
		class	ENGINE_EXPORT	SubEntity	:
			public	Common::IProduct,
			public	MovableObject
		{
		public:
			struct	Info{
				AString	strMeshName;
				AString	strMaterialName;
			};
		public:
			SubEntity(CAString&	strName,Info* pInfo);
	
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		IPage
			*	@return   	U1
			*	@note
			*
			**/
			virtual U1	Create();
	
			/**	\brief	摧毁
			*   
			*	@remarks 	摧毁
			*	@see		IPage
			*	@return   	U1
			*	@note
			*
			**/
			virtual U1	Destroy();
			/**	\brief	更新
			*   
			*	@remarks 	更新
			*	@see		IPage
			*	@return   	void
			*	@note
			*
			**/
			virtual void	Updata();
	
			virtual	void	GetShape(Physics::Shape*	pShape,Float3 vScale	=	Float3(1,1,1));
		protected:
			Info			m_Info;
		};
	
		class	SubEntityFactory	:
			public	IFactory{
		public:
			SubEntityFactory();
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		BuffFactory
			*	@return   	IProduct*
			*	@param		AString strName
			*	@param		IFactoryParamList * lstParam
			*	@note
			*
			**/
			virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam =	NULL);
		};
	
	};
};
#endif // ENGINESUBENTITY_HEAD_FILE