#ifndef INTERFACEUISTATICTEXT_HEAD_FILE
#define INTERFACEUISTATICTEXT_HEAD_FILE

#include "AirInterfaceUIWindowControl.h"
namespace Air{
	
	namespace Client{
	
		namespace	UI{
			namespace	Window{
				/**	\brief	静态文本框
				*
				*	静态文本框
				*
				***/
				class	IStaticText{
				public:
					/**	\brief	设置文本
					*   
					*	@remarks 	设置文本
					*	@see		IStaticText
					*	@return   	void
					*	@param		AString strName
					*	@note
					*
					**/
					virtual	void	SetText(AString	strName)	=	NULL;
					/**	\brief	获取文本
					*   
					*	@remarks 	获取文本
					*	@see		IStaticText
					*	@return   	AString
					*	@note
					*
					**/
					virtual	AString	GetText()					=	NULL;
					/**	\brief	设置文本大小
					*   
					*	@remarks 	设置文本大小
					*	@see		IStaticText
					*	@return   	void
					*	@param		Real fSize
					*	@note
					*
					**/
					virtual	void	SetTextSize(Real	fSize)	=	NULL;
					/**	\brief	获取文字大小
					*   
					*	@remarks 	获取文字大小
					*	@see		IStaticText
					*	@return   	Real
					*	@note
					*
					**/
					virtual	Real	GetTextureSize()			=	NULL;
					/**	\brief	设置文本颜色
					*   
					*	@remarks 	设置文本颜色
					*	@see		IStaticText
					*	@return   	void
					*	@param		Float4 v
					*	@note
					*
					**/
					virtual	void	SetTextColor(Float4 v)		=	NULL;
					/**	\brief	获取文本颜色
					*   
					*	@remarks 	获取文本颜色
					*	@see		IStaticText
					*	@return   	Client::Float4
					*	@note
					*
					**/
					virtual	Float4	GetTextureColor()			=	NULL;
				};
			}
		}
	
	};
};
#endif // INTERFACEUISTATICTEXT_HEAD_FILE