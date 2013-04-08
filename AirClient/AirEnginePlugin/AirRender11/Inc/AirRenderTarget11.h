#ifndef RENDERTARGET_HEAD_FILE
#define RENDERTARGET_HEAD_FILE


#include "AirRenderHeader11.h"
#include "AirRenderFactory11.h"

namespace Air{
	
	namespace Engine{
	
		class	IMovableObject;
	
		namespace	Render{
	
			class	Target11 :
				public	Target{
			public:
				Target11(CAString& strName,Info* pInfo);
				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		Target
				*	@return   	U1
				*	@note
				*
				**/
				virtual U1	Create( );
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
				virtual	U1			BeforeUpdate(U32	uiFace	=	0);
				virtual	U1			AfterUpdate(U1 bSwapBuffer);
	
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

				virtual		void*	GetDepthRTV()	;
				virtual		void*	GetDepthSRV()	;
				virtual		void*	GetDepthBuffer();

				virtual		void	OnMainWindowSize(Window* pMainWindow);
			protected:
				DxDSV*							m_pDepthBufferDSV;
				DxSRV*							m_pDepthBufferSRV;
				DxTexture*						m_pDepthBuffer;
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