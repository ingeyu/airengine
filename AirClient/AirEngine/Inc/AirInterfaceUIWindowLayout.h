#ifndef INTERFACEUIWINDOWLAYOUT_HEAD_FILE
#define INTERFACEUIWINDOWLAYOUT_HEAD_FILE

#include "AirInterfaceUIWindowControl.h"
namespace Air{
	
	namespace Engine{
	
		namespace	UI{
			namespace	Window{
	
				class	Layout	:
					public	IControl{
				public:
	
				public:
					Layout(AString	strName,AString*	strLayout,Info*	pInfo);
	 
	
					/**	\brief	创建
					*   
					*	@remarks 	创建
					*	@see		Layout
					*	@return   	U1
					*	@note
					*
					**/
					virtual	U1	Create();
					/**	\brief	判断是否鼠标在此区域中
					*   
					*	@remarks 	判断是否鼠标在此区域中
					*	@see		IControl
					*	@return   	IControl*
					*	@note
					*
					**/
					virtual	IControl*		IsMouseInWindow();
	
				protected:
					U1	ParseKey(KeyUnion&	k,AString&	strInfo);
					U8	GetKey(AString&	str);
	
					AString		m_strLayout;
				};
			}
		}
	
	};
};
#endif // INTERFACEUIWINDOWLAYOUT_HEAD_FILE