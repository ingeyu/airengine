/*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2009/12/02
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  InterfaceSceneNode.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/

#ifndef INTERFACESCENENODE_HEAD_FILE
#define INTERFACESCENENODE_HEAD_FILE


#include "AirEngineHeader.h"
#include "AirEngineMovableObject.h"
#include "AirCommonLock.h"

namespace Air{
	
	
	
	namespace Engine{
		namespace	Render{
			class	Queue;
		}
	
	 	class SceneNode;
		typedef std::list<MovableObject*>					MovableObjectList;
		typedef MovableObjectList::iterator					MovableObjectListItr;
	
	
		typedef std::list<SceneNode*>								SceneNodeList;
		typedef std::list<SceneNode*>::iterator					SceneNodeListItr;

		enum	enumSceneNodeType{
			enSNT_UNKNOWN,
			enSNT_STATIC,
			enSNT_DYNAMIC,
			enSNT_MAX
		};
		enum	enumSceneNodeFlag{
			enSNF_VISIABLE,
			enSNF_MAX
		};
	
		/**	\brief	场景节点
		*
		*	场景节点
		*
		***/
		class ENGINE_EXPORT SceneNode : 
			public	Common::INode,
			public	Flag<enumSceneNodeFlag>{
		public:
			SceneNode();
			SceneNode(CAString&	strName,SceneNode*	pParentNode);
			virtual ~SceneNode();
			/**	\brief	返回父场景节点
			*   
			*	@remarks 	返回父场景节点
			*	@see		SceneNode
			*	@return   	SceneNode*
			*	@note
			*
			**/
			virtual SceneNode* GetParentSceneNode();
	
			/**	\brief	创建子节点
			*   
			*	@remarks 	创建子场景节点
			*	@see		SceneNode
			*	@return   	SceneNode*
			*	@param		CAString&	strName
			*	@note
			*
			**/
			virtual SceneNode* CreateChildSceneNode(const	Float3&	pos	=	Float3(0,0,0),
													const	Float4&	rot	=	Float4(0,0,0,1),
													const	Float3&	scale	=	Float3(1,1,1));
			/**	\brief	绑定物体
			*   
			*	@remarks	绑定物体
			*	@see		SceneNode
			*	@return   	void
			*	@param		MovableObject * obj
			*	@note
			*
			**/
			virtual void attachObject(MovableObject* obj);
	
			/**	\brief	移除物体
			*   
			*	@remarks 	移除物体
			*	@see		SceneNode
			*	@return   	void
			*	@param		MovableObject * obj
			*	@note
			*
			**/
			virtual void detachObject(MovableObject* obj);
	
			/**	\brief	延迟解除物体的绑定
			*   
			*	@remarks 	延迟解除物体的绑定
			*	@see		SceneNode
			*	@return   	void
			*	@param		MovableObject * obj
			*	@note
			*
			**/
			//virtual	void detachObjectDelay(MovableObject* obj);
	
			/**	\brief	移除所有物体
			*   
			*	@remarks 	
			*	@see		SceneNode
			*	@return   	void
			*	@param		void
			*	@note
			*
			**/
			virtual void detachAllObjects(void);
	
			/**	\brief	返回渲染物体列表
			*   
			*	@remarks 	返回渲染物体列表
			*	@see		SceneNode
			*	@return   	MovableObjectList&
			*	@note
			*
			**/
			const MovableObjectList&		GetObjectList()const ;
	
			/**	\brief	返回子场景列表节点
			*   
			*	@remarks 	返回子场景列表节点
			*	@see		SceneNode
			*	@return   	Client::ChildSceneNodeList
			*	@note
			*
			**/
			virtual SceneNodeList GetChildSceneNodeList();
			/**	\brief	更新
			*   
			*	@remarks 	更新(只需要根节点调用)更新节点矩阵 更新回调列表 更新包围盒 检测是否可见 检测该节点上的物体是否可见
			*	@see		SceneNode
			*	@return   	void
			*	@note
			*
			**/
			virtual void	Update(	const	Float44&	ParentGlobalWorldMatrix,
									const	Float4&		ParentGlobalWorldQuat,
									const	Float3&		ParentGlobalWorldScale,
									U1					bParentDirty);
	
			/**	\brief	附加节点
			*   
			*	@remarks 	将一个节点附加到此节点  作为这个节点的子节点 如果节点已经依附到其他节点，则会移除他们的之间的父子关系
			*	@see		INode
			*	@return   	void
			*	@param		INode * pObject
			*	@note
			*
			**/
			virtual void		AddChild(INode* pObject);
			/**	\brief	移除节点
			*   
			*	@remarks 	从此节点移除一个子节点 通过指针来移除
			*	@see		INode
			*	@return   	void
			*	@param		INode * pObject	
			*	@param		bool bDestroy	如果为TRUE 则会将这个节点摧毁
			*	@note
			*
			**/
			virtual void		RemoveChild(INode* pObject,bool bDestroy = false);
			/**	\brief	移除所有子节点
			*   
			*	@remarks 	移除所有子节点
			*	@see		INode
			*	@return   	void
			*	@param		bool bDestroy
			*	@note
			*
			**/
			virtual void		RemoveAllChild(bool bDestroy = false);
			/**	\brief	添加节点监听器
			*   
			*	@remarks 	添加节点监听器
			*	@see		INode
			*	@return   	void
			*	@param		IListener * pListener
			*	@note
			*
			**/
			virtual void AddListener(Common::INodeListener* pListener);
			/**	\brief	移除节点监听器
			*   
			*	@remarks 	移除节点监听器
			*	@see		INode
			*	@return   	void
			*	@param		IListener * pListener
			*	@note
			*
			**/
			virtual void RemoveListener(Common::INodeListener* pListener);

			/**	\brief	查找场景物体
			*   
			*	@remarks 	查找场景物体
			*	@see		SceneNode
			*	@return   	void
			*	@param		Camera * pCamera
			*	@note
			*
			**/
			virtual	void	FindMovableObject(Camera*	pCamera);

			virtual	U1		RayCast(const Ray& ray,MovableObject*& pOutObject,float*	pOutDistance	=	NULL);
		protected:
			/**	\brief	创建子节点
			*   
			*	@remarks 	创建子节点
			*	@see		SceneNode
			*	@return   	Node*
			*	@note
			*
			**/
			virtual INode*	CreateChildImp(CAString& strName);
			
			enumSceneNodeType	GetType();
			void				SetType(enumSceneNodeType	t);

			inline	U1			IsVisiable(){
				return	HasFlag(enSNF_VISIABLE);
			};
			inline	void		SetVisiable(U1	bVisiable){
				if(bVisiable){
					AddFlag(enSNF_VISIABLE);
				}else{
					RemoveFlag(enSNF_VISIABLE);
				}
			}

		private:
			MovableObjectList	m_lstMovableObject;				///<	可移动物体列表
				
	
		protected:
			Common::CriticalSection	m_NodeCS;					///<	子节点锁
			Common::CriticalSection	m_ListenCS;					///<	监听器锁
			Common::CriticalSection	m_ObjectCS;					///<	物品锁
			enumSceneNodeType		m_Type;
			U32						m_uiFlag;					///<	属性
		};
	};
};

#endif // INTERFACESCENENODE_HEAD_FILE