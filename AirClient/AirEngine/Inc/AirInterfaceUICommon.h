#ifndef INTERFACEUICOMMON_HEAD_FILE
#define INTERFACEUICOMMON_HEAD_FILE

#include "AirEngineHeader.h"
namespace Air{
	
	namespace Client{
	
		namespace	UI{
			namespace	Window{
				class	IControl;
			}
			/**	\brief	状态枚举
			*
			*	状态枚举
			*
			***/
			enum	enumStateType{
				enDisable,
				enNormal,
				enHover,
				enPush,
				enMax
			};
			/**	\brief	界面消息
			*
			*	界面消息
			*
			***/
			class	Message{
			public:
				enum	enumType{
					//鼠标事件
					enMouseEnter,		//
					enMouseLeave,
					enMouseLButtonDown,
					enMouseLButtonUp,
					enMouseMButtonDown,
					enMouseMButtonUp,
					enMouseRButtonDown,
					enMouseRButtonUp,
					enMouseWheelDown,
					enMouseWheelUp,
					enMouse3ButtonDown,
					enMouse3ButtonUp,
					enMouse4ButtonDown,
					enMouse4ButtonUp,
					enMouse5ButtonDown,
					enMouse5ButtonUp,
					enMouse6ButtonDown,
					enMouse6ButtonUp,
					enMouse7ButtonDown,
					enMouse7ButtonUp,
					//键盘事件
					enShortCutKeyDown,
					enShortCutKeyUp,
					enKeyUp,
					//普通事件
					enEnableChange,
					enVisiableChange,
					enAlphaChange,
					enColorChange,
					enPositionChange,
					enSizeChange,
					enActiveChange,
	
					enMax
	
				};
				Message(Window::IControl*	pControl	=	NULL,Union4 u	=	0){
					m_State		=	u;
					m_pControl	=	pControl;
				}
				Window::IControl*	m_pControl;
				Union4				m_State;
			};
	
			/**	\brief	快捷键组合
			*
			*	快捷键组合
			*
			***/
			union	KeyUnion{
				KeyUnion(U8	mouse	=	0,U8 key	=	0,U1	bAlt	=	false,U1	bShift	=	false,	U1	bCtrl	=	false){
					Mouse	=	mouse;
					Key		=	key;
					Alt		=	bAlt;
					Shift	=	bShift;
					Ctrl	=	bCtrl;
				};
				/**	\brief	对比按键
				*   
				*	@remarks 	对比按键
				*	@see		ShortcutKey
				*	@return   	U1
				*	@param		ShortcutKey & key
				*	@note
				*
				**/
				inline	U1	Compare(KeyUnion&	key){
					return (Value==key.Value);
				};
				/**	\brief	判断是否相等
				*   
				*	@remarks 	判断是否相等
				*	@see		ShortcutKey
				*	@return   	U1
				*	@param		const ShortcutKey & key
				*	@note
				*
				**/
				U1	operator	==	(const KeyUnion&	key){
					return	(Value==key.Value);
				}
				U1	operator	<	(const KeyUnion&	key){
					return	(Value<key.Value);
				}
				/**	\brief	设置是否需要Alt
				*   
				*	@remarks 	设置是否需要Alt
				*	@see		ShortcutKey
				*	@return   	void
				*	@param		U1 bEnable
				*	@note
				*
				**/
				inline	void	SetAlt(U1	bEnable){
					Alt		=	bEnable;
				};
				/**	\brief	设置是否需要Alt
				*   
				*	@remarks 	设置是否需要Alt
				*	@see		ShortcutKey
				*	@return   	void
				*	@param		U1 bEnable
				*	@note
				*
				**/
				inline	void	SetCtrl(U1	bEnable){
					Ctrl		=	bEnable;
				};
				/**	\brief	设置是否需要Alt
				*   
				*	@remarks 	设置是否需要Alt
				*	@see		ShortcutKey
				*	@return   	void
				*	@param		U1 bEnable
				*	@note
				*
				**/
				inline	void	SetShift(U1	bEnable){
					Shift	=	bEnable;
				}
				struct{
					U8					Mouse;		///<	鼠标
					S8					MouseX;		///<	X轴
					S8					MouseY;		///<	Y轴
					S8					MouseZ;		///<	Z轴
					U8					Key;		///<	按键
					U8					Alt;		///<	Alt按键
					U8					Shift;		///<	Shift按键
					U8					Ctrl;		///<	Ctrl按键
				};
				U64						Value;		///<	比较值
			};
	
			/**	\brief	回调基类
			*
			*	回调基类
			*
			***/
			class	FunctionBase{
			public:
				virtual ~FunctionBase(){};
				/**	\brief	函数执行回调接口
				*
				*	函数执行回调接口
				*
				***/
				virtual bool operator()(Message*	pMessage) = 0;
			};
	
			/**	\brief	普通函数回调
			*
			*	普通函数回调
			*
			***/
			class	Function	:	
				public	FunctionBase{
			public:
				typedef U1 (NormalCallBack)(Message*);
	
				Function(NormalCallBack* func) :
				m_pFunction(func)
				{}
	
				/**	\brief	调用回调函数
				*   
				*	@remarks 	调用回调函数
				*	@see		Function
				*	@return   	bool
				*	@param		const Event & evt
				*	@note
				*
				**/
				virtual bool operator()(Message*	pMessage){
					return m_pFunction(pMessage);
				}
	
				//private:
				NormalCallBack* m_pFunction;		///<	回调函数
			};
	
			/**	\brief	成员函数回调
			*
			*	成员函数回调
			*
			***/
			template<typename	T_Member>
			class	MemberFunction	:
				public FunctionBase{
			public:
				//! Member function	typedef
				typedef U1(T_Member::*MemberCallBack)(Message*);
				MemberFunction(MemberCallBack func, T_Member* obj) :
				m_pFunction(func),
					m_pObject(obj){
	
				};
	
				/**	\brief	调用回调函数
				*   
				*	@remarks 	调用回调函数
				*	@see		MemberFunction
				*	@return   	bool
				*	@param		const Event & evt
				*	@note
				*
				**/
				virtual bool operator()(Message*	pMessage){
					return (m_pObject->*m_pFunction)(pMessage);
				}
	
				//private:
				MemberCallBack	m_pFunction;		///<	类成员函数
				T_Member*		m_pObject;			///<	类指针
			};
	
			/**	\brief	函数包含体
			*
			*	函数包含体
			*
			***/
			class	FunctionSlot{
			public:
				FunctionSlot(){m_pFunction=NULL;};
				FunctionSlot(U1 (*func)(Message*)){m_pFunction	=	new	Function(func);};
				//编译不过去 （提示 没有重载函数接受 2 个参数）头疼了
				template<class T>
				FunctionSlot(U1 (T::*function)(Message*), T* obj)
					:m_pFunction(new	MemberFunction<T>(function,obj)){
				};
	
				/**	\brief	清理
				*   
				*	@remarks 	清理
				*	@see		FunctionSlot
				*	@return   	void
				*	@note
				*
				**/
				void	Clean(){
					SAF_D(m_pFunction);
				}
	
				/**	\brief	是否为空
				*   
				*	@remarks 	是否为空
				*	@see		FunctionSlot
				*	@return   	U1
				*	@note
				*
				**/
				U1	IsNull(){return	m_pFunction	==	NULL;};
	
				FunctionBase*	m_pFunction;
			};
		}
	
	};
};
#endif // INTERFACEUICOMMON_HEAD_FILE