#ifndef ENGINEENTITYCLOTH_HEAD_FILE
#define ENGINEENTITYCLOTH_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirInterfacePhysicsCloth.h"
#include "AirEngineMovableObject.h"
namespace Air{
	
	namespace Engine{
		namespace	Physics{
			class	IScene;
		}	
		/**	\brief	布料实体类
		*
		*	布料实体类
		*
		***/
		class	EntityCloth	:
			public	MovableObject,
			public	Common::IProduct{
		public:
			/**	\brief	创建信息
			*
			*	创建信息
			*
			***/
			struct	Info{
				Info(){
					pXScene	=	NULL;
				};
				AString				strMeshName;
				AString				strMaterialName;
				Physics::IScene*		pXScene;			///<	场景指针
				Physics::ICloth::Info	clothInfo;		
			};
		public:
			EntityCloth(CAString&	strName,Info*	pInfo);
	
			virtual	U1	Create();
	
			virtual	U1	Destroy();
	
			virtual	const BoundingBox&	GetWorldBoundingBox()const;
	
			virtual	void	Updata();
	
			virtual	void	Render();
		protected:
			U1		CreatePhysxMesh();
			U1		CreateRenderMesh();
		protected:
			Physics::ICloth*		m_pCloth;
			Info				m_Info;
		};
	
		class	EntityClothFactory	:
			public	IFactory{
		public:
			EntityClothFactory(){
				m_strTypeName	=	"EntityCloth";
			};
	
			virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam /* = NULL */){
				if(lstParam==NULL)
					return	NULL;
				return	new	EntityCloth(strName,(EntityCloth::Info*)lstParam);
			};
		};
	
	};
};
#endif // ENGINEENTITYCLOTH_HEAD_FILE