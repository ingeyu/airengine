//*****************************************************/
/* @All Right Reserved (C), 2008-2010, 82NET TECO CO.



 \author    InfernalHell	Xinhe
 \date      2009/10/21
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  InterfaceMovableObject.h
 \note     
       
 \attention:
			可移动可渲染物体基类
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef INTERFACEMOVABLEOBJECT_HEAD_FILE
#define INTERFACEMOVABLEOBJECT_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirInterfaceObject.h"
#include "AirCommonProduct.h"
#include "AirEngineRenderable.h"

namespace Air{
	
	
	namespace Engine{
		class	SceneNode;
		class	Camera;
		enum	enumMovableObjectFlag{
			enMOF_DEFAULT,			///<	是否可以被主相机查找
			enMOF_REFLECT,			///<	是否产生反射
			enMOF_CASTSHADOW,		///<	是否投射阴影
			enMOF_VISIABLE,			///<	是否可见
			enMOF_DYNAMIC,			///<	是否为动态物体
			enMOF_UPDATE,			///<	是否需要更新
			enMOF_NEED_FRUSTUM_CULL,///<	是否需要视锥裁剪
			enMOF_UPDATE_IN_VIEW,	///<	只在可见的时候更新

			enMOF_MAX
		};
		/**	\brief	可移动可渲染物体基类
		*
		*	这里把渲染和可移动物体组合起来 作为引擎的基本物体类
		*
		***/
		class ENGINE_EXPORT MovableObject :
			public	Common::IProduct,
			public	Flag<enumMovableObjectFlag>{
		public:
			MovableObject(const AString& strName);
			virtual ~MovableObject();
			virtual	U1			Create();
			virtual	U1			Destroy();
			U1					IsAttached();
			void				SetParent(SceneNode*	pParentNode);
			/**	\brief	返回场景父节点
			*   
			*	@remarks 	返回场景父节点
			*	@see		MovableObject
			*	@return   	SceneNode*
			*	@note
			*
			**/
			virtual SceneNode*	GetParentSceneNode();
			/**	\brief	获取包围盒
			*   
			*	@remarks 	获取包围盒
			*	@see		MovableObject
			*	@return   	BoundBox&
			*	@note
			*
			**/
			virtual	const BoundingBox&	GetWorldBoundingBox()const;
	
			/**	\brief	更新
			*   
			*	@remarks 	更新
			*	@see		MovableObject
			*	@return   	void
			*	@note
			*
			**/
			virtual	void		Prepare(Float44*	pMatrix);
			/**	\brief	准备渲染
			*   
			*	@remarks 	准备渲染
			*	@see		MovableObject
			*	@return   	void
			*	@param		Float44 * pWorldMatrix
			*	@param		Float4 * pWorldQuat
			*	@param		Float3 * pWorldScale
			*	@note
			*
			**/
			virtual	void		Update(	const	Float44&	ParentGlobalWorldMatrix,
										const	Float4&		ParentGlobalWorldQuat,
										const	Float3&		ParentGlobalWorldScale,
										U1					bParentDirty);
	
			/**	\brief	更新
			*   
			*	@remarks 	更新
			*	@see		MovableObject
			*	@return   	void
			*	@note
			*
			**/
			virtual	void		Update(const FrameTime& frameTime);
	
			/**	\brief	获取最终矩阵
			*   
			*	@remarks 	获取最终矩阵
			*	@see		MovableObject
			*	@return   	Client::Float44
			*	@note
			*
			**/
			Float44*					GetWorldMatrix();

			/**	\brief	获取原始包围盒
			*   
			*	@remarks 	这个包围盒没有经过坐标转换
			*	@see		ICullable
			*	@return   	BoundBox&
			*	@note
			*
			**/
			const	BoundingBox&		GetOrginBoundingBox()const;
			/**	\brief	获取包围球
			*   
			*	@remarks 	获取包围球
			*	@see		ICullable
			*	@return   	Common::BoundSphere
			*	@note
			*
			**/
			Sphere			GetBoundSphere();

			/**	\brief	是否在视野
			*   
			*	@remarks 	是否在视野
			*	@see		ICullable
			*	@return   	U1
			*	@note
			*
			**/
			inline	U1		IsInView();

			/**	\brief	手动更新包围盒
			*   
			*	@remarks 	手动更新包围盒
			*	@see		ICullable
			*	@return   	void
			*	@param		Float3 & vMin
			*	@param		Float3 & vMax
			*	@note
			*
			**/
			void			SetBoundBox(const Float3& vMin,const Float3& vMax);

			void			SetCheckView(U1	bEnable	=	true){
				m_bNeedCheckView	=	bEnable;
			};

			virtual	void	ProcessRenderObject(U32	uiPhaseFlag);

			virtual	U1		RayCast(const	Ray&	ray,float*	pOutDistance	=	NULL);

			virtual	U1		OnCameraCull(Camera*	pCamera);
		protected:
			BoundingBox			m_WorldBound;		///<	世界包围盒
			Float44				m_WorldMatrix;		///<	世界矩阵
			Float44				m_ResultMatrix;		///<	渲染所需的最终矩阵
			BoundingBox			m_BoundingBox;			///<	包围盒
			U1					m_bDirty;			///<	自身的矩阵和包围盒是否需要更新

			U1					m_bInView;			///<	是否在视野中
			U1					m_bNeedCheckView;	///<	是否需要视锥裁剪
			SceneNode*			m_pParentNode;
			//Buffer*		m_pObjectCB;	

			RenderableVector	m_vecRenderable;
			U32					m_uiVisiableFrame;	
		};
	};
};
#endif