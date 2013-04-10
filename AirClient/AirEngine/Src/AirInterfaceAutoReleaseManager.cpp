#include "AirInterfaceAutoReleaseManager.h"
namespace Air{
	
	namespace	Engine{
	
	
		IAutoReleaseManager::IAutoReleaseManager(){
			m_uiProductCount	=	0;
			m_uiCacheSize		=	0;
		}
	
		void	IAutoReleaseManager::PushObject2Release(IProduct*	pObject){
			if(pObject==NULL)
				return;
			m_lstProduct.push_back(pObject);
			m_uiProductCount++;
			//::OutputDebugStringA(p->GetProductName().c_str());
			//::OutputDebugStringA("存入自动摧毁物体\n");
		}
		UInt	IAutoReleaseManager::GetProductCount(){
			return	m_uiProductCount;
		}
	
		void	IAutoReleaseManager::ReleaseAllAutoObject(){
			ProductListItr	i	=	m_lstProduct.begin();
			for(;i!=m_lstProduct.end();i++){
				IProduct*	p	=	(IProduct*)(*i);
				if(p!=NULL){
					p->ReleaseRef();
				}
			}
			m_uiProductCount	=	0;
			m_lstProduct.clear();
	
		}
	
		void IAutoReleaseManager::ReleaseOneObject(){
			while(true){
				ProductListItr	i	=	m_lstProduct.begin();
				if(i!=m_lstProduct.end()){
					IProduct*	p	=	(IProduct*)(*i);
					m_lstProduct.pop_front();
					if(p!=NULL){
						p->ReleaseRef();
					}
					m_uiProductCount--;
					if(m_uiProductCount<=m_uiCacheSize)
						return;
				}else{
					return;
				}
			}
		}
	}
};