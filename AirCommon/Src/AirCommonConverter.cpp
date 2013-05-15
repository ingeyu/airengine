#include "AirCommonConverter.h"

namespace Air{
	
	namespace Common{
	
		WString Converter::Utf82Unicode(const AString& utf8string){
			int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);
			if (widesize == ERROR_NO_UNICODE_TRANSLATION)	{
				throw std::exception("Invalid UTF-8 sequence.");
			}
			if (widesize == 0)	{
				throw std::exception("Error in conversion.");
			}
	
			std::vector<wchar_t> resultstring(widesize);
	
			int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);
	
			if (convresult != widesize){
				throw std::exception("La falla!");
			}
	
			return WString(&resultstring[0]);
		}
	
		AString Converter::WideByte2Acsi(const WString& wstrcode){
			int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, NULL, 0, NULL, NULL);
			if (asciisize == ERROR_NO_UNICODE_TRANSLATION)	{
				throw std::exception("Invalid UTF-8 sequence.");
			}
			if (asciisize == 0)	{
				throw std::exception("Error in conversion.");
			}
			std::vector<char> resultstring(asciisize);
			int convresult =::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);
	
			if (convresult != asciisize)	{
				throw std::exception("La falla!");
			}
	
			return AString(&resultstring[0]);
		}
	
		AString Converter::UTF_82ASCII(const AString& strUtf8Code){
			AString strRet("");
			//先把 utf8 转为 unicode 
			WString wstr = Utf82Unicode(strUtf8Code);
			//最后把 unicode 转为 ascii
			strRet = WideByte2Acsi(wstr);
			return strRet;
		}
	
		WString Converter::Acsi2WideByte(const AString& strascii){
			int widesize = MultiByteToWideChar (CP_ACP, 0, (char*)strascii.c_str(), -1, NULL, 0);
			if (widesize == ERROR_NO_UNICODE_TRANSLATION)	{
				throw std::exception("Invalid UTF-8 sequence.");
			}
			if (widesize == 0)	{
				throw std::exception("Error in conversion.");
			}
				std::vector<wchar_t> resultstring(widesize);
			int convresult = MultiByteToWideChar (CP_ACP, 0, (char*)strascii.c_str(), -1, &resultstring[0], widesize);
	
			if (convresult != widesize)	{
				throw std::exception("La falla!");
			}
	
			return WString(&resultstring[0]);
		}
	
		AString Converter::Unicode2Utf8(const WString& widestring){
			int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
			if (utf8size == 0)	{
				throw std::exception("Error in conversion.");
			}
	
			std::vector<char> resultstring(utf8size);
	
			int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);
	
			if (convresult != utf8size)	{
				throw std::exception("La falla!");
			}
	
			return AString(&resultstring[0]);
		}
		AString Converter::ASCII2UTF_8(const AString& strAsciiCode)
		{
			AString strRet("");
	
	
			//先把 ascii 转为 unicode 
			WString wstr = Acsi2WideByte(strAsciiCode);
	
			//最后把 unicode 转为 utf8
	
			strRet = Unicode2Utf8(wstr);
	
	
			return strRet;
		}

		AString Converter::ToString( U8 val ){
			AChar	str[16];	
			_itoa_s(val,str,10);
			return	str;
		}

		Air::AString Converter::ToString( U16 val ){
			AChar	str[16];	
			_ui64toa_s(val,str,16,10);
			return	str;
		}

		Air::AString Converter::ToString( U32 val ){
			AChar	str[16];	
			_ui64toa_s(val,str,16,10);
			return	str;
		}

		Air::AString Converter::ToString( U64 val ){
			AChar	str[32];	
			_ui64toa_s(val,str,32,10);
			return	str;
		}

		Air::AString Converter::ToString( S8 val ){
			AChar	str[16];	
			_itoa_s(val,str,10);
			return	str;
		}

		Air::AString Converter::ToString( S16 val ){
			AChar	str[16];	
			_itoa_s(val,str,10);
			return	str;
		}

		Air::AString Converter::ToString( S32 val ){
			AChar	str[16];	
			_itoa_s(val,str,10);
			return	str;
		}

		Air::AString Converter::ToString( S64 val ){
			AChar	str[32];	
			_i64toa_s(val,str,32,10);
			return	str;
		}

		Air::AString Converter::ToString( Real val ){
			AChar	str[16];
			_gcvt_s(str,16,val,10);
			return	str;
		}

		Air::AString Converter::ToString( double val ){
			AChar	str[16];
			_gcvt_s(str,16,val,10);
			return	str;
		}

		Air::AString Converter::ToString( U1 val ){
			if(val){
				return	"true";
			}else{
				return	"false";
			}
		}
		Air::U16 Converter::ToU16( const AString& str ){
			return	atoi(str.c_str());
		}

		Air::U32 Converter::ToU32( const AString& str ){
			return	_strtoui64(str.c_str(),NULL,10);
		}

		Air::U64 Converter::ToU64( const AString& str ){
			return	_strtoui64(str.c_str(),NULL,10);
		}

		Air::S16 Converter::ToS16( const AString& str ){
			return	atoi(str.c_str());
		}

		Air::S32 Converter::ToS32( const AString& str ){
			return	atoi(str.c_str());
		}

		Air::S64 Converter::ToS64( const AString& str ){
			return	_atoi64(str.c_str());
		}

		Air::Real Converter::ToFloat( const AString& str ){
			return	atof(str.c_str());
		}

		double Converter::ToDouble( const AString& str ){
			return	atof(str.c_str());
		}

		Air::AString Converter::ToLowerCase( const AString& str ){
			static	char coffset	=	'a'	-	'A';
			U32	uiSize	=	str.size();
			AString	s	=	str;
			while (uiSize--)
			{
				if(	s[uiSize]	>=	'A'	&&	
					s[uiSize]	<=	'Z')
				{
					s[uiSize]	+=	coffset;
				}
			}
			return	s;
		}

		void Converter::ToLowerCase( AString& str )
		{
			static	char coffset	=	'a'	-	'A';	
			U32	uiSize	=	str.size();
			while (uiSize--)
			{
				if(	str[uiSize]	>=	'A'	&&	
					str[uiSize]	<=	'Z')
				{
					str[uiSize]	+=	coffset;
				}
			}
		}

		Air::AString Converter::ToUpperCase( const AString& str ){
			static	char coffset	=	'A'-'a';	
			U32	uiSize	=	str.size();
			AString	s	=	str;
			while (uiSize--)
			{
				if(	s[uiSize]	>=	'a'	&&	
					s[uiSize]	<=	'z')
				{
					s[uiSize]	+=	coffset;
				}
			}
			return	s;
		}

		void Converter::ToUpperCase( AString& str )
		{
			static	char coffset	=	'A'-'a';
			U32	uiSize	=	str.size();
			while (uiSize--)
			{
				if(	str[uiSize]	>=	'a'	&&	
					str[uiSize]	<=	'z')
				{
					str[uiSize]	+=	26;
				}
			}
		}

		Air::U1 Converter::ToU1( const AString& str ){
			AString	s	=	ToLowerCase(str);
			if(	s	==	"true"	||
				s	==	"1"		||
				s	==	"yes"	||
				s	==	"ok")
			{
				return	true;
			}else{
				return	false;
			}
		}

		Air::U1 Converter::SplitFilePath( const AString& str, AString* strPath /*= NULL*/, AString* strFileName /*= NULL*/, AString* strExe /*= NULL*/ )
		{
			if(str.empty())
				return	false;
			U32	uiStrSize	=	str.size();
			S32	uiPoint	=	uiStrSize;
			S32	uiSlash	=	-1;


			for(S32 i=uiStrSize-1;i>-1;i--){
				if(str[i]	==	'.'	&&	uiPoint	==	uiStrSize){
					uiPoint	=	i;
				}
				if(	str[i]	==	'/'	||
					str[i]	==	'\\'){
					uiSlash	=	i;
					break;
				}
			}

			if(	uiPoint	!=	uiStrSize	&&
				strExe	!=	NULL)
			{
				if(uiPoint!=uiStrSize-1)
					*strExe	=	&str[uiPoint+1];
			}

			if(	uiSlash	!=	-1		&&
				strPath	!=	NULL)
			{
				if(uiSlash<uiStrSize){
					strPath->resize(uiSlash+1);
					memcpy(&((*strPath)[0]),&str[0],uiSlash+1);
				}else{
					*strPath	=	str;
				}
			}

			if(strFileName!=NULL){
				U32	uiFileNameSize	=	uiPoint;
				U32	uiFileNameStart	=	0;
				if(uiPoint==uiStrSize)
					uiFileNameSize--;

				if(uiSlash<uiStrSize){
					if(uiSlash!=-1){
						uiFileNameSize	-=		uiSlash+1;
						uiFileNameStart	=		uiSlash+1;
					}

					strFileName->resize(uiFileNameSize);
					memcpy(&((*strFileName)[0]),&str[uiFileNameStart],uiFileNameSize);
				}
			}
			return	true;
		}

		void Converter::ParseString( const AString& str,Float2& v )
		{
			sscanf(str.c_str(),"%f %f",&v.x,&v.y);
		}

		void Converter::ParseString( const AString& str,Float3& v )
		{
			sscanf(str.c_str(),"%f %f %f",&v.x,&v.y,&v.z);
		}

		void Converter::ParseString( const AString& str,Float4& v )
		{
			sscanf(str.c_str(),"%f %f %f %f",&v.x,&v.y,&v.z,&v.w);
		}

		void Converter::ParseString( const AString& str,float* pOut,U32 uiCount )
		{
			switch(uiCount){
			case 2:{
				sscanf(str.c_str(),"%f %f",&pOut[0],&pOut[1]);
				break;}
			case 3:{
				sscanf(str.c_str(),"%f %f %f",&pOut[0],&pOut[1],&pOut[2]);
				break;}
			case 4:{
				sscanf(str.c_str(),"%f %f %f %f",&pOut[0],&pOut[1],&pOut[2],&pOut[3]);
				break;}
			}
		}

		Air::U1 Converter::IsNumber( CAString& str )
		{
			U32 uiCount=str.size();
			for(U32 i=0;i<uiCount;i++){
				if(str[i]<'0'||str[i]>'9'){
					return false;
				}
			}
			return true;
		}

		Air::U1 Converter::IsHexNumber( CAString& str )
		{
			U32 uiCount=str.size();
			for(U32 i=0;i<uiCount;i++){
				if(	(str[i]>='0'&&str[i]<='9')	||
					(str[i]>='a'&&str[i]<='f')	||
					(str[i]>='A'&&str[i]<='F')
					)
				{
					continue;
				}
				else
				{
					return false;
				}
			}
			return true;
		}

		Air::U32 Converter::ToHex( const AString& str )
		{
			U32 uiHex=0;
			sscanf_s(str.c_str(),"%x",&uiHex);
			return uiHex;
		}

	};
};