#ifndef INTERFACEUIEVENT_HEAD_FILE
#define INTERFACEUIEVENT_HEAD_FILE

#include "AirInterfaceUICommon.h"
namespace Air{
	
	namespace Client{
	
		namespace	UI{
			namespace	Event{
				/**	\brief	消息发送器
				*
				*	消息发送器
				*
				***/
				class	ENGINE_EXPORT	Sender{
				public:
					Sender();
					virtual	~Sender();
					/**	\brief	添加事件
					*
					*	添加事件
					*
					***/
					virtual	void	AddEvent(Message::enumType	type,const FunctionSlot& slot){
						m_pFunctionArray[type]	=	slot.m_pFunction;
					}
					
					/**	\brief	移除事件
					*   
					*	@remarks 	移除事件
					*	@see		Sender
					*	@return   	void
					*	@param		enumType type
					*	@note
					*
					**/
					void	RemoveEvent(Message::enumType	type);
					/**	\brief	移除所有事件
					*   
					*	@remarks 	移除所有事件
					*	@see		Sender
					*	@return   	void
					*	@note
					*
					**/
					void	RemoveAllEvent();
					/**	\brief	执行事件
					*   
					*	@remarks 	执行事件
					*	@see		Sender
					*	@return   	U1
					*	@param		enumType type
					*	@param		const Event & evt
					*	@note
					*
					**/
					U1	ExecuteEvent(Message::enumType	type,Message*	pMessage);
				private:
					FunctionBase* m_pFunctionArray[Message::enMax];		///<	事件数组
				};
			};
		}
	};
};
#endif // INTERFACEUIEVENT_HEAD_FILE