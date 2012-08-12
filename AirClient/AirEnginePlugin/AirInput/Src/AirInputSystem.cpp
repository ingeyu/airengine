#include "AirInputSystem.h"
#include "AirGlobalSetting.h"
namespace Air{
	
	namespace	Client{
		namespace	Input{
	
			const AChar *g_DeviceType[6] = {
				"OISUnknown", 
				"OISKeyboard", 
				"OISMouse", 
				"OISJoyStick",
				"OISTablet", 
				"OISOther"
			};
	
	
			System::System(){
				m_strName		=	"OIS InputSystem";
	
				m_bMouseEnable		=	true;
				m_bKeyEnable		=	true;
				m_bJoyStickEnable	=	true;
	
				m_pInputMgr			=	NULL;
				m_pKeyboard			=	NULL;
				m_pMouse			=	NULL;
				m_pJoyStick[0]		=	NULL;
				m_pJoyStick[1]		=	NULL;
				m_pJoyStick[2]		=	NULL;
				m_pJoyStick[3]		=	NULL;
	
	
	
				Client::GetGlobalSetting().m_pInputSystem	=	this;
	
			}
	
			System::~System(){
				Client::GetGlobalSetting().m_pInputSystem	=	NULL;
			}
	
			bool System::keyPressed( const ::OIS::KeyEvent &arg ){
				if(!m_bKeyEnable)return true;
	
				KeyListenList::iterator	i	=	m_lstKey.begin();
				for(;i!=m_lstKey.end();i++){
					KeyListener*	p	=	(KeyListener*)(*i);
					if(p!=NULL){
						p->keyPressed(arg);
					}
				}
				//AChar*	p	 = (AChar*)&arg.text;
				return true;
			}
	
			bool System::keyReleased( const ::OIS::KeyEvent &arg ){
				if(!m_bKeyEnable)return true;
	
	
				KeyListenList::iterator	i	=	m_lstKey.begin();
				for(;i!=m_lstKey.end();i++){
					KeyListener*	p	=	(KeyListener*)(*i);
					if(p!=NULL){
						p->keyReleased(arg);
					}
				}
				return true;
			}
	
			bool System::mouseMoved( const ::OIS::MouseEvent &arg ){
				
				//using namespace	Client;
				
				GlobalSetting&	setting	=	GetGlobalSetting();
	
				if(!m_bMouseEnable)return true;
	
				m_iX				=	arg.state.X.abs;
				m_iY				=	arg.state.Y.abs;
				m_iXDelta			=	arg.state.X.rel;
				m_iYDelta			=	arg.state.Y.rel;
				m_iZDelta			=	arg.state.Z.rel;
	
				ShaderShareParam&	sParam	=	setting.m_ShaderParam;
	
	
				sParam.m_vCursorPosition.x	=	m_iX;
				sParam.m_vCursorPosition.y	=	m_iY;
				sParam.m_vCursorMove.x		=	m_iXDelta;//
				sParam.m_vCursorMove.y		=	m_iYDelta;//
				sParam.m_vCursorMove.z		=	m_iZDelta;//
				
	
	
				MouseListenList::iterator	i	=	m_lstMouse.begin();
				for(;i!=m_lstMouse.end();i++){
					MouseListener*	p	=	(MouseListener*)(*i);
					if(p!=NULL){
						p->mouseMoved(arg);
					}
				}
				return true;
			}
	
			bool System::mousePressed( const ::OIS::MouseEvent &arg,::OIS::MouseButtonID id ){
				if(!m_bMouseEnable)return true;
	
				m_MouseArray[id]	=	true;
	
				MouseListenList::iterator	i	=	m_lstMouse.begin();
				for(;i!=m_lstMouse.end();i++){
					MouseListener*	p	=	(MouseListener*)(*i);
					if(p!=NULL){
						p->mousePressed(arg,id);
					}
				}
				return true;
			}
	
			bool System::mouseReleased( const ::OIS::MouseEvent &arg, ::OIS::MouseButtonID id ){
				if(!m_bMouseEnable)return true;
	
				m_MouseArray[id]	=	false;
	
				MouseListenList::iterator	i	=	m_lstMouse.begin();
				for(;i!=m_lstMouse.end();i++){
					MouseListener*	p	=	(MouseListener*)(*i);
					if(p!=NULL){
						p->mouseReleased(arg,id);
					}
				}
	
				return true;
			}
	
			bool System::buttonPressed( const ::OIS::JoyStickEvent &arg, int button ){
				if(!m_bJoyStickEnable)return true;
	
				JoyStickListenList::iterator	i	=	m_lstJoyStick.begin();
				for(;i!=m_lstJoyStick.end();i++){
					JoyStickListener*	p	=	(JoyStickListener*)(*i);
					if(p!=NULL){
						p->buttonPressed(arg,button);
					}
				}
				return true;
			}
	
			bool System::buttonReleased( const ::OIS::JoyStickEvent &arg, int button ){
				if(!m_bJoyStickEnable)return true;
	
				JoyStickListenList::iterator	i	=	m_lstJoyStick.begin();
				for(;i!=m_lstJoyStick.end();i++){
					JoyStickListener*	p	=	(JoyStickListener*)(*i);
					if(p!=NULL){
						p->buttonReleased(arg,button);
					}
				}
				return true;
			}
	
			bool System::axisMoved( const ::OIS::JoyStickEvent &arg, int axis ){
				if(!m_bJoyStickEnable)return true;
	
				JoyStickListenList::iterator	i	=	m_lstJoyStick.begin();
				for(;i!=m_lstJoyStick.end();i++){
					JoyStickListener*	p	=	(JoyStickListener*)(*i);
					if(p!=NULL){
						p->axisMoved(arg,axis);
					}
				}
				return true;
			}
	
			bool System::povMoved( const ::OIS::JoyStickEvent &arg, int pov ){
				if(!m_bJoyStickEnable)return true;
	
				JoyStickListenList::iterator	i	=	m_lstJoyStick.begin();
				for(;i!=m_lstJoyStick.end();i++){
					JoyStickListener*	p	=	(JoyStickListener*)(*i);
					if(p!=NULL){
						p->povMoved(arg,pov);
					}
				}
				return true;
			}
	
			bool System::vector3Moved( const ::OIS::JoyStickEvent &arg, int index ){
				if(!m_bJoyStickEnable)return true;
	
				JoyStickListenList::iterator	i	=	m_lstJoyStick.begin();
				for(;i!=m_lstJoyStick.end();i++){
					JoyStickListener*	p	=	(JoyStickListener*)(*i);
					if(p!=NULL){
						p->vector3Moved(arg,index);
					}
				}
				return true;
			}
	
			U1 System::Initialization(){
				::OIS::ParamList pl;
	
				HWND*	pWnd	=	&Client::GetGlobalSetting().m_EngineParam.hWnd;
				while(*pWnd==NULL){
					Sleep(0);
					//等待窗口创建完成
				}
	
				std::ostringstream wnd;
				wnd << (size_t)(*pWnd);
	
				pl.insert(std::make_pair( std::string("WINDOW"), wnd.str() ));
	
				//Default mode is foreground exclusive..but, we want to show mouse - so nonexclusive
				pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
				pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	
				//This never returns null.. it will raise an exception on errors
				m_pInputMgr = ::OIS::InputManager::createInputSystem(pl);
	
				//Lets enable all addons that were compiled in:
				m_pInputMgr->enableAddOnFactory(::OIS::InputManager::AddOn_All);
	
				//Print debugging information
				unsigned int v = m_pInputMgr->getVersionNumber();
				std::cout << "OIS Version: " << (v>>16 ) << "." << ((v>>8) & 0x000000FF) << "." << (v & 0x000000FF)
					<< "\nRelease Name: " << m_pInputMgr->getVersionName()
					<< "\nManager: " << m_pInputMgr->inputSystemName()
					<< "\nTotal Keyboards: " << m_pInputMgr->getNumberOfDevices(::OIS::OISKeyboard)
					<< "\nTotal Mice: " << m_pInputMgr->getNumberOfDevices(::OIS::OISMouse)
					<< "\nTotal JoySticks: " << m_pInputMgr->getNumberOfDevices(::OIS::OISJoyStick);
	
				//List all devices
				::OIS::DeviceList list = m_pInputMgr->listFreeDevices();
				for( ::OIS::DeviceList::iterator i = list.begin(); i != list.end(); ++i )
					std::cout << "\n\tDevice: " << g_DeviceType[i->first] << " Vendor: " << i->second;
	
				m_pKeyboard = (::OIS::Keyboard*)m_pInputMgr->createInputObject( ::OIS::OISKeyboard, true );
				m_pKeyboard->setEventCallback( this );
				m_pKeyboard->setTextTranslation(OIS::Keyboard::Ascii);
	
				m_pMouse = (::OIS::Mouse*)m_pInputMgr->createInputObject( ::OIS::OISMouse, true );
				m_pMouse->setEventCallback( this );
				const ::OIS::MouseState &ms = m_pMouse->getMouseState();
				ms.width = Client::GetGlobalSetting().m_ShaderParam.m_iScreenWidth;
				ms.height = Client::GetGlobalSetting().m_ShaderParam.m_iScreenHeight;
	
				try
				{
					//This demo uses at most 4 joysticks - use old way to create (i.e. disregard vendor)
					int numSticks = min(m_pInputMgr->getNumberOfDevices(::OIS::OISJoyStick), 4);
					for( int i = 0; i < numSticks; ++i )
					{
						m_pJoyStick[i] = (::OIS::JoyStick*)m_pInputMgr->createInputObject( ::OIS::OISJoyStick, true );
						m_pJoyStick[i]->setEventCallback( this );
						std::cout << "\n\nCreating Joystick " << (i + 1)
							<< "\n\tAxes: " << m_pJoyStick[i]->getNumberOfComponents(::OIS::OIS_Axis)
							<< "\n\tSliders: " << m_pJoyStick[i]->getNumberOfComponents(::OIS::OIS_Slider)
							<< "\n\tPOV/HATs: " << m_pJoyStick[i]->getNumberOfComponents(::OIS::OIS_POV)
							<< "\n\tButtons: " << m_pJoyStick[i]->getNumberOfComponents(::OIS::OIS_Button)
							<< "\n\tVector3: " << m_pJoyStick[i]->getNumberOfComponents(::OIS::OIS_Vector3);
					}
				}
				catch(OIS::Exception &ex)
				{
					std::cout << "\nException raised on joystick creation: " << ex.eText << std::endl;
				}
	
				return true;
			}
	
			U1 System::Release(){
	
				RemoveAll();
	
				if(m_pKeyboard!=NULL){
					m_pInputMgr->destroyInputObject(m_pKeyboard);
					m_pKeyboard	=	NULL;
				}
	
				if(m_pMouse!=NULL){
					m_pInputMgr->destroyInputObject(m_pMouse);
					m_pMouse	=	NULL;
				}
	
				for(int i=0;i<4;i++){
					if(m_pJoyStick[i]!=NULL){
						m_pInputMgr->destroyInputObject(m_pJoyStick[i]);
						m_pJoyStick[i]	=	NULL;
					}
				}
	
	
				//Destroying the manager will cleanup unfreed devices
				if( m_pInputMgr!=NULL ){
					::OIS::InputManager::destroyInputSystem(m_pInputMgr);
					m_pInputMgr	=	NULL;
				}
	
				return true;
			}
	
			void System::Add( KeyListener* pListener ){
				m_lstKey.push_back(pListener);
			}
	
			void System::Add( MouseListener* pListener ){
				m_lstMouse.push_back(pListener);
			}
	
			void System::Add( JoyStickListener* pListener ){
				m_lstJoyStick.push_back(pListener);
			}
	
			void System::Remove( KeyListener* pListener ){
				m_lstKey.remove(pListener);
			}
	
			void System::Remove( MouseListener* pListener ){
				m_lstMouse.remove(pListener);
			}
	
			void System::Remove( JoyStickListener* pListener ){
				m_lstJoyStick.remove(pListener);
			}
	
			void System::Enable( enumType	type,U1 bEnable ){
	
				switch(type){
					case	enKey:{
						m_bKeyEnable		=	bEnable;
					break;}
					case	enMouse:{
						m_bMouseEnable		=	bEnable;
					}
					case	enJoyStick:{
						m_bJoyStickEnable	=	bEnable;
					}
					default:{
	
					}
				}
			}
	
			U1 System::IsEnable( enumType	type ){
				switch(type){
					case	enKey:{
						return	m_bKeyEnable;
						break;}
					case	enMouse:{
						return	m_bMouseEnable;
									}
					case	enJoyStick:{
						return	m_bJoyStickEnable;
									   }
					default:{
						return false;
							}
				}
			}
	
			void System::EnableAll( U1 bEnable ){
				m_bMouseEnable		=	bEnable;
				m_bKeyEnable		=	bEnable;
				m_bJoyStickEnable	=	bEnable;
	
			}
	
			void System::RemoveAll(){
				m_lstMouse.clear();
				m_lstKey.clear();
				m_lstJoyStick.clear();
			}
	
			U1 System::Capture(){
				if(m_pKeyboard!=NULL){
					m_pKeyboard->capture();
					m_pKeyboard->copyKeyStates(m_KeyArray);
				}
				if(m_pMouse!=NULL){
					m_pMouse->capture();
				}
				for(int i=0;i<4;i++){
					if(m_pJoyStick[i]!=NULL){
						m_pJoyStick[i]->capture();
					}
				}
				Client::GlobalSetting&	setting		=	Client::GetGlobalSetting();
				//更新当前鼠标位置
				if(m_MouseArray[OIS::MB_Left])
					setting.m_ShaderParam.m_vCursorPosition.z	=	1.0f;
				else
					setting.m_ShaderParam.m_vCursorPosition.z	=	-1.0f;
				if(m_MouseArray[OIS::MB_Right])
					setting.m_ShaderParam.m_vCursorPosition.w=	1.0f;
				else
					setting.m_ShaderParam.m_vCursorPosition.w	=	-1.0f;
	
	
	
				return true;
				
			}
	
			U1 System::Start(){
		
				return true;
			}

			Air::U1 System::Stop(){
				return	true;
			}

		}
	}
};