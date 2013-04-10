#include "AirInterfaceUISystem.h"
#include "AirInterfaceUIWindowLayout.h"
#include "AirInterfaceInputSystem.h"
#include "AirGlobalSetting.h"
#include "AirEngineFont.h"
#include "AirEngineSystem.h"

#include "AirInterfaceUILookfeel.h"
namespace Air{
	
	namespace	Engine{
		namespace	UI{
	
	
			ISystem::ISystem(){
				//m_strPluginName	=	"UISystem";
				m_pRootWindow	=	NULL;
				m_pImageSet		=	NULL;
				memset(&m_Key,0,sizeof(KeyUnion));
				m_pActiveWindow	=	NULL;
			}
	
			U1 ISystem::Initialization(){
				
				//添加工厂
				//AddFactory(new	Window::LayoutFactory());
				AddFactory(new	NoParamFactory<Lookfeel>());
	
				Font::Info	fontInfo;
				fontInfo.bBorder	=	false;
				fontInfo.bItalic	=	false;
				fontInfo.uiSize		=	25;
				Font*	pDefaultFont	=	EngineSystem::GetSingleton()->CreateProduct<Font>(AString("..\\Data\\STLITI.ttf"),&fontInfo);
	
	
				pDefaultFont->AddString(L"`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?");
				//初始化效果
				InitEffect();
	
				//m_pRootWindow	=	CreateIWindow("RootWindow","Layout");
				//添加鼠标键盘回调
				Input::ISystem*	pSys	=	GetGlobalSetting().m_pInputSystem;
				if(pSys!=NULL){
					pSys->Add((OIS::MouseListener*)this);
					pSys->Add((OIS::KeyListener*)this);
				}
				return true;
			}
	
			U1 ISystem::Start(){
				return true;
			}
	
			U1 ISystem::Release(){
				//移除键盘鼠标回调
				Input::ISystem*	pSys	=	GetGlobalSetting().m_pInputSystem;
				if(pSys!=NULL){
					pSys->Remove((OIS::MouseListener*)this);
					pSys->Remove((OIS::KeyListener*)this);
				}
				//设置根窗口为空
				SetRootWindow(NULL);
				//移除效果
				ReleaseEffect();
	
				//GetGlobalSetting().m_pDefaultFont	=	NULL;
	
				return true;
			}
	
			void ISystem::Update(){
				//窗口更新
				if(m_pRootWindow!=NULL){
					m_pRootWindow->Update();
				}
	
	
			}
	
			void ISystem::SetActive( Window::IControl* pWindow ){
				if(m_pActiveWindow!=NULL){
					m_pActiveWindow->SetActive(false);
				}
				m_pActiveWindow	=	pWindow;
				if(m_pActiveWindow!=NULL){
					m_pActiveWindow->SetActive(true);
				}
			}
	
			void ISystem::RenderWindowTree( Window::IControl* pWindow ){
				//渲染窗口树
				if(pWindow!=NULL)
					pWindow->RenderUI();
			}
	
			void ISystem::Render(){
				//渲染根窗口及其子窗口
				RenderWindowTree(m_pRootWindow);
				//最后渲染一遍激活窗口
				//RenderWindowTree(m_pActiveWindow);
				//调用渲染
				//StartRender();
			}
	
			Window::IControl* ISystem::CreateIWindow( AString strName,AString strType,void*	pParam ){
				return	CreateProduct<Window::IControl>(strName,strType,pParam);
			}
	
			void ISystem::DestroyIWindow( Window::IControl* pWindow ){
				pWindow->ReleaseRef();
			}
	
			void ISystem::SetRootWindow( Window::IControl* pWindow ){
	// 			if(m_pRootWindow!=NULL){
	// 				DestroyIWindow(m_pRootWindow);
	// 			}
				m_pRootWindow	=	pWindow;
			}
	
			bool ISystem::keyPressed( const OIS::KeyEvent &arg ){
				UpdateKey(m_Key,arg.key,true);
				ProcessKey(m_Key.Value,true);
				if(m_pActiveWindow!=NULL)m_pActiveWindow->keyPressed(arg);
				return	true;
			}
	
			bool ISystem::keyReleased( const OIS::KeyEvent &arg ){
				//这里需要先处理按键
				ProcessKey(m_Key.Value,false);
				//再更新按键状态
				UpdateKey(m_Key,arg.key,false);
	
				if(m_pActiveWindow!=NULL)m_pActiveWindow->keyReleased(arg);
				return	true;
			}
	
			bool ISystem::mouseMoved( const OIS::MouseEvent &arg ){
				if(arg.state.Z.rel>0)
					m_Key.MouseZ	=	1;
				else	if(arg.state.Z.rel<0){
					m_Key.MouseZ	=	-1;
				}else{
					m_Key.MouseZ	=	0;
				}
				ProcessKey(m_Key.Value,true);
	
				if(m_pRootWindow!=NULL){
					static	Window::IControl*	pWindow	=	NULL;
					Window::IControl*	pCurrentWindow	=	m_pRootWindow->IsMouseInWindow();
	// 				if(pCurrentWindow!=NULL){
	//  					::OutputDebugStringA(pCurrentWindow->GetProductName().c_str());
	//  					::OutputDebugStringA("\n");
	// 				}else{
	// 					::OutputDebugStringA("NoWindow\n");
	// 				}
	
					//if(pCurrentWindow!=NULL){
						if(pCurrentWindow!=pWindow){
							//窗口不变化
							if(pWindow!=NULL){
								pWindow->SetState(enNormal);
							}
							pWindow	=	pCurrentWindow;
							//窗口不变化
							if(pWindow!=NULL){
								pWindow->SetState(enHover);
							}
						}
					//}
				}
				if(m_pActiveWindow!=NULL)m_pActiveWindow->mouseMoved(arg);
				return	true;
				//return	true;
			}
	
			bool ISystem::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
				m_Key.Mouse	=	id;
				ProcessKey(m_Key.Value,true);
	
				if(	id	==	OIS::MB_Left	||	
					id	==	OIS::MB_Right	){
					if(m_pRootWindow!=NULL){
						Window::IControl*	pActiveWin	=	m_pRootWindow->IsMouseInWindow();
						if(pActiveWin!=NULL){
							pActiveWin->SetState(enPush);
						}
						if(pActiveWin!=NULL){
							pActiveWin->mousePressed(arg,id);
						}
						//窗口不变化
						if(pActiveWin==m_pActiveWindow){
							return	true;
						}
						SetActive(pActiveWin);
					}
				}
				//if(m_pActiveWindow!=NULL)m_pActiveWindow->mousePressed(arg,id);
				return	true;
			}
	
			bool ISystem::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ){
				m_Key.Mouse	=	id;
				ProcessKey(m_Key.Value,false);
	
				if(	id	==	OIS::MB_Left	||	
					id	==	OIS::MB_Right	){
						if(m_pRootWindow!=NULL){
							
							Window::IControl*	pActiveWin	=	m_pRootWindow->IsMouseInWindow();
							if(pActiveWin!=NULL){
								pActiveWin->SetState(enHover);
								pActiveWin->mouseReleased(arg,id);
							}
							//窗口不变化
							if(pActiveWin==m_pActiveWindow){
								return	true;
							}
							SetActive(pActiveWin);
						}
				}
	
				return	true;
	
	
			}
	
			void ISystem::UpdateKey( KeyUnion& k,const OIS::KeyCode& code,U1	bDown,U1	bMouse ){
				//暂时不对鼠标做快捷键处理
				if(bMouse){
	
				}else{
					switch(code){
						case	OIS::KC_LCONTROL:
						case	OIS::KC_RCONTROL:{
							k.Ctrl	=	bDown;
							break;}
						case	OIS::KC_LMENU:
						case	OIS::KC_RMENU:{
							k.Alt	=	bDown;
							break;}
						case	OIS::KC_LSHIFT:
						case	OIS::KC_RSHIFT:{
							k.Shift	=	bDown;
							break;}
						default:{
							k.Key	=	code;
							break;}
					}
				}
				
			}
	
			long ISystem::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing,void* pUserContext ){
				return	0;
			}
	
			void ISystem::OnResetDevice(){
				Window::IControl*	pRootWindow	=	GetRootWindow();
				if(pRootWindow!=NULL)
					pRootWindow->SetNeedReRender();
			}
		}
	}
};