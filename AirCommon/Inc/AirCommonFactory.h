//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/04/03
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonFactory.h
 \note     
       
 \attention:
			工厂模版
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONFACTORY_HEAD_FILE
#define COMMONFACTORY_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"
#include "AirCommonProduct.h"
#include "AirCommonLock.h"
namespace Air{
	
	namespace Common{
	
		/**	\brief	参数列表
		*
		*	工厂类创建时候使用的参数列表
		*
		***/
		typedef	void						IFactoryParamList;
		/**	\brief	工厂模版接口基类
		*
		*	工厂模版接口基类
		*
		***/
		class COMMON_EXPORT IBaseFactory{
		public:
			IBaseFactory();
			virtual ~IBaseFactory();
			/**	\brief	设置类型
			*   
			*	@remarks 	设置类型
			*	@see		IBaseFactory
			*	@return   	void
			*	@param		AString strTypeName
			*	@note
			*
			**/
			virtual void SetType(const AString& strTypeName);
			/**	\brief	获取工厂类型
			*   
			*	@remarks 	获取工厂类型
			*	@see		IBaseFactory
			*	@return   	AString
			*	@note
			*
			**/
			const AString& GetType()const;
		protected:
			AString		m_strTypeName;		///<	工厂类型名
		};
		/**	\brief 工厂模版
		*
		*	工厂模版 主要用于创建 删除
		*
		***/
		class COMMON_EXPORT IFactory : public IBaseFactory{
		friend class IFactoryManager;
		public:
			typedef stdext::hash_map<AString,IProduct*>					ProductMap;
			typedef stdext::hash_map<AString,IProduct*>::iterator		ProductMapItr;
			typedef stdext::hash_map<AString,IProduct*>::value_type		ProductMapPair;
		public:
			IFactory();
			virtual ~IFactory();
			/**	\brief	创建产品
			*   
			*	@remarks 	创建产品
			*	@see		IFactory
			*	@return   	T_Product*
			*	@param		AString strName
			*	@note
			*
			**/
			template<typename T_Product>
			T_Product	NewProduct(CAString& strName,IFactoryParamList* lstParam = NULL){
				return dynamic_cast<T_Product>(Create(strName,lstParam));
			};
	
			virtual IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam = NULL)=NULL;
	
	
			/**	\brief	摧毁产品
			*   
			*	@remarks 	
			*	@see		IFactory
			*	@return   	bool
			*	@param		T_Product * pProduct
			*	@note
			*
			**/
			virtual bool		Destroy(IProduct* pProduct);
	
			/**	\brief	销毁所有产品
			*   
			*	@remarks 	销毁所有产品
			*	@see		IFactory
			*	@return   	bool
			*	@note
			*
			**/
			virtual bool		DestroyAllProduct();
	
			/**	\brief	返回产品数量
			*   
			*	@remarks 	返回产品数量
			*	@see		IFactory
			*	@return   	int
			*	@note
			*
			**/
			virtual U32			GetProductCount()const;
	
			/**	\brief	查找产品
			*   
			*	@remarks 	获取产品 通过名字查找
			*	@see		IFactory
			*	@return   	T_Product
			*	@param		AString strName
			*	@note
			*
			**/
			template<typename T_Product>
			T_Product GetProduct(const AString& strName){
				return dynamic_cast<T_Product>(GetProduct(strName));
			};
			IProduct* GetProduct(const AString& strName);
			/**	\brief	是否存在于列表中
			*   
			*	@remarks 	
			*	@see		IFactory
			*	@return   	bool
			*	@param		AString strName
			*	@note
			*
			**/
			bool Exist(const AString& strName)const;
			/**	\brief	从列表中移除
			*   
			*	@remarks 	仅移除 不做摧毁
			*	@see		IFactory
			*	@return   	bool
			*	@param		const AString& strName
			*	@note
			*
			**/
			virtual bool Erase(const AString& strName);
			/**	\brief	从列表中移除
			*   
			*	@remarks 	仅移除 不做摧毁
			*	@see		IFactory
			*	@return   	bool
			*	@param		IProduct*  pProduct
			*	@note
			*
			**/
			virtual bool Erase(IProduct* pProduct);
	
			/**	\brief	获取产品列表
			*   
			*	@remarks 	获取产品列表
			*	@see		IFactory
			*	@return   	ProductList&
			*	@note
			*
			**/
			const ProductMap&		GetProductList()const;
		//protected:
			/**	\brief	插入产品列表中
			*   
			*	@remarks 	当派生类创建了一个产品之后 记得调用Insert函数 将产品指针添加到工厂的列表中 这样在工厂被销毁的时候 所有未销毁的产品将一同被销毁
			*	@see		IFactory
			*	@return   	void
			*	@param		IProduct * pProduct
			*	@note
			*
			**/
			void		Insert(IProduct* pProduct);
	
			/**	\brief	设置工厂管理器
			*   
			*	@remarks 	设置工厂管理器
			*	@see		IFactory
			*	@return   	void
			*	@param		IFactoryManager * pFactoryMgr
			*	@note
			*
			**/
			void		SetFactoryManager(IFactoryManager* pFactoryMgr);
		protected:
			ProductMap								m_mapProduct;		///<	产品列表
			IFactoryManager*						m_pFactoryMgr;		///>	工厂管理器
			CriticalSection							m_CS;				///<	临界区锁
		};
		/**	\brief	工厂管理器模版
		*
		*	工厂管理器模版 管理工厂
		*
		***/
		class COMMON_EXPORT IFactoryManager : public IBaseFactory{
		public:
			IFactoryManager();
			virtual ~IFactoryManager();
	
			/**	\brief	添加一个工厂
			*   
			*	@remarks 	添加一个工厂
			*	@see		IFactoryManager
			*	@return   	void
			*	@param		IBaseFactory * pFactory
			*	@note
			*
			**/
			virtual void AddFactory(IFactory* pFactory);
			/**	\brief	移除工厂
			*   
			*	@remarks 	移除工厂
			*	@see		IFactoryManager
			*	@return   	void
			*	@param		IBaseFactory * pFactory
			*	@note
			*
			**/
			virtual void RemoveFactory(IFactory* pFactory);
			/**	\brief	移除工厂
			*   
			*	@remarks 	移除工厂
			*	@see		IFactoryManager
			*	@return   	void
			*	@param		const AString& strFactoryName
			*	@note
			*
			**/
			virtual void RemoveFactory(const AString& strFactoryName);
			/**	\brief	获取工厂指针
			*   
			*	@remarks 	获取工厂指针
			*	@see		IFactoryManager
			*	@return   	*
			*	@param		const AString& strFactoryName
			*	@note
			*
			**/
			IFactory* GetFactory(const AString& strFactoryName)const;
	
			/**	\brief	获取产品
			*   
			*	@remarks 	获取产品
			*	@see		IFactoryManager
			*	@return   	IProduct*
			*	@note
			*
			**/
			IProduct* GetProduct(const AString& strName,const AString& strFactoryName)const;
	
			/**	\brief	创建产品
			*   
			*	@remarks 	创建产品
			*	@see		IFactoryManager
			*	@return   	T_Product*;
			*	@param		const AString& strName
			*	@param		const AString& strFactoryName
			*	@param		IFactoryParamList* lstParam
			*	@note
			*
			**/
			template<typename T_Product>
			T_Product CreateProduct(const AString& strName,const AString& strFactoryName,IFactoryParamList* lstParam = NULL){
				IProduct*	pProduct	=	CreateProduct(strName,strFactoryName,lstParam);
				if(pProduct==NULL)
					return	NULL;
				T_Product	p	=	dynamic_cast<T_Product>(pProduct);
				if(	p	==	NULL){
					pProduct->ReleaseRef();
				}
				return p;
			};
			IProduct* CreateProduct(const AString& strName,const AString& strFactoryName,IFactoryParamList* lstParam = NULL);
	
			/**	\brief	摧毁产品
			*   
			*	@remarks 	
			*	@see		IFactoryManager
			*	@return   	bool
			*	@param		T_Product * pProduct
			*	@note
			*
			**/
	
			bool Destroy(IProduct* pProduct);
	
			/**	\brief	摧毁产品
			*   
			*	@remarks 	摧毁产品
			*	@see		IFactoryManager
			*	@return   	bool
			*	@param		T_Product pProduct
			*	@note
			*
			**/
	 		template	<typename	T_Product>
			bool DestroyProduct(T_Product* pProduct){
				//这里需要注意的是继承树问题 必须要用dynamic_cast
				//否则可能会出现异常
				//如下图的继承树 如果要把A*->B*就需要使用dynamic_cast
				//------------------------------------------------------
				//	A     B
				//	 \   /
				//    \ /
				//	   C
				//     |
				//     |
				//     D
				//------------------------------------------------------
				m_CS.Enter();
	 			IProduct*	p	=	dynamic_cast<IProduct*>(pProduct);
	 			bool	bReturn	= Destroy(p);
	 			pProduct	=	NULL;
				m_CS.Leave();
	 			return bReturn;
	 		};
	
			/**	\brief	释放所有已创建的产品
			*   
			*	@remarks 	释放所有已创建的产品
			*	@see		IFactoryManager
			*	@return   	bool
			*	@note
			*
			**/
			bool DestroyAllProduct();
	
			/**	\brief	清理所有工厂
			*   
			*	@remarks 	清理所有工厂
			*	@see		IFactoryManager
			*	@return   	bool
			*	@note
			*
			**/
			virtual bool DestroyAllFactory();
	
			typedef stdext::hash_map<AString,IFactory*>				FactoryMap;			///<	工厂列表
			typedef stdext::hash_map<AString,IFactory*>::iterator	FactoryMapItr;		///<	工厂列表迭代器
			typedef stdext::hash_map<AString,IFactory*>::value_type	FactoryMapPair;		///<	工厂列表组
	
			typedef	std::list<IFactory*>							FactoryList;
			typedef	FactoryList::iterator							FactoryListItr;
		protected:
			FactoryMap		m_mapFactory;		///<	工厂列表
			FactoryList		m_lstFactory;
			CriticalSection	m_CS;				///<	临界区锁
		};
	
	

};
	/**	\brief	模板工厂无参数
	*
	*	模板工厂无参数
	*
	***/
	template<typename	T_Product>
	class	NoParamFactory	:	
		public	Common::IFactory{
	public:
		NoParamFactory(const AString&	strName){
			m_strTypeName	=	strName;
		};
		virtual	Common::IProduct*	NewProduct(CAString& strName,Common::IFactoryParamList* lstParam /* = NULL */){
			return	new	T_Product(strName);
		}
	};
	/**	\brief	模板工厂有参数
	*
	*	模板工厂有参数
	*
	***/
	template<typename	T_Product>
	class	ParamFactory	:	
		public	Common::IFactory{
	public:
		ParamFactory(const AString&	strName){
			m_strTypeName	=	strName;
		};
		virtual	Common::IProduct*	NewProduct(CAString& strName,Common::IFactoryParamList* lstParam /* = NULL */){
			if(lstParam	==	NULL)
				return	NULL;
			return	new	T_Product(strName,(T_Product::Info*)lstParam);
		}
	};
		/**	\brief	模板工厂有参数
	*
	*	模板工厂有参数
	*
	***/
	template<typename	T_Product>
	class	OptionParamFactory	:	
		public	Common::IFactory{
	public:
		OptionParamFactory(const AString&	strName){
			m_strTypeName	=	strName;
		};
		virtual	Common::IProduct*	NewProduct(CAString& strName,Common::IFactoryParamList* lstParam /* = NULL */){
			return	new	T_Product(strName,(T_Product::Info*)lstParam);
		}
	};
	/**	\brief	模板工厂有参数
	*
	*	模板工厂有参数 非标准
	*
	***/
	template<typename	T_Product,typename	T_ProductInfo>
	class	ExtraParamFactory	:	
		public	Common::IFactory{
	public:
		ExtraParamFactory(const AString&	strName){
			m_strTypeName	=	strName;
		};
		virtual	Common::IProduct*	NewProduct(CAString& strName,Common::IFactoryParamList* lstParam /* = NULL */){
			if(lstParam	==	NULL)
				return	NULL;
			return	new	T_Product(strName,(T_ProductInfo*)lstParam);
		}
	};
	/**	\brief	模板工厂可选参数
	*
	*	模板工厂可选参数 非标准
	*
	***/
	template<typename	T_Product,typename	T_ProductInfo>
	class	ExtraOptionParamFactory	:	
		public	Common::IFactory{
	public:
		ExtraOptionParamFactory(const AString&	strName){
			m_strTypeName	=	strName;
		};
		virtual	Common::IProduct*	NewProduct(CAString& strName,Common::IFactoryParamList* lstParam /* = NULL */){
			return	new	T_Product(strName,(T_ProductInfo)lstParam);
		}
	};
};
#endif