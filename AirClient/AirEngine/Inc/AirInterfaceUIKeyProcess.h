#ifndef INTERFACEUIKEYPROCESS_HEAD_FILE
#define INTERFACEUIKEYPROCESS_HEAD_FILE

#include "AirInterfaceUICommon.h"
namespace Air{
	
	namespace Client{
	
		namespace	UI{
			namespace	Window{
				class	IControl;
			}
	
			typedef		std::map<U64,Window::IControl*>	KeyMap;
			typedef		KeyMap::iterator				KeyMapItr;
			typedef		KeyMap::value_type				KeyMapPair;
			/**	\brief	快捷键处理
			*
			*	快捷键处理
			*
			***/
			class	ENGINE_EXPORT	KeyProcess{
			public:
				KeyProcess();
	
				/**	\brief	添加一个快捷键
				*   
				*	@remarks 	添加一个快捷键
				*	@see		KeyProcess
				*	@return   	void
				*	@param		U64 Key
				*	@param		Window::IControl * pControl
				*	@note
				*
				**/
				void	AddKey(U64	Key,Window::IControl*	pControl);
				/**	\brief	移除一个快捷键
				*   
				*	@remarks 	移除一个快捷键
				*	@see		KeyProcess
				*	@return   	void
				*	@param		U64 Key
				*	@param		Window::IControl * pControl
				*	@note
				*
				**/
				void	RemoveKey(U64	Key,Window::IControl*	pControl);
	
				/**	\brief	处理按键消息
				*   
				*	@remarks 	处理按键消息
				*	@see		KeyProcess
				*	@return   	void
				*	@param		U64 Key
				*	@param		U1 bKeyDown
				*	@note
				*
				**/
				void	ProcessKey(U64	Key,U1	bKeyDown);
	
				KeyMap		m_mapKey;
			};
		}
	
	};
};
#endif // INTERFACEUIKEYPEOCESS_HEAD_FILE