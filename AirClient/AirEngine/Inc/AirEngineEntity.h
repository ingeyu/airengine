#ifndef ENGINEENTITY_HEAD_FILE
#define ENGINEENTITY_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineSceneNode.h"
namespace Air{
	
	namespace Engine{

		class	SubEntity;
	
		/**	\brief	引擎基本物体类
		*
		*	引擎基本物体类
		*
		***/
		class	Entity	:
			public	TProduct<Entity>,
			public	Common::INodeListener{
		public:
			struct Info{
				Info(){
					pParentNode	=	NULL;


				};
				AString						strConfigName;		///<	配置文件名
				AString						strConfigMemery;	///<	配置内容
				SceneNode*					pParentNode;		///<	父节点
			};
	
		public:
			Entity(CAString&	strName,Info*	pInfo);
	
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		Entity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1					Create();
	
			/**	\brief	摧毁
			*   
			*	@remarks 	摧毁
			*	@see		Entity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1					Destroy();
	
			/**	\brief	获取节点
			*   
			*	@remarks 	获取节点
			*	@see		Entity
			*	@return   	SceneNode*
			*	@note
			*
			**/
			virtual	SceneNode*			GetSceneNode();
	
			/**	\brief	获取碰撞模型
			*   
			*	@remarks 	获取碰撞模型
			*	@see		Entity
			*	@return   	Physx::ICollision*
			*	@note
			*
			**/
			//virtual	Physics::ICollision*	GetCollision();
	
			/**	\brief	获取渲染模型
			*   
			*	@remarks 	获取渲染模型
			*	@see		Entity
			*	@return   	SubEntity*
			*	@note
			*
			**/
			virtual	SubEntity*			GetSubEntity();
	
			/**	\brief	更新
			*   
			*	@remarks 	此函数由节点(INode)来调用 用于物体的一些更新动作
			*	@see		IListener
			*	@return   	void
			*	@param		Float3 vPos
			*	@param		Float4 vQuat
			*	@param		Float3 vScale
			*	@note
			*
			**/
			virtual void UpdateMatrix(Float44* pMatrix,Float4*	pQuat,Float3*	pScale);
		protected:
			/**	\brief	解析配置文件
			*   
			*	@remarks 	解析配置文件
			*	@see		Entity
			*	@return   	U1
			*	@note
			*
			**/
			U1	ParseConfig();
	
		protected:
			SubEntity*		m_pRenderObj;			///<	渲染物体
			SceneNode*			m_pNode;				///<	节点
			Info				m_Info;					///<	创建信息
		};

	
	};
};
#endif // ENGINEENTITY_HEAD_FILE