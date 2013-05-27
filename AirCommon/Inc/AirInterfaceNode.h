//*****************************************************/
/* @All Right Reserved (C), 2008-2010, 82NET TECO CO.



 \author    InfernalHell	Xinhe
 \date      2009/10/21
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  InterfaceNode.h
 \note     
       
 \attention:
			节点类
       
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef INTERFACENODE_HEAD_FILE
#define INTERFACENODE_HEAD_FILE


#include "AirCommon.h"
#include "AirCommonHeader.h"
#include "AirInterfaceObject.h"

namespace Air{
	
	namespace Common{

		class	INode;
	
		/**	\brief	节点监听器
		*
		*	节点监听器
		*
		***/
		class COMMON_EXPORT INodeListener{
		public:
			INodeListener();
			/**	\brief	更新
			*   
			*	@remarks 	更新
			*	@see		INodeListener
			*	@return   	void
			*	@param		const	Float44& pMatrix
			*	@param		const	Float4 & pQuat
			*	@param		const	Float3 & pScale
			*	@note
			*
			**/
			virtual void UpdateMatrix(	const	Float44& matWorld,
										const	Float4&	pQuat,
										const	Float3&	pScale,
										U1		bParentDirty);

			U1		m_bDirty;
		};
		typedef std::list<INodeListener*>				NodeListenerList;				///<	节点监听器列表
		typedef std::list<INodeListener*>::iterator		NodeListenerListItr;			///<	节点监听器列表迭代器
	
		typedef std::list<INode*>						NodeList;			///<	子节点列表
		typedef std::list<INode*>::iterator				NodeListItr;		///<	子节点列表迭代器
		//class INodeListener
		/**	\brief	节点基类
		*
		*	可以移动的任何物体都要继承于此
		*
		***/
		class COMMON_EXPORT INode : 
			public IObject{
		public:
			INode();
			virtual ~INode();
	
			/**	\brief	创建子节点
			*   
			*	@remarks 	创建一个子节点
			*	@see		INode
			*	@return   	INode*
			*	@param		CAString& strName
			*	@note
			*
			**/
			virtual INode*		CreateChild();
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
			
			/**	\brief	获取子节点个数
			*   
			*	@remarks 	获取子节点或者子物体的个数
			*	@see		INode
			*	@return   	int
			*	@note
			*
			**/
			inline	U32 GetChildCount()const{
				return	m_lstChild.size();
			};

			/**	\brief	判断是否存在子节点
			*   
			*	@remarks 	判断是否存在子节点
			*	@see		INode
			*	@return   	bool
			*	@note
			*
			**/
			inline	U1		Empty()const{
				return m_lstChild.empty();	
			};
			/**	\brief	获取指针
			*   
			*	@remarks 	
			*	@see		INode
			*	@return   	void*
			*	@note
			*
			**/
			virtual void*		getHandle();
	
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
	
			/**	\brief	获取相对坐标
			*   
			*	@remarks 	相对于父节点（没有父节点 则表示这是根节点）
			*	@see		INode
			*	@return   	Client::Vector3
			*	@note
			*
			**/
			const Float3&		GetPosition()const;
			/**	\brief	设置相对坐标
			*   
			*	@remarks 	目前不允许直接去设置全局坐标 如果想要实现直接设置全局坐标 最好将你需要调节的节点 作为根结点的第一层子节点 设置之后此节点的状态处于已更改状态  具体会影响到 GetGlobalMatrix函数
			*	@see		INode
			*	@return   	void
			*	@param		Float3 vPos
			*	@note
			*
			**/
			void		SetPosition(const	Float3& vPos);
			void		SetPosition(float x,float y,float z);
			/**	\brief	获取相对四元数
			*   
			*	@remarks 	即物体的旋转方向 相对于父节点的旋转向量
			*	@see		INode
			*	@return   	Client::Float4
			*	@note
			*
			**/
			const	Float4&	GetQuat()const;
			/**	\brief	设置相对旋转向量
			*   
			*	@remarks 	设置相对旋转向量 设置之后此节点的状态处于已更改状态  具体会影响到 GetGlobalMatrix函数
			*	@see		INode
			*	@return   	void
			*	@param		Float4 vQuat
			*	@note
			*
			**/
			void		SetQuat(const	Float4& vQuat);
			/**	\brief	获取相对缩放系数
			*   
			*	@remarks 	获取相对缩放系数
			*	@see		INode
			*	@return   	Client::Vector3
			*	@note
			*
			**/
			const	Float3&		GetScale()const;
			/**	\brief	设置相对缩放系数
			*   
			*	@remarks 	设置相对缩放系数 设置之后此节点的状态处于已更改状态  具体会影响到 GetGlobalMatrix函数
			*	@see		INode
			*	@return   	void
			*	@param		Vector3 vScale
			*	@note
			*
			**/
			void		SetScale(const	Float3& vScale);
			void		SetScale(float fScale);
			/**	\brief	获取全局位置
			*   
			*	@remarks 	获取全局位置
			*	@see		INode
			*	@return   	Client::Float3
			*	@note
			*
			**/
			const	Float3&		GetGlobalPosition()const;
			/**	\brief	获取全局缩放系数
			*   
			*	@remarks	需节点更新
			*	@see		INode
			*	@return   	Client::Vector3
			*	@note
			*
			**/
			const	Float3&		GetGlobalScale()const;
			/**	\brief	获取全局旋转向量
			*   
			*	@remarks 	需节点更新
			*	@see		INode
			*	@return   	Client::Quaternion
			*	@note
			*
			**/
			const	Float4&		GetGlobalQuat()const;
			/**	\brief	获取全局变换矩阵
			*   
			*	@remarks 	需节点更新
			*	@see		INode
			*	@return   	Client::Matrix4
			*	@note
			*
			**/
			const	Float44&	GetGolbalMatrix()const;
	
			/**	\brief	 直接获取全局缩放
			*   
			*	@remarks 	无需节点更新
			*	@see		INode
			*	@return   	Common::Vector3
			*	@note
			*
			**/
			Float3		GetGlobalScaleImmediately();
			/**	\brief	直接获取全局旋转
			*   
			*	@remarks 	无需节点更新
			*	@see		INode
			*	@return   	Common::Quaternion
			*	@note
			*
			**/
			Float4	GetGlobalQuatImmediately();
			/**	\brief	直接获取全局矩阵
			*   
			*	@remarks 	无需节点更新
			*	@see		INode
			*	@return   	Common::Matrix4
			*	@note
			*
			**/
			Float44		GetGlobalMatrixImmediately();
	
			/**	\brief	获取结果矩阵
			*   
			*	@remarks 	获取结果矩阵
			*	@see		INode
			*	@return   	Common::Matrix4
			*	@note
			*
			**/
			const	Float44&		GetMatrix()const;
	
			/**	\brief	返回子节点列表
			*   
			*	@remarks 	返回子节点列表
			*	@see		INode
			*	@return   	Client::ChildList
			*	@note
			*
			**/
			const NodeList&	GetChildNodeList()const;
	
			/**	\brief	添加节点监听器
			*   
			*	@remarks 	添加节点监听器
			*	@see		INode
			*	@return   	void
			*	@param		IListener * pListener
			*	@note
			*
			**/
			void AddListener(INodeListener* pListener);
			/**	\brief	移除节点监听器
			*   
			*	@remarks 	移除节点监听器
			*	@see		INode
			*	@return   	void
			*	@param		IListener * pListener
			*	@note
			*
			**/
			void RemoveListener(INodeListener* pListener);
			/**	\brief	更新
			*   
			*	@remarks 	此函数由节点(INode)来调用 用于物体的一些更新动作
			*	@see		IListener
			*	@return   	void
			*	@note
			*
			**/
			virtual void Update(const	Float44&	ParentGlobalWorldMatrix,
								const	Float4&		ParentGlobalWorldQuat,
								const	Float3&		ParentGlobalWorldScale,
								U1					bParentDirty);
			/**	\brief	另外一个构造函数
			*   
			*	@remarks 	由Scene来调用
			*	@see		INode
			*	@return   	
			*	@param		char * strName
			*	@param		INode * pParentNode
			*	@note
			*
			**/
			INode(INode* pParentNode);
			/**	\brief	创建子节点
			*   
			*	@remarks 	作用是派生类 重写此函数 用于NEW对象的时候使用
			*	@see		INode
			*	@return   	INode*
			*	@note
			*
			**/
			virtual INode* CreateChildImp();
			
		protected:
			NodeList			m_lstChild;					///<	子节点列表
			INode*				m_pParentNode;				///<	依附的父节点指针
			Float3				m_vPos;						///<	相对坐标
			Float3				m_vScale;					///<	相对缩放
			Float4				m_qQuat;					///<	相对旋转
			Float44				m_matWorld;					///<	相对世界矩阵
			
			NodeListenerList	m_lstListener;				///<	监听器
	
			Float44				m_GlobalWorldMatrix;		///<	全局矩阵	主线程计算完成 所保存的世界矩阵
			Float3				m_GlobaPosition;
			Float4				m_GlobalWorldQuat;			///<	全局旋转
			Float3				m_GlobalScale;				///<	全局缩放

			U1					m_bDirty;					///<	是否需要重建世界矩阵
		};
	 };
};
#endif