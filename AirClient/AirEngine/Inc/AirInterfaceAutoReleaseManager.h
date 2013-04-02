#ifndef INTERFACEAUTORELEASEMANAGER_HEAD_FILE
#define INTERFACEAUTORELEASEMANAGER_HEAD_FILE

#include "AirEngineHeader.h"
namespace Air{
	
	namespace Engine{
	
		/**	\brief	自动释放类
		*
		*	主要用于哪种频繁创建摧毁的物体 比如地形块 粒子效果 声效
		*
		***/
		class	IAutoReleaseManager{
		public:
			IAutoReleaseManager();
	
			/**	\brief	添加需要自动释放的产品
			*   
			*	@remarks 	添加需要自动释放的产品
			*	@see		IAutoReleaseManager
			*	@return   	void
			*	@param		IProduct * pProduct
			*	@note
			*
			**/
			void	PushObject2Release(IProduct*	pProduct);
			/**	\brief	获取产品数量
			*   
			*	@remarks 	获取产品数量
			*	@see		IAutoReleaseManager
			*	@return   	UInt
			*	@note
			*
			**/
			UInt	GetProductCount();
			/**	\brief	摧毁一个产品 如果当前数量大于缓冲值
			*   
			*	@remarks 	则摧毁一个
			*	@see		IAutoReleaseManager
			*	@return   	void
			*	@note
			*
			**/
			void	ReleaseOneObject();
			/**	\brief	释放所有产品
			*   
			*	@remarks 	释放所有产品
			*	@see		IAutoReleaseManager
			*	@return   	void
			*	@note
			*
			**/
			void	ReleaseAllAutoObject();
			/**	\brief	设置缓冲区大小
			*   
			*	@remarks 	设置缓冲区大小
			*	@see		IAutoReleaseManager
			*	@return   	void
			*	@param		UInt uiSize
			*	@note
			*
			**/
			inline	void	SetCacheSize(UInt	uiSize){
				m_uiCacheSize	=	uiSize;
			};
			/**	\brief	获取缓冲区大小
			*   
			*	@remarks 	获取缓冲区大小
			*	@see		IAutoReleaseManager
			*	@return   	UInt
			*	@note
			*
			**/
			UInt	GetCacheSize(){
				return	m_uiCacheSize;
			};
	
			typedef	std::list<IProduct*>	ProductList;
			typedef	ProductList::iterator	ProductListItr;
	
			ProductList				m_lstProduct;
			SInt					m_uiProductCount;
			SInt					m_uiCacheSize;
		};
	
	};
};
#endif // INTERFACEAUTORELEASEMANAGER_HEAD_FILE