#include "AirCommonRequest.h"

namespace	Air{
	namespace	Common{


		RequestManager::~RequestManager(){
			RequestList::iterator	i	=	m_lstRequest.begin();
			for(;i!=m_lstRequest.end();i++){
				IRequest*	p	=	(IRequest*)(*i);
				SAF_D(p);
			}
			m_lstRequest.clear();

			FunctionMap::iterator	itr	=	m_mapFunction.begin();
			for(;itr!=m_mapFunction.end();itr++){
				SAF_D(itr->second);
			}
			m_mapFunction.clear();
		}

		void RequestManager::AddRequest( IRequest* pRequest ){
			m_lstRequest.push_back(pRequest);
		}

		IRequest* RequestManager::GetRequest(){
			IRequest*	p	=	NULL;
			RequestList::iterator	i	=	m_lstRequest.begin();
			if(i!=m_lstRequest.end()){
				p	=	(IRequest*)(*i);
				m_lstRequest.pop_front();
			}

			return	p;
		}

		Air::U1 RequestManager::HasReuqest(){
			return	m_lstRequest.empty();
		}

		void RequestManager::ProcessRequest(){
			if(HasReuqest()){
				IRequest*	p	=	GetRequest();
				while(p!=NULL){
					ExcuteFunction(*p);
					SAF_D(p);
					p	=	GetRequest();
				}
			}
		}

		void RequestManager::ExcuteFunction(const IRequest&	request){
			FunctionMap::iterator	i	=	m_mapFunction.find(request.type);
			if(i!=m_mapFunction.end()){
				(*i->second)(request);
			}
		}

		void RequestManager::AddFunction( UInt iRequestID,RFunction* pFunction ){
			if(pFunction==NULL)
				return;
			FunctionMap::iterator	i	=	m_mapFunction.find(iRequestID);
			if(i!=m_mapFunction.end()){
				SAF_D(i->second);
			}

			m_mapFunction[iRequestID]	=	pFunction;
		}
	}
}