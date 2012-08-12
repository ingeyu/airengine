#ifndef RENDERTEXT_HEAD_FILE
#define RENDERTEXT_HEAD_FILE


#include "AirRenderHeader9.h"
#include "AirRenderFactory9.h"
namespace Air{
	
	
	namespace Client{
	
		namespace	Render{
			class	Text	:
				public	Product,
				public	IText{
			public:
	
			public:
				Text(CAString&	strName,Info* pInfo);
				virtual ~Text();
	
				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		Text
				*	@return   	U1
				*	@note
				*
				**/
				virtual U1	Create( );
				/**	\brief	摧毁
				*   
				*	@remarks 	摧毁
				*	@see		Text
				*	@return   	U1
				*	@note
				*
				**/
				virtual U1	Destroy( );
	
				/**	\brief	设备丢失回调函数
				*   
				*	@remarks 	设备丢失回调函数
				*	@see		Product
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	OnLostDevice();
				/**	\brief	重置设备回调函数
				*   
				*	@remarks 	重置设备回调函数
				*	@see		Product
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	OnResetDevice();
				/**	\brief	设置文字
				*   
				*	@remarks 	设置文字
				*	@see		Text
				*	@return   	void
				*	@param		AString str
				*	@note
				*
				**/
				virtual	void	SetText(AString	str);
				/**	\brief	设置颜色
				*   
				*	@remarks 	设置颜色
				*	@see		Text
				*	@return   	void
				*	@param		Vector4 vColor
				*	@note
				*
				**/
				virtual	void	SetColor(Float4	vColor);
				/**	\brief	渲染
				*   
				*	@remarks 	渲染
				*	@see		Text
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	Render();
			protected:
				Info		m_Info;
				AString		m_strInfo;
				RECT		m_Rect;
				DWORD		m_Color;
			private:
			};
	
			class	TextFactory	:
				public	Factory{
			public:
				TextFactory();
				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		BuffFactory
				*	@return   	IProduct*
				*	@param		AString& strName
				*	@param		IFactoryParamList * lstParam
				*	@note
				*
				**/
				virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam =	NULL);
			};
		}
	
	};
};
#endif // RENDERTEXT_HEAD_FILE