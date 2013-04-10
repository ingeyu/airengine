#include "AirCommonFactory.h"


namespace Air{
	
	namespace Common{
	
	
		IBaseFactory::IBaseFactory(const AString& strTypeName):m_strTypeName(strTypeName){
		}
	
		IBaseFactory::~IBaseFactory(){

		}

	
		const AString& IBaseFactory::GetType()const{
			return m_strTypeName;
		}
	
		IFactory::IFactory(const AString& strTypeName):IBaseFactory(strTypeName){
			m_pFactoryMgr	= NULL;
		}
	
		IFactory::~IFactory(){
			DestroyAllProduct();
	
		}
	
		bool IFactory::Destroy( IProduct* pProduct ){
			if(pProduct!=NULL){
				pProduct->ReleaseRef();
			}
			return true;
		}
	
		U32 IFactory::GetProductCount()const{
			return m_mapProduct.size();
		}
	
		IProduct* IFactory::GetProduct( const AString& strName ){
			IProduct*	pProduct	=	NULL;
			m_CS.Enter();
			ProductMap::const_iterator itr = m_mapProduct.find(strName.c_str());
			if(itr!=m_mapProduct.end())
				pProduct	= itr->second;
			if(pProduct!=NULL)
				pProduct->AddRef();
			m_CS.Leave();

			return pProduct;
		}
	
		bool IFactory::Exist( const AString& strName )const{
			ProductMap::const_iterator itr = m_mapProduct.find(strName);
			return	(itr!=m_mapProduct.end());
		}
	
		bool IFactory::Erase(const AString& strName ){
			bool bRet	=	true;
			m_CS.Enter();
			ProductMapItr itr = m_mapProduct.find(strName.c_str());
			if(itr!=m_mapProduct.end()){
				if(itr->second->GetRefCount()==0){
					m_mapProduct.erase(itr);
				}else{
					bRet	=	false;
				}
			}
			m_CS.Leave();
			return	bRet;
		}
	
		bool IFactory::Erase( IProduct* pProduct ){
			if(pProduct==NULL)
				return false;
			return Erase(pProduct->GetProductName());
		}
	
		void IFactory::Insert( IProduct* pProduct ){
			if(pProduct==NULL)
				return;
			m_CS.Enter();
			m_mapProduct[pProduct->GetProductName().c_str()]	=	pProduct;
			m_CS.Leave();
		}
	
		void IFactory::SetFactoryManager( IFactoryManager* pFactoryMgr ){
			m_pFactoryMgr = pFactoryMgr;
		}
	
		bool IFactory::DestroyAllProduct(){
			//将产品列表拷贝到另外一个列表 把原来的列表进行清空
			//如果不清空 在DELETE IProduct的时候 会调用 IProduct的析构函数 进而调用到IFactory::Erase 最终导致迭代器不正常的问题
			while(!m_mapProduct.empty()){
				ProductMap lst = m_mapProduct;
			
				ProductMapItr i = lst.begin();
				for(;i!=lst.end();i++){
					IProduct* &p = i->second;
					if(p!=NULL){
						p->ReleaseRef();
					}
				}
				lst.clear();
			}
			return true;
		}
	
		const IFactory::ProductMap& IFactory::GetProductList()const{
			return	m_mapProduct;
		}

		IProduct* IFactory::CreateProduct( CAString& strName,IFactoryParamList* lstParam /*= NULL*/ )
		{
			IProduct*	pProduct	=	NULL;
			m_CS.Enter();
			ProductMap::const_iterator itr = m_mapProduct.find(strName);
			if(itr!=m_mapProduct.end()){
				pProduct	= itr->second;
			}else{
				pProduct	= NewProduct(strName,lstParam);
				if(pProduct!=NULL){
					pProduct->SetFactory(this);
					pProduct->SetFactoryManager(m_pFactoryMgr);
					m_mapProduct[strName.c_str()]	=	pProduct;
				}
			}
			if(pProduct!=NULL)
				pProduct->AddRef();
			m_CS.Leave();
			return pProduct;

		}

		IFactoryManager::IFactoryManager(){
			
		}
	
		IFactoryManager::~IFactoryManager(){
			DestroyAllFactory();
		}
	
		void IFactoryManager::AddFactory( IFactory* pFactory ){
			if(pFactory==NULL)
				return;
			FactoryMapItr	i	=	m_mapFactory.find(pFactory->GetType());
			if(i!=m_mapFactory.end()){
				m_lstFactory.remove(i->second);
				SAF_D(i->second);
				i->second	=	pFactory;
				m_lstFactory.push_back(pFactory);
			}else{
				m_lstFactory.push_back(pFactory);
				m_mapFactory.insert(FactoryMapPair(pFactory->GetType().c_str(),pFactory));
			}
			pFactory->SetFactoryManager(this);
		}
	
		void IFactoryManager::RemoveFactory( IFactory* pFactory ){
	
			FactoryMapItr itr = m_mapFactory.begin();
			for(;itr!=m_mapFactory.end();itr++){
				IFactory* p = itr->second;
				if(pFactory == p){
					m_lstFactory.remove(pFactory);
					SAF_D(p);
					m_mapFactory.erase(itr);
					return;
				}
			}
		}
	
		void IFactoryManager::RemoveFactory( const AString& strFactoryName ){
			FactoryMapItr i = m_mapFactory.find(strFactoryName.c_str());
			if(i!=m_mapFactory.end()){
				IFactory*	pFactory	=	i->second;
				m_lstFactory.remove(pFactory);
				SAF_D(pFactory);
				m_mapFactory.erase(i);
			}
		}
	
		bool IFactoryManager::DestroyAllFactory(){
	// 		FactoryMapItr i = m_mapFactory.begin();
	// 		for(;i != m_mapFactory.end();i++){
	// 			IBaseFactory* pFactory = i->second;
	// 			SAF_D(pFactory);
	// 		}
			//逆向释放所有工厂  工厂与工厂之间存在着依赖性
			FactoryList::reverse_iterator	i	=	m_lstFactory.rbegin();
			for(;i!=m_lstFactory.rend();i++){
				IFactory*	pFactory	=	(IFactory*)(*i);
				SAF_D(pFactory);
			}
			m_lstFactory.clear();
			m_mapFactory.clear();
			return true;
		}
	
		IFactory* IFactoryManager::GetFactory( const AString& strFactoryName )const{
			FactoryMap::const_iterator i = m_mapFactory.find(strFactoryName.c_str());
			if(i!=m_mapFactory.end()){
				IFactory* pFactory = i->second;//dynamic_cast<IFactory<T_Product>*>(i->second);
				return pFactory;
			}
			return NULL;
		}
	
		bool IFactoryManager::Destroy( IProduct* pProduct){
			if(pProduct==NULL)
				return false;
			IFactory* pFactory = GetFactory(pProduct->GetProductTypeName());
			if(pFactory == NULL)
				return false;
			return pFactory->Destroy(pProduct);
		}
	
		IProduct* IFactoryManager::CreateProduct( const AString& strName,const AString& strFactoryName,IFactoryParamList* lstParam /*= NULL*/ ){
			if(strName.empty())
				return	NULL;
			//查找工厂
			IFactory* pFactory = GetFactory(strFactoryName);
			if(pFactory == NULL)
				return 0;
			return pFactory->CreateProduct(strName,lstParam);
		}
	
		IProduct* IFactoryManager::GetProduct(const AString& strName,const AString& strFactoryName)const{
			//查找工厂
			IFactory* pFactory = GetFactory(strFactoryName);
			if(pFactory == NULL)
				return 0;
			//查找是否已经创建 是则直接返回
			IProduct* pProduct = pFactory->GetProduct(strName);
			return	pProduct;
		}
	
		bool IFactoryManager::DestroyAllProduct(){
	// 		FactoryMapItr i = m_mapFactory.begin();
	// 		if(i!=m_mapFactory.end()){
	// 			IFactory* pFactory = i->second;//dynamic_cast<IFactory<T_Product>*>(i->second);
	// 			if(pFactory!=NULL){
	// 				pFactory->DestroyAllProduct();
	// 			}
	// 		}
			//逆向释放所有工厂  工厂与工厂之间存在着依赖性
			FactoryList::reverse_iterator	i	=	m_lstFactory.rbegin();
			for(;i!=m_lstFactory.rend();i++){
				IFactory*	pFactory	=	(IFactory*)(*i);
				if(pFactory!=NULL){
					pFactory->DestroyAllProduct();
				}
			}
			return true;
		}
	
	// 	bool IFactoryManager::DestroyProduct( void* pProduct ){
	// 		IProduct*	p	=	dynamic_cast<IProduct*>(pProduct);
	// 		Destroy(p);
	// 		return true;
	// 	}	
	}
};