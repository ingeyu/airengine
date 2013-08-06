#include "AirCppScriptParse.h"


namespace	Air{

	namespace	CppScript{
		Air::U1 IsNumber(const CAString& str )
		{
			U32 uiCount=str.size();
			for(U32 i=0;i<uiCount;i++){
				if(str[i]<'0'||str[i]>'9'){
					return false;
				}
			}
			return true;
		}
		Air::U1 IsHexNumber( CAString& str )
		{
			U32 i=0;
			if(str.size()>2){
				if(str[0]=='0'){
					if(str[1]=='x'	||	str[1]=='X'){
						i=2;
					}
				}
			}
			U32 uiCount=str.size();
			for(;i<uiCount;i++){
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

		Air::U32 ToHex( const AString& str )
		{
			if(str.empty())
				return 0;
			U32 i=0;
			if(str.size()>2){
				if(str[0]=='0'){
					if(str[1]=='x'	||	str[1]=='X'){
						i=2;
					}
				}
			}
			U32 uiHex=0;
			sscanf_s(&str[i],"%x",&uiHex);
			return uiHex;
		}
		Air::S32 ToS32( const AString& str ){
			return	atoi(str.c_str());
		}
		Air::Real ToFloat( const AString& str ){
			return	(Real)atof(str.c_str());
		}
		U1 StartWith( CAString& strWhole,CAString& strPart ){
			if(strWhole.empty())
				return	false;
			if(strPart.empty())
				return	true;

			int iWSize	=	strWhole.size();
			int	iPSize	=	strPart.size();

			if(	iWSize	<	iPSize)
				return	false;

			for(int i=0;i<iPSize;i++){
				if(strPart[i]	!=	strWhole[i])
					return	false;
			}

			return	true;
		}

		U1 EndWith( CAString& strWhole,CAString& strPart ){
			if(strWhole.empty())
				return	false;
			if(strPart.empty())
				return	true;

			int iWSize	=	strWhole.size();
			int	iPSize	=	strPart.size();

			if(	iWSize	<	iPSize)
				return	false;

			for(int i=0;i<iPSize;i++){
				if(	strPart[iPSize-1-i]	!=	
					strWhole[iWSize-1-i])
					return	false;
			}

			return	true;
		}
		void ToLowerCase( AString& str )
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
			if(p[*pPos]=='\''){
				U32& uiPos	=	*pPos;
				for(;;){
					str[iBegin++]	=	p[uiPos++];
					if(p[uiPos]=='\''){
						str[iBegin++]	=	p[uiPos++];
						break;
					}
				}
				return str;
			}
			
			//普通运算符
			//for(U32 i=*pPos;;i++){
			//	if(!IsWord(p[i])){
			//		*pPos	=	i;
			//		break;
			//	}
			//	if(!IsOperator(p[i])){
			//		*pPos	=	i;
			//		break;
			//	}
			//	if(IsAreaOperator(p[i])){
			//		*pPos	=	i;
			//		break;
			//	}
			//	str[iBegin]	=	p[i];
			//	iBegin++;
			//}
			U32& i=*pPos;
			if(p[i]=='/'){
				if(p[i+1]=='/'){
					i+=2;
					return "//";
				}else if(p[i+1]=='*'){
					i+=2;
					return "/*";
				}
			}
			str[0]	=	p[i++];
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
						*pPos	=	i+1;
						return;
				}
			}
		};
	
		U1 StringToWord( U8*	pData,U32	uiSize,StringVector& vecWord){
			//判断数据是否为空
			if(pData	==	NULL)
			{
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

		Air::U1 StringToWordScript( U8*	pData,U32	uiSize,StringVector& vecWord,U1 bLowerCase /*= false*/,AString* pError /*= NULL*/ ){
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
							ToLowerCase(s);
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
							ToLowerCase(s);
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

		float ParseFloat( StringVector& vecWord,U32& i )
		{
			AChar str[32];
			U32		uiLength=0;
			if(vecWord[i]	==	"-"){
				str[uiLength]=vecWord[i][0];
				i++;
				uiLength++;
			}
			if(IsNumber(vecWord[i])){
				memcpy(&str[uiLength],vecWord[i].c_str(),vecWord[i].size());
				uiLength+=vecWord[i].size();
				i++;
			}
			if(vecWord[i]	==	"."){
				str[uiLength]=vecWord[i][0];
				i++;
				uiLength++;
				if(IsNumber(vecWord[i])){
					memcpy(&str[uiLength],vecWord[i].c_str(),vecWord[i].size());
					uiLength+=vecWord[i].size();
					i++;
				}
			}
			str[uiLength]=0;
			return ToFloat(str);
		}

		Air::S32 ParseInt( StringVector& vecWord,U32& i )
		{
			if(StartWith(vecWord[i],"0x")){
				if(IsHexNumber(&vecWord[i][2]))
				{
					return ToHex(&vecWord[i++][2]);
				}
			}else	if(IsHexNumber(vecWord[i]))
			{
				return ToHex(vecWord[i++]);
			}

			AChar str[32];
			U32		uiLength=0;
			if(vecWord[i]	==	"-"){
				str[uiLength]=vecWord[i][0];
				i++;
				uiLength++;
			}
			if(IsNumber(vecWord[i])){
				memcpy(&str[uiLength],vecWord[i].c_str(),vecWord[i].size());
				uiLength+=vecWord[i].size();
				i++;
				return ToS32(str);
			}else{
				return 0;
			}
		}

		Air::U1 IsFloatEnd( const AString& str )
		{
			if(str.empty())
				return false;
			U32 uiSize = str.size();
			if(str[uiSize-1]	==	'f'){
				uiSize--;
			}
			for(U32 i=0;i<uiSize-1;i++){
				if(	(str[i]<'0'||str[i]>'9'))
				{
					return false;
				}
			}
			return true;
		}


	}
};
