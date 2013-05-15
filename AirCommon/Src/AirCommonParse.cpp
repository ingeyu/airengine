#include "AirCommonParse.h"
#include "AirCommonConverter.h"
#include "AirCommonString.h"
namespace Air{
	
	namespace	Common{
		bool	IsWord(char	c){
			if(c	==	0x20	||
				c	==	0x09	||
				c	==	0x0d	||
				c	==	0x0a)
			{
				return	false;
			}else
				return	true;
		};
	
		bool	IsAreaOperator(char	c){
			switch(c){
					case	'(':
					case	')':
					case	'[':
					case	']':
					case	'{':
					case	'}':{
						return	true;
								}
					default:
						return	false;
			}
		}
	
		bool	IsOperator(char c){
			switch(c){
					case	'+':
					case	'-':
					case	'*':
					case	'/':
					case	'%':
					case	'=':
					case	'!':
					case	'&':
					case	'|':
					case	'>':
					case	'<':
					case	'\\':
					case	':':
					case	';':
					case	'"':
					case	'\'':
					case	'(':
					case	')':
					case	'[':
					case	']':
					case	'{':
					case	'}':
					case	'.':
					case	',':
					case	'?':
					case	'#':{
						return	true;
								}
					default:
						return	false;
			}
		};
	
		AString	MakeOperator(char*	p,U32* pPos){
			char	str[128];
			memset(str,0,128);
			int		iBegin	=	0;
			//判断是否为区域操作符
			bool	bAreaOperator	=	IsAreaOperator(p[*pPos]);
			if(bAreaOperator){
				str[0]	=	p[*pPos];
				*pPos	=	(*pPos)	+	1;
				return	str;
			}
	
			//判断是否为字符串
			if(p[*pPos]=='"'){
				str[iBegin]	=	p[*pPos];
				iBegin++;
				for(U32 i=1+(*pPos);;i++){
// 					if(p[i]=='\\'){
// 						i++;
// 					}else	
					if(p[i]=='"'){
						str[iBegin]	=	p[i];
						iBegin++;
						*pPos	=	i+1;
						return	str;
					}
					str[iBegin]	=	p[i];
					iBegin++;
				}
			}
			//普通运算符
			for(U32 i=*pPos;;i++){
				if(!IsWord(p[i])){
					*pPos	=	i;
					break;
				}
				if(!IsOperator(p[i])){
					*pPos	=	i;
					break;
				}
				if(IsAreaOperator(p[i])){
					*pPos	=	i;
					break;
				}
				str[iBegin]	=	p[i];
				iBegin++;
			}
	
			return	str;
	
		};
	
		AString	MakeWord(char*	p,U32* pPos){
			char	str[128];
			memset(str,0,128);
			int		iBegin	=	0;
			for(U32 i=*pPos;;i++){
				if(!IsWord(p[i])){
					*pPos	=	i;
					break;
				}
				if(IsOperator(p[i])){
					*pPos	=	i;
					break;
				}
				str[iBegin]	=	p[i];
				iBegin++;
			}
	
			return	str;
		};
	
		void	SkipToNextLine(char*	p,U32*	pPos){
			for(U32 i=*pPos;;i++){
				if(p[i]	==	0x0a){
					*pPos	=	i;
					return;
				}
			}
		}
	
		void	SkipComment(char*	p,U32*	pPos){
			for(U32 i=*pPos;;i++){
				if(	p[i]	==	'/'	&&
					p[i-1]	==	'*'){
						*pPos	=	i;
						return;
				}
			}
		}
	
		U1 Parse::StringToWord( U8*	pData,U32	uiSize,StringVector& vecWord,U1	bLowerCase	/*=	false*/,AString* pError /*= NULL*/ ){
			//判断数据是否为空
			if(pData	==	NULL)
			{
				if(pError!=NULL){
					*pError	=	"Empty	Data\n";
				}
				return	false;
			}
			AChar*	p	=	(AChar*)pData;//->GetBuff();
			U32	iSize	=	uiSize;//pData->GetSize();
	
			std::list<AString>	lst;
	
			U32	iNumWord	=	0;
	
			for(U32 i=0;i<iSize;){
				//判断是否为一个词
				if(IsWord(p[i])){
					//判断是否为运算符
					if(!IsOperator(p[i])){
						//取出这个词
						lst.push_back(MakeWord(p,&i));
					}else{
						//取出操作符
						AString	strTemp	=	MakeOperator(p,&i);
						//判断是否为注释行
						if(strTemp	==	"//"){
							SkipToNextLine(p,&i);
							continue;
						}else	if(strTemp	==	"/*"){
							SkipComment(p,&i);
							continue;
						}else
							lst.push_back(strTemp);
					}
					//递增
					iNumWord++;
				}else{
					i++;
					continue;
				}
			}
	
			vecWord.resize(iNumWord);
			std::list<AString>::iterator	itr	=	lst.begin();
			for(U32 i=0;i<iNumWord;i++,itr++){
				vecWord[i]	=	(AString)(*itr);
				if(bLowerCase){
					if(vecWord[i][0]!='"')
						Converter::ToLowerCase(vecWord[i]);
				}
			}
	
	
			return	true;
		}


		bool	IsWord2(char	c){
			if(c	==	0x20	||
				c	==	0x09	||
				c	==	0x0d	||
				c	==	0x0a	||
				c	==	'('		||
				c	==	')'		||
				c	==	'['		||
				c	==	']'		||
				c	==	'{'		||
				c	==	'}')
			{
				return	false;
			}else
				return	true;
		};

		Air::U1 Parse::StringToWordScript( U8*	pData,U32	uiSize,StringVector& vecWord,U1 bLowerCase /*= false*/,AString* pError /*= NULL*/ ){
			//判断数据是否为空
			if(pData	==	NULL)
			{
				if(pError!=NULL){
					*pError	=	"Empty	Data\n";
				}
				return	false;
			}
			AChar*	p		=	(AChar*)pData;//->GetBuff();
			U32	iSize		=	uiSize;//pData->GetSize();
			U32	uiBegin		=	0;

			for(U32	i=0;;i++){
				if(i>=iSize){
					if(i	-	uiBegin	>	0){
						AString	s;
						U32	uiStrSize	=	i	-	uiBegin;
						s.resize(uiStrSize);
						memcpy(&s[0],&p[uiBegin],uiStrSize);
						if(bLowerCase	&&	s[0]	!=	'\"'){
							Common::Converter::ToLowerCase(s);
						}
						vecWord.push_back(s);
					}
					break;
				}
				if(IsWord2(p[i])){
					continue;
				}else{
					if(i	-	uiBegin	>	0){
						AString	s;
						U32	uiStrSize	=	i	-	uiBegin;
						s.resize(uiStrSize);
						memcpy(&s[0],&p[uiBegin],uiStrSize);
						if(bLowerCase	&&	s[0]	!=	'\"'){
							Common::Converter::ToLowerCase(s);
						}
						vecWord.push_back(s);
						uiBegin	=	i+1;
					}else{
						uiBegin =	i+1;
					}
				}
			}

			return	true;
		}

		float Parse::ParseFloat( StringVector& vecWord,U32& i )
		{
			AChar str[32];
			U32		uiLength=0;
			if(vecWord[i]	==	"-"){
				str[uiLength]=vecWord[i][0];
				i++;
				uiLength++;
			}
			if(Common::Converter::IsNumber(vecWord[i])){
				memcpy(&str[uiLength],vecWord[i].c_str(),vecWord[i].size());
				uiLength+=vecWord[i].size();
				i++;
			}
			if(vecWord[i]	==	"."){
				str[uiLength]=vecWord[i][0];
				i++;
				uiLength++;
				if(Common::Converter::IsNumber(vecWord[i])){
					memcpy(&str[uiLength],vecWord[i].c_str(),vecWord[i].size());
					uiLength+=vecWord[i].size();
					i++;
				}
			}
			str[uiLength]=0;
			return Converter::ToFloat(str);
		}

		Air::S32 Parse::ParseInt( StringVector& vecWord,U32& i )
		{
			if(Common::StartWith(vecWord[i],"0x")){
				if(Common::Converter::IsHexNumber(&vecWord[i][2]))
				{
					return Common::Converter::ToHex(&vecWord[i++][2]);
				}
			}else	if(Common::Converter::IsHexNumber(vecWord[i]))
			{
				return Common::Converter::ToHex(vecWord[i++]);
			}

			AChar str[32];
			U32		uiLength=0;
			if(vecWord[i]	==	"-"){
				str[uiLength]=vecWord[i][0];
				i++;
				uiLength++;
			}
			if(Common::Converter::IsNumber(vecWord[i])){
				memcpy(&str[uiLength],vecWord[i].c_str(),vecWord[i].size());
				uiLength+=vecWord[i].size();
				i++;
				return Common::Converter::ToS32(str);
			}else{
				return 0;
			}
		}

	}
};