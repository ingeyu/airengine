#include "AirCommonProduct.h"
#include "AirCommonFactory.h"
namespace Air{
	
	namespace Common{
		
	
		IProduct::IProduct(const AString& strName)
		:	m_pFactoryMgr(NULL),
			m_strProductName(strName){
			m_pFactory	=	NULL;
			
		}
	
		const	AString& IProduct::GetProductTypeName()const{
			return m_pFactory->GetType();
		}
	
		const AString& IProduct::GetProductName()const{
			return m_strProductName;
		}
	
		void IProduct::SetFactoryManager( IFactoryManager* pFactoryMgr ){
			m_pFactoryMgr = pFactoryMgr;
		}
	
		U32 IProduct::ReleaseRef(){
			U32	uiRef	=	InterlockedDecrement(&m_uiNumRef);
			//这里要考虑多线程的卸载
			if(uiRef==0){
				if(m_pFactory!=NULL){
					if(!m_pFactory->Erase(m_strProductName)){
						return m_uiNumRef;
					}
				}
				Destroy();
				delete this;
			}
			return uiRef;
		}
	
		U32 IProduct::AddRef(){
			U32	uiRef	=	InterlockedIncrement(&m_uiNumRef);
			if(uiRef==1){
				//这里要考虑多线程的加载
				if(!Create()){
					return	0;
				};
			}
			return uiRef;
		}

		U32 IProduct::GetSize(){
			return	sizeof(IProduct)+m_strProductName.size()+1;
		}
		void IProduct::SetProductName( CAString& strName )
		{
			m_strProductName	=	strName;
		}

	}
};