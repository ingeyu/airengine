#ifndef ENGINESCREENENTITY_HEAD_FILE
#define ENGINESCREENENTITY_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirRenderSystem.h"
#include "AirEngineMovableObject.h"
namespace Air{
	
	namespace Engine{
		class	Material;
		/**	\brief	屏幕后期渲染物体
		*
		*	屏幕后期渲染物体
		*
		***/
		class	ENGINE_EXPORT	ScreenEntity	:
			public	Common::IProduct,
			public	MovableObject
		{
		public:
			static AString ProductTypeName;
	 		struct	Info{
				Info(AString	strName	=	""){strMaterialName	=	strName;};
	 			AString	strMaterialName;
	 		};
		public:
			ScreenEntity(CAString&	strName,Info*	pInfo);
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		ScreenEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual U1	Create();
			/**	\brief	摧毁
			*   
			*	@remarks 	摧毁
			*	@see		ScreenEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual U1	Destroy();
	
			/**	\brief	更新
			*   
			*	@remarks 	更新
			*	@see		ScreenEntity
			*	@return   	void
			*	@note
			*
			**/
			virtual void	Update();
		
			/**	\brief	渲染
			*   
			*	@remarks 	渲染
			*	@see		ScreenEntity
			*	@return   	void
			*	@note
			*
			**/
			virtual	void	Render();
	
			/**	\brief	渲染后期效果
			*   
			*	@remarks 	渲染后期效果
			*	@see		ScreenEntity
			*	@return   	ITexture*
			*	@param		IMaterial * pMaterial
			*	@param		ITexture * pInputTexture
			*	@note
			*
			**/
			virtual void	RenderPostComposer(Material*	pMaterial/*,Render::ITexture*	pInputTexture*/);
		protected:
			Info			m_Info;
	
		};
	
		class	ScreenEntityFactory	:
			public	IFactory{
		public:
			ScreenEntityFactory();
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		BuffFactory
			*	@return   	IProduct*
			*	@param		AString strName
			*	@param		IFactoryParamList * lstParam
			*	@note
			*
			**/
			virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam =	NULL);
		};
	
	};
};
#endif // ENGINESCREENENTITY_HEAD_FILE