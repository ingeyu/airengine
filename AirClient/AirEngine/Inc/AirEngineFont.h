#ifndef ENGINEFONT_HEAD_FILE
#define ENGINEFONT_HEAD_FILE


#include "AirEngineHeader.h"

struct FT_LibraryRec_;		///<	FT2	Library
struct FT_FaceRec_;			///<	FT2	Face
namespace Air{
	
	
	namespace Engine{
		namespace	Render{
			class	ITexture;
		}
	
		/**	\brief	字体类
		*
		*	字体类
		*
		***/
		class	ENGINE_EXPORT	Font	:
			public	IProduct{
		public:
			static AString	ProductTypeName;
			/**	\brief	创建信息
			*
			*	创建信息
			*
			***/
			struct	Info{
				Info(){
					uiSize		=	25;
					bBorder		=	false;
					bItalic		=	false;
					uiTexSize	=	2048;
				}
				UInt	uiSize;		///<	字体大小
				U1		bBorder;	///<	加粗
				U1		bItalic;	///<	斜体
				UInt	uiTexSize;	///<	文字图片纹理大小
			};
	
			typedef	std::map<WCHAR,Float4>		CharMap;
			typedef	CharMap::iterator			CharMapItr;
			typedef	CharMap::value_type			CharMapPair;
	
	
		public:
			Font(AString	strName,Info*	pInfo);
	
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		Font
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Create();
			/**	\brief	摧毁
			*   
			*	@remarks 	摧毁
			*	@see		Font
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Destroy();
	
			/**	\brief	添加文字
			*   
			*	@remarks 	添加文字
			*	@see		Font
			*	@return   	Client::Float4
			*	@param		WChar c
			*	@note
			*
			**/
			virtual	Float4			AddChar(WChar	c);
			/**	\brief	添加字符串
			*   
			*	@remarks 	添加字符串
			*	@see		Font
			*	@return   	Client::VectorArray
			*	@param		WString s
			*	@note
			*
			**/
			virtual	VectorArray		AddString(WString	s);
	
			/**	\brief	获取纹理
			*   
			*	@remarks 	获取纹理
			*	@see		Font
			*	@return   	Texture*
			*	@note
			*
			**/
			virtual	Texture*	GetTexture();
		protected:
			/**	\brief	创建文字贴图
			*   
			*	@remarks 	创建文字贴图
			*	@see		Font
			*	@return   	U1
			*	@param		WChar c
			*	@param		Float4 & vPosSize
			*	@param		U8 * * pBuff
			*	@note
			*
			**/
			U1	CreateCharBitmap(WChar	c,Float4& vPosSize,U8**	pBuff);
			/**	\brief	获取文字在图片中的位置和大小
			*   
			*	@remarks 	获取文字在图片中的位置和大小
			*	@see		Font
			*	@return   	U1
			*	@param		WChar c
			*	@param		Float4 & vPosSize
			*	@note
			*
			**/
			U1	GetCharPosSize(WChar c,Float4& vPosSize);
			/**	\brief	合并文字到纹理中
			*   
			*	@remarks 	合并文字到纹理中
			*	@see		Font
			*	@return   	U1
			*	@param		U8 * pBuff
			*	@param		SInt w
			*	@param		SInt h
			*	@param		Float4 & vPosSize
			*	@param		U1	bEng
			*	@note
			*
			**/
			U1	Combine2Texture(U8*	pBuff,SInt	w,SInt h,Float4& vPosSize,U1	bEng);
		protected:
			Info				m_Info;				///<	信息
			FT_LibraryRec_*		m_pLibrary;			///<	FT2	库指针 void* 
			FT_FaceRec_*		m_pFace;			///<	FT2	字体指针
			CharMap				m_mapChar;			///<	字符表（存储已经生成的文字）
			Texture*			m_pCharTexture;		///<	保存文字的图片
			Float2				m_vLastPosition;	///<	上次写入文件的位置
			static	UInt		m_uiCharSize;		///<	文字大小(多少个像素)
		};
	
		/**	\brief	字体工厂
		*
		*	字体工厂
		*
		***/
		class	FontFactory	:
			public	IFactory{
		public:
			FontFactory();
	
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		FontFactory
			*	@return   	IProduct*
			*	@param		AString strName
			*	@param		IFactoryParamList * lstParam
			*	@note
			*
			**/
			virtual	IProduct*	NewProduct(CAString&	strName,IFactoryParamList* lstParam = NULL);
		};
	};
};
#endif // ENGINEFONT_HEAD_FILE