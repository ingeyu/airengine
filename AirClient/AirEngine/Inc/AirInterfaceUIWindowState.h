#ifndef INTERFACEUIWINDOWSTATE_HEAD_FILE
#define INTERFACEUIWINDOWSTATE_HEAD_FILE


#include "AirInterfaceUIElement.h"
#include "AirInterfaceUIEvent.h"
#include "AirEngineMovableObject.h"

namespace Air{
	
	namespace Engine{
	
		namespace	UI{
	
			namespace	Window{
				/**	\brief	创建信息
				*
				*	创建信息
				*
				***/
				struct	Info{
					Info(){
						vPositionSize	=	Float4(1,1,0,0);
						vColor			=	Float4(1,1,1,1);
						vTextColor		=	Float4(1,1,1,1);
						vCenter			=	Float2(0,0);
						bVisiable		=	true;
						bEnable			=	true;
						memset(&key,0,sizeof(KeyUnion));
					};
					Float4		vPositionSize;
					Float4		vColor;
					Float2		vCenter;
					Float4		vTextColor;
					AString		strText;
					U1			bVisiable;
					U1			bEnable;
					KeyUnion	key;
				};
				//typedef	std::vector<Float4>	VectorArray;
				/**	\brief	窗口状态
				*
				*	窗口状态
				*
				***/
				class	ENGINE_EXPORT	State	:
					public	Event::Sender,
					public	MovableObject{
				public:
	
				public:
					State(StateArray*	pArray,Info*	pInfo);
					/**	\brief	设置是否可见
					*   
					*	@remarks 	设置是否可见
					*	@see		IControl
					*	@return   	void
					*	@param		U1 bVisiable
					*	@note
					*
					**/
					void			SetVisiable(U1	bVisiable);
					/**	\brief	是否可见
					*   
					*	@remarks 	是否可见
					*	@see		IControl
					*	@return   	U1
					*	@note
					*
					**/
					inline	U1		IsVisiable(){return	m_Info.bVisiable;};
					/**	\brief	设置是否有效
					*   
					*	@remarks 	设置是否有效
					*	@see		IControl
					*	@return   	void
					*	@param		U1 bEnable
					*	@note
					*
					**/
					void			SetEnable(U1	bEnable);
					/**	\brief	获取是否有效
					*   
					*	@remarks 	获取是否有效
					*	@see		IControl
					*	@return   	U1
					*	@note
					*
					**/
					inline	U1		IsEnable(){return	m_Info.bEnable;};
	
	
					/**	\brief	设置激活
					*   
					*	@remarks 	设置激活
					*	@see		IControl
					*	@return   	void
					*	@param		U1 bActive
					*	@note
					*
					**/
					virtual	void			SetActive(U1	bActive);
	
					/**	\brief	窗口是否为激活窗口
					*   
					*	@remarks 	窗口是否为激活窗口
					*	@see		State
					*	@return   	U1
					*	@note
					*
					**/
					U1				IsActive(){
						return	m_bActive;
					};
					/**	\brief	设置快捷键
					*   
					*	@remarks	设置快捷键
					*	@see		IControl
					*	@return   	void
					*	@param		ShortcutKey & key
					*	@note
					*
					**/
					inline	void	SetKey(KeyUnion&	key){
						memcpy(&m_Info.key,&key,sizeof(KeyUnion));
					};
	
					/**	\brief	是否有效
					*   
					*	@remarks 	是否有效
					*	@see		IControl
					*	@return   	U1
					*	@note
					*
					**/
					U1				IsKeyVaild(){
						return	(m_Info.key.Value!=0);
					}
					/**	\brief	设置状态
					*   
					*	@remarks 	设置状态
					*	@see		WindowState
					*	@return   	void
					*	@param		enumStateType type
					*	@note
					*
					**/
					virtual	void	SetState(enumStateType	type);
					/**	\brief	获取状态
					*   
					*	@remarks 	获取状态
					*	@see		WindowState
					*	@return   	enumStateType
					*	@note
					*
					**/
					inline	enumStateType	GetState(){
						return		m_Type;
					}
					/**	\brief	根据当前状态选择渲染
					*   
					*	@remarks 	根据当前状态选择渲染
					*	@see		WindowState
					*	@return   	void
					*	@note
					*
					**/
					virtual	void	RenderElement();
	
					/**	\brief	渲染元素
					*   
					*	@remarks 	
					*	@see		State
					*	@return   	void
					*	@param		ElementArray&	eArray
					*	@note
					*
					**/
					virtual	void	BeforeRenderElement(ElementArray&	eArray)	=	NULL;
				protected:
					StateArray							m_StateArray;		///<	图片集列表
					enumStateType						m_Type;				///<	当前状态
					enumStateType						m_LastType;			///<	上一状态
					U1									m_bActive;			///<	设置激活
					Info								m_Info;
					Message								m_Message;
					U1									m_bChanged;	
				};
			}
		}
	
	};
};
#endif // INTERFACEUISTATE_HEAD_FILE