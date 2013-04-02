#include "AirInterfaceUIKeyProcess.h"
#include "AirInterfaceUIWindowControl.h"

namespace Air{
	
	namespace Engine{
	
		namespace	UI{
			
	
			KeyProcess::KeyProcess(){
	
			}
	
			void KeyProcess::AddKey( U64 Key,Window::IControl* pControl ){
				if(Key==NULL	||	pControl	==	NULL)
					return;
	
				m_mapKey.insert(KeyMapPair(Key,pControl));
			}
	
			void KeyProcess::RemoveKey( U64 Key,Window::IControl* pControl ){
				if(Key==NULL	||	pControl	==	NULL)
					return;
				KeyMapItr	i	=	m_mapKey.find(Key);
				if(i!=m_mapKey.end()){
					if(i->second	==	pControl){
						m_mapKey.erase(i);
						return;
					}
				}
			}
	
			void KeyProcess::ProcessKey( U64 Key,U1	bKeyDown ){
				if(Key==0)
					return;
				KeyMapItr	i	=	m_mapKey.find(Key);
				if(i!=m_mapKey.end()){
					Window::IControl*	pControl	=	i->second;
	
					if(NULL	!=	pControl){
						if(bKeyDown){
							pControl->SetState(enPush);
							//pControl->ExecuteEvent(Message::enShortCutKeyDown,&Message(Union4(true)));
						}else{
							pControl->SetState(enNormal);
							//pControl->ExecuteEvent(Message::enShortCutKeyUp,&Message(Union4(true)));
						}
					}
				}
			}
		}
	}
};