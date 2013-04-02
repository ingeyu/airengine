#ifndef ENGINEPOSTCOMPOSER_HEAD_FILE
#define ENGINEPOSTCOMPOSER_HEAD_FILE

#include "AirEngineHeader.h"
namespace Air{
	
	namespace Engine{
		class	Material;
	
		/**	\brief	后期效果
		*
		*	后期效果
		*
		***/
		class	PostComposer	:
			public	IProduct{
		public:
			PostComposer(AString	strName,AString*	strMaterialName);
	
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		PostComposer
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1		Create();
			/**	\brief	摧毁
			*   
			*	@remarks 	摧毁
			*	@see		PostComposer
			*	@return   	U1
			*	@note
			*
			**/
			virtual U1		Destroy();
	
			/**	\brief	设置是否启用该后期效果
			*   
			*	@remarks 	设置是否启用该后期效果
			*	@see		PostComposer
			*	@return   	void
			*	@param		U1 bEnable
			*	@note
			*
			**/
			inline	void	SetEnable(U1	bEnable);
			/**	\brief	获取是否已经启用
			*   
			*	@remarks 	获取是否已经启用
			*	@see		PostComposer
			*	@return   	U1
			*	@note
			*
			**/
			inline	U1		GetEnable();
			/**	\brief	渲染该后期效果
			*   
			*	@remarks 	渲染该后期效果
			*	@see		PostComposer
			*	@return   	void
			*	@note
			*
			**/
			virtual	void	Render();
	
		protected:
			U1					m_bEnable;				///<	是否启用渲染目标
			RenderTarget*		m_pTerget;				///<	渲染目标
			Material*			m_pMaterial;			///<	材质
			AString				m_strMaterialName;		///<	材质名
		};
	
		class	PostComposerFactory	:
			public	IFactory{
		public:
			PostComposerFactory();
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		BuffFactory
			*	@return   	IProduct*
			*	@param		CAString& strName
			*	@param		IFactoryParamList * lstParam
			*	@note
			*
			**/
			virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam =	NULL);
		};
	
	};
};
#endif // ENGINEPOSTCOMPOSER_HEAD_FILE