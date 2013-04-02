#ifndef ENGINETEXTINSTANCE_HEAD_FILE
#define ENGINETEXTINSTANCE_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineInstanceEntity.h"
namespace Air{
	
	namespace Engine{
		class	Font;
	
		/**	\brief	纹理实体类
		*
		*	用于渲染上千个文字
		*
		***/
		class	ENGINE_EXPORT	TextInstance	:
			public	InstanceEntity{
		public:
			/**	\brief	创建信息
			*
			*	创建信息
			*
			***/
			struct	Info{
				Info(){
					uiMaxInstance	=	1024;
					uiSize			=	25;
				}
				AString	strMaterialName;	///<	材质
				UInt	uiMaxInstance;		///<	最大实体个数
				UInt	uiSize;				///<	文字大小
			};
		public:
			TextInstance(CAString&	strName,Info*	pInfo);
	
			/**	\brief	创建模型顶点缓冲
			*   
			*	@remarks 	创建模型顶点缓冲
			*	@see		InstanceEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	CreateModelVertexBuff();
			/**	\brief	创建实体顶点缓冲
			*   
			*	@remarks 	创建实体顶点缓冲
			*	@see		InstanceEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	CreateInstanceVertexBuff();
	
			/**	\brief	创建声明
			*   
			*	@remarks 	创建声明
			*	@see		InstanceEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	CreateDeclare();
	
			/**	\brief	创建索引
			*   
			*	@remarks 	创建索引
			*	@see		InstanceEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	CreateIndex();
	
			/**	\brief	设置字符串
			*   
			*	@remarks 	设置字符串
			*	@see		TextInstance
			*	@return   	void
			*	@param		AString strText
			*	@note
			*
			**/
			virtual	void	SetText(AString	strText);
	
			/**	\brief	获取文字
			*   
			*	@remarks 	获取文字
			*	@see		TextInstance
			*	@return   	AString
			*	@note
			*
			**/
			virtual	AString	GetText();
			/**	\brief	设置文字大小
			*   
			*	@remarks 	设置文字大小
			*	@see		TextInstance
			*	@return   	void
			*	@param		UInt uiSize
			*	@note
			*
			**/
			virtual	void	SetTextSize(UInt	uiSize);
			/**	\brief	获取文字大小
			*   
			*	@remarks 	获取文字大小
			*	@see		TextInstance
			*	@return   	UInt
			*	@note
			*
			**/
			inline	UInt	GetTextSize(){
				return	m_uiTextSize;
			};
	
			/**	\brief	设置文字矩阵
			*   
			*	@remarks 	设置文字矩阵
			*	@see		TextInstance
			*	@return   	void
			*	@param		RECT rect
			*	@note
			*
			**/
			virtual	void	SetTextRect(RECT rect);
			/**	\brief	获取文字矩阵
			*   
			*	@remarks 	获取文字矩阵
			*	@see		TextInstance
			*	@return   	RECT
			*	@note
			*
			**/
			RECT			GetTextRect();
		protected:
			WString		m_strText;			///<	保存字符串
			Font*		m_pFont;			///<	字体类
			UInt		m_uiTextSize;		///<	文字大小
			UInt		m_Rect[4];			///<	文字矩形
		};
	
	
		class	TextInstanceFactory	:
			public		IFactory{
		public:
			TextInstanceFactory();
	
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		TextInstanceFactory
			*	@return   	IProduct*
			*	@param		AString strName
			*	@param		IFactoryParamList * lstParam
			*	@note
			*
			**/
			virtual	IProduct*	NewProduct(CAString&	strName,IFactoryParamList* lstParam	=	NULL);
		};
	
	};
};
#endif // ENGINETEXTINSTANCEENTITY_HEAD_FILE