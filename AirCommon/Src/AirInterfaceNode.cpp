#include "AirInterfaceNode.h"
#include "AirRandom.h"
#include "AirCommonMath.h"

namespace Air{
	
	
	namespace Common{
		INode::INode():IObject(){
			
			m_pParentNode	= NULL;
			m_vPos			=	Float3(0,0,0);
			m_vScale		=	Float3(1,1,1);
			m_qQuat			=	Float4(0,0,0,1);
			m_matWorld		=	Common::Matrix(m_vPos,m_vScale,m_qQuat);
			m_GlobalScale		=	m_vScale;
			m_GlobalWorldQuat	=	m_qQuat;
			m_GlobalWorldMatrix	=	m_matWorld;
			m_bDirty	= true;
		}
		INode::INode(INode* pParentNode):IObject(){
			m_pParentNode	= pParentNode;
			m_vPos			=	Float3(0,0,0);//		= ;//Vector3::;
			m_vScale		=	Float3(1,1,1);
			m_qQuat			=	Float4(0,0,0,1);
			m_matWorld		=	Common::Matrix(m_vPos,m_vScale,m_qQuat);
			m_GlobalScale		=	m_vScale;
			m_GlobalWorldQuat	=	m_qQuat;
			m_GlobalWorldMatrix	=	m_matWorld;
			m_bDirty	= true;
		}
		INode::~INode(){
			if(m_pParentNode!=NULL)
				m_pParentNode->RemoveChild(this);
			m_pParentNode = NULL;
	
			RemoveAllChild(true);
	
		}
		INode* INode::CreateChild(){
			INode* pChildNode = CreateChildImp();
			AddChild(pChildNode);
			return pChildNode;
		}
		void INode::AddChild(INode* pObject){
			if(pObject==NULL || this == pObject)
				return;
			INode*&	pOldParent	=	pObject->m_pParentNode;
			if(pOldParent!=NULL){
				//如果以前的父节点就是当前节点 直接返回
				//if(pOldParent==this){
				//	return;
				//}
				pOldParent->RemoveChild(pObject);
			}
			pOldParent			=	this;
			//标记 下次需要更新世界矩阵
			pObject->m_bDirty	=	true;
			m_lstChild.push_back(pObject);
		}
		void INode::RemoveChild(INode* pObject,bool bDestroy){
			if(pObject	==	NULL	||
				pObject	==	this)
				return;
	
			m_lstChild.remove(pObject);
			if(bDestroy){
				delete pObject;
				pObject = NULL;
			}
		}
	
		void* INode::getHandle(){
			return NULL;
		}
	
		void INode::RemoveAllChild( bool bDestroy /*= false*/ ){
			if(m_lstChild.empty())
				return;
			NodeList lst = m_lstChild;
			m_lstChild.clear();
			if(bDestroy){
				NodeListItr i = lst.begin();
				for(;i!=lst.end();i++){
					INode* pChildNode = (INode*)(*i);
					SAF_D(pChildNode);
				}
			}
			lst.clear();
		}
	
		INode* INode::CreateChildImp(){
			return new INode(this);
		
		}
	
		const	Float3& INode::GetPosition()const{
			return m_vPos;
		}
	
		void INode::SetPosition( const	Float3& vPos ){
			m_vPos = vPos;
			m_bDirty	= true;
		}

		void INode::SetPosition( float x,float y,float z )
		{
			m_vPos.x	=	x;
			m_vPos.y	=	y;
			m_vPos.z	=	z;
			m_bDirty	=	true;
		}


		const	Float4& INode::GetQuat()const{
			return m_qQuat;
		}
	
		void INode::SetQuat( const	Float4& vQuat ){
			m_qQuat = vQuat;
			m_bDirty = true;
		}
	
		const	Float3& INode::GetScale()const{
			return m_vScale;
		}
	
		void INode::SetScale( const	Float3& vScale ){
			m_vScale = vScale;
			m_bDirty	= true;
		}

		void INode::SetScale( float fScale )
		{
			m_vScale.x	=	m_vScale.y	=	m_vScale.z	=	fScale;
			m_bDirty	= true;
		}


		const	Float3& INode::GetGlobalPosition()const{
			return	m_GlobaPosition;
		}
	
		const	Float3& INode::GetGlobalScale()const{
			return	m_GlobalScale;
		}
	
		const	Float4& INode::GetGlobalQuat()const{
			return	m_GlobalWorldQuat;
		}
	
		const	Float44& INode::GetGolbalMatrix()const{
			return	m_GlobalWorldMatrix;
		}
	
		const	Common::NodeList& INode::GetChildNodeList()const{
			return m_lstChild;
		}
	
		void INode::AddListener( INodeListener* pListener ){
			if(pListener!=NULL){
				m_lstListener.push_back(pListener);
				pListener->m_bDirty	=	true;
			}
		}
	
		void INode::RemoveListener( INodeListener* pListener ){
			if(pListener!=NULL)
				m_lstListener.remove(pListener);
		}
	
		void INode::Update(	const	Float44&	ParentGlobalWorldMatrix,
							const	Float4&		ParentGlobalWorldQuat,
							const	Float3&		ParentGlobalWorldScale,
							U1					bParentDirty)
		{
			U1	bDirty	=	m_bDirty	||	bParentDirty;

			if(m_bDirty){
				m_matWorld	=	Matrix(m_vPos,m_vScale,m_qQuat);
				m_bDirty	=	false;
			}

			if(bDirty){
				m_GlobalWorldMatrix	=	m_matWorld*ParentGlobalWorldMatrix;
				m_GlobalScale		=	m_vScale	*	ParentGlobalWorldScale;
				m_GlobalWorldQuat	=	ParentGlobalWorldQuat	*	m_qQuat;
				m_GlobalWorldMatrix.Decompose(&m_GlobaPosition,NULL,NULL);
			}

			//更新子节点信息
			Common::NodeList	lstChild	=	m_lstChild;
			Common::NodeListItr	i	=	lstChild.begin();
			for(;i!=lstChild.end();i++){
				Common::INode*	pChild	=	(Common::INode*)(*i);
				if(pChild!=NULL){
					pChild->Update(	m_GlobalWorldMatrix,
									m_GlobalWorldQuat,
									m_GlobalScale,
									bDirty);
				}
			}
			//更新监听器信息
			NodeListenerList	lstListener	=	m_lstListener;
			NodeListenerListItr it = lstListener.begin();
			for(;it!=lstListener.end();it++){
				INodeListener* pListener = (INodeListener*)(*it);
 				if(pListener!=NULL)
 					pListener->UpdateMatrix(m_GlobalWorldMatrix,
 											m_GlobalWorldQuat,
 											m_GlobalScale,
											bDirty);
			}
		}
	
		const	Float44& INode::GetMatrix()const{
			return	m_matWorld;
		}
	
		Float3 INode::GetGlobalScaleImmediately(){
			if(m_pParentNode!=NULL){

				return	m_pParentNode->GetGlobalScaleImmediately()*m_vScale;
			}else
				return	m_vScale;
		}
	
		Float4 INode::GetGlobalQuatImmediately(){
			if(m_pParentNode!=NULL){
				return	m_pParentNode->GetGlobalQuatImmediately()*m_qQuat;
			}else
				return	m_qQuat;
		}
	
		Float44 INode::GetGlobalMatrixImmediately(){
			if(m_pParentNode!=NULL){
				return	m_matWorld*m_pParentNode->GetGlobalMatrixImmediately();
			}else
				return	m_matWorld;
		}

		void INodeListener::UpdateMatrix( const Float44& matWorld, const Float4& pQuat, const Float3& pScale, U1 bParentDirty )
		{

		}

		INodeListener::INodeListener()
		{
			m_bDirty	=	true;
		}

	};
};