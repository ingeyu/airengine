#include "AirCommonRequestProduct.h"

namespace	Air{
	namespace	Common{


		RequestProduct::RequestProduct( const AString& strName ):IProduct(strName){

		}

		void RequestProduct::AddRequest( IRequest* pRequest ){
			m_CS.Enter();
			RequestManager::AddRequest(pRequest);
			m_CS.Leave();
		}

		IRequest* RequestProduct::GetRequest(){
			IRequest*	p	=	NULL;
			m_CS.Enter();
			p	=	RequestManager::GetRequest();
			m_CS.Leave();
			return	p;
		}

		Air::U1 RequestProduct::HasReuqest(){
			U1	b	=	false;
			m_CS.Enter();
			b	=	RequestManager::HasReuqest();
			m_CS.Leave();
			return	b;
		}

		void RequestProduct::ExcuteFunction( const IRequest& request ){
			m_CS.Enter();
			RequestManager::ExcuteFunction(request);
			m_CS.Leave();
		}
	}
}