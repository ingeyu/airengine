#include "AirInterfaceUIEvent.h"
namespace Air{
	
	namespace	Client{
		namespace	UI{
			namespace	Event{
	
				Sender::Sender(){
					memset(m_pFunctionArray,0,Message::enMax*4);
				}
	
				Sender::~Sender(){
					RemoveAllEvent();
				}
	
				void Sender::RemoveEvent( Message::enumType type ){
					SAF_D(m_pFunctionArray[type]);
				}
	
				void Sender::RemoveAllEvent(){
					for(UInt i=0;i<Message::enMax;i++){
						//FunctionBase*	pFunctionBase	=	m_pFunctionArray[i];
						SAF_D(m_pFunctionArray[i]);
					}
				}
	
				U1 Sender::ExecuteEvent( Message::enumType type,Message*	pMessage){
					if(m_pFunctionArray[type]!=NULL){
						return	(*m_pFunctionArray[type])(pMessage);
					}else{
						return true;
					}
				}
			}
		}
	}
};