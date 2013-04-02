#include "AirEngineSceneNode.h"
#include "AirGlobalSetting.h"

#include "AirEngineCamera.h"
namespace Air{
	
	namespace Engine{
	
	
		SceneNode::SceneNode()	:
			Common::INode(){
				m_Type	=	enSNT_DYNAMIC;
				AddFlag(enSNF_VISIABLE);
		}

		SceneNode::SceneNode( CAString& strName,SceneNode* pParentNode )	:
			Common::INode(strName,pParentNode){
				m_Type	=	pParentNode->GetType();
				AddFlag(enSNF_VISIABLE);
		}

		SceneNode::~SceneNode(){
			//m_CS.Enter();
			detachAllObjects();
			//m_CS.Leave();
		}
	
	
		Common::INode* SceneNode::CreateChildImp(CAString& strName){
			SceneNode*	p	=	new SceneNode(strName,this);
			p->SetType(m_Type);
			return p;
		}
	
		SceneNode* SceneNode::GetParentSceneNode(){
			return static_cast<SceneNode*>(m_pParentNode);
		}
	
		void SceneNode::attachObject( MovableObject* obj ){
			if(obj==NULL)
				return;
			obj->SetParent(this);
			m_ObjectCS.Enter();
			m_lstMovableObject.push_back(obj);
			m_ObjectCS.Leave();
			//更新obj内部的世界矩阵和 包围盒
			obj->Updata(m_GlobalWorldMatrix,m_GlobalWorldQuat,m_GlobalScale,true);
	
		}
	
		void SceneNode::detachObject( MovableObject* obj ){
			if(obj==NULL)
				return;
			obj->SetParent(NULL);
			m_ObjectCS.Enter();
			m_lstMovableObject.remove(obj);
			m_ObjectCS.Leave();
		}
	
		void SceneNode::detachAllObjects( void ){
	
			m_ObjectCS.Enter();
			MovableObjectList&	lstObject	=	m_lstMovableObject;
			MovableObjectList::iterator	i	=	lstObject.begin();
			for(;i!=lstObject.end();i++){
				MovableObject*	pObject	=	(MovableObject*)(*i);
				if(pObject!=NULL)
					pObject->SetParent(NULL);
			}
			m_ObjectCS.Leave();
	
		}
	
	
		SceneNodeList SceneNode::GetChildSceneNodeList(){
			SceneNodeList lst;
			m_NodeCS.Enter();
			Common::NodeList&	lstChild	=	m_lstChild;
			
			Common::NodeListItr i = lstChild.begin();
			for(;i!=lstChild.end();i++){
				SceneNode* pNode = (SceneNode*)(*i);
				lst.push_back(pNode);
			}
			m_NodeCS.Leave();
			return lst;
		}
	
		SceneNode* SceneNode::CreateChildSceneNode(CAString&	strName){
			SceneNode* pSceneNode = static_cast<SceneNode*>(CreateChild(strName));
			return pSceneNode;
		}
	
		void SceneNode::Updata(	const	Float44&	ParentGlobalWorldMatrix,
								const	Float4&		ParentGlobalWorldQuat,
								const	Float3&		ParentGlobalWorldScale,
								U1					bParentDirty)
		{
	
			U1	bDirty	=	m_bDirty	||	bParentDirty;

			INode::Updata(	ParentGlobalWorldMatrix,
							ParentGlobalWorldQuat,
							ParentGlobalWorldScale,
							bParentDirty);
			{
				m_ObjectCS.Enter();
				//调用该节点上物体的更新
				//因为节点可能会 改变它所绑定到节点的位置 方向 缩放信息
				MovableObjectList&	lstObject	=	m_lstMovableObject;
				MovableObjectListItr	itr		=	lstObject.begin();
				for(;itr!=lstObject.end();itr++){
					MovableObject*	pObject	=	(MovableObject*)(*itr);
					if(pObject!=NULL){
 						pObject->Updata(m_GlobalWorldMatrix,
 										m_GlobalWorldQuat,
 										m_GlobalScale,
										bDirty);
					}
				}
				m_ObjectCS.Leave();	
			}
		}
	
		const MovableObjectList& SceneNode::GetObjectList()const {
			return m_lstMovableObject;
		}
		void SceneNode::AddChild( INode* pObject ){
			if(pObject==NULL)
				return;
	
			m_NodeCS.Enter();
			INode::AddChild(pObject);
			m_NodeCS.Leave();	
		}
	
		void SceneNode::RemoveChild( INode* pObject,bool bDestroy /*= false*/ ){
			if(	pObject	==	NULL	||
				pObject	==	this)
				return;
			m_NodeCS.Enter();
			m_lstChild.remove(pObject);
			m_NodeCS.Leave();
			if(bDestroy){
				delete pObject;
				pObject = NULL;
			}
		}
	
		void SceneNode::RemoveAllChild( bool bDestroy /*= false*/ ){
			m_NodeCS.Enter();
	
			Common::NodeList lst = m_lstChild;
			m_lstChild.clear();
			if(bDestroy){
				Common::NodeListItr i = lst.begin();
				for(;i!=lst.end();i++){
					Common::INode* pChildNode = (Common::INode*)(*i);
					SAF_D(pChildNode);
				}
			}
			lst.clear();
	
			m_NodeCS.Leave();
		}
	
		void SceneNode::AddListener( Common::INodeListener* pListener ){
			if(pListener!=NULL){
				RemoveListener(pListener);
				m_ListenCS.Enter();
				m_lstListener.push_back(pListener);
				m_ListenCS.Leave();
			}
		}
	
		void SceneNode::RemoveListener( Common::INodeListener* pListener ){
			if(pListener!=NULL){
				m_ListenCS.Enter();
				m_lstListener.remove(pListener);
				m_ListenCS.Leave();
			}
		}

		void SceneNode::FindMovableObject( Camera* pCamera ){
			if(IsVisiable()){
				MovableObject*	pObj	=	NULL;
				MovableObjectListItr	i	=	m_lstMovableObject.begin();
				for(;i!=m_lstMovableObject.end();++i){
					pObj	=	*i;
					if(pObj->HasFlag(enMOF_VISIABLE)){
						if(pCamera->IsVisiable(pObj->GetWorldBoundingBox()))
							pCamera->AddMovableObject(*i);
					}
				}

				Common::NodeListItr	itr	=	m_lstChild.begin();
				for(;itr!=m_lstChild.end();itr++){
					(static_cast<SceneNode*>(*itr))->FindMovableObject(pCamera);
				}
			}
		}

		Air::Engine::enumSceneNodeType SceneNode::GetType(){
			return	m_Type;
		}

		void SceneNode::SetType( enumSceneNodeType t ){
			m_Type	=	t;
		}

		Air::U1 SceneNode::RayCast( const Ray& ray,float* pOutDistance /*= NULL*/ )
		{
			U1	bHit	=	false;
			float	fLastDistance	=	999999.0f;
			

				MovableObject*	pObj	=	NULL;
				MovableObjectListItr	i	=	m_lstMovableObject.begin();
				for(;i!=m_lstMovableObject.end();++i){
					pObj	=	*i;
					if(pObj->HasFlag(enMOF_VISIABLE)){
						float	fMaxDistance	=	9999999.0f;
						if((*i)->RayCast(ray,&fMaxDistance)){
							if(fMaxDistance<fLastDistance){
								fLastDistance	=	fMaxDistance;
							}
							bHit	=	true;
						};
					}
				}

				Common::NodeListItr	itr	=	m_lstChild.begin();
				for(;itr!=m_lstChild.end();itr++){
					float	fMaxDistance	=	9999999.0f;
					if((static_cast<SceneNode*>(*itr))->RayCast(ray,&fMaxDistance)){
						if(fMaxDistance<fLastDistance){
							fLastDistance	=	fMaxDistance;
						}
						bHit	=	true;
					};
				}
				if(pOutDistance!=NULL){
					if(fLastDistance	<	*pOutDistance){
						*pOutDistance	=	fLastDistance;
					}
				}
			return	bHit;
		}

	}	
};