#include "AirGameControl.h"
#include "AirGlobalSetting.h"
#include "AirGameSystem.h"
#include "AirGameSection.h"
#include "AirEngineScene.h"
namespace Air{
	

		namespace	Game{
	
	
			Control::Control(CAString& strName):Common::IProduct(strName){
				m_pInputState			=	Engine::GetGlobalSetting().m_pInputSystem;
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
				S8* pKeyArray	=	m_pInputState->m_KeyArray;
				Key k;
				k.control	=	pKeyArray[OIS::KC_LCONTROL]|pKeyArray[OIS::KC_RCONTROL];
				k.alt		=	pKeyArray[OIS::KC_LMENU]|pKeyArray[OIS::KC_RMENU];
				k.shift		=	pKeyArray[OIS::KC_LSHIFT]|pKeyArray[OIS::KC_RSHIFT];
				k.evt		=	enKET_KeyUp;
				k.mouse		=	0xff;
				k.key		=	arg.key;
				k.pObject	=	0;
				k.pCB		=	0;
				KeyCallBackMap::iterator	itr	=	m_mapKeyCallback.find(k.uiKeyValue);
				if(itr!=m_mapKeyCallback.end()){
					Key& key	=	itr->second;
					(*key.pCB)(key.pObject,key);
				}

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
				S8* pKeyArray	=	m_pInputState->m_KeyArray;
				Key k;
				k.control	=	pKeyArray[OIS::KC_LCONTROL]|pKeyArray[OIS::KC_RCONTROL];
				k.alt		=	pKeyArray[OIS::KC_LMENU]|pKeyArray[OIS::KC_RMENU];
				k.shift		=	pKeyArray[OIS::KC_LSHIFT]|pKeyArray[OIS::KC_RSHIFT];
				k.evt		=	enKET_MouseDown;
				k.mouse		=	id;
				k.key		=	0;
				k.pObject	=	0;
				k.pCB		=	0;
				KeyCallBackMap::iterator	itr	=	m_mapKeyCallback.find(k.uiKeyValue);
				if(itr!=m_mapKeyCallback.end()){
					Key& key	=	itr->second;
					(*key.pCB)(key.pObject,key);
				}

				ControlListItr	i	=	m_lstControl.begin();
				for(;i!=m_lstControl.end();i++){
					Control*	p	=	(Control*)(*i);
					p->mousePressed(arg,id);
				}
				return true;
			}
	
			bool Control::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
				S8* pKeyArray	=	m_pInputState->m_KeyArray;
				Key k;
				k.control	=	pKeyArray[OIS::KC_LCONTROL]|pKeyArray[OIS::KC_RCONTROL];
				k.alt		=	pKeyArray[OIS::KC_LMENU]|pKeyArray[OIS::KC_RMENU];
				k.shift		=	pKeyArray[OIS::KC_LSHIFT]|pKeyArray[OIS::KC_RSHIFT];
				k.evt		=	enKET_MouseUp;
				k.mouse		=	id;
				k.key		=	0;
				k.pObject	=	0;
				k.pCB		=	0;
				KeyCallBackMap::iterator	itr	=	m_mapKeyCallback.find(k.uiKeyValue);
				if(itr!=m_mapKeyCallback.end()){
					Key& key	=	itr->second;
					(*key.pCB)(key.pObject,key);
				}

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
	
			U1 Control::Update(const FrameTime& frameTime){
				ControlListItr	i	=	m_lstControl.begin();
				for(;i!=m_lstControl.end();i++){
					Control*	p	=	(Control*)(*i);
					p->Update(frameTime);
				}
				return	true;
			}
	
			Engine::SceneNode* Control::GetControlNode(){
				return	NULL;
			}

			void Control::RegisterMouseCallback( OIS::MouseButtonID mouse,const void* pObject,KeyCallback pCB,enumKeyEventType evt/*=enKET_MouseUp*/,U1 bControl/*=false*/,U1 bAlt/*=false*/,U1 bShift/*=false*/ )
			{
				Key k;
				k.control	=	bControl;
				k.alt		=	bAlt;
				k.shift		=	bShift;
				k.evt		=	evt;
				k.mouse		=	mouse;
				k.key		=	0;
				k.pObject	=	(void*)pObject;
				k.pCB		=	(KeyCallback)pCB;
				RegisterKeyCallback(k);
			}

			void Control::RegisterKeyCallback( OIS::KeyCode key,const void* pObject,KeyCallback pCB,enumKeyEventType evt/*=enKET_KeyUp*/,U1 bControl/*=false*/,U1 bAlt/*=false*/,U1 bShift/*=false*/ )
			{
				Key k;
				k.control	=	bControl;
				k.alt		=	bAlt;
				k.shift		=	bShift;
				k.evt		=	evt;
				k.mouse		=	0xff;
				k.key		=	key;
				k.pObject	=	(void*)pObject;
				k.pCB		=	(KeyCallback)pCB;
				RegisterKeyCallback(k);
			}

			void Control::RegisterKeyCallback( const Key& k )
			{
				if(k.pObject	==	NULL	||	k.pCB	==	NULL){
					return;
				}
				m_mapKeyCallback[k.uiKeyValue]	=	k;
			}

			void Control::UnRegisterKeyCallback( U32 key )
			{
				KeyCallBackMap::iterator i = m_mapKeyCallback.find(key);
				if(i!=m_mapKeyCallback.end()){
					m_mapKeyCallback.erase(i);
				}
			}

			Air::Ray Control::GetMouseRay( S32 x,S32 y )
			{
				Engine::Scene* pScene	=	GameSystem::GetSingleton()->GetCurrentSection()->GetScene();
				POINT	p;
				p.x	=	x;//arg.state.X.abs;
				p.y	=	y;//arg.state.Y.abs;

				RECT	r;
				GetClientRect(Engine::GetGlobalSetting().m_EngineParam.hWnd,&r);

				POINT	size;
				size.x	=	r.right		-	r.left;
				size.y	=	r.bottom	-	r.top;

				return pScene->GetMainCamera()->BuildRay(p.x/(float)size.x,p.y/(float)size.y);
			}

		}
	
};