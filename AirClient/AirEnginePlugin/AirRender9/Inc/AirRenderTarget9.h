#ifndef RENDERTARGET_HEAD_FILE
#define RENDERTARGET_HEAD_FILE


#include "AirRenderHeader9.h"
#include "AirRenderFactory9.h"

namespace Air{
	
	namespace Client{
	
		class	IMovableObject;
	
		namespace	Render{
	
			class	Target9	:
				public	ITarget{
			public:
				Target9(CAString& strName,Info* pInfo);
				/**	\brief	摧毁
				*   
				*	@remarks 	摧毁
				*	@see		Target
				*	@return   	U1
				*	@note
				*
				**/
				virtual U1	Destroy( );

				U1			CreateDepthStencil();
				U1			DestroyDepthStencil();
	
	
				/**	\brief	开始渲染
				*   
				*	@remarks 	开始渲染
				*	@see		ITarget
				*	@return   	U1
				*	@note
				*
				**/
				virtual U1			BeforeUpdate();
				virtual	U1			AfterUpdate();
	
				/**	\brief	设置渲染目标物体
				*   
				*	@remarks 	设置渲染目标物体
				*	@see		Target
				*	@return   	void
				*	@param		MovableObject * pObject
				*	@note
				*
				**/
				virtual	void		SetRenderObject(MovableObject*	pObject);
				/**	\brief	获取渲染目标物体
				*   
				*	@remarks 	获取渲染目标物体
				*	@see		ITarget
				*	@return   	IMovableObject*
				*	@note
				*
				**/
				virtual	MovableObject*	GetRenderObject();
	
				/**	\brief	重建
				*   
				*	@remarks 	重建
				*	@see		Target
				*	@return   	void
				*	@param		Info & info
				*	@note
				*
				**/
				virtual	void		ReCreate(Info&	info);
	
				virtual	void*		GetDepthStencil();

				virtual	void		OnLostDevice();
				virtual	void		OnResetDevice();
			protected:
				DxSurface*						m_pSurface;			///<	深度模版
				MovableObject*					m_pTargetObject;	///<	渲染目标物体
			};
	
			class	Target9Factory	:
				public	Factory
			{
			public:
				Target9Factory();
				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		BuffFactory
				*	@return   	IProduct*
				*	@param		AString& strName
				*	@param		IFactoryParamList * lstParam
				*	@note
				*
				**/
				virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam =	NULL);
			};
		};
	};
};
#endif // RENDERTARGET_HEAD_FILE