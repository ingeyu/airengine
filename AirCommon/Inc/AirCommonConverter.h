//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/03/29
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CharacterTrans.h
 \note     
       
 \attention:
			字符编码转换
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONCONVERTER_HEAD_FILE
#define COMMONCONVERTER_HEAD_FILE



#include "AirCommon.h"
#include "AirCommonHeader.h"

namespace Air{
	
	namespace Common{
		/** \brief 字符编码转换
		*	
		*	支持UTF-8 Unicode ASCII相互转换
		*
		***/
		class COMMON_EXPORT Converter{
		public:
	
			/**	\brief	utf8 转 Unicode
			***/
			static WString Utf82Unicode(const AString& utf8string);
	
			/**	\brief	unicode 转为 ascii
			***/
			static AString WideByte2Acsi(const	WString& wstrcode);
	
			/**	\brief	utf-8 转 ascii
			***/
			static AString UTF_82ASCII(const	AString& strUtf8Code);
	
			/**	\brief	ascii 转 Unicode
			***/
			static WString Acsi2WideByte(const	AString& strascii);
	
			/**	\brief	Unicode 转 Utf8
			***/
			static AString Unicode2Utf8(const	WString& widestring);
	
			/**	\brief	ascii 转 Utf8
			***/
			static AString ASCII2UTF_8(const	AString& strAsciiCode);
	
			static	AString		ToString(U1		val);
			static	AString		ToString(U8		val);
			static	AString		ToString(U16	val);
			static	AString		ToString(U32	val);
			static	AString		ToString(U64	val);
			static	AString		ToString(S8		val);
			static	AString		ToString(S16	val);
			static	AString		ToString(S32	val);
			static	AString		ToString(S64	val);
			static	AString		ToString(Real	val);
			static	AString		ToString(double	val);
			
			static	U1			ToU1(const	AString&	str);
			static	U16			ToU16(const	AString&	str);
			static	U32			ToU32(const	AString&	str);
			static	U64			ToU64(const	AString&	str);
			static	S16			ToS16(const	AString&	str);
			static	S32			ToS32(const	AString&	str);
			static	S64			ToS64(const	AString&	str);
			static	Real		ToFloat(const	AString&	str);
			static	double		ToDouble(const	AString&	str);

			static	void		ParseString(const	AString&	str,Float2&	v);
			static	void		ParseString(const	AString&	str,Float3&	v);
			static	void		ParseString(const	AString&	str,Float4&	v);
			static	void		ParseString(const	AString&	str,float*	pOut,U32	uiCount);

			static	AString		ToLowerCase(const	AString&	str);
			static	AString		ToUpperCase(const	AString&	str);
			static	void		ToLowerCase(AString&	str);
			static	void		ToUpperCase(AString&	str);

			static	U1			SplitFilePath(		const	AString&	str,
													AString*			strPath		=	NULL,
													AString*			strFileName	=	NULL,
													AString*			strExe		=	NULL);
		};
		#ifndef LANGUAGE_TYPE
		#define LANGUAGE_TYPE
		#define LANGUAGE_TYPE_CN	1
		#define LANGUAGE_TYPE_EN	2
		#define LANGUAGE_TYPE_FR	3
		#endif
		/**	\brief	字符串辅助类
		*
		*	对字符串辅助功能
		*
		***/
		class CChar{
		public:
			/**	\brief	添加小括号
			*   
			*	@remarks 	添加小括号
			*	@see		CChar
			*	@return   	Common::String
			*	@param		String sText
			*	@note
			*
			**/
			static inline String AddBracket(String sText){
				String sReturnText = String(_T("(")) + sText + String(_T(")"));
				return sReturnText;
			};
			/**	\brief	添加中括号
			*   
			*	@remarks 	添加中括号
			*	@see		CChar
			*	@return   	Common::String
			*	@param		String sText
			*	@note
			*
			**/
			static inline String AddMiddleBracket(String sText){
				String sReturnText = String(_T("[")) + sText + String(_T("]"));
				return sReturnText;
			};
			/**	\brief	添加大括号
			*   
			*	@remarks 	添加大括号
			*	@see		CChar
			*	@return   	Common::String
			*	@param		String sText
			*	@note
			*
			**/
			static inline String AddLargeBracket(String sText){
				String sReturnText = String(_T("{")) + sText + String(_T("}"));
				return sReturnText;
			};
			/**	\brief	添加SayWord
			*   
			*	@remarks 	添加SayWord
			*	@see		CChar
			*	@return   	Common::String
			*	@param		String sText
			*	@note
			*
			**/
			static inline String AddSayWord(String sText = _T("")){
				String sReturnText = sText + String(_T(" 说："));
				return sReturnText;
			};
			/**	\brief	添加QuietSayWord
			*   
			*	@remarks 	添加QuietSayWord
			*	@see		CChar
			*	@return   	Common::String
			*	@param		String sText
			*	@note
			*
			**/
			static inline String AddQuietSayWord(String sText = _T("")){
				String sReturnText = sText + String(_T(" 悄悄的对你说："));
				return sReturnText;
			};
			/**	\brief	添加LoudSayWord
			*   
			*	@remarks 	添加LoudSayWord
			*	@see		CChar
			*	@return   	Common::String
			*	@param		String sText
			*	@note
			*
			**/
			static inline String AddLoudSayWord(String sText = _T("")){
				String sReturnText = sText + String(_T(" 大声疾呼："));
				return sReturnText;
			};
		};
	
	};
};
#endif