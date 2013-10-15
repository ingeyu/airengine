#ifndef ENGINEINSTANCEENTITY_HEAD_FILE
#define ENGINEINSTANCEENTITY_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirRenderSystem.h"
#include "AirEngineMovableObject.h"
namespace Air{
	
	namespace Engine{
	
		/**	\brief	实体类
		*
		*	实例类
		*
		***/
		class	ENGINE_EXPORT	InstanceEntity	:
			public	MovableObject{
		public:
			InstanceEntity(CAString&	strName,UInt	uiMaxInstance);
			
	
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		InstanceEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Create();
			/**	\brief	摧毁
			*   
			*	@remarks 	摧毁
			*	@see		InstanceEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Destroy();
	
			/**	\brief	创建模型顶点缓冲
			*   
			*	@remarks 	创建模型顶点缓冲
			*	@see		InstanceEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	CreateModelVertexBuff()		=	NULL;
			/**	\brief	创建实体顶点缓冲
			*   
			*	@remarks 	创建实体顶点缓冲
			*	@see		InstanceEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	CreateInstanceVertexBuff()	=	NULL;
	
			/**	\brief	创建声明
			*   
			*	@remarks 	创建声明
			*	@see		InstanceEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	CreateDeclare()				=	NULL;
	
			/**	\brief	创建索引
			*   
			*	@remarks 	创建索引
			*	@see		InstanceEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	CreateIndex()				=	NULL;
	
			/**	\brief	更新
			*   
			*	@remarks 	更新
			*	@see		InstanceEntity
			*	@return   	void
			*	@note
			*
			**/
			virtual	void	Update();
	
			/**	\brief	渲染
			*   
			*	@remarks 	渲染
			*	@see		InstanceEntity
			*	@return   	void
			*	@note
			*
			**/
			virtual	void	Render();
	
			/**	\brief	设置实体个数
			*   
			*	@remarks 	设置实体个数
			*	@see		InstanceEntity
			*	@return   	void
			*	@param		UInt uiCount
			*	@note
			*
			**/
			inline	void	SetInstanceCount(UInt	uiCount){
				m_uiInstanceCount	=	uiCount;
			}
		protected:
			Render::Vertex::IBuff*	m_pModelVertexBuff;		///<	模型数据
			Render::Vertex::IBuff*	m_pInstanceVertexBuff;	///<	实体数据
			UInt					m_uiInstanceCount;		///<	实体个数
			AString					m_strMaterialName;
		};
	
	};
};
#endif // ENGINEINSTANCEENTITY_HEAD_FILE