#include "AirCppScript.h"
#include <malloc.h>

namespace	Air{
	namespace	CppScript{


		void* __Alloc( U32 uiSize )
		{
			return malloc(uiSize);
		}

		void __Free( void* p )
		{
			return free(p);
		}
		void ToLower(wchar_t* str){
			int iLen=wcslen(str);

			static int iOffset = (L'A')-(L'a');
			for(int i=0;i<iLen;i++){
				if(str[i]>=(L'A') && str[i]<=(L'Z')){
					str[i]-=iOffset;
				}
			}
		}
		void ToLower(char* str){
			int iLen=strlen(str);

			static int iOffset = ('A')-('a');
			for(int i=0;i<iLen;i++){
				if(str[i]>=('A') && str[i]<=('Z')){
					str[i]-=iOffset;
				}
			}
		}

		bool SplitFilePath( const std::wstring& str, std::wstring* strPath /*= NULL*/, std::wstring* strFileName /*= NULL*/, std::wstring* strExe /*= NULL*/ )
		{
			if(str.empty())
				return	false;
			U32	uiStrSize	=	str.size();
			U32	uiPoint	=	uiStrSize;
			U32	uiSlash	=	0xffffffff;


			for(U32 i=uiStrSize-1;i>-1;i--){
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

			if(	uiSlash	!=	0xffffffff		&&
				strPath	!=	NULL)
			{
				if(uiSlash<uiStrSize){
					strPath->resize(uiSlash+1);
					memcpy(&((*strPath)[0]),&str[0],(uiSlash+1)*sizeof(wchar_t));
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
					if(uiSlash!=0xffffffff){
						uiFileNameSize	-=		uiSlash+1;
						uiFileNameStart	=		uiSlash+1;
					}

					strFileName->resize(uiFileNameSize);
					memcpy(&((*strFileName)[0]),&str[uiFileNameStart],uiFileNameSize*sizeof(wchar_t));
				}
			}
			return	true;
		}

	}

}