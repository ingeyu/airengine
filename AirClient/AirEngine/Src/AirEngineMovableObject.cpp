#include "AirEngineMovableObject.h"
#include "AirRandom.h"
#include "AirEngineSceneNode.h"
#include "AirGlobalSetting.h"
#include "AirEngineSystem.h"
namespace Air{
	
	
	namespace Client{
	
		MovableObject::MovableObject(){
			m_pParentNode	=	NULL;
			
			m_bDirty		=	true;
			AddFlag(enMOF_VISIABLE);
		}
	
		MovableObject::~MovableObject(){
			if(m_pParentNode!=NULL){
				m_pParentNode->detachObject(this);
			}				
		}
	
	 	SceneNode* MovableObject::GetParentSceneNode(){
	 		return	m_pParentNode;
	 	}
		const BoundingBox& MovableObject::GetWorldBoundingBox()const{
			return	m_WorldBound;
		}

		void MovableObject::Prepare(Float44*	pMatrix){
			//更新矩阵 和世界包围盒 供渲染时使用
			//m_CS.Enter();
			m_ResultMatrix	=	*(Float44*)pMatrix;
			//memcpy(&m_ResultBound,&m_WorldBound,sizeof(BoundBox));
			//m_CS.Leave();
	
			
		}
	
		void MovableObject::Updata( const	Float44&	ParentGlobalWorldMatrix,
									const	Float4&		ParentGlobalWorldQuat,
									const	Float3&		ParentGlobalWorldScale,
									U1					bParentDirty )
		{
			//m_CS.Enter();
			if(bParentDirty || m_bDirty){
				m_WorldMatrix		=	ParentGlobalWorldMatrix;
				m_WorldBound		=	m_BoundingBox.Transform(ParentGlobalWorldMatrix);
				m_bDirty			=	false;
			}

			Updata();
		}
	
		void MovableObject::Updata(){
	
		}
	
		Float44* MovableObject::GetWorldMatrix(){
			return	&m_WorldMatrix;
		}

		const BoundingBox& MovableObject::GetOrginBoundingBox()const{
			return	m_BoundingBox;
		}

// 		void MovableObject::CheckIsInView( PlaneList& lstPlane ){
// 
// 		}

		Air::U1 MovableObject::IsInView(){
			return	m_bInView;
		}

		void MovableObject::SetBoundBox( const Float3& vMin,const Float3& vMax ){
			m_BoundingBox.vMin	=	vMin;
			m_BoundingBox.vMax	=	vMax;
			m_bDirty		=	true;
		}

		void MovableObject::SetParent( SceneNode* pParentNode ){
			m_pParentNode	=	pParentNode;
			//更换父节点时 矩阵和包围盒需要更新
			m_bDirty		=	true;
		}

		Air::U1 MovableObject::IsAttached(){
			return	m_pParentNode!=NULL;
		}

		void MovableObject::ProcessRenderObject(U32	uiPhaseFlag){

			RenderableVector::iterator	i		=	m_vecRenderable.begin();
			RenderableVector::iterator	iEnd	=	m_vecRenderable.end();
			for(;i!=iEnd;i++){
				if((*i)->IsVisiable())
					(*i)->AddToRenderQueue(uiPhaseFlag);
			}
		}

		Air::U1 MovableObject::RayCast( const Ray& ray,float* pOutDistance /*= NULL*/ )
		{
			return	ray.Intersect(m_WorldBound,pOutDistance);
		}

// 		Buffer* MovableObject::GetObjectConstantBuffer(){
// 			
// 			return	m_pObjectCB;
// 		}

	
	};
};