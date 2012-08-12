#include "AirCommonProduct.h"
#include "AirCommonFactory.h"
namespace Air{
	
	namespace Common{
		
	
		IProduct::IProduct(const AString& strName)
		:	m_pFactoryMgr(NULL),
			m_strProductName(strName){
			m_pFactory	=	NULL;
		}
	
		AString IProduct::GetProductTypeName()const{
			return m_pFactory->GetType();
		}
	
		const AString& IProduct::GetProductName()const{
			return m_strProductName;
		}
	
		void IProduct::SetFactoryManager( IFactoryManager* pFactoryMgr ){
			m_pFactoryMgr = pFactoryMgr;
		}
	
		U1 IProduct::ReleaseRef(){
			m_CS.Enter();
			m_uiNumRef--;
			//这里要考虑多线程的卸载
			if(m_uiNumRef<=0){
				
				if(m_pFactory!=NULL)
					m_pFactory->Erase(m_strProductName);
				Destroy();
				m_CS.Leave();
				delete	this;
				return	true;
			}
			m_CS.Leave();
			return true;
		}
	
		U1 IProduct::AddRef(){
			U1	ret	=	true;
			m_CS.Enter();
			if(m_uiNumRef<=0){
				//这里要考虑多线程的加载
				ret	=	Create();
			}
			m_uiNumRef++;
			m_CS.Leave();
			return ret;
		}

		Air::U32 IProduct::GetSize(){
			return	sizeof(IProduct)+m_strProductName.size()+1;
		}

		void IProduct::SetUserData( void* pUserData ){
			m_pUserData	=	pUserData;
		}

		void* IProduct::GetUserData(){
			return	m_pUserData;
		}

		void IProduct::SetUserString( CAString& strUserString ){
			m_strUserString	=	strUserString;
		}

		Air::AString IProduct::GetUserString(){
			return	m_strUserString;
		}

		void IProduct::GetUserString( AString& strUserString ){
			strUserString	=	m_strUserString;
		}

		void IProduct::SetProductName( CAString& strName )
		{
			m_strProductName	=	strName;
		}

	}
};