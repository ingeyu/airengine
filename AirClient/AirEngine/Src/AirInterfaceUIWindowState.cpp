#include "AirInterfaceUIWindowState.h"
#include "AirGlobalSetting.h"
#include "AirInterfaceUISystem.h"
namespace Air{
	
	namespace	Client{
		namespace	UI{
			namespace	Window{
	
				AString	vStateTypeArray[]	=	{
					"DisEnable",
					"Normal",
					"MouseOver",
					"ButtonDown",
					"ButtonUp"
				};
	
				State::State(StateArray*	pArray,Info*	pInfo){
					m_Type			=	enNormal;
					m_LastType		=	m_Type;
					//m_StateArray.resize(enMax);
					if(pArray!=NULL)
						m_StateArray	=	*pArray;
					if(pInfo!=NULL)
						m_Info			=	*pInfo;
					//Refresh
					m_bActive			=	false;
					m_bChanged			=	true;
				}
	
				void State::RenderElement(){
					//一下几种状况需要重新生成渲染缓冲区
					//窗口的状态改变
					//窗口的创建 摧毁
					//文字变化
					if(m_StateArray.empty())
						return;
					//static	ElementArray	eArray;
					ElementArray&	eArray		=	m_StateArray[m_Type];
					//BeforeRenderElement(eArray);
					for(UInt i=0;i<eArray.size();i++){
						GetGlobalSetting().m_pUISystem->Push(&eArray[i]);
					}
	
					GetGlobalSetting().m_pUISystem->StartRender();
				}
				void State::SetState( enumStateType type ){
					if(m_Type==type)
						return;
					m_LastType	=	m_Type;
					m_Type		=	type;
					//需要重新渲染
					m_bChanged	=	true;
					//状态事件
	
					Message::enumType	msgType;
	
					switch(m_Type){
						case	enHover:{
							if(m_LastType	==	enNormal)
								msgType	=	Message::enMouseEnter;
							if(m_LastType	==	enPush)
								msgType	=	Message::enShortCutKeyUp;
							break;}
						case	enNormal:{
							if(m_LastType	==	enHover)
								msgType	=	Message::enMouseLeave;
							if(m_LastType	==	enPush)
								msgType	=	Message::enShortCutKeyUp;
							break;}
						case	enPush:{
								msgType	=	Message::enShortCutKeyDown;
							break;}
						default:{
							return;
							break;}
					}
					m_Message.m_State	=	m_Type;
					ExecuteEvent(msgType,&m_Message);
				}
	
				void State::SetVisiable( U1 bVisiable ){
					if(bVisiable==m_Info.bVisiable)
						return;
					m_Info.bVisiable	=	bVisiable;
					m_Message.m_State	=	bVisiable;
					ExecuteEvent(Message::enVisiableChange,&m_Message);
				}
	
				void State::SetEnable( U1 bEnable ){
					if(bEnable==m_Info.bEnable)
						return;
					m_Info.bEnable	=	bEnable;
					m_Message.m_State	=	bEnable;
					ExecuteEvent(Message::enEnableChange,&m_Message);
				}
				void State::SetActive( U1 bActive ){
					if(bActive==m_bActive)
						return;
					m_bActive	=	bActive;
					m_Message.m_State	=	bActive;
					ExecuteEvent(Message::enActiveChange,&m_Message);
				}
			}
		}
	}
};