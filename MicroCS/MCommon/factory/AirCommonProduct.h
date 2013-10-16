
/*****************************************************/
/* @All Right Reserved (C), 2008-2010, 82NET TECO CO.


 \author    InfernalHell	Xinhe
 \date      2009/11/05
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  InterfaceProduct.h
 \note     
       
 \attention:
			产品模版
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/

#ifndef COMMONPRODUCT_HEAD_FILE
#define COMMONPRODUCT_HEAD_FILE


#include "MCommon.h"

#include "AirCommonReference.h"
#include "AirCommonLock.h"
namespace Air{
	
	namespace Common{
		class IFactoryManager;
	
		/**	\brief	资源来源类型
		*
		*	资源来源类型
		*
		***/
		enum enumSourceType{
			SOURCE_TYPE_NEW,			///<	新建
			SOURCE_TYPE_FILE,			///<	从文件加载
			SOURCE_TYPE_MEMERY,			///<	从内存加载
			SOURCE_TYPE_RESOURCE		///<	从资源加载
		};
		/**	\brief	产品模版
		*
		*	产品模版
		*
		***/
		class MCOMMON_EXPORT IProduct	:	
			public	IReference{
		friend class IFactory;
		public:
			IProduct(const AString& strName);
			/**	\brief	返回产品类型名
			*   
			*	@remarks 	返回产品类型名
			*	@see		IProduct
			*	@return   	String
			*	@note
			*
			**/
			virtual	const	AString& GetProductTypeName()const;
			/**	\brief	返回产品名
			*   
			*	@remarks 	返回产品名
			*	@see		IProduct
			*	@return   	String
			*	@note
			*
			**/
			const AString&	GetProductName()const;

			void			SetProductName(CAString& strName);
			/**	\brief	设置工厂管理器
			*   
			*	@remarks 	设置工厂管理器
			*	@see		IProduct
			*	@return   	void
			*	@param		IFactoryManager * pFactoryMgr
			*	@note
			*
			**/
			void		SetFactoryManager(IFactoryManager* pFactoryMgr);
	
			/**	\brief	获取工厂管理器
			*   
			*	@remarks 	获取工厂管理器
			*	@see		IProduct
			*	@return   	IFactoryManager*
			*	@note
			*
			**/
			IFactoryManager*	GetFactoryManager(){
				return	m_pFactoryMgr;
			};
			/**	\brief	设置工厂指针
			*   
			*	@remarks 	设置工厂指针
			*	@see		IProduct
			*	@return   	void
			*	@param		IFactory * pFactory
			*	@note
			*
			**/
			void				SetFactory(IFactory*	pFactory){
				m_pFactory	=	pFactory;
			};
			/**	\brief	添加引用计数
			*   
			*	@remarks 	添加引用计数
			*	@see		IProduct
			*	@return   	U32
			*	@note
			*
			**/
			virtual	U32		AddRef();
	
			/**	\brief	减少引用
			*   
			*	@remarks 	减少引用
			*	@see		IReference
			*	@return   	U32
			*	@note
			*
			**/
			virtual	U32		ReleaseRef();
			virtual	U32		GetSize();

		protected:
			IFactoryManager*	m_pFactoryMgr;					///<	场景指针
			IFactory*			m_pFactory;						///<	工厂指针
			AString				m_strProductName;				///<	产品名
		};

	};
	template<typename T>
	class TProduct	:	public	Common::IProduct{
	public:
		TProduct(const AString& strName):IProduct(strName){};
		static AString	ProductTypeName;

		virtual	const	AString& GetProductTypeName()const{
			return ProductTypeName;
		};
	};
	template<typename T>
	AString	TProduct<T>::ProductTypeName	=	typeid(T).name();

	template<typename T>
	void	TReleaseRef(void*&	pProduct){
		if(pProduct!=NULL){
			T*	p	=	(T*)pProduct;
			p->ReleaseRef();
			pProduct	=	NULL;
		}
	}
	typedef	std::list<Common::IProduct*>	ProductList;
};

#endif // INTERFACEPRODUCT_HEAD_FILE