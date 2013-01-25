/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/08/06
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  EngineRenderable.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef ENGINERENDERABLE_HEAD_FILE
#define ENGINERENDERABLE_HEAD_FILE

#include "AirRenderCommon.h"

namespace	Air{
	namespace Client{
		class	Material;
		namespace	Render{
			namespace	Vertex{
				class	IBuff;
				class	IDeclare;
			}
			namespace	Index{
				class	IBuff;
			}
			class	Buffer;
			class	Device;
		}
	
		/**	\brief	物品渲染的回调
		*
		*	物品渲染的回调
		*
		***/
		class	ENGINE_EXPORT	Renderable{
		public:
			Renderable();
			virtual	~Renderable();

			/**	\brief	获取骨骼数量
			*   
			*	@remarks 	获取骨骼数量
			*	@see		Renderable
			*	@return   	Air::U32
			*	@note
			*
			**/
			virtual	U32		GetBoneCount();
			/**	\brief	获取骨骼矩阵
			*   
			*	@remarks 	获取骨骼矩阵
			*	@see		Renderable
			*	@return   	Matrix*
			*	@note
			*
			**/
			virtual	Float44*	GetBoneMatrix();
			/**	\brief	判断是否有骨骼
			*   
			*	@remarks 	判断是否有骨骼
			*	@see		Renderable
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1		HasSkeleton();
			/**	\brief	设置可见
			*   
			*	@remarks 	设置可见
			*	@see		Renderable
			*	@return   	void
			*	@param		U1 bVisiable
			*	@note
			*
			**/
			void			SetVisiable(U1	bVisiable){
				m_bVisiable	= bVisiable;
			};
			/**	\brief	是否可见
			*   
			*	@remarks 	是否可见
			*	@see		Renderable
			*	@return   	U1
			*	@note
			*
			**/
			U1				IsVisiable(){return m_bVisiable;};
			/**	\brief	获取材质
			*   
			*	@remarks 	获取材质
			*	@see		Renderable
			*	@return   	IMaterial*
			*	@param		enumPhaseIndex	index
			*	@note
			*
			**/
			Material*		GetMaterial(enumPhaseIndex	index	=	enPI_MRT);
			void			SetMaterial(Material*	pMaterial);
			void			SetMaterialNull(enumPhaseIndex	index);
			void			SetMaterialName(CAString&	strMaterialName);

			/**	\brief	渲染前回调
			*   
			*	@remarks 	渲染前回调
			*	@see		Renderable
			*	@return   	void
			*	@param		Material * pMaterial
			*	@note
			*
			**/
			virtual	void	BeforeRender(Material*	pMaterial);

			virtual	void	OnRender(Render::Device* pDevice);
			/**	\brief	判断自身是否需要世界矩阵
			*   
			*	@remarks 	由SceneNode->MovableObject->Renderable传递而来	自身并不创建
			*	@see		Renderable
			*	@return   	Air::U1
			*	@note
			*
			**/
			U1				NeedWorldMatrix();
			/**	\brief	设置自身是否需要世界矩阵
			*   
			*	@remarks 	由SceneNode->MovableObject->Renderable传递而来
			*	@see		Renderable
			*	@return   	void
			*	@param		U1 bNeed
			*	@note
			*
			**/
			void			SetNeedWorldMatrix(U1	bNeed);

			

			/**	\brief	设置Instance个数
			*   
			*	@remarks 	设置Instance个数
			*	@see		Renderable
			*	@return   	void
			*	@param		U32 uiCount
			*	@note
			*
			**/
			void			SetInstanceCount(U32	uiCount);

			void			AddToRenderQueue(U32	uiPhaseFlag);

			virtual	Matrix*	GetWorldMatrix(){return	NULL;};
		protected:
			U1							m_bVisiable;			///<	是否可见
			U1							m_bNeedWorldMatrix;		///<	是否需要世界矩阵	//默认需要传递世界矩阵
			Material*					m_pMaterial[32];		///<	材质
			DrawBuff					m_DrawBuff;				///<	渲染缓冲
			Buffer*						m_pObjectCB;			///<	由MovableObject->Renderable传递而来
			Buffer*						m_pBoneCB;
		};

		typedef	TVector<Renderable*>	RenderableVector;
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // ENGINERENDERABLE_HEAD_FILE