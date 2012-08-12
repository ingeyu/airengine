#include "AirGameControl.h"
namespace Air{
	
	namespace	Client{
		namespace	Game{
	
	
			Control::Control(){
				m_pInputState			=	GetGlobalSetting().m_pInputSystem;
				m_pActionStateCallback	=	NULL;
			}
	
			bool Control::keyPressed( const OIS::KeyEvent &arg ){
				ControlListItr	i	=	m_lstControl.begin();
				for(;i!=m_lstControl.end();i++){
					Control*	p	=	(Control*)(*i);
					p->keyPressed(arg);
				}
				return true;
			}
	
			bool Control::keyReleased( const OIS::KeyEvent &arg ){
				ControlListItr	i	=	m_lstControl.begin();
				for(;i!=m_lstControl.end();i++){
					Control*	p	=	(Control*)(*i);
					p->keyReleased(arg);
				}
				return true;
			}
	
			bool Control::mouseMoved( const OIS::MouseEvent &arg ){
				ControlListItr	i	=	m_lstControl.begin();
				for(;i!=m_lstControl.end();i++){
					Control*	p	=	(Control*)(*i);
					p->mouseMoved(arg);
				}
				return true;
			}
	
			bool Control::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
				ControlListItr	i	=	m_lstControl.begin();
				for(;i!=m_lstControl.end();i++){
					Control*	p	=	(Control*)(*i);
					p->mousePressed(arg,id);
				}
				return true;
			}
	
			bool Control::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
				ControlListItr	i	=	m_lstControl.begin();
				for(;i!=m_lstControl.end();i++){
					Control*	p	=	(Control*)(*i);
					p->mouseReleased(arg,id);
				}
				return true;
			}
			bool Control::buttonPressed( const OIS::JoyStickEvent &arg, int button ){
				ControlListItr	i	=	m_lstControl.begin();
				for(;i!=m_lstControl.end();i++){
					Control*	p	=	(Control*)(*i);
					p->buttonPressed(arg,button);
				}
	
				return	true;
			}
	
			bool Control::buttonReleased( const OIS::JoyStickEvent &arg, int button ){
				ControlListItr	i	=	m_lstControl.begin();
				for(;i!=m_lstControl.end();i++){
					Control*	p	=	(Control*)(*i);
					p->buttonReleased(arg,button);
				}
	
				return	true;
			}
	
			bool Control::axisMoved( const OIS::JoyStickEvent &arg, int axis ){
				ControlListItr	i	=	m_lstControl.begin();
				for(;i!=m_lstControl.end();i++){
					Control*	p	=	(Control*)(*i);
					p->axisMoved(arg,axis);
				}
	
				return	true;
			}
	
			void Control::AddControl( Control* pControl ){
				if(pControl==NULL)
					return;
				m_lstControl.push_back(pControl);
			}
	
			void Control::RemoveControl( Control* pControl ){
				if(pControl==NULL)
					return;
				m_lstControl.remove(pControl);
			}
	
			U1 Control::OnFrameMove(){
				ControlListItr	i	=	m_lstControl.begin();
				for(;i!=m_lstControl.end();i++){
					Control*	p	=	(Control*)(*i);
					p->OnFrameMove();
				}
				return	true;
			}
	
			SceneNode* Control::GetControlNode(){
				return	NULL;
			}
		}
	}
};